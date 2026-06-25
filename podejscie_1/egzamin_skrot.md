# C++ Egzamin — ściągawka (krótka wersja)

---

## 1. Kiedy KONIECZNY jest `dynamic_cast`?

Gdy masz `Base*` i chcesz wywołać metodę **istniejącą tylko w klasie pochodnej** (niedostępną przez polimorfizm). `static_cast` skompiluje się ale da UB jeśli typ jest zły — `dynamic_cast` zwraca `nullptr` bezpiecznie.

```cpp
if (Ptak* p = dynamic_cast<Ptak*>(zwierze_ptr))
    p->lec();  // lec() nie ma w klasie bazowej
```

---

## 2. Operatory tylko jako metody (nie globalne)

`=`, `[]`, `()`, `->`, `->*`, konwersja `operator T()`

**Powody:**
- `=` — kompilator zawsze generuje domyślny jako metodę → globalny tworzyłby niejednoznaczność
- `[]` — potrzebuje dostępu do prywatnych pól + musi rozróżniać wersje `const`/nie-`const`
- `()` — musi mieć dostęp do stanu obiektu (funktor)
- `->` — rekurencyjnie stosowany przez kompilator, musi być powiązany z obiektem

`<<`, `+` itp. **mogą** być globalne bo lewy operand (`ostream`) nie jest naszą klasą.

---

## 3. Dlaczego funktor a nie funkcja?

Funktor = klasa z `operator()`. Kluczowa zaleta: **przechowuje stan**.

```cpp
struct Dodaj { int n; int operator()(int x) const { return x + n; } };
// Dodaj{5} zapamiętuje n=5 między wywołaniami
```

- Funkcja globalna: brak stanu (lub brzydki `static`)
- Funktor: stan w polach, konstruktor ustawia kontekst
- Lambda = cukier syntaktyczny nad funktorem (kompilator generuje klasę z `operator()`)
- Bonus: kompilator łatwiej inlinuje funktor niż wskaźnik do funkcji

---

## 4. `operator new`/`delete` nie jest dziedziczony (poprawnie)

Technicznie jest widoczny, ale jest **niebezpieczny** gdy bazowa implementacja ignoruje parametr `size`:

```cpp
void* operator new(std::size_t) {         // BUG: ignoruje size
    return std::malloc(sizeof(Base));      // Derived dostanie za mało pamięci!
}
void* operator new(std::size_t size) {    // OK: respektuje size
    return std::malloc(size);
}
```

Kompilator przekazuje `size = sizeof(rzeczywistej klasy)` — jeśli implementacja zakłada stały rozmiar, klasa pochodna dostanie **za mało pamięci → UB**. Każda klasa powinna definiować własny `operator new`.

---

## 5. Klasa vs instancja — gdzie w pamięci?

**Klasa** = definicja typu, nie zajmuje RAM (poza segmentem `.text` dla kodu metod)  
**Instancja** = konkretny kawałek pamięci z danymi

| Tworzenie | Gdzie |
|---|---|
| `T x;` lokalna | stos |
| `new T` | sterta |
| `static T x;` / globalna | segment danych |

**Metody:** przechowywane **raz** w `.text` dla całej klasy — nie w każdym obiekcie! Kompilator przekształca `p.metoda()` → `Klasa::metoda(&p)` (`this` = ukryty parametr).

**`vptr`** (dla klas z `virtual`): jeden na **obiekt**, wskazuje na **`vtable`** (jedna na **klasę**, w segmencie danych).

---

## 6. Dlaczego standard nie definiuje implementacji metod wirtualnych?

Standard definiuje tylko **zachowanie** (semantykę) — nie mówi że musi być vtable.

**Po co ta swoboda:**
1. **ABI** — różne kompilatory (g++, MSVC, clang) mogą implementować różnie → brak stabilnego ABI między nimi
2. **Optymalizacje** — kompilator może devirtualizować (zamienić na wczesne wiązanie) gdy zna typ
3. **Egzotyczne platformy** — embedded może unikać vtable
4. **Granica C/C++** — layout vtable nieokreślony → nie można przekazywać obiektów z `virtual` do kodu C

---

## 7. Wczesne i późne wiązanie

**Wczesne** (static dispatch): decyzja w czasie **kompilacji** — metody nie-wirtualne, wywołania bezpośrednie  
**Późne** (dynamic dispatch): decyzja w **runtime** — przez vtable, tylko dla `virtual`

Mechanizm vtable: obiekt ma ukryty `vptr` → wskazuje na vtable klasy → wywołanie idzie przez `vptr[i]()`.

### PUŁAPKA: konstruktor i destruktor

W konstruktorze/destruktorze wywołania wirtualne używają **wczesnego wiązania**:
```cpp
Base() { print(); }  // woła Base::print, NIE Derived::print!
```
Bo w konstruktorze `Base` obiekt `Derived` jeszcze nie istnieje — `vptr` wskazuje na `vtable Base`. Dopiero po zakończeniu `Base()` ustawiany jest `vptr Derived`.  
Kolejność: `Base()→vptr=Base → Derived()→vptr=Derived`  
Destrukcja odwrotna: `~Derived()→vptr wraca do Base → ~Base()`

---

## 8. Definicja czystej wirtualnej poza ciałem klasy

```cpp
virtual void f() = 0;        // deklaracja w klasie — OK
virtual void f() = 0 { }     // BŁĄD SKŁADNI — niedozwolone!

void Klasa::f() { }          // definicja na zewnątrz — OK
```

**Dlaczego?** Definicja w ciele klasy sugeruje `inline`. Ale `virtual` potrzebuje stałego adresu w vtable — `inline` może ten adres eliminować. To sprzeczność. Zewnętrzna definicja jasno mówi: *"ta funkcja ma adres w .text"*.

