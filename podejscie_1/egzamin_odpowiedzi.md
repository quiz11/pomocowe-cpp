# Odpowiedzi na pytania egzaminacyjne — C++ zaawansowany

> Opracowane na podstawie plików `1.cpp`–`20.cpp`, `notatki_cpp.md`, `zaawansowane_cpp.md`  
> oraz wiedzy z zakresu standardu C++11/14/17.

---

## Spis treści

1. [Przykład kodu gdzie konieczne jest użycie `dynamic_cast`](#1-przykład-kodu-gdzie-konieczne-jest-użycie-dynamic_cast)
2. [Dlaczego część operatorów można przeładować tylko jako metody](#2-dlaczego-część-operatorów-można-przeładować-tylko-jako-metody-a-nie-jako-funkcje-globalne)
3. [Dlaczego korzystamy z funktora](#3-dlaczego-korzystamy-z-funktora)
4. [Przeładowany `operator new` i `delete` nie jest dziedziczony](#4-przeładowany-operator-new-i-delete-nie-jest-dziedziczony)
5. [Czym jest klasa, czym jest instancja klasy — pamięć i metody](#5-czym-jest-klasa-czym-jest-instancja-klasy--gdzie-są-w-pamięci-i-gdzie-są-metody)
6. [Dlaczego standard nie definiuje implementacji metod wirtualnych](#6-dlaczego-to-jest-istotne-że-standard-nie-definiuje-jak-mają-być-zaimplementowane-metody-wirtualne)
7. [Wczesne i późne wiązanie — konstruktor i destruktor](#7-wczesne-i-późne-wiązanie--co-to-jest-kiedy-zachodzi-jak-działa-konstruktor-i-destruktor)
8. [Definicja czystej metody wirtualnej poza ciałem klasy](#8-dlaczego-definicja-czystej-metody-wirtualnej-musi-się-znajdować-poza-ciałem-klasy)
9. [Destruktor musi być wirtualny przy funkcjach wirtualnych](#9-dlaczego-przy-funkcjach-wirtualnych-destruktor-musi-być-wirtualny)
10. [Gdzie musimy użyć `dynamic_cast`](#10-gdzie-musimy-użyć-operatora-dynamic_cast)
11. [Dlaczego `vector` korzysta z alokatora zamiast `new`/`delete`](#11-dlaczego-vector-korzysta-z-alokatora-zamiast-new-i-delete)
12. [Szablon `swap` z semantyką przenoszenia](#12-szablon-swap-z-semantyką-przenoszenia)
13. [Częściowa specjalizacja szablonu](#13-częściowa-specjalizacja-szablonu)
14. [Różna ilość pamięci dla listy w zależności od typu](#14-czemu-czasami-trzeba-zaalokować-inną-ilość-pamięci-dla-listy-w-zależności-od-typu)
15. [Szablonowe parametry szablonów](#15-szablonowe-parametry-szablonów-template-template-parameters)

---

## 1. Przykład kodu gdzie konieczne jest użycie `dynamic_cast`

### Czym jest `dynamic_cast`?

`dynamic_cast` to rzutowanie **wykonywane w czasie działania programu** (ang. *runtime*). Sprawdza, czy wskaźnik lub referencja do klasy bazowej faktycznie wskazuje na obiekt **danej klasy pochodnej**. Działa tylko z klasami posiadającymi co najmniej jedną **metodę wirtualną** (bo do działania potrzebuje vtable / RTTI — ang. *Run-Time Type Information*).

### Kiedy jest KONIECZNY?

`dynamic_cast` jest niezbędny gdy:
- Masz wskaźnik do **klasy bazowej** (`Base*`)
- Chcesz wywołać metodę lub uzyskać dostęp do składowej istniejącej **tylko w klasie pochodnej** (niedostępnej przez polimorfizm)
- Nie wiesz statycznie (w czasie kompilacji) jakiego dokładnie typu jest obiekt

### Przykład — konieczne użycie `dynamic_cast`

```cpp
#include <iostream>
#include <vector>

class Zwierze {
public:
    virtual void oddychaj() const {
        std::cout << "Zwierze oddycha\n";
    }
    virtual ~Zwierze() = default;
};

class Ptak : public Zwierze {
public:
    void lec() const {  // metoda TYLKO w Ptak — nie ma jej w Zwierze!
        std::cout << "Ptak leci\n";
    }
    void oddychaj() const override {
        std::cout << "Ptak oddycha plucami\n";
    }
};

class Ryba : public Zwierze {
public:
    void plyw() const { // metoda TYLKO w Ryba
        std::cout << "Ryba plywa\n";
    }
    void oddychaj() const override {
        std::cout << "Ryba oddycha skrzelami\n";
    }
};

int main() {
    std::vector<Zwierze*> zoo = {new Ptak, new Ryba, new Ptak};

    for (Zwierze* z : zoo) {
        z->oddychaj();  // OK — polimorfizm, bez dynamic_cast

        // Chcemy wywołać lec() — ale to metoda TYLKO Ptaka.
        // static_cast<Ptak*>(z)->lec();  // NIEBEZPIECZNE — UB gdy z jest Rybą!

        // dynamic_cast sprawdza w runtime czy z wskazuje na Ptaka:
        if (Ptak* p = dynamic_cast<Ptak*>(z)) {
            p->lec();  // bezpieczne — wiemy że to Ptak
        } else {
            std::cout << "(to nie jest Ptak, nie lata)\n";
        }
    }

    for (Zwierze* z : zoo) delete z;
}
```

**Output:**
```
Ptak oddycha plucami
Ptak leci
Ryba oddycha skrzelami
(to nie jest Ptak, nie lata)
Ptak oddycha plucami
Ptak leci
```

### Dlaczego `static_cast` tu nie wystarczy?

`static_cast<Ptak*>(z)` skompiluje się bez błędu, ale jeśli `z` wskazuje na `Ryba`, to mamy **niezdefiniowane zachowanie** (ang. *Undefined Behavior*). `dynamic_cast` zwraca `nullptr` dla wskaźników lub rzuca `std::bad_cast` dla referencji gdy rzutowanie się nie powiodło — **bezpiecznie**.

### Wersja z referencją (rzuca wyjątek)

```cpp
try {
    Zwierze& z = *new Ryba;
    Ptak& p = dynamic_cast<Ptak&>(z);  // rzuca std::bad_cast — to nie Ptak!
} catch (const std::bad_cast& e) {
    std::cout << "Zly rzutowanie: " << e.what() << "\n";
}
```

---

## 2. Dlaczego część operatorów można przeładować tylko jako metody, a nie jako funkcje globalne

### Podział operatorów

W C++ operatory dzielimy na dwie grupy względem tego, **gdzie mogą być zdefiniowane**:

| Operator | Tylko jako metoda | Może być globalny |
|---|---|---|
| `=` (przypisanie) | TAK | NIE |
| `[]` (indeksowanie) | TAK | NIE |
| `()` (wywołanie) | TAK | NIE |
| `->` (dostęp do składowej) | TAK | NIE |
| `->*` (wskaźnik do składowej) | TAK | NIE |
| Konwersja `operator T()` | TAK | NIE |
| `+`, `-`, `*`, `<<`, `>>`, `==` itp. | Może | TAK |

### Dlaczego `=`, `[]`, `()`, `->` mogą być **tylko metodami**?

Standard C++ celowo zabrania definiowania tych operatorów jako funkcji globalnych (wolnych). Powód to **semantyka i bezpieczeństwo** języka:

#### `operator=` — operator przypisania

```cpp
// ZABRONIENIE globalnego:
// Zwierze& operator=(Zwierze& a, const Zwierze& b);  // BŁĄD KOMPILACJI

// Tylko jako metoda:
class MyClass {
public:
    MyClass& operator=(const MyClass& other) {  // OK
        // ...
        return *this;
    }
};
```

**Dlaczego?** Gdyby `operator=` mógł być globalny, programista mógłby zdefiniować przypisanie **między dwoma klasami bez ich modyfikacji**, co złamałoby enkapsulację. Co gorsza, kompilator **zawsze generuje domyślny `operator=` jako metodę** — gdyby globalne przeciążenie było możliwe, powstałaby **niejednoznaczność** (dwuznaczność rozstrzygania nazw). Standard mówi: przypisanie to operacja na *tym* obiekcie — musi być metodą.

#### `operator[]` — operator indeksowania

```cpp
// ZABRONIENIE globalnego:
// int& operator[](MyArray& arr, int idx);  // BŁĄD KOMPILACJI

// Tylko jako metoda:
class MyArray {
public:
    int& operator[](int idx) {      // wersja do modyfikacji
        return _data[idx];
    }
    const int& operator[](int idx) const {  // wersja tylko do odczytu
        return _data[idx];
    }
private:
    int _data[100];
};
```

**Dlaczego?** Operator `[]` z semantycznego punktu widzenia to **dostęp do wewnętrznej struktury obiektu**. Musi być metodą bo:
- Wymaga dostępu do prywatnych składowych
- Musi móc zwrócić **referencję do wewnętrznego elementu**
- Standard wymaga metody by umożliwić poprawne różnicowanie wersji `const` i nie-`const`

#### `operator()` — operator wywołania (funktor)

```cpp
// Tylko jako metoda — tworzy funktor:
class Mnoznik {
    int _factor;
public:
    Mnoznik(int f) : _factor(f) {}
    int operator()(int x) const { return x * _factor; }  // OK jako metoda
};

Mnoznik razy3(3);
std::cout << razy3(5);  // 15
```

**Dlaczego?** `operator()` to rdzeń wzorca **funktora** (obiektu wywoływalnego). Jako metoda ma dostęp do stanu obiektu (pól), co umożliwia funktorom "zapamiętywanie" kontekstu. Jako funkcja globalna nie miałby dostępu do stanu.

#### `operator->` — dostęp do składowej

```cpp
// Tylko jako metoda — implementacja smart pointera:
template<typename T>
class SmartPtr {
    T* _ptr;
public:
    T* operator->() const { return _ptr; }  // musi być metodą
    T& operator*() const { return *_ptr; }
};
```

**Dlaczego?** `operator->` jest **rekurencyjnie stosowany** przez kompilator dopóki nie zwróci surowego wskaźnika. Musi być metodą bo jego semantyka jest ściśle powiązana z obiektem, na którym jest wywoływany.

### Dlaczego `operator<<` i `operator+` MOGĄ być globalne?

```cpp
// operator<< jako globalna funkcja (najczęstszy wzorzec z 1.cpp, 4.cpp):
std::ostream& operator<<(std::ostream& s, const B& b) {
    return b.printOn(s);  // deleguje do wirtualnej metody
}
```

Bo dla nich **lewy operand** (`std::ostream`) nie jest naszą klasą — nie możemy dodać metody do `std::ostream`. Muszą być globalne lub `friend`.

---

## 3. Dlaczego korzystamy z funktora

### Czym jest funktor?

**Funktor** (ang. *functor*, też: *function object*, *callable object*) to **obiekt klasy, która przeciąża `operator()`**. Dzięki temu obiekt można wywoływać jak funkcję, ale jednocześnie może **przechowywać stan** między wywołaniami.

### Porównanie: zwykła funkcja vs funktor

```cpp
// === ZWYKŁA FUNKCJA ===
bool f2(int c) {
    return c % 2 == 0;
}

// === FUNKTOR — z pliku 9.cpp ===
template <typename T>
struct f3 {
    T _value;                           // STAN — przechowuje wartość!
    f3(T& value) : _value(value) {}

    int operator()(int element) const {
        return element + _value;        // używa stanu
    }
};

// Użycie (z 9.cpp):
int add_value{-1};
std::list<int> cl2 = {7, 6, 5, 4, 3, 2, 1};
change(begin(cl2), end(cl2), f3{add_value});  // funktor z parametrem -1
```

### Dlaczego funktor a nie zwykła funkcja?

| Cecha | Zwykła funkcja | Funktor |
|---|---|---|
| Stan między wywołaniami | Brak (lub `static` — brzydkie) | Pola klasy |
| Parametryzacja | Tylko przez argumenty | Konstruktor ustawia kontekst |
| Inline przez kompilator | Rzadko | Często (optymalizacja) |
| Polimorfizm szablonowy | Wskaźnik do funkcji — zły typ | Typ = rodzaj funktora |
| Implementacja interfejsu | Nie | Tak (np. `std::less`) |

### Przykład: funktor jako parametr szablonu

```cpp
// Szablon akceptujący DOWOLNY typ wywoływalny (funkcję, funktor, lambdę):
template <typename It, typename Fun>
void print_to_if(std::ostream& os, It start, It end, Fun f) {
    for (auto it = start; it != end; ++it) {
        if (f(*it)) {           // wywołanie jak funkcja
            os << *it << " ";
        }
    }
    os << "\n";
}

// Można przekazać:
print_to_if(std::cout, begin(cl), end(cl), f2);        // zwykła funkcja
print_to_if(std::cout, begin(cl), end(cl), f3{val});   // funktor ze stanem
print_to_if(std::cout, begin(cl), end(cl),             // lambda
    [](int x) { return x > 3; });
```

### Kluczowa zaleta: stan bez zmiennych globalnych

```cpp
// Zły sposób — zmienna globalna:
int g_threshold = 5;
bool bigger_than_global(int x) { return x > g_threshold; }

// Dobry sposób — funktor ze stanem:
struct BiggerThan {
    int threshold;
    BiggerThan(int t) : threshold(t) {}
    bool operator()(int x) const { return x > threshold; }
};

// Można tworzyć wiele niezależnych filtrów:
BiggerThan bt3(3);
BiggerThan bt7(7);
// bt3 i bt7 mają różne progi — nie interferują!
```

### Funktor vs Lambda

Lambda to **cukier syntaktyczny** nad funktorem — kompilator generuje anonimową klasę z `operator()`:

```cpp
// Lambda:
auto f = [add_value](int element) { return element + add_value; };

// Odpowiednik jako funktor (co kompilator "widzi"):
struct __lambda_xxx {
    int add_value;  // przechwycona zmienna
    int operator()(int element) const { return element + add_value; }
};
```

Funktory są preferowane gdy:
- Potrzebujemy **nazwanego, testowalnego** obiektu
- Funktor jest **złożony** (wiele metod, duży stan)
- Chcemy **dziedziczyć** po funktorze lub implementować interfejs

---

## 4. Przeładowany `operator new` i `delete` nie jest dziedziczony

### Problem

Choć `operator new` i `operator delete` są widoczne w hierarchii dziedziczenia, ich semantyka sprawia że **nie mogą być poprawnie "odziedziczone"** bez ryzyka błędów.

Jeśli klasa pochodna **nie definiuje własnego** `operator new`, to zostanie użyty `operator new` **z klasy bazowej** — który może alokować złą ilość pamięci.

### Przykład problemu

```cpp
#include <iostream>
#include <cstdlib>

class Base {
public:
    int _x;

    // Własny operator new — zakładający stały rozmiar zamiast używać parametru
    void* operator new(std::size_t size) {
        std::cout << "Base::operator new, size=" << size << "\n";
        return std::malloc(size);
    }

    void operator delete(void* ptr) {
        std::cout << "Base::operator delete\n";
        std::free(ptr);
    }

    virtual ~Base() = default;
};

class Derived : public Base {
public:
    int _y;
    int _z;
    double _d;
    // Derived NIE definiuje własnego operator new!
    // sizeof(Derived) > sizeof(Base) !!!
};

int main() {
    // Wywołany zostanie Base::operator new z size=sizeof(Derived)
    // Ale jeśli implementacja zakłada stały rozmiar — alokuje za mało!
    Derived* d = new Derived;
    delete d;
}
```

### Dlaczego to jest problem?

**Parametr `size`** w `operator new(std::size_t size)` jest ustawiany przez kompilator na `sizeof(TworzonejKlasy)`. Jeśli programista napisał `operator new` dla klasy bazowej **ignorując** parametr i alokując tylko `sizeof(Base)`:

```cpp
// BŁĘDNA implementacja — ignoruje size:
void* operator new(std::size_t) {
    return std::malloc(sizeof(Base));  // ZAWSZE tylko sizeof(Base)!
    // Derived dostanie za mało pamięci -> UB!
}

// PRAWIDŁOWA implementacja:
void* operator new(std::size_t size) {
    return std::malloc(size);  // size to sizeof rzeczywistej klasy
}
```

### Rozwiązanie: każda klasa definiuje własny `operator new`

```cpp
class Derived : public Base {
public:
    int _y, _z;
    double _d;

    // Własny operator new — gwarantuje poprawną alokację dla Derived
    void* operator new(std::size_t size) {
        std::cout << "Derived::operator new, size=" << size << "\n";
        return std::malloc(size);
    }

    void operator delete(void* ptr) {
        std::free(ptr);
    }
};
```

### Podsumowanie

- `operator new` / `operator delete` są technicznie *widoczne* przez dziedziczenie
- Ale jeśli bazowa implementacja zakłada stały rozmiar — dziedziczenie jest **niebezpieczne**
- Standard wymaga by parametr `size` był zawsze poprawnie ustawiony przez kompilator
- Dobra praktyka: klasy zarządzające pamięcią definiują własny `operator new`

---

## 5. Czym jest klasa, czym jest instancja klasy — gdzie są w pamięci i gdzie są metody

### Klasa

**Klasa** to **typ danych** zdefiniowany przez programistę — jest to opis/szablon/przepis mówiący:
- Jakie **pola** (dane) będzie miał obiekt i jakiego są typu
- Jakie **metody** (operacje) można na nim wykonywać
- Jakie są prawa dostępu (`private`, `protected`, `public`)

Klasa **nie zajmuje pamięci w trakcie działania programu** (z wyjątkiem metod, które jako kod binarny są w segmencie `.text`).

```cpp
class Punkt {        // KLASA — definicja typu, nie zajmuje RAM per se
    double x, y;
public:
    Punkt(double x, double y) : x(x), y(y) {}
    double odleglosc() const { return std::sqrt(x*x + y*y); }
};
```

### Instancja klasy (obiekt)

**Instancja klasy** (obiekt) to **konkretny egzemplarz** klasy — faktyczny kawałek pamięci zawierający dane.

```cpp
Punkt p1(3.0, 4.0);   // instancja 1 — zajmuje sizeof(Punkt) bajtów
Punkt p2(0.0, 0.0);   // instancja 2 — inny kawałek pamięci, te same metody
```

### Gdzie w pamięci jest instancja?

Zależy od sposobu tworzenia:

| Sposób tworzenia | Segment pamięci | Czas życia |
|---|---|---|
| `Punkt p(3, 4);` (lokalna) | **Stos (stack)** | Do końca bloku `{}` |
| `new Punkt(3, 4)` | **Sterta (heap)** | Do wywołania `delete` |
| `static Punkt p;` | **Segment danych** | Cały czas działania programu |
| `Punkt p;` (globalna) | **Segment danych** | Cały czas działania programu |

```
PAMIĘĆ PROCESU:
+-----------------------------------+
| Segment kodu (.text)              |  <- metody (kod binarny): Punkt::odleglosc()
+-----------------------------------+
| Segment danych (.data/.bss)       |  <- zmienne globalne, static
+-----------------------------------+
| Sterta (heap) v                   |  <- new Punkt(...)
| ...                               |
| Stos (stack) ^                    |  <- Punkt p(3, 4) -- lokalna zmienna
+-----------------------------------+
```

### Gdzie są metody?

**Metody NIE są przechowywane w każdym obiekcie osobno!**

Metody (kod binarny) są przechowywane **raz** w segmencie kodu (`.text`) — niezależnie ile istnieje instancji danej klasy. Każde wywołanie metody to skok do tego samego miejsca w kodzie.

```cpp
Punkt p1(1, 2);
Punkt p2(3, 4);

// p1.odleglosc() i p2.odleglosc() wywołują TĘ SAMĄ funkcję w .text
// Kompilator przekształca to na:
// Punkt::odleglosc(&p1)  // jawnie przekazuje this = &p1
// Punkt::odleglosc(&p2)  // jawnie przekazuje this = &p2
```

**`this` to ukryty parametr** wskazujący na konkretną instancję.

### Co zajmuje pamięć w obiekcie?

```cpp
class BezWirtualnych {
    int a;      // 4 bajty
    double b;   // 8 bajtów
    char c;     // 1 bajt (+ padding)
};
// sizeof(BezWirtualnych) = 24 bajty (z paddingiem)
// W tym ZERO bajtów na metody!

class ZWirtualnymi {
    int a;      // 4 bajty
    // + ukryty wskaźnik vptr: 8 bajtów (na 64-bit)
    virtual void f() {}
};
// sizeof(ZWirtualnymi) = 16 bajtów (4 + padding + 8 vptr)
```

### Wskaźnik `vptr` i tabela `vtable`

Obiekty klas z metodami wirtualnymi przechowują **ukryty wskaźnik `vptr`** (virtual pointer) wskazujący na **`vtable`** (virtual table) klasy:

```
OBIEKT d (typu Derived):
+-------------------------+
| vptr  ----------------> vtable dla Derived:
| pole1                   |  [0] -> Derived::printOn()
| pole2                   |  [1] -> Derived::innaMetodaWirt()
+-------------------------+
```

- `vtable` jest **jedna na klasę** (nie na obiekt!) — w segmencie danych
- `vptr` jest **jeden na obiekt** — przechowywany w każdej instancji

---

## 6. Dlaczego to jest istotne, że standard nie definiuje jak mają być zaimplementowane metody wirtualne

### Co standard mówi (a czego nie mówi)?

Standard C++ definiuje **zachowanie** (semantykę) metod wirtualnych:
- Że wywołanie przez wskaźnik/referencję do bazy wybierze implementację najbardziej pochodnej klasy
- Że obiekty klas z metodami wirtualnymi mają pewien narzut

Standard **NIE definiuje**:
- Że implementacją ma być vtable (tablica wskaźników do funkcji)
- Jak ma wyglądać `vptr`
- Jak mają być rozmieszczone wpisy w vtable
- Jak działa RTTI

### Dlaczego to jest ważne?

#### 1. Przenośność binarna (ABI — Application Binary Interface)

Różne kompilatory mogą implementować vtable różnie:
- **g++**, **clang++** — używają vtable z `vptr` na początku obiektu
- **MSVC** — używa podobnego mechanizmu, ale z różnicami przy wielokrotnym dziedziczeniu
- **Hipotetyczny kompilator** — mógłby użyć hash mapy lub B-drzewa

To dlatego **biblioteki C++ nie mają stabilnego ABI** i musisz kompilować wszystko tym samym kompilatorem.

#### 2. Wolność implementacyjna (optymalizacje)

Ponieważ standard nie narzuca implementacji, kompilatory mogą:
- **Devirtualizować** wywołania (zamienić późne wiązanie na wczesne) gdy znają typ obiektu
- Używać **inline** dla metod wirtualnych w określonych kontekstach

```cpp
// Kompilator może to zoptymalizować:
Derived d;
Base& b = d;
b.virtual_method();  // Kompilator MOŻE wiedzieć że b to Derived
                     // i wywołać Derived::virtual_method() bezpośrednio!
```

#### 3. Embedded / specjalizowane platformy

Na niektórych platformach (mikrokontrolery, DSP) vtable może być zbyt kosztowna. Implementacja bez vtable byłaby możliwa dzięki nieokreśloności standardu.

#### 4. Niezgodność ze strukturami C (`extern "C"`)

Ponieważ layout vtable jest nieokreślony, nie możemy przekazywać obiektów C++ z metodami wirtualnymi do kodu C. To ważna granica między C i C++.

### Podsumowanie

Nieokreśloność implementacji metod wirtualnych przez standard jest **celowym zabiegiem** który:
- Daje kompilatorom **wolność optymalizacji**
- Nie wymaga istnienia vtable (choć wszystkie główne kompilatory jej używają)
- Jest powodem **braku stabilnego ABI** między kompilatorami C++
- Umożliwia specjalizowane implementacje na egzotycznych platformach

---

## 7. Wczesne i późne wiązanie — co to jest, kiedy zachodzi, jak działa, konstruktor i destruktor

### Wiązanie (ang. *binding*)

**Wiązanie** to moment, w którym kompilator/runtime decyduje, **która konkretna implementacja funkcji zostanie wywołana**.

### Wczesne wiązanie (ang. *early binding* / *static dispatch*)

Decyzja podejmowana jest **w czasie kompilacji** — kompilator zna dokładnie, która funkcja zostanie wywołana.

```cpp
class Base {
public:
    void print() const { std::cout << "Base::print\n"; }  // NIE wirtualna
};

class Derived : public Base {
public:
    void print() const { std::cout << "Derived::print\n"; }
};

int main() {
    Derived d;
    Base* p = &d;

    p->print();  // WCZESNE WIĄZANIE: kompilator widzi Base*, wywołuje Base::print
                 // nawet jeśli obiekt jest Derived!
    d.print();   // WCZESNE WIĄZANIE: kompilator widzi Derived, wywołuje Derived::print
}
// Output:
// Base::print
// Derived::print
```

**Kiedy?** Gdy metoda **nie jest wirtualna** — kompilator po prostu podmienia wywołanie na adres funkcji w czasie kompilacji.

### Późne wiązanie (ang. *late binding* / *dynamic dispatch*)

Decyzja podejmowana jest **w czasie działania programu** (runtime) — przez mechanizm vtable.

```cpp
class Base {
public:
    virtual void print() const { std::cout << "Base::print\n"; }  // WIRTUALNA
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void print() const override { std::cout << "Derived::print\n"; }
};

int main() {
    Derived d;
    Base* p = &d;

    p->print();  // PÓŹNE WIĄZANIE:
                 // 1. Pobierz vptr z obiektu *p
                 // 2. Przejdź do vtable dla Derived
                 // 3. Wywołaj Derived::print
}
// Output:
// Derived::print   <- poprawna klasa pochodna!
```

### Jak działa vtable (mechanizm późnego wiązania)?

```
W czasie kompilacji — kompilator tworzy:
vtable dla Base:      [0] -> Base::print()
                      [1] -> Base::~Base()

vtable dla Derived:   [0] -> Derived::print()   <- nadpisane!
                      [1] -> Derived::~Derived()

W runtime — każdy obiekt:
[ vptr ] ------> właściwa vtable (ustawiana w konstruktorze!)
[ dane ]

Wywołanie p->print():
  1. Pobierz p->vptr
  2. vptr[0]()         <- wywołaj pierwszą metodę z vtable
  -> Derived::print()  <- bo vptr wskazuje na vtable Derived
```

### Konstruktor a wiązanie — WAŻNA PUŁAPKA!

W **konstruktorze** i **destruktorze** wywołania metod wirtualnych używają **wczesnego wiązania**!

```cpp
class Base {
public:
    Base() {
        print();  // WCZESNE WIĄZANIE w konstruktorze!
                  // Nawet jeśli tworzony jest Derived — wywoła Base::print
    }
    virtual void print() const { std::cout << "Base::print\n"; }
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    int _data = 42;
    void print() const override { std::cout << "Derived::print, _data=" << _data << "\n"; }
};

int main() {
    Derived d;
    // Output w konstruktorze: Base::print  <- NIE Derived::print!
    d.print();
    // Output po konstruktorze: Derived::print, _data=42
}
```

**Dlaczego?** Kolejność konstruowania:
1. Konstruktor `Base` uruchamia się **zanim** `Derived` jest w pełni skonstruowany
2. W tym momencie `vptr` wskazuje na `vtable Base` (jeszcze nie Derived!)
3. Wywołanie `Derived::print` byłoby niebezpieczne — `_data` może nie być jeszcze zainicjalizowane
4. Dopiero po zakończeniu `Base::Base()` kompilator ustawia `vptr` na `vtable Derived`

**Destruktor** — odwrotna kolejność, analogiczny problem:
```
Kolejność konstruowania:    Kolejność destruowania:
Base()      -> vptr = Base  ~Derived() -> vptr wraca do Base
Derived()   -> vptr = Derived ~Base() -> vptr = Base
```

---

## 8. Dlaczego definicja czystej metody wirtualnej musi się znajdować poza ciałem klasy

### Czysta metoda wirtualna — przypomnienie

```cpp
class Abstrakcyjna {
public:
    virtual void metoda() = 0;  // czysta wirtualna — DEKLARACJA
};
```

`= 0` oznacza: klasa jest abstrakcyjna, nie można tworzyć jej instancji, klasy pochodne MUSZĄ nadpisać tę metodę.

### Czy czysta wirtualna może mieć definicję?

**TAK** — czysta wirtualna metoda w C++ MOŻE mieć implementację (ciało). Ale ta implementacja **musi być zdefiniowana poza ciałem klasy**.

```cpp
class Abstrakcyjna {
public:
    virtual void metoda() = 0;  // deklaracja WEWNĄTRZ klasy
};

// DEFINICJA MUSI BYĆ NA ZEWNĄTRZ:
void Abstrakcyjna::metoda() {
    std::cout << "Domyslna implementacja czystej wirtualnej\n";
}
```

```cpp
// BŁĄD KOMPILACJI — nie można tak:
class Abstrakcyjna {
public:
    virtual void metoda() = 0 {  // BŁĄD SKŁADNI!
        std::cout << "to nie skompiluje sie\n";
    }
};
```

### Dlaczego ta zasada istnieje? — Argument z sugestią `inline`

Umieszczenie definicji wewnątrz ciała klasy w C++ sugeruje kompilatorowi, że metoda jest **kandydatem do inlinowania** (wstawienia kodu w miejscu wywołania):

```cpp
class Foo {
public:
    void zwykla() {        // implicitly inline
        std::cout << "inline?\n";
    }
};
```

**Konflikt semantyczny:**
- `inline` sugeruje: *"skompiluj tę funkcję w miejscu wywołania, nie twórz osobnego symbolu"*
- `virtual` wymaga: *"stwórz wpis w vtable z adresem tej funkcji"*

Gdyby zdefiniowanie ciała wewnątrz klasy sugerowało `inline`, a jednocześnie ta metoda jest `virtual`, powstałaby logiczna sprzeczność. `vtable` potrzebuje stałego adresu funkcji — `inline` ten adres znosi lub komplikuje. Dlatego standard zabrania umieszczania ciała czystej wirtualnej wewnątrz klasy — wymuszając definicję zewnętrzną, **jasno sygnalizuje że metoda ma konkretny adres w segmencie kodu**.

### Kiedy używa się definicji czystej wirtualnej?

Gdy chcemy dostarczyć **domyślną implementację** którą klasy pochodne mogą jawnie wywołać:

```cpp
class Baza {
public:
    virtual void rysuj() = 0;  // abstrakcyjna
};

void Baza::rysuj() {  // DEFINICJA ZEWNĄTRZ — domyślna implementacja
    std::cout << "Rysowanie podstawowe\n";
}

class Pochodna : public Baza {
public:
    void rysuj() override {
        Baza::rysuj();  // jawne wywołanie domyślnej implementacji
        std::cout << "Rysowanie zaawansowane\n";
    }
};
```

---

## 9. Dlaczego przy funkcjach wirtualnych destruktor musi być wirtualny

### Problem bez wirtualnego destruktora

```cpp
class Base {
public:
    int* _data;
    Base() : _data(new int[100]) {}
    ~Base() {             // NIE wirtualny!
        delete[] _data;
        std::cout << "~Base()\n";
    }
};

class Derived : public Base {
public:
    int* _extra;
    Derived() : _extra(new int[200]) {}
    ~Derived() {          // nigdy nie zostanie wywołany!
        delete[] _extra;
        std::cout << "~Derived()\n";
    }
};

int main() {
    Base* p = new Derived;   // polimorfizm — p wskazuje na Derived
    delete p;                // wywołuje ~Base() — NIE ~Derived()!
    // _extra NIE zostaje zwolnione -> WYCIEK PAMIĘCI!
}
// Output:
// ~Base()
// (brak ~Derived() -> wyciek _extra!)
```

### Rozwiązanie: wirtualny destruktor

```cpp
class Base {
public:
    int* _data;
    Base() : _data(new int[100]) {}
    virtual ~Base() {    // WIRTUALNY!
        delete[] _data;
        std::cout << "~Base()\n";
    }
};

class Derived : public Base {
public:
    int* _extra;
    Derived() : _extra(new int[200]) {}
    ~Derived() override {  // automatycznie wirtualny
        delete[] _extra;
        std::cout << "~Derived()\n";
    }
};

int main() {
    Base* p = new Derived;
    delete p;
    // Wywołuje ~Derived() (przez vtable), potem ~Base()
}
// Output:
// ~Derived()
// ~Base()
// Brak wycieków!
```

### Jak to działa?

`delete p` przy wirtualnym destruktorze:
1. Pobierz `vptr` z obiektu `*p`
2. Przejdź do `vtable` dla `Derived`
3. Wywołaj `Derived::~Derived()` (przez późne wiązanie)
4. Automatycznie wywołaj `Base::~Base()` (łańcuch destruktorów)

### Przykład z kodu (1.cpp)

```cpp
class B {
protected:
    B() = default;
public:
    virtual ~B() = default;  // WIRTUALNY destruktor — niezbędny!
};
```

### Zasada ogólna

> **Jeśli klasa ma jakąkolwiek metodę wirtualną — destruktor MUSI być wirtualny.**

Wyjątki (kiedy destruktor NIE musi być wirtualny):
- Klasa jest `final` i nie można po niej dziedziczyć
- Klasa jest czysto wewnętrzna i nigdy nie będzie używana przez wskaźnik do bazy
- Używamy `std::shared_ptr` z własnym deleterem (który zna prawdziwy typ)

### Dlaczego `= default` jest OK?

```cpp
virtual ~Base() = default;  // wirtualny, kompilator generuje ciało
```

`= default` nakazuje kompilatorowi wygenerować standardową implementację (która nic nie robi). To wystarczy — ważne że destruktor jest `virtual`.

---

## 10. Gdzie musimy użyć operatora `dynamic_cast`

### Odpowiedź: używamy `dynamic_cast` gdy polimorfizm nie wystarczy

Polimorfizm przez metody wirtualne pozwala wywoływać właściwe implementacje **bez znajomości dokładnego typu**. Ale istnieją sytuacje, gdzie polimorfizm nie wystarczy:

### Sytuacja 1: Dostęp do metody istniejącej tylko w klasie pochodnej

```cpp
class Pojazd {
public:
    virtual void jedz() = 0;
    virtual ~Pojazd() = default;
};

class Samolot : public Pojazd {
public:
    void jedz() override { std::cout << "Samolot jedzie\n"; }
    void lec() { std::cout << "Samolot leci!\n"; }  // TYLKO w Samolot!
};

void obsluz(Pojazd* p) {
    p->jedz();  // OK — polimorfizm

    // Chcemy wywołać lec() jeśli to samolot:
    if (Samolot* s = dynamic_cast<Samolot*>(p)) {
        s->lec();  // KONIECZNY dynamic_cast — lec() nie ma w Pojazd
    }
}
```

### Sytuacja 2: Downcast — rzutowanie w dół hierarchii

```cpp
// Mamy wskaźnik do bazy, wiemy że to Derived — ale nie możemy tego udowodnić statycznie:
Base* getObject() { return new Derived; }

int main() {
    Base* b = getObject();

    // static_cast — niebezpieczne (no check):
    // Derived* d = static_cast<Derived*>(b);

    // dynamic_cast — bezpieczne:
    Derived* d = dynamic_cast<Derived*>(b);
    if (d) {
        d->metodaTylkoWDerived();
    }
}
```

### Sytuacja 3: Rzutowanie w bok (cross-cast) przy wielokrotnym dziedziczeniu

```cpp
class A { public: virtual ~A() = default; };
class B { public: virtual ~B() = default; };
class C : public A, public B {};

A* a = new C;

// Chcemy uzyskać B* z A* — to cross-cast:
// static_cast<B*>(a);  // BŁĄD KOMPILACJI — brak relacji A->B
B* b = dynamic_cast<B*>(a);  // OK! dynamic_cast potrafi to zrobić
// b != nullptr jeśli *a to faktycznie C
```

### Sytuacja 4: Sprawdzenie typu w runtime (RTTI)

```cpp
void diagnozuj(const Base* p) {
    if (dynamic_cast<const Derived1*>(p)) {
        std::cout << "To jest Derived1\n";
    } else if (dynamic_cast<const Derived2*>(p)) {
        std::cout << "To jest Derived2\n";
    }
    // Alternatywnie przez typeid:
    // std::cout << typeid(*p).name() << "\n";
}
```

### Kiedy NIE używamy `dynamic_cast`?

- Gdy polimorfizm wystarczy — preferuj metody wirtualne
- Gdy znamy typ statycznie — użyj `static_cast`
- Częste użycie `dynamic_cast` to **zapach kodu** (*code smell*) — sugeruje zły projekt hierarchii

---

## 11. Dlaczego `vector` korzysta z alokatora zamiast `new` i `delete`

### Problem z `new` i `delete`

`std::vector` przechowuje elementy w ciągłym bloku pamięci i musi często go **realokować** (gdy dodajemy elementy). Gdyby używał `new`/`delete`:

```cpp
// HIPOTETYCZNA zła implementacja:
template<typename T>
class BadVector {
    T* _data = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;

    void push_back(const T& val) {
        if (_size == _capacity) {
            T* new_data = new T[_capacity * 2];  // PROBLEM 1: domyślnie konstruuje elementy!
            for (size_t i = 0; i < _size; i++)
                new_data[i] = _data[i];          // kopiuje
            delete[] _data;                       // PROBLEM 2: destruuje wszystkie elementy!
            _data = new_data;
        }
        _data[_size++] = val;
    }
};
```

**Problem 1:** `new T[n]` wywołuje **domyślny konstruktor** dla każdego z `n` elementów — nawet tych jeszcze nieużywanych! To marnotrawstwo i może być niemożliwe (typ bez domyślnego konstruktora).

**Problem 2:** `delete[] _data` wywołuje **destruktor** dla każdego elementu tablicy — nawet "pustych" slotów rezerwowych.

**Problem 3:** `new`/`delete` zawsze **alokują i konstruują** razem — nie można oddzielić alokacji pamięci od konstruowania obiektów.

### Rozwiązanie: alokator + placement new

`std::vector` używa dwuetapowego podejścia:

1. **Alokacja surowej pamięci** (bez konstruowania obiektów) — przez alokator
2. **Konstruowanie obiektów w tej pamięci** — przez `placement new`

```cpp
#include <memory>  // std::allocator

template<typename T, typename Allocator = std::allocator<T>>
class Vector {
    T* _data = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;
    Allocator _alloc;

    void reserve(size_t new_cap) {
        // KROK 1: Alokuj surową pamięć BEZ konstruowania:
        T* new_data = _alloc.allocate(new_cap);
        //            ^^^^^^^^^^^^^^^^^^^^^^^^
        //            tylko malloc() — żaden konstruktor nie jest wołany!

        // KROK 2: Przenieś istniejące elementy przez placement new:
        for (size_t i = 0; i < _size; i++) {
            std::allocator_traits<Allocator>::construct(
                _alloc, new_data + i, std::move(_data[i]));
        }

        // KROK 3: Zniszcz stare elementy (bez zwalniania pamięci):
        for (size_t i = 0; i < _size; i++) {
            std::allocator_traits<Allocator>::destroy(_alloc, _data + i);
        }

        // KROK 4: Zwolnij starą pamięć:
        _alloc.deallocate(_data, _capacity);

        _data = new_data;
        _capacity = new_cap;
    }
};
```

### Dlaczego alokator a nie własny `operator new`?

1. **Elastyczność** — użytkownik może dostarczyć własny alokator:
   ```cpp
   // Własny alokator z puli pamięci:
   std::vector<int, PoolAllocator<int>> v;

   // Alokator debugujący (liczy alokacje):
   std::vector<int, DebugAllocator<int>> v;
   ```

2. **Separacja alokacji od konstrukcji** — kluczowa dla wydajności:
   ```cpp
   // vector rezerwuje 100 miejsc — JEDNA alokacja
   v.reserve(100);
   // Potem dodaje po jednym — żadnych nowych alokacji, tylko placement new
   for (int i = 0; i < 50; i++) v.push_back(i);
   ```

3. **Własne pule pamięci** — dla systemów embedded lub wysokowydajnych.

4. **Strategia wzrostu** — vector może zmieniać rozmiar bez wywoływania konstruktorów na "rezerwowych" slotach.

### Placement new — fundament mechanizmu

```cpp
char buf[sizeof(MyClass)];  // surowa pamięć na stosie

// Konstruuj MyClass w tej pamięci:
MyClass* p = new (buf) MyClass(args);  // placement new!
//           ^^^^^^^^^
//           wskaźnik do pamięci — nie alokuje, tylko konstruuje!

// Jawne zniszczenie (bez free):
p->~MyClass();  // jawne wywołanie destruktora
// (NIE delete p — buf jest na stosie!)
```

---

## 12. Szablon `swap` z semantyką przenoszenia

### Dlaczego semantyka przenoszenia jest kluczowa dla `swap`?

Klasyczny `swap` bez przenoszenia:

```cpp
// Stara wersja C++03:
template<typename T>
void swap_old(T& a, T& b) {
    T temp = a;  // KOPIOWANIE — może być drogie!
    a = b;       // KOPIOWANIE
    b = temp;    // KOPIOWANIE
}
// Dla stringa z 1 milionem znaków: 3 głębokie kopie!
```

### `swap` z semantyką przenoszenia (C++11)

```cpp
template<typename T>
void swap(T& a, T& b) noexcept(
    std::is_nothrow_move_constructible_v<T> &&
    std::is_nothrow_move_assignable_v<T>
) {
    T temp = std::move(a);  // PRZENOSZENIE — tanio! (kradniemy zasoby z a)
    a = std::move(b);       // PRZENOSZENIE — tanio!
    b = std::move(temp);    // PRZENOSZENIE — tanio!
}
```

**Co się dzieje dla `std::string`:**
```
a = "bardzo dlugi string..."
b = "inny dlugi string..."

T temp = std::move(a):
  temp._ptr = a._ptr   // kradniemy wskaźnik — O(1)!
  a._ptr = nullptr     // a jest teraz pusty

a = std::move(b):
  a._ptr = b._ptr      // O(1)
  b._ptr = nullptr

b = std::move(temp):
  b._ptr = temp._ptr   // O(1)
```

Cały `swap` to **3 operacje O(1)** zamiast 3 operacji O(n)!

### Przykład własnej klasy z `swap`

```cpp
class MyString {
    char* _data;
    size_t _size;
public:
    MyString(const char* s) : _size(strlen(s)), _data(new char[_size + 1]) {
        strcpy(_data, s);
    }

    // Konstruktor przenoszący — kluczowy dla swap!
    MyString(MyString&& other) noexcept
        : _data(other._data), _size(other._size) {
        other._data = nullptr;  // kradniemy wskaźnik
        other._size = 0;
    }

    // Przenoszący operator przypisania:
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            delete[] _data;         // zwolnij swoje
            _data = other._data;    // przejmij
            _size = other._size;
            other._data = nullptr;
            other._size = 0;
        }
        return *this;
    }

    ~MyString() { delete[] _data; }
};

int main() {
    MyString a("Ala ma kota");
    MyString b("Kot ma Ale");

    // std::swap używa konstruktora i operatora przenoszącego:
    std::swap(a, b);  // 3x przeniesienie = O(1), a nie O(n)!
}
```

### Własna metoda `swap` jako `friend` (idiom copy-and-swap)

```cpp
class Resource {
    int* _data;
    size_t _size;
public:
    // Friend swap — najwydajniejszy dla danej klasy:
    friend void swap(Resource& a, Resource& b) noexcept {
        using std::swap;
        swap(a._data, b._data);   // zamiana wskaźników — O(1)
        swap(a._size, b._size);   // zamiana rozmiarów — O(1)
    }

    // Operator przypisania z idiomem copy-and-swap:
    Resource& operator=(Resource other) {  // kopiuje lub przenosi argument
        swap(*this, other);                // zamienia z tymczasową kopią
        return *this;
        // 'other' jest niszczony — stare zasoby są zwolnione
    }
};
```

---

## 13. Częściowa specjalizacja szablonu

### Co to jest?

**Pełna specjalizacja** szablonu podaje konkretne typy dla WSZYSTKICH parametrów:
```cpp
template<>
class Box<int> { ... };  // specjalizacja dla dokładnie int
```

**Częściowa specjalizacja** podaje konkretny typ/wzorzec tylko dla **części parametrów**, lub nakłada ograniczenie na kształt parametru:

```cpp
template<typename T>
class Box<T*> { ... };  // specjalizacja dla DOWOLNEGO wskaźnika
```

### Przykład z kodu — `14.cpp`

```cpp
// Szablon ogólny:
template <typename T>
class B {
    T _b;
public:
    using value_type = T;
    B(T b) : _b(b) {}
    B(const B& b) : _b(b._b) {}  // kopiowanie OK
    T get() { return _b; }
};

// CZĘŚCIOWA SPECJALIZACJA — dla wskaźników T*:
template <typename T>
class B<T*> {             // <- T* zamiast T
    T* _b;
public:
    using value_type = T;  // value_type to T, nie T*!

    B(T* b) : _b(b) {}

    T get() { return *_b; }  // dereferencja — zwraca T, nie T*!

    ~B() { delete _b; }      // zarządza pamięcią!

    B(const B&) = delete;    // zakaz kopiowania (własność wskaźnika)
    B(const B&&) = delete;
};

// Użycie:
B<int>  a(1);              // używa szablonu ogólnego
B<int*> b(new int{2});     // używa specjalizacji dla wskaźnika
```

### Więcej przykładów częściowej specjalizacji

#### Specjalizacja gdy oba parametry są takie same

```cpp
// Ogólny szablon:
template<typename T, typename U>
struct MyPair {
    T first;
    U second;
};

// Częściowa specjalizacja gdy oba typy są takie same:
template<typename T>
struct MyPair<T, T> {
    T first, second;
    T average() const { return (first + second) / 2; }  // sens tylko gdy T==U
};

MyPair<int, double> p1;    // ogólny szablon
MyPair<int, int> p2;       // specjalizacja — ma metodę average()
```

#### Specjalizacja dla tablic

```cpp
template<typename T>
class Container { /* ogólna implementacja */ };

template<typename T, size_t N>
class Container<T[N]> {  // specjalizacja dla tablic o rozmiarze N
    T _data[N];
public:
    static constexpr size_t size = N;
};
```

### Reguła rozstrzygania (który szablon wybrać?)

Kompilator wybiera **najbardziej wyspecjalizowany** pasujący szablon:

```
Hierarchia priorytetów:
1. Pełna specjalizacja (template<>)
2. Częściowa specjalizacja (template<typename T> class Foo<T*>)
3. Szablon ogólny (template<typename T> class Foo)
```

---

## 14. Czemu czasami trzeba zaalokować inną ilość pamięci dla listy w zależności od typu

### Kontekst: implementacja listy połączonej

Lista połączona przechowuje elementy w **węzłach** (ang. *nodes*). Każdy węzeł musi zawierać:
- **Dane** (element listy): `T`
- **Wskaźnik(i)** na następny/poprzedni węzeł

```cpp
// Naiwna implementacja węzła:
template<typename T>
struct Node {
    T data;        // rozmiar zależy od T!
    Node* next;    // zazwyczaj 8 bajtów (64-bit)
};
```

`sizeof(Node<T>)` zależy bezpośrednio od `sizeof(T)`:

| `T` | `sizeof(T)` | `sizeof(Node<T>)` |
|---|---|---|
| `char` | 1 | 9 (+ padding -> 16) |
| `int` | 4 | 12 (+ padding -> 16) |
| `double` | 8 | 16 |
| `std::string` | 32 | 40 |
| `MyHugeStruct` | 256 | 264 |

### Dlaczego to ważne?

#### Problem 1: `T` jest wskaźnikiem lub typem zarządzającym pamięcią

```cpp
// Częściowa specjalizacja z 14.cpp — lista przechowuje T*, nie T:
template<typename T>
class B<T*> {
    T* _b;              // 8 bajtów — wskaźnik
    ~B() { delete _b; }  // B zarządza życiem T
};

// vs ogólna wersja:
template<typename T>
class B {
    T _b;              // sizeof(T) bajtów — kopia wartości
};
```

Dla `B<int>`: przechowujemy `int` (4 bajty) — brak zarządzania pamięcią.
Dla `B<int*>`: przechowujemy `int*` (8 bajtów) + `delete` w destruktorze.

#### Problem 2: Alokacja węzłów musi znać rozmiar

```cpp
template<typename T>
class List {
    struct Node {
        T data;
        Node* next;
    };

    void push_front(const T& val) {
        Node* n = new Node{val, _head};  // new alokuje sizeof(Node) = sizeof(T) + sizeof(Node*)
        _head = n;
    }
};

// sizeof(Node<int>)    = 4 + 8 = 12 (może być 16 z paddingiem)
// sizeof(Node<double>) = 8 + 8 = 16
// sizeof(Node<BigObj>) = sizeof(BigObj) + 8
```

#### Problem 3: `T` może nie mieć domyślnego konstruktora

```cpp
class NoDef {
    NoDef(int x) {}  // brak domyślnego konstruktora!
};

// new Node<NoDef>{}  // BŁĄD — nie można domyślnie skonstruować data!

// Rozwiązanie: oddziel alokację od konstrukcji (placement new):
void* mem = ::operator new(sizeof(Node<NoDef>));
Node<NoDef>* n = new (mem) Node<NoDef>(NoDef{42}, _head);
//                 ^^ placement new — konstruuje w już zaalokowanej pamięci
```

#### Problem 4: Specjalizacja dla wskaźników (optymalizacja)

```cpp
// Optymalizacja: lista wskaźników zamiast wartości dla dużych typów:
template<>
class List<void*> {
    struct Node {
        void* data;   // ZAWSZE 8 bajtów — niezależnie od T!
        Node* next;
    };
};

template<typename T>
class List<T*> : private List<void*> {
    // Dziedziczy implementację List<void*> — jedna implementacja dla wszystkich wskaźników!
    // Technika: "thin template" / "type erasure"
public:
    T* front() { return static_cast<T*>(List<void*>::front()); }
};
```

### Podsumowanie

Różna ilość pamięci dla listy wynika z:
1. `sizeof(Node<T>)` zależy od `sizeof(T)` — każdy typ ma inny rozmiar
2. Specjalizacje dla wskaźników (`T*`) vs wartości (`T`) mają inną semantykę i zarządzanie pamięcią
3. Placement new + alokatory umożliwiają obsługę typów bez domyślnego konstruktora
4. Optymalizacje kodu (thin templates) mogą używać wspólnej implementacji dla wszystkich wskaźników

---

## 15. Szablonowe parametry szablonów (*Template Template Parameters*)

### Co to jest?

Normalny parametr szablonu to **typ** (`typename T`) lub **wartość** (`int N`).
**Template template parameter** to parametr który sam jest **szablonem klasy** — przekazujesz nie gotowy typ (np. `std::deque<int>`), ale "przepis na typ" (np. `std::deque`).

### Problem bez template template parameters

```cpp
// Klasa kolejki z konfigurowalnym kontenerem — ZŁY SPOSÓB:
template<typename T, typename StorageType>
class Fifo {
    StorageType _storage;  // StorageType to np. std::deque<int>
};

// Problem: musimy pisać T dwa razy!
Fifo<int, std::deque<int>>   f1;  // redundancja: int pojawia się dwa razy
Fifo<int, std::vector<int>>  f2;

// Można popełnić błąd typów:
Fifo<double, std::deque<int>> f_bug;  // T=double ale storage trzyma int -> BUG!
```

### Rozwiązanie: template template parameter

```cpp
// Z kodu 15.cpp:
template <
    typename T = int,
    template <typename...> class StorageType = std::deque
    //         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //         StorageType to SZABLON przyjmujący typename...
    //         Pasuje: std::deque, std::vector, std::list
>
class fifo {
    StorageType<T> _storage;  // kompilator SAM instancjonuje std::deque<int>
    //          ^^
    //          niemożliwe popełnienie błędu typów!

public:
    using storage_type = StorageType<T>;

    void push(const T& item) { _storage.push_back(item); }

    T get() {
        T front = _storage.front();
        _storage.pop_front();
        return front;
    }

    size_t size() const { return _storage.size(); }

    typename storage_type::const_iterator begin() const { return _storage.begin(); }
    typename storage_type::const_iterator end()   const { return _storage.end();   }
};

// Użycie (z 15.cpp):
fifo<>                    ft;   // T=int, StorageType=std::deque (domyślne)
fifo<int, std::deque>     f;    // jawnie
fifo<double, std::vector> fv;   // double + vector
fifo<std::string, std::list> fl;

// BŁĄD — std::deque<int> to gotowy typ, nie szablon:
// fifo<double, std::deque<int>> f_err;  // BŁĄD KOMPILACJI
```

### Składnia template template parameter

```cpp
// Pełna składnia:
template <
    template <typename>           class C1,  // szablon z 1 param typename
    template <typename, typename> class C2,  // szablon z 2 param typename
    template <typename...>        class C3   // szablon z dowolną liczbą params (C++11)
>
class MyClass { ... };
```

### Przykład: adapter kontenera

```cpp
// Własny wrapper który eksponuje interfejs STL, ale pozwala zmienić kontener:
template<
    typename T,
    template<typename...> class Container = std::vector
>
class Stack {
    Container<T> _data;
public:
    void push(T val) { _data.push_back(val); }
    void pop() { _data.pop_back(); }
    T& top() { return _data.back(); }
    bool empty() const { return _data.empty(); }
    size_t size() const { return _data.size(); }
};

// Różne implementacje:
Stack<int>                       s1;  // stack na vector<int>
Stack<int, std::deque>           s2;  // stack na deque<int>
Stack<std::string, std::list>    s3;  // stack na list<string>

// s1, s2, s3 mają IDENTYCZNY interfejs, różne wewnętrzne kontenery!
```

### `typename storage_type::const_iterator` — dlaczego `typename`?

```cpp
typename storage_type::const_iterator begin() const {
    return _storage.begin();
}
```

Kompilator **nie wie** czy `storage_type::const_iterator` to:
- **Typ** (co chcemy)
- **Statyczna wartość** (np. `static int const_iterator = 5;`)

Słowo kluczowe `typename` mówi kompilatorowi: *"to jest typ, nie wartość"*. Bez `typename` kompilator zwróciłby błąd.

### Schemat zastosowań

```
Użyj template template parameters gdy:
1. Klasa posiada wewnętrzny kontener STL
   i chcesz pozwolić użytkownikowi wybrać ten kontener
   bez zmuszania do podwajania parametru T.

2. Piszesz adapter/wrapper nad kontenerem STL.

3. Chcesz tworzyć klasy konfigurowane "przepisem na typ",
   a nie gotowym typem.
```

---

*Dokument opracowany na podstawie plików źródłowych z tego folderu oraz standardów C++11/14/17.*
*Pliki referencyjne: `1.cpp`, `4.cpp`, `9.cpp`, `11.cpp`, `13.cpp`, `14.cpp`, `15.cpp`, `notatki_cpp.md`, `zaawansowane_cpp.md`*