Użycie: klasy pochodne mogą jawnie wywołać `Baza::f()` jako domyślną implementację.

---

## 9. Destruktor musi być wirtualny

```cpp
Base* p = new Derived;
delete p;  // bez virtual ~Base(): wywołuje tylko ~Base() → wyciek Derived!
           // z virtual ~Base():   wywołuje ~Derived(), potem ~Base() → OK
```

**Reguła:** jeśli klasa ma **jakąkolwiek metodę wirtualną** → destruktor musi być wirtualny.  
`virtual ~Base() = default;` wystarczy.

Wyjątki: klasa `final`, nigdy nie używana przez `Base*`, lub `shared_ptr` z własnym deleterem.

---

## 10. Gdzie MUSIMY użyć `dynamic_cast`?

1. **Metoda tylko w pochodnej** — `Base*` nie ma jej w interfejsie → `dynamic_cast<Derived*>`
2. **Downcast bez pewności** — nie wiesz czy `Base*` wskazuje na `Derived` → bezpieczne sprawdzenie
3. **Cross-cast** przy wielokrotnym dziedziczeniu:
   ```cpp
   class C : public A, public B {};
   A* a = new C;
   B* b = dynamic_cast<B*>(a);  // static_cast tu nie zadziała!
   ```
4. **Sprawdzenie typu** w runtime (zamiast `typeid`)

Częste `dynamic_cast` = **code smell** → sugeruje zły projekt hierarchii.

---

## 11. `vector` używa alokatora zamiast `new`/`delete`

Problem z `new T[n]`:
- Wywołuje **domyślny konstruktor** dla KAŻDEGO elementu — nawet nieużywanych rezerwowych slotów
- Wymaga domyślnego konstruktora (niektóre typy go nie mają)
- `delete[]` wywołuje destruktor dla wszystkich — nawet "pustych"

**Alokator rozdziela:**
1. `alloc.allocate(n)` → tylko `malloc()`, **zero konstruktorów**
2. `std::allocator_traits::construct(...)` → **placement new** w konkretnym miejscu
3. `::destroy(...)` → wywołuje destruktor **bez** `free()`
4. `alloc.deallocate(...)` → tylko `free()`

**Dodatkowe zalety:** własne pule pamięci, alokatory debugujące, strategia wzrostu bez marnotrawienia konstrukcji.

---

## 12. `swap` z semantyką przenoszenia

```cpp
// C++03 — 3x głęboka kopia: O(n)
template<typename T> void swap(T& a, T& b) { T t=a; a=b; b=t; }

// C++11 — 3x przeniesienie: O(1)
template<typename T> void swap(T& a, T& b) noexcept {
    T t = std::move(a);   // kradnie wskaźnik z a, a._ptr = nullptr
    a = std::move(b);     // kradnie z b
    b = std::move(t);     // kradnie z t
}
```

Dla `string` z milionem znaków: zamiast kopiować znaki — **zamieniamy wskaźniki**, O(1).  
Wymaga: konstruktora przenoszącego i przenoszącego `operator=` w `T`.

Idiom **copy-and-swap**: `friend void swap(A&, A&) noexcept { using std::swap; swap(a._ptr, b._ptr); }` — najszybszy bo zamienia surowe pola.

---

## 13. Częściowa specjalizacja szablonu

Pełna: wszystkie parametry konkretne (`template<> class Foo<int>`)  
Częściowa: tylko część/wzorzec (`template<typename T> class Foo<T*>`)

```cpp
template<typename T> class B { T _b; };        // ogólny
template<typename T> class B<T*> {             // dla KAŻDEGO wskaźnika
    T* _b;
    ~B() { delete _b; }      // różna semantyka!
    T get() { return *_b; }  // value_type = T, nie T*
};
```

Z `14.cpp`: `B<int>` przechowuje `int` (bez delete), `B<int*>` przechowuje `int*` (z delete).  
Kompilator wybiera **najbardziej wyspecjalizowany** pasujący szablon.

---

## 14. Różna ilość pamięci dla listy w zależności od typu

Węzeł listy: `struct Node { T data; Node* next; };`  
`sizeof(Node<T>)` = `sizeof(T)` + `sizeof(Node*)` — **rośnie z T**.

Różne typy → różna semantyka:
- `T` wartość: kopiowana do węzła, brak delete
- `T*` wskaźnik: węzeł trzyma 8B wskaźnik + odpowiada za `delete` (specjalizacja)

Typy bez domyślnego konstruktora: `new Node<NoDef>{}` nie zadziała → trzeba **placement new** po oddzielnej alokacji.

Optymalizacja (thin template): `List<T*>` dziedziczy po `List<void*>` — jedna implementacja dla wszystkich wskaźników, tylko rzutowanie na zewnątrz.

---

## 15. Template template parameters

Normalny: `typename T` (typ) lub `int N` (wartość)  
Template template: przekazujesz **szablon** (przepis), nie gotowy typ

```cpp
// BEZ — trzeba pisać T dwa razy, można pomylić typy:
template<typename T, typename Storage>   // np. Storage = deque<int>
class Fifo { Storage s; };
Fifo<int, deque<int>> f;  // int dwa razy, można napisać Fifo<double, deque<int>> — BUG

// Z template template — T tylko raz, kompilator sam instancjonuje:
template<typename T = int, template<typename...> class Storage = std::deque>
class fifo { Storage<T> _s; };  // Storage<T> = deque<int> automatycznie

fifo<> f1;                      // deque<int>
fifo<double, std::vector> f2;   // vector<double>
// fifo<double, deque<int>> — BŁĄD: deque<int> to typ, nie szablon
```

`typename storage_type::const_iterator` — słowo `typename` konieczne bo kompilator nie wie czy to typ czy wartość statyczna.
