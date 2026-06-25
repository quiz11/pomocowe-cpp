# Notatki C++ — Pełny przegląd zagadnień z zadań 1–20

> Opracowane na podstawie plików `1.cpp` – `20.cpp`.  
> Każda sekcja zawiera wyjaśnienie konceptu, przykład z kodu i omówienie pułapek.

---

## Spis treści

1. [Konstruktory — wszystkie rodzaje](#1-konstruktory--wszystkie-rodzaje)
2. [Destruktory](#2-destruktory)
3. [Specjalne funkcje składowe: `= default` i `= delete`](#3-specjalne-funkcje-składowe--default-i--delete)
4. [Dziedziczenie proste i wielopoziomowe](#4-dziedziczenie-proste-i-wielopoziomowe)
5. [Dziedziczenie wielokrotne i wirtualne (problem diamentu)](#5-dziedziczenie-wielokrotne-i-wirtualne-problem-diamentu)
6. [Klasy abstrakcyjne i czyste funkcje wirtualne](#6-klasy-abstrakcyjne-i-czyste-funkcje-wirtualne)
7. [Polimorfizm — `virtual`, `override`, vtable](#7-polimorfizm--virtual-override-vtable)
8. [Przeciążanie operatorów](#8-przeciążanie-operatorów)
9. [Semantyka przenoszenia — `std::move`, rvalue reference `&&`](#9-semantyka-przenoszenia--stdmove-rvalue-reference-)
10. [Szablony funkcji (`template<typename T>`)](#10-szablony-funkcji-templatetypename-t)
11. [Szablony klas](#11-szablony-klas)
12. [Specjalizacja częściowa i pełna szablonów](#12-specjalizacja-częściowa-i-pełna-szablonów)
13. [Template template parameters](#13-template-template-parameters)
14. [Aliasy typów: `using` i `typedef`](#14-aliasy-typów-using-i-typedef)
15. [Wyrażenia lambda](#15-wyrażenia-lambda)
16. [Funktory (callable objects)](#16-funktory-callable-objects)
17. [Iteratory i algorytmy STL](#17-iteratory-i-algorytmy-stl)
18. [Kontenery STL: `vector`, `list`, `deque`, `array`](#18-kontenery-stl-vector-list-deque-array)
19. [Smart pointery: `std::unique_ptr`](#19-smart-pointery-stdunique_ptr)
20. [Własny smart pointer (ręczne zarządzanie pamięcią)](#20-własny-smart-pointer-ręczne-zarządzanie-pamięcią)
21. [Przestrzenie nazw (`namespace`)](#21-przestrzenie-nazw-namespace)
22. [Składowe statyczne (`static`)](#22-składowe-statyczne-static)
23. [`constexpr` — obliczenia w czasie kompilacji](#23-constexpr--obliczenia-w-czasie-kompilacji)
24. [Metaprogramowanie szablonowe — silnia w czasie kompilacji](#24-metaprogramowanie-szablonowe--silnia-w-czasie-kompilacji)
25. [`static_assert` — asercje w czasie kompilacji](#25-static_assert--asercje-w-czasie-kompilacji)
26. [`friend` — operator zaprzyjaźniony](#26-friend--operator-zaprzyjaźniony)
27. [Operator rzutowania (`operator T()`)](#27-operator-rzutowania-operator-t)
28. [`__PRETTY_FUNCTION__`](#28-__pretty_function__)
29. [`noexcept`](#29-noexcept)
30. [Operator przecinkowy i subtelności wypisywania](#30-operator-przecinkowy-i-subtelności-wypisywania)
31. [Powtarzające się wzorce i schematy](#31-powtarzające-się-wzorce-i-schematy)

---

## 1. Konstruktory — wszystkie rodzaje

### 1.1 Konstruktor domyślny

Wywoływany bez argumentów. Może być wygenerowany automatycznie przez kompilator, jawnie zdefiniowany lub oznaczony `= default`.

```cpp
// Automatycznie wygenerowany (kompilator robi to sam, jeśli nie ma innych):
class A {};

// Jawnie domyślny:
A() = default;

// Z listą inicjalizacyjną:
A() : _a(0), _b(0) {}
```

**Przykład z zadań (2.cpp):**
```cpp
A() : A(0,0) {   // <-- konstruktor delegujący (patrz niżej)
    cout << __PRETTY_FUNCTION__ << ": _a=" << _a << ",_b=" << _b << "\n";
}
```

**Przykład z zadań (5.cpp):**
```cpp
Type_t() : _v{} {}  // inicjalizacja wartościująca (value-initialization)
                     // dla double: _v = 0.0; dla int: _v = 0
```

---

### 1.2 Konstruktor parametryczny (ogólny)

Przyjmuje argumenty i inicjalizuje pola klasy.

```cpp
class A {
    int _a, _b;
public:
    A(int a, int b) : _a(a), _b(b) {}
};
```

**Lista inicjalizacyjna (`: _a(a), _b(b)`)** — inicjalizuje pola *przed* wejściem do ciała konstruktora. Jest to efektywniejsze niż przypisanie wewnątrz `{}`, szczególnie dla typów nietrywialnych.

---

### 1.3 Konstruktor `explicit`

Blokuje niejawną konwersję (implicit conversion). Bez `explicit` kompilator mógłby automatycznie konwertować `int` → `A` wszędzie gdzie oczekuje się `A`.

```cpp
explicit A(int a) : A(a, 0) {
    cout << __PRETTY_FUNCTION__ << "\n";
}
```

**Skutek (2.cpp):**
```cpp
// A f = 1;  // BŁĄD kompilacji! explicit blokuje tę konwersję
A b(1);       // OK - wywołanie jawne
```

**Analogicznie dla own smart pointer (5.cpp i 7.cpp):**
```cpp
explicit ptr(T* p) : m_ptr(p) {}
// ptr<A> _b_error = new A;   // BŁĄD — explicit blokuje przypisanie "=" surowego wskaźnika
// ptr<A> p(new A);           // OK — wywołanie jawne
```

---

### 1.4 Konstruktor kopiujący

Tworzy nowy obiekt jako kopię istniejącego. Sygnatura: `ClassName(const ClassName&)`.

```cpp
// 3.cpp
A(A& kopia) : napis(kopia.napis) {}   // kopia bez const — może modyfikować źródło (rzadki wzorzec)

// 13.cpp — klasyczny kopiujący:
A(const A&) {
    std::cout << "Kopiowanie wersja 2\n";  // konstruktor kopiujący (inicjalizacja)
}

// 14.cpp — kopiujący z inicjalizacją pola:
B(const B& b) : _b(b._b) {}
```

**Kiedy się wywołuje:**
```cpp
A c = a;    // konstruktor kopiujący (inicjalizacja kopią)
A c(a);     // to samo — konstruktor kopiujący
```

**Blokada kopiowania (4.cpp, 5.cpp):**
```cpp
Derived1(const Derived1&) = delete;
ptr(const ptr&) = delete;
```
Po takiej deklaracji próba skopiowania jest **błędem kompilacji**.

---

### 1.5 Konstruktor przenoszący (move constructor)

Przyjmuje **rvalue reference** (`&&`). "Kradnie" zasoby z tymczasowego obiektu zamiast kopiować.

```cpp
// 2.cpp — prosty:
A(A&& zrodlo) {
    this->_a = zrodlo._a;
    this->_b = zrodlo._b;
    // uwaga: nie zerujemy zrodlo._a — to uproszczona wersja
}

// 5.cpp — prawidłowy (z nullptr):
ptr(ptr&& other) noexcept : m_ptr(other.m_ptr) {
    other.m_ptr = nullptr;  // konieczne! unikamy double-free
}

// 13.cpp — z std::move na stringu:
A(A&& a) {
    s = std::move(a.s);  // przeniesienie stringa (nie kopiowanie!)
    std::cout << "Przenoszenie wersja 2\n";
}
```

**Kiedy się wywołuje:**
```cpp
A d = std::move(c);         // jawne przeniesienie
Type_ptr t2 = std::move(t1); // przeniesienie smart pointera
A c = f(A{"var_c"});         // przeniesienie wartości zwróconej przez funkcję
```

---

### 1.6 Konstruktor delegujący

Jeden konstruktor wywołuje inny konstruktor tej samej klasy z listy inicjalizacyjnej. Pozwala unikać duplikacji kodu.

```cpp
// 2.cpp
A(int a, int b) : _a(a), _b(b) {      // konstruktor bazowy
    cout << __PRETTY_FUNCTION__ << "\n";
}

explicit A(int a) : A(a, 0) {           // deleguje do (int, int)
    cout << __PRETTY_FUNCTION__ << "\n";
}

A() : A(0, 0) {                         // deleguje do (int, int)
    cout << __PRETTY_FUNCTION__ << "\n";
}
```

**Output pokazujący kolejność:**
```
a-> A::A(int,int): _a=0,_b=0    // najpierw delegowany
    A::A(): _a=0,_b=0            // potem ciało delegującego
```

> **Ważne:** Ciało delegowanego konstruktora wykonuje się PRZED ciałem delegującego.

---

### 1.7 Konstruktor z wartością domyślną parametru szablonu

```cpp
// 16.cpp
box(T val = T{}) : value(val) {}
// T{} to value-initialization — dla int to 0, dla double to 0.0, dla klasy to domyślny konstruktor
```

---

## 2. Destruktory

Destruktor jest wywoływany automatycznie gdy obiekt wychodzi poza zakres lub jest usuwany przez `delete`.

### 2.1 Wirtualny destruktor

**KLUCZOWA ZASADA:** Jeśli klasa ma metody wirtualne i jest używana przez wskaźniki/referencje do klasy bazowej, destruktor **musi być wirtualny**, aby poprawnie niszczyć obiekty klas pochodnych.

```cpp
// 1.cpp
class B {
public:
    virtual ~B() = default;  // wirtualny destruktor — niezbędny!
};
```

Bez `virtual ~B()`, gdy robimy `delete ptr_to_base`, wywołany zostanie tylko destruktor `B`, a nie `D`, co prowadzi do wycieków pamięci.

### 2.2 Destruktor z `delete[]`

Dla tablic alokowanych przez `new T[n]` należy użyć `delete[]`:

```cpp
// 11.cpp
~Array() {
    delete[] _data;  // delete[] dla tablic, nie delete!
}

// 16.cpp
~array() {
    delete[] _data;
}
```

### 2.3 Destruktor zwalniający wskaźnik

```cpp
// 5.cpp — własny smart pointer
~ptr() { delete m_ptr; }

// 14.cpp — specjalizacja dla wskaźnika
~B() { delete _b; }
```

---

## 3. Specjalne funkcje składowe: `= default` i `= delete`

C++11 wprowadził możliwość jawnego sterowania generowaniem specjalnych funkcji składowych.

### `= default`

Nakazuje kompilatorowi wygenerować domyślną implementację:

```cpp
// 1.cpp
B() = default;           // domyślny konstruktor (ale protected!)
virtual ~B() = default;  // wirtualny destruktor z domyślną implementacją

// 4.cpp
Derived1() = default;    // jawne żądanie domyślnego konstruktora
Derived2() = default;
```

### `= delete`

Usuwa (zabrania) danej funkcji:

```cpp
// 2.cpp
A(const A&) = delete;          // kopiowanie zabronione

// 4.cpp
Derived1(const Derived1&) = delete;   // kopiowanie zabronione

// 5.cpp
ptr(const ptr&) = delete;             // zakaz kopiowania
ptr& operator=(const ptr&) = delete;  // zakaz kopiującego przypisania

// 14.cpp — w specjalizacji dla wskaźnika:
B(const B&) = delete;
B(const B&&) = delete;  // const rvalue reference — rzadkie, celowo blokuje przenoszenie
```

**Skutek `= delete`:**
```cpp
// A e = c;  // BŁĄD kompilacji — kopiowanie jest zablokowane
// ptr<A> p2 = p1;  // BŁĄD kompilacji
```

---

## 4. Dziedziczenie proste i wielopoziomowe

### 4.1 Podstawowa składnia

```cpp
class Base {
public:
    virtual void print() const = 0;
};

class Derived1 : public Base {
public:
    void print() const override { ... }
};

class Derived3 : public Derived2 {  // wielopoziomowe
    void print() const override { ... }
};
```

### 4.2 Inicjalizacja w konstruktorze klasy pochodnej

Konstruktor klasy pochodnej **musi** wywołać konstruktor klasy bazowej (jeśli bazowa nie ma konstruktora domyślnego). Robi się to z listy inicjalizacyjnej:

```cpp
// 3.cpp
class A : public is_printable {
public:
    std::string napis;
    A(std::string s) : napis(s) {}  // pola inicjalizowane, baza ma domyślny
};
```

### 4.3 Object slicing (krojenie obiektów)

```cpp
// 4.cpp
Derived3 d3;
Derived2 d2 = d3;  // OK — kopiuje tylko część Derived2 z d3 (slicing!)
                   // d2.print() wywoła Derived2::print, nie Derived3::print
```

**WAŻNE:** Gdy kopiujemy obiekt klasy pochodnej do zmiennej klasy bazowej (nie wskaźnik/referencja), tracimy część pochodną. Dlatego polimorfizm działa tylko przez wskaźniki/referencje!

```cpp
// 4.cpp
std::vector<Base*> v = {&d1, &d2, &d3};  // wskaźniki — polimorfizm działa!
// std::vector<Base> v_make_err = {d1, d2, d3};  // BŁĄD — Base jest abstrakcyjna
                                                  // a nawet gdyby nie była, byłby slicing
```

---

## 5. Dziedziczenie wielokrotne i wirtualne (problem diamentu)

### 5.1 Problem diamentu

```
      B
     / \
    D1  D3
     \ /
      D4
```

Bez `virtual`: `D4` miałoby **dwie kopie** podobiektów `B` (jedną przez `D1`, drugą przez `D3`). Wywoływanie metod `B` byłoby niejednoznaczne.

### 5.2 Wirtualne dziedziczenie — rozwiązanie

```cpp
// 1.cpp
class D1 : virtual public B { ... };  // virtual!
class D3 : virtual public B { ... };  // virtual!
class D4 : public D1, public D3 { ... };  // D4 ma JEDNĄ kopię B
```

**Z `virtual`:** `D4` ma tylko jeden podobjekt `B`. Nie ma niejednoznaczności.

### 5.3 Konstruktor klasy bazowej w diamencie

Przy wirtualnym dziedziczeniu, konstruktor klasy **najbardziej pochodnej** (tutaj `D4`) jest odpowiedzialny za inicjalizację wirtualnej bazy `B`. Klasy pośrednie (`D1`, `D3`) **nie** inicjalizują `B` dla `D4`.

```cpp
// 1.cpp — B ma tylko protected konstruktor domyślny
// D4 może skonstruować B przez swój konstruktor domyślny
```

**Blokada konstrukcji z zewnątrz:**
```cpp
// 1.cpp
class B {
protected:
    B() = default;  // protected — nikt spoza klasy i klas pochodnych nie może tworzyć B wprost
public:
    virtual ~B() = default;
};
// B b;  // BŁĄD KOMPILACJI
```

### 5.4 Jawne wywołanie metod bazowych

```cpp
// 1.cpp
class D4 : public D1, public D3 {
    virtual std::ostream& printOn(std::ostream& s) const {
        B::printOn(s);   // wywołanie metody B
        D1::printOn(s);  // wywołanie metody D1
        D3::printOn(s);  // wywołanie metody D3
        s << __PRETTY_FUNCTION__ << "\n";
        return s;
    }
};
```

---

## 6. Klasy abstrakcyjne i czyste funkcje wirtualne

### 6.1 Czyste funkcje wirtualne (`= 0`)

```cpp
// 4.cpp
class Base {
public:
    virtual std::ostream& print(std::ostream& s) const = 0;  // czysta wirtualna
};

// 8.cpp
struct Obj {
    virtual void Draw() const = 0;  // czysta wirtualna
};

// 3.cpp
class is_printable {
public:
    virtual std::ostream& printable(std::ostream& s) const = 0;
};
```

**Skutki:**
- Nie można tworzyć obiektów klasy z czystą wirtualną: `Base b;` — błąd kompilacji
- Klasa pochodna MUSI nadpisać czystą wirtualną, inaczej sama staje się abstrakcyjna
- Czyste wirtualne mogą mieć implementację (rzadko używane)

### 6.2 Wzorzec: interfejs + wiele implementacji

```cpp
// 3.cpp — wzorzec interface
class is_printable {
public:
    virtual std::ostream& printable(std::ostream& s) const = 0;
};

class A : public is_printable {
    std::ostream& printable(std::ostream& s) const { s << napis; return s; }
};

class B : public is_printable {
    std::ostream& printable(std::ostream& s) const { s << liczba; return s; }
};

// Operator << działa dla KAŻDEJ klasy implementującej is_printable:
std::ostream& operator<<(std::ostream& s, const is_printable& print) {
    print.printable(s);
    return s;
}
```

---

## 7. Polimorfizm — `virtual`, `override`, vtable

### 7.1 Słowo kluczowe `virtual`

Deklaracja metody wirtualnej powoduje, że jej wywołanie przez wskaźnik/referencję do bazy jest rozwiązywane **dynamicznie** (w czasie wykonania), a nie statycznie.

```cpp
// Bez virtual:
Base* p = new Derived;
p->print();  // wywoła Base::print — BŁĄD logiczny

// Z virtual:
p->print();  // wywoła Derived::print — POPRAWNIE
```

### 7.2 `override`

Jawnie wskazuje, że metoda nadpisuje metodę wirtualną z klasy bazowej. Kompilator zgłosi błąd, jeśli metoda NIE nadpisuje żadnej metody bazowej (np. literówka w nazwie).

```cpp
// 4.cpp
std::ostream& print(std::ostream& s) const override { ... }  // bezpieczne
```

### 7.3 Polimorfizm przez wskaźniki — wzorzec (4.cpp)

```cpp
Derived1 d1;
Derived3 d3;
Derived2 d2 = d3;               // slicing — d2 jest Derived2

std::vector<Base*> v = {&d1, &d2, &d3};  // przechowujemy wskaźniki do bazy

for (size_t i = 0; i < vec.size(); ++i) {
    s << *vec[i];  // wywołanie przez operator<< (Base&) — wirtualna dispatch
}
```

**Output (4.cpp):**
```
virtual std::ostream& Derived1::print(std::ostream&) const
virtual std::ostream& Derived2::print(std::ostream&) const   // d2 to Derived2 (po slicingu)
virtual std::ostream& Derived3::print(std::ostream&) const
```

### 7.4 Polimorfizm przez referencje (3.cpp)

```cpp
const is_printable& a_r = a;  // referencja do interfejsu
const is_printable& b_r = b;
std::cout << a_r << b_r;      // wirtualna dispatch przez operator<< (is_printable&)
```

### 7.5 Dziedziczenie metody bez nadpisania (1.cpp — D2)

```cpp
class D2 : public D1 {
    // brak printOn — D2 dziedziczy D1::printOn
};
// d2.printOn() wywoła D1::printOn
```

---

## 8. Przeciążanie operatorów

### 8.1 Operator `<<` (wyjście na strumień)

**Jako funkcja wolna (globalna):**

```cpp
// 1.cpp — bazowy wzorzec ze wzorcem printOn
std::ostream& operator<<(std::ostream& s, const B& b) {
    return b.printOn(s);  // deleguje do wirtualnej metody
}

// 3.cpp — przez interfejs abstrakcyjny
std::ostream& operator<<(std::ostream& s, const is_printable& print) {
    print.printable(s);
    return s;
}

// 4.cpp — dla wektora wskaźników
std::ostream& operator<<(std::ostream& s, std::vector<Base*>& vec) {
    s << "[\n";
    for (size_t i = 0; i < vec.size(); ++i) {
        s << *vec[i];
        if (i < vec.size()-1) s << ",\n";
        else s << "\n";
    }
    s << "]";
    return s;
}
```

**Jako `friend` (16.cpp):**

```cpp
friend std::ostream& operator<<(std::ostream& os, const box& b) {
    return os << b.value;
}
```

`friend` pozwala funkcji globalnej na dostęp do prywatnych składowych klasy.

**Wzorzec wirtualnego `printOn` (1.cpp, 3.cpp, 4.cpp):**
```
operator<< (globalny) → printOn/print/printable (wirtualna) → właściwa klasa pochodna
```
To jeden z najczęstszych wzorców przy polimorfizmie — operator `<<` nie może być wirtualny (jest globalny), więc deleguje do metody wirtualnej.

---

### 8.2 Operator `[]` (indeksowanie)

```cpp
// 11.cpp — prosta wersja
T& operator[](unsigned index) {
    return _data[index];
}

// 16.cpp — z obsługą ujemnych indeksów i wyjątkiem
T& operator[](int index) {
    if (index < 0) index += _size;      // Python-style: -1 = ostatni
    if (index < 0 || index >= _size)
        throw std::out_of_range("Indeks poza zakresem!");
    return _data[index];
}

// const wersja (dla obiektów const):
const T& operator[](int index) const {
    if (index < 0) index += _size;
    if (index < 0 || index >= _size)
        throw std::out_of_range("Indeks poza zakresem!");
    return _data[index];
}
```

**Ważne:** Zwykle definiujemy **dwie wersje** `operator[]`:
1. Nie-const: `T& operator[](int)` — zwraca referencję, możliwa modyfikacja
2. Const: `const T& operator[](int) const` — tylko do odczytu

```cpp
// 16.cpp — użycie ujemnych indeksów
a[-1] = ...;         // ostatni element
a[-a.size()] = ...; // pierwszy element
```

---

### 8.3 Operator `~` (bitowy NOT — przeładowany semantycznie)

```cpp
// 11.cpp — zwraca rozmiar tablicy
unsigned operator~() const {
    return _size;
}

// użycie:
for (unsigned i = 0; i != ~a; i++) { ... }  // ~a zwraca rozmiar
```

Przykład przeładowania operatora unary z niestandardową semantyką.

---

### 8.4 Operator `%` (przeładowany jako wstawianie)

```cpp
// 11.cpp — wstawianie elementu do tablicy
Array& operator%(T s) {
    return insert(s);  // deleguje do insert()
}

// użycie — łańcuchowe wywołanie:
a.insert('#'-1).insert('P') % type::value_type('O') % ('-') % ('E');
```

Operator zwraca `Array&` (referencję do siebie), co pozwala na **łańcuchowanie** wywołań.

---

### 8.5 Operator `*` i `->` (dereferencja i dostęp do składowej)

Używane do implementacji smart pointerów:

```cpp
// 5.cpp
T& operator*() const { return *m_ptr; }   // dereferencja — zwraca obiekt
T* operator->() const { return m_ptr; }   // dostęp do składowej — zwraca surowy wskaźnik

// 7.cpp
T& operator*() const { return *_ptr; }
T* operator->() const { return _ptr; }

// użycie:
(*t1).first = ...;   // operator*
t1->second = ...;    // operator->
```

**Subtelność:** `operator->` musi zwrócić wskaźnik lub obiekt z własnym `operator->`. Kompilator automatycznie wywołuje `->` na zwróconym wskaźniku.

---

### 8.6 Operatory porównania `==` i `!=`

```cpp
// 7.cpp
bool operator==(const ptr& other) const {
    if (_ptr == other._ptr) return true;
    else return false;
}

bool operator!=(const ptr& other) const {
    if (_ptr != other._ptr) return true;
    else return false;
}

// użycie:
std::cout << (a == ptr<A>())  // porównanie z domyślnym (nullptr)
          << (a != b);
```

---

### 8.7 Kopiujący operator przypisania `operator=(const T&)`

```cpp
// 13.cpp
A& operator=(const A& a) {
    std::cout << "Kopiowanie wersja 1\n";
    if (this == &a) return *this;  // self-assignment guard!
    s = a.s;
    return *this;
}
```

**Wzorzec:**
1. Sprawdź self-assignment: `if (this == &a) return *this;`
2. Skopiuj dane
3. Zwróć `*this` (pozwala na `a = b = c`)

**Kiedy się wywołuje:**
```cpp
a = b;  // kopiujący operator przypisania (a już istnieje)
```

---

### 8.8 Przenoszący operator przypisania `operator=(T&&)`

```cpp
// 5.cpp
ptr& operator=(ptr&& other) noexcept {
    if (this != &other) {    // guard przed self-move
        delete m_ptr;        // zwolnij własne zasoby
        m_ptr = other.m_ptr; // przejmij zasoby
        other.m_ptr = nullptr; // wyzeruj źródło
    }
    return *this;
}

// 13.cpp
A& operator=(A&& a) {
    std::cout << "Przenoszenie wersja 1\n";
    s = std::move(a.s);  // przeniesienie stringa
    return *this;
}
```

**Kiedy się wywołuje:**
```cpp
b = std::move(a);     // przenoszący operator przypisania
a = f(A{"var_c"});    // f zwraca tymczasowy (rvalue) → przenoszący
```

---

## 9. Semantyka przenoszenia — `std::move`, rvalue reference `&&`

### 9.1 lvalue vs rvalue

- **lvalue** — ma nazwę, ma adres: `int x = 5;` — `x` jest lvalue
- **rvalue** — tymczasowe, bez nazwy: `5`, `A{"var_c"}`, wynik `std::move(x)`

### 9.2 `std::move`

`std::move` **nie przenosi** — jedynie rzutuje lvalue na rvalue reference. Samo przeniesienie następuje w konstruktorze/operatorze przenoszącym.

```cpp
// 13.cpp
b = std::move(a);        // rzutowanie a na rvalue — wywoła operator=(A&&)
Type_ptr t2 = std::move(t1);  // wywoła konstruktor przenoszący
```

**Po `std::move(a)`:** `a` jest w "nieokreślonym, ale poprawnym stanie" — można je zniszczyć lub ponownie przypisać, ale nie należy używać jego wartości.

### 9.3 Przenoszenie w łańcuchu funkcji (13.cpp)

```cpp
A f(A&& a) {
    return std::move(a);   // przenoszenie z parametru funkcji
}

a = f(A{"var_c"});
// 1. A{"var_c"}      → konstruktor (Tworzenie: var_c)
// 2. f(A{"var_c"})   → konstruktor przenoszący przy budowaniu wartości zwracanej
// 3. a = ...         → przenoszący operator przypisania
```

### 9.4 `noexcept` przy przenoszeniu

```cpp
// 5.cpp
ptr(ptr&& other) noexcept : m_ptr(other.m_ptr) { ... }
ptr& operator=(ptr&& other) noexcept { ... }
```

`noexcept` informuje kompilator i bibliotekę STL, że operacja nie rzuci wyjątku. STL (np. `std::vector`) używa konstruktorów przenoszących zamiast kopiujących **tylko wtedy**, gdy są oznaczone `noexcept`.

### 9.5 `std::move` w implementacji `my_swap` (6.cpp)

```cpp
template <typename T>
void my_swap(T& a, T& b) {
    T temp = std::move(a);  // przeniesienie a → temp
    a = std::move(b);       // przeniesienie b → a
    b = std::move(temp);    // przeniesienie temp → b
}
```

To efektywniejsze niż klasyczny swap (kopiowanie), bo przenoszenie jest O(1) dla `unique_ptr`.

---

## 10. Szablony funkcji (`template<typename T>`)

### 10.1 Podstawowa składnia

```cpp
// 6.cpp
template <typename T>
void my_print(const T& kontener, const std::string& sep = ";", const std::string& end = "") {
    std::cout << "[";
    for (const auto& el : kontener) {
        std::cout << *el << sep;
    }
    std::cout << "]" << end;
}
```

`T` jest dedukowany automatycznie z argumentu.

### 10.2 Szablon z dwoma parametrami typów (9.cpp)

```cpp
template <typename It, typename Fun>
void change(It start, It end, Fun f) {
    for (auto it = start; it != end; ++it) {
        *it = f(*it);  // wywołanie funktora/lambdy/funkcji
    }
}

template <typename It, typename Fun>
void print_to_if(std::ostream& os, It start, It end, Fun f) {
    for (auto it = start; it != end; ++it) {
        if (f(*it)) {           // f to predykat — zwraca bool
            os << *it << " ";
        }
    }
    os << "\n";
}
```

**Użycie z różnymi callable:**
```cpp
print_to_if(std::cout << "All: ", begin(cl), end(cl), f1);     // zwykła funkcja
print_to_if(std::cout << "All: ", begin(cl), end(cl), f2);     // inna funkcja
change(begin(cl2), end(cl2), f3{add_value});                   // funktor
```

### 10.3 Szablon z operatorem `<<` (5.cpp)

```cpp
template <typename T>
std::ostream& operator<<(std::ostream& os, const Type_t<T>& obj) {
    return os << obj._v;
}
```

---

## 11. Szablony klas

### 11.1 Podstawowy szablon klasy z wartością domyślną

```cpp
// 5.cpp
template <typename T = double>  // wartość domyślna parametru!
struct Type_t {
    T _v;
    Type_t() : _v{} {}
    explicit Type_t(T v) : _v(v) {}
};

using Float_t = Type_t<>;  // używa wartości domyślnej: Type_t<double>
```

### 11.2 Szablon klasy z `using value_type`

Powszechny wzorzec — eksportowanie typu dla użytkowników szablonu:

```cpp
// 5.cpp
template <typename T>
class ptr {
public:
    using value_type = T;    // alias — dostępny jako ptr<X>::value_type
    ...
};

// 11.cpp
template <typename T>
class Array {
public:
    using value_type = T;
    ...
};

// 14.cpp, 15.cpp, 16.cpp — identyczny wzorzec
```

**Użycie:**
```cpp
using Type_ptr = ptr<std::pair<Float_t, Float_t>>;
Type_ptr t1 { new Type_ptr::value_type{} };  // value_type = std::pair<Float_t, Float_t>

// ptr::value_type::first_type = Float_t
(*t1).first = Type_ptr::value_type::first_type{1};

// ptr::value_type::second_type = Float_t
t1->second = Type_ptr::value_type::second_type{2.5};
```

### 11.3 Szablon klasy `Array` (11.cpp)

```cpp
namespace OOP {
    template <typename T>
    class Array {
    private:
        T* _data;
        unsigned _capacity;
        unsigned _size;

    public:
        using value_type = T;

        explicit Array(unsigned capacity) 
            : _capacity(capacity), _size(0), _data(new T[capacity]) {}

        ~Array() { delete[] _data; }

        Array& insert(T s) {     // zwraca *this — łańcuchowanie
            if (_size < _capacity) {
                _data[_size] = s;
                _size += 1;
            }
            return *this;
        }

        Array& operator%(T s) { return insert(s); }  // wygodny alias

        T& operator[](unsigned index) { return _data[index]; }

        unsigned operator~() const { return _size; }
    };
}
```

**Użycie z `typedef` i namespace:**
```cpp
typedef ::OOP::Array<int> type;   // :: na początku = global scope
type a(rand() % 100 + 10);
a.insert('#'-1).insert('P') % type::value_type('O') % ('-');
```

---

## 12. Specjalizacja częściowa i pełna szablonów

### 12.1 Specjalizacja pełna (explicit specialization)

Pełna specjalizacja definiuje zachowanie dla konkretnego typu/wartości.

```cpp
// 18.cpp — specjalizacja Factorial<0>
template <>            // puste nawiasy = pełna specjalizacja
struct Factorial<0> {
    enum { value = 1 };  // warunek stopu rekurencji
};

// 19.cpp — specjalizacja metody szablonowej klasy
template<>
void X::f<int>(const int& t) {
    private_ = t;   // dostęp do prywatnych pól przez specjalizację!
}
```

### 12.2 Specjalizacja częściowa (partial specialization) — tylko dla klas

```cpp
// 14.cpp — specjalizacja dla typów wskaźnikowych T*
template <typename T>
class B {          // szablon ogólny
    T _b;
public:
    using value_type = T;
    B(T b) : _b(b) {}
    B(const B& b) : _b(b._b) {}
    T get() { return _b; }
};

template <typename T>
class B<T*> {      // specjalizacja dla T* — inna implementacja!
    T* _b;
public:
    using value_type = T;
    B(T* b) : _b(b) {}
    T get() { return *_b; }   // dereferencja!
    ~B() { delete _b; }        // zarządzanie pamięcią
    B(const B&) = delete;     // zakaz kopiowania
    B(const B&&) = delete;
};
```

**Użycie:**
```cpp
typedef B<int>  int_b;    // używa ogólnego szablonu
typedef B<int*> int_p_b;  // używa specjalizacji dla wskaźnika
int_b a(1);               // B<int>: przechowuje int
int_p_b b(new int{2});    // B<int*>: przechowuje wskaźnik i usuwa go w destruktorze
```

### 12.3 Specjalizacja częściowa z typem szablonowym (8.cpp)

```cpp
// Ogólny szablon
template <typename T>
struct Box : public Obj {
    T _val;
    explicit Box(T val) : _val(val) {}
    operator T() const { return _val; }      // konwersja do T
    void Draw() const override { ... }
};

// Specjalizacja dla Box<Box<T>> — gdy T samo jest Boxem
template <typename T>
struct Box<Box<T>> : public Obj {
    Box<T> _val;
    explicit Box(T val) : _val(val) {}       // konstruktor przyjmuje T, nie Box<T>!
    operator Box<T>() const { return _val; } // konwersja do Box<T>
    void Draw() const override { ... }
};
```

**Użycie:**
```cpp
Box<int> b_i{3};         // korzysta z ogólnego szablonu
Box<Box<int>> bb_i{3};   // korzysta ze specjalizacji Box<Box<T>>
                          // konstruktor przyjmuje int (T), tworzy Box<int> wewnątrz
Box<int> br_i = bb_i;    // konwersja przez operator Box<T>()
```

---

## 13. Template template parameters

Parametr szablonu, który sam jest szablonem klasy.

```cpp
// 15.cpp
template <
    typename T = int,                              // parametr typu z domyślnym
    template <typename...> class StorageType = std::deque  // template template parameter!
>
class fifo {
private:
    StorageType<T> _storage;  // np. std::deque<int>

public:
    using storage_type = StorageType<T>;

    void push(const T& item) { _storage.push_back(item); }
    T get() {
        T front_item = _storage.front();
        _storage.pop_front();
        return front_item;
    }
    size_t size() const { return _storage.size(); }

    typename storage_type::const_iterator begin() const { return _storage.begin(); }
    typename storage_type::const_iterator end() const { return _storage.end(); }
};
```

**Użycie:**
```cpp
fifo<> ft;                         // T=int, StorageType=std::deque (wartości domyślne)
fifo<int, std::deque> f = ft;      // jawne podanie obu parametrów
```

**`typename` przed `storage_type::const_iterator`:**  
Kompilator nie wie a priori, czy `storage_type::const_iterator` to typ czy wartość. `typename` mówi mu "to jest typ" (dependent name).

---

## 14. Aliasy typów: `using` i `typedef`

### 14.1 `using` — aliasy w klasach szablonowych

```cpp
// 5.cpp, 11.cpp, 14.cpp, 15.cpp, 16.cpp
using value_type = T;       // wewnątrz klasy
using storage_type = StorageType<T>;

// w main:
using Type_ptr = ptr<std::pair<Float_t, Float_t>>;  // lokalny alias
using Float_t = Type_t<>;                            // globalny alias
```

### 14.2 `typedef` — starszy sposób

```cpp
// 11.cpp, 14.cpp
typedef ::OOP::Array<int> type;
typedef B<int>  int_b;
typedef B<int*> int_p_b;
```

`typedef` i `using` są równoważne dla prostych aliasów. `using` jest nowszy (C++11) i bardziej czytelny, wspiera też szablony aliasów.

### 14.3 Dostęp do zagnieżdżonych typów przez `::`

```cpp
// ptr<std::pair<Float_t, Float_t>>::value_type = std::pair<Float_t, Float_t>
Type_ptr t1 { new Type_ptr::value_type{} };

// pair::first_type = Float_t
(*t1).first = Type_ptr::value_type::first_type{1};

// pair::second_type = Float_t
t1->second = Type_ptr::value_type::second_type{2.5};
```

---

## 15. Wyrażenia lambda

### 15.1 Podstawowa składnia

```
[przechwycenia](parametry) -> typ_zwracany { ciało }
```

`-> typ_zwracany` można pominąć (dedukowane automatycznie).

### 15.2 Lambda bez przechwytywania (10.cpp, 12.cpp)

```cpp
// 10.cpp — funkcja zwraca lambdę (higher-order function)
auto liftToVector() {
    return [](std::vector<int> x) {     // przechwycenie puste []
        for (int& a : x) { a += 2; }
        return x;
    };
}

auto vadd2 = liftToVector();   // vadd2 to lambda
auto v = vadd2(x);             // wywołanie lambdy
```

```cpp
// 12.cpp — generyczna lambda z auto (C++14)
std::for_each(begin(c), end(c), [](auto x) { std::cout << x << " "; });
```

### 15.3 Lambda z przechwytywaniem przez wartość `[a]` (12.cpp)

```cpp
auto a = c[0];  // a = 7 (po sortowaniu malejącym)
std::for_each(begin(c), end(c), [a](auto& x) { x = x + a; });
//                               ^^^ przechwycenie a przez wartość (kopia)
```

`a` jest kopiowane przy tworzeniu lambdy. Zmiany `a` po utworzeniu lambdy nie wpływają na przechwycone `a`.

### 15.4 Lambda z przechwytywaniem przez referencję `[&x]` (12.cpp)

```cpp
int x = c[0];
auto f = [&x](int a) {  // przechwycenie x przez referencję
    x += a;
    return x;
};
std::cout << f(6);   // modyfikuje oryginalne x!
std::cout << x;      // x zostało zmienione przez lambdę
```

**Podsumowanie przechwytywań:**
- `[a]` — kopia wartości, lambda ma własną kopię
- `[&a]` — referencja, lambda modyfikuje oryginalną zmienną
- `[=]` — przechwytuje wszystko przez wartość
- `[&]` — przechwytuje wszystko przez referencję

### 15.5 Lambda w `std::for_each` i `std::sort`

```cpp
// for_each
std::for_each(v.begin(), v.end(), [](const int n) { std::cout << n << ' '; });

// sort malejący
std::sort(std::begin(c), std::end(c), [](auto a, auto b) { return a > b; });
```

---

## 16. Funktory (callable objects)

Funktor to klasa z zdefiniowanym `operator()`. Działa jak funkcja, ale może przechowywać stan.

```cpp
// 9.cpp
template <typename T>
struct f3 {
    T _value;                    // stan — przechowuje wartość
    f3(T& value) : _value(value) {}

    int operator()(int element) const {  // operator wywołania
        return element + _value;
    }
};

// użycie:
int add_value{-1};
change(begin(cl2), end(cl2), f3{add_value});
// f3{add_value} → CTAD (Class Template Argument Deduction) — kompilator dedukuje T=int
```

**Przewaga funktora nad funkcją:** funktor może przechowywać stan (jak lambda z przechwytywaniem).

---

## 17. Iteratory i algorytmy STL

### 17.1 `std::for_each`

```cpp
// 12.cpp
std::for_each(std::begin(c), std::end(c), [](auto x) { std::cout << x << " "; });
//             ^^^^^^^^^^^^^  ^^^^^^^^^^^  ^^^^^^^^^^^
//             iterator begin  iterator end  callable

// 10.cpp
std::for_each(v.begin(), v.end(), [](const int n) { std::cout << n << ' '; });
```

### 17.2 `std::sort`

```cpp
// 12.cpp
std::sort(std::begin(c), std::end(c), [](auto a, auto b) { return a > b; });
// sortowanie malejące — comparator zwraca true gdy a > b
```

### 17.3 Ręczne iterowanie przez iteratory (9.cpp)

```cpp
template <typename It, typename Fun>
void change(It start, It end, Fun f) {
    for (auto it = start; it != end; ++it) {
        *it = f(*it);    // dereferencja iteratora
    }
}
```

### 17.4 `begin()` i `end()` — wersje wolne (9.cpp)

```cpp
const auto cl = {1,2,3,4,5,6,7};     // std::initializer_list<int>
print_to_if(std::cout, begin(cl), end(cl), f1);  // begin/end jako wolne funkcje
```

`begin()` i `end()` jako wolne funkcje (ADL) działają zarówno dla kontenerów STL jak i dla surowych tablic.

### 17.5 Własne `begin()`/`end()` w klasie (15.cpp)

```cpp
typename storage_type::const_iterator begin() const { return _storage.begin(); }
typename storage_type::const_iterator end() const { return _storage.end(); }

// użycie jawne przez iterator:
for (fifo<>::storage_type::const_iterator i = f.begin(); i != f.end(); ++i)
    std::cout << *i << ",";
```

---

## 18. Kontenery STL: `vector`, `list`, `deque`, `array`

### 18.1 `std::vector<T>`

Dynamiczna tablica. Alokuje ciągłą pamięć, wspiera losowy dostęp.

```cpp
// 4.cpp
std::vector<Base*> v = {&d1, &d2, &d3};  // wektor wskaźników (polimorfizm)
v.front()   // pierwszy element
v.size()    // rozmiar
v[i]        // losowy dostęp

// 12.cpp
std::vector<int> c = {1,2,3,4,5,6,7};
```

### 18.2 `std::list<T>`

Dwukierunkowa lista powiązana. Nie wspiera losowego dostępu, ale efektywne wstawianie/usuwanie.

```cpp
// 9.cpp
std::list<int> cl2 = {7,6,5,4,3,2,1};
change(begin(cl2), end(cl2), f3{add_value});  // iteracja przez iteratory
```

### 18.3 `std::deque<T>`

Double-ended queue. Efektywne wstawianie/usuwanie z obu końców.

```cpp
// 15.cpp — jako domyślny storage dla fifo
_storage.push_back(item);  // dodaj na koniec
_storage.front();          // peek z przodu
_storage.pop_front();      // usuń z przodu (FIFO!)
```

### 18.4 `std::array<T, N>`

Tablica o stałym rozmiarze — opakowanie na surową tablicę C.

```cpp
// 6.cpp
std::array<std::unique_ptr<int>, 2> a = {
    std::unique_ptr<int>(new int{1}),
    std::unique_ptr<int>(new int{2})
};

my_swap(a[0], a[1]);   // zamiana unique_ptr (przez move)
my_swap(*a[0], *a[1]); // zamiana wskazywanych intów
```

### 18.5 `std::pair<T1, T2>`

```cpp
// 5.cpp
using Type_ptr = ptr<std::pair<Float_t, Float_t>>;
(*t1).first = Type_ptr::value_type::first_type{1};
t1->second = Type_ptr::value_type::second_type{2.5};
// pair::first_type  = Float_t
// pair::second_type = Float_t
```

---

## 19. Smart pointery: `std::unique_ptr`

`std::unique_ptr` jest właścicielem zasobu — zwalnia go automatycznie w destruktorze.

### 19.1 Tworzenie

```cpp
// 6.cpp
std::unique_ptr<int>(new int{1})  // stary styl
// Nowszy: std::make_unique<int>(1) (C++14)
```

### 19.2 Zakaz kopiowania — tylko przenoszenie

`unique_ptr` nie może być kopiowany. Można go przenosić:

```cpp
// 6.cpp — my_swap z unique_ptr działa przez std::move
my_swap(a[0], a[1]);
// wewnątrz: T temp = std::move(a); — przeniesienie unique_ptr
```

### 19.3 Dereferencja i dostęp

```cpp
*a[0]        // operator* zwraca wartość zarządzanego obiektu
a[0].get()   // dostęp do surowego wskaźnika (rzadko używane)
```

---

## 20. Własny smart pointer (ręczne zarządzanie pamięcią)

### 20.1 Pełna implementacja (5.cpp)

```cpp
template <typename T>
class ptr {
private:
    T* m_ptr;

public:
    using value_type = T;

    ptr() : m_ptr(nullptr) {}
    explicit ptr(T* p) : m_ptr(p) {}       // explicit — nie można: ptr<A> p = new A;
    ~ptr() { delete m_ptr; }               // automatyczne zwalnianie

    ptr(const ptr&) = delete;              // zakaz kopiowania
    ptr& operator=(const ptr&) = delete;   // zakaz kopiującego przypisania

    ptr(ptr&& other) noexcept : m_ptr(other.m_ptr) {  // przenoszący konstruktor
        other.m_ptr = nullptr;
    }

    ptr& operator=(ptr&& other) noexcept {  // przenoszący operator przypisania
        if (this != &other) {
            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
};
```

### 20.2 Subtelność: `const ptr<T>` a modyfikacja obiektu

```cpp
// 5.cpp i 7.cpp
const Type_ptr t3 = std::move(t2);  // t3 jest const
t3->first = ...;   // OK! ptr jest const, ale wskazywany obiekt NIE jest!
```

`const ptr<T>` znaczy: nie można zmienić `m_ptr` (na co wskazuje pointer), ale można modyfikować obiekt, na który wskazuje.

---

## 21. Przestrzenie nazw (`namespace`)

### 21.1 Definiowanie

```cpp
// 11.cpp
namespace OOP {
    template <typename T>
    class Array { ... };
}

// 17.cpp
namespace exam {
    static int i = 1;
}
```

### 21.2 Dostęp i rozwiązywanie nazw

```cpp
// 11.cpp
typedef ::OOP::Array<int> type;
// ::    = globalny namespace
// OOP:: = namespace OOP
// Array<int> = szablon w OOP

// 17.cpp
using namespace exam;   // importuje wszystkie nazwy z exam do bieżącego zakresu
```

### 21.3 Zasłanianie nazw (name shadowing) — 17.cpp

```cpp
int i = 10;             // globalna i

namespace exam {
    static int i = 1;  // exam::i
}

int main() {
    int i = 15;         // lokalna i — zasłania globalną!

    using namespace exam;  // dodaje exam::i, ale lokalna i nadal wygrywa

    std::cout << i;         // 15 — lokalna
    std::cout << ::i;       // 10 — globalna (:: wymusza globalny namespace)
}
```

### 21.4 Obliczenie `MyStruct::j` — szczegóły (17.cpp)

```cpp
struct MyStruct {
    static int j;
    const static int i = 5;
    int a;
};

int i = 10;
int MyStruct::j = i + 1;   // i odnosi się do globalnego i = 10 → j = 11
int j = i + 1;              // globalne j = 10 + 1 = 11

int main() {
    MyStruct A;
    A.a = j + i;      // j = globalne 11, i = globalne 10 → a = 21
    int i = 15;

    std::cout << i;              // 15 (lokalna)
    std::cout << ::i;            // 10 (globalna)
    std::cout << MyStruct::j;    // 11
    std::cout << j;              // 11 (globalne j, lokalna i zasłania, ale j nie)
    std::cout << A.a;            // 21
}
```

---

## 22. Składowe statyczne (`static`)

### 22.1 `static` w strukturze/klasie

```cpp
// 17.cpp
struct MyStruct {
    static int j;            // statyczna — jedna dla wszystkich instancji
    const static int i = 5; // statyczna stała — może być zainicjowana inline
    int a;                   // niestatyczna — każda instancja ma własną
};

int MyStruct::j = i + 1;    // definicja poza klasą (wymagana dla non-const static)
```

**Dostęp:**
```cpp
MyStruct::j   // bez tworzenia obiektu
MyStruct::i   // bez tworzenia obiektu
MyStruct A;
A.a           // przez obiekt
```

### 22.2 `static` w przestrzeni nazw

```cpp
namespace exam {
    static int i = 1;  // static ogranicza widoczność do jednostki translacji
}
```

### 22.3 `static constexpr` metoda (20.cpp)

```cpp
template <typename T, unsigned N>
struct array {
    static constexpr unsigned size() { return N; }  // metoda statyczna, constexpr
};

// wywołanie bez tworzenia obiektu:
array<unsigned, factorial(4)>::size()  // = 24
// lub przez obiekt:
a.size()                               // = 6
```

---

## 23. `constexpr` — obliczenia w czasie kompilacji

### 23.1 Funkcja `constexpr`

```cpp
// 20.cpp
constexpr unsigned factorial(unsigned n) {
    if (n == 1) return 1;
    return n * factorial(n-1);
}

// Użycie jako parametr szablonu (musi być stałą czasu kompilacji!):
array<int, factorial(3)> b;   // factorial(3) = 6 obliczone w czasie kompilacji
array<int, factorial(4)> c;   // factorial(4) = 24
```

`constexpr` funkcja może być wywołana zarówno w czasie kompilacji (jeśli argumenty są stałymi) jak i w czasie wykonania.

### 23.2 `constexpr` vs. metaprogramowanie (18.cpp vs 20.cpp)

| | `constexpr` (20.cpp) | Metaprogramowanie (18.cpp) |
|---|---|---|
| Styl | Normalna funkcja | Rekurencja szablonów |
| Czytelność | Wysoka | Niska |
| Wersja C++ | C++11+ | C++98+ |
| Elastyczność | Działa też w runtime | Tylko compile-time |

---

## 24. Metaprogramowanie szablonowe — silnia w czasie kompilacji

### 24.1 Rekurencja szablonów (18.cpp)

```cpp
// Ogólny przypadek: N! = N * (N-1)!
template <int N>
struct Factorial {
    enum { value = N * Factorial<N - 1>::value };
    // nowszy C++: static const int value = N * Factorial<N-1>::value;
};

// Warunek stopu: 0! = 1
template <>          // pełna specjalizacja
struct Factorial<0> {
    enum { value = 1 };
};

// Użycie:
std::cout << Factorial<5>::value;  // 120 — obliczone w CZASIE KOMPILACJI
```

**Jak to działa (rozwijanie):**
```
Factorial<5>::value
= 5 * Factorial<4>::value
= 5 * 4 * Factorial<3>::value
= 5 * 4 * 3 * Factorial<2>::value
= 5 * 4 * 3 * 2 * Factorial<1>::value
= 5 * 4 * 3 * 2 * 1 * Factorial<0>::value  ← specjalizacja: value = 1
= 120
```

### 24.2 `enum` vs `static const` vs `static constexpr`

```cpp
enum { value = N * Factorial<N-1>::value };          // stara technika (C++98)
static const int value = N * Factorial<N-1>::value;  // C++03+
static constexpr int value = N * Factorial<N-1>::value; // C++11 — najlepsza
```

---

## 25. `static_assert` — asercje w czasie kompilacji

```cpp
// 20.cpp
static_assert(a.size() == 6);          // sprawdza w czasie kompilacji
static_assert(array<unsigned, factorial(4)>::size() == 24);
static_assert(array<unsigned, factorial(3)>::size() == b.size());

// Ten nie przejdzie — różne typy szablonów (T=int vs T=unsigned):
// static_assert(array<int, factorial(4)>::size() == b.size()); // BŁĄD
```

`static_assert(wyrażenie)`:
- `true` → kompilacja przebiega normalnie
- `false` → błąd kompilacji z podanym komunikatem (lub domyślnym)

**Uwaga** na typy: `array<int, 24>` i `array<unsigned, 24>` to **różne typy** — nie można porównywać ich `size()` w `static_assert` między różnymi specjalizacjami typów.

---

## 26. `friend` — operator zaprzyjaźniony

```cpp
// 16.cpp — w ciele klasy box
friend std::ostream& operator<<(std::ostream& os, const box& b) {
    return os << b.value;  // dostęp do prywatnego value!
}
```

`friend` zdefiniowany wewnątrz klasy — jest globalną funkcją, ale ma dostęp do prywatnych składowych.

**Kiedy używać `friend operator<<`:**  
Gdy operator `<<` musi mieć dostęp do prywatnych pól klasy, a nie chcemy tworzyć metody `printOn`.

**Alternatywa — poprzez `printOn` (1.cpp, 3.cpp):**
```cpp
// Operator<< jest publiczny i woła publiczną metodę printOn (która może być wirtualna)
std::ostream& operator<<(std::ostream& s, const B& b) {
    return b.printOn(s);
}
```

---

## 27. Operator rzutowania (`operator T()`)

Pozwala na niejawną konwersję obiektu klasy do innego typu.

```cpp
// 8.cpp — Box<T> konwertuje się do T
template <typename T>
struct Box : public Obj {
    T _val;
    explicit Box(T val) : _val(val) {}

    operator T() const {    // operator rzutowania do T
        return _val;
    }
};

// Box<Box<T>> konwertuje się do Box<T>
template <typename T>
struct Box<Box<T>> : public Obj {
    Box<T> _val;
    explicit Box(T val) : _val(val) {}

    operator Box<T>() const { return _val; }  // konwersja do Box<T>
};

// Użycie — niejawna konwersja:
Box<int> b_i{3};
int i = b_i;              // operator int() wywoływany niejawnie

Box<Box<int>> bb_i{3};
Box<int> br_i = bb_i;    // operator Box<int>() wywoływany niejawnie
```

**Uwaga:** `explicit Box(T val)` blokuje `Box<int> _ = 3;` (przypisanie z `=`), ale `Box<int> b{3}` i `Box<int> b(3)` są poprawne.

---

## 28. `__PRETTY_FUNCTION__`

Makro (GCC/Clang) zawierające pełną sygnaturę funkcji z typami szablonowymi.

```cpp
// 1.cpp
s << __PRETTY_FUNCTION__ << "\n";
// Output: virtual std::ostream& D1::printOn(std::ostream&) const

// 4.cpp
s << __PRETTY_FUNCTION__;
// Output: virtual std::ostream& Derived1::print(std::ostream&) const

// 8.cpp
std::cout << __PRETTY_FUNCTION__;
// Output (ogólny):     void Box<T>::Draw() const [with T = int]
// Output (specjalizacja): void Box<Box<K>>::Draw() const [with T = int]

// 15.cpp — w konstruktorze szablonu:
fifo<T, StorageType>::fifo() [with T = int, StorageType = std::deque]
```

Użyteczne do debugowania — pokazuje dokładnie, która instancja szablonu i która wirtualna metoda jest wywoływana.

---

## 29. `noexcept`

Specyfikator informujący kompilator i STL o braku wyjątków.

```cpp
// 5.cpp
ptr(ptr&& other) noexcept : m_ptr(other.m_ptr) { other.m_ptr = nullptr; }
ptr& operator=(ptr&& other) noexcept { ... }
```

**Dlaczego ważne dla STL:**  
`std::vector` realokuje pamięć gdy się zapełni. Musi przenieść stare elementy do nowej pamięci. Używa konstruktorów przenoszących TYLKO gdy są `noexcept` — w przeciwnym razie używa kopiujących (co jest bezpieczniejsze przy wyjątkach, bo można wycofać operację).

---

## 30. Operator przecinkowy i subtelności wypisywania

### 30.1 Operator przecinkowy w wyrażeniu (7.cpp)

```cpp
std::cout << (((*a).i, a->i))
//            ^^^^^^^^^^^^^^^
//            operator przecinkowy: ewaluuje oba, zwraca prawy
//            (*a).i = 1, a->i = 1  → wynik: a->i = 1
```

`(wyrA, wyrB)` — oba wyrażenia są ewaluowane od lewej do prawej, wynikiem jest wartość prawego wyrażenia.

### 30.2 `++c->i` — preinkrement przez smart pointer

```cpp
++c->i    // priorytet: operator-> > operator++
          // c->i zwraca i z obiektu wskazanego przez c
          // ++ inkrementuje to i
          // wynik: 2 (bo i było 1)
```

### 30.3 Wypisywanie w warunku (9.cpp)

```cpp
print_to_if(std::cout << "All: ", begin(cl), end(cl), f1);
//           ^^^^^^^^^^^^^^^^
//           std::cout << "All: " zwraca std::ostream& !
//           i to jest przekazywane jako pierwszy argument do print_to_if
```

Operator `<<` zwraca referencję do strumienia, dzięki czemu można go użyć jako argumentu.

### 30.4 `std::endl` vs `"\n"`

```cpp
std::cout << std::endl;  // '\n' + flush bufora — wolniejsze
std::cout << "\n";       // tylko nowy wiersz — szybsze
```

---

## 31. Powtarzające się wzorce i schematy

### Schemat 1: `printOn` + `operator<<`

Pojawia się w **1.cpp, 3.cpp, 4.cpp**:

```cpp
// Metoda wirtualna:
virtual std::ostream& printOn(std::ostream& s) const { ... }

// Operator globalny deleguje:
std::ostream& operator<<(std::ostream& s, const Base& b) {
    return b.printOn(s);   // wirtualna dispatch
}
```

**Po co:** `operator<<` nie może być wirtualny (jest globalny). Przez delegację do `printOn` uzyskujemy polimorfizm.

---

### Schemat 2: Własny kontener/smart pointer z `using value_type`

Pojawia się w **5.cpp, 11.cpp, 14.cpp, 15.cpp, 16.cpp**:

```cpp
template <typename T>
class Container {
public:
    using value_type = T;
    explicit Container(...) { ... }
    ~Container() { delete[] ... }
    Container(const Container&) = delete;
    Container(Container&&) noexcept { ... }
    T& operator[](int) { ... }
    const T& operator[](int) const { ... }
};
```

---

### Schemat 3: `= delete` dla kopiowania + przenoszenie

Pojawia się w **2.cpp, 4.cpp, 5.cpp, 6.cpp, 7.cpp, 14.cpp**:

```cpp
MyClass(const MyClass&) = delete;
MyClass& operator=(const MyClass&) = delete;
MyClass(MyClass&&) noexcept { ... }   // tylko przenoszenie jest dozwolone
```

---

### Schemat 4: Konstruktor `explicit` + `= delete` na kopiowaniu

Chroni przed niechcianymi konwersjami:

```cpp
explicit ptr(T* p) : m_ptr(p) {}         // blokuje: ptr<A> p = new A;
ptr(const ptr&) = delete;                 // blokuje: ptr<A> p2 = p1;
// Tylko jawne tworzenie i przenoszenie:
ptr<A> p{new A};                          // OK
ptr<A> p2 = std::move(p);                 // OK
```

---

### Schemat 5: Łańcuchowe wywołania przez `return *this`

Pojawia się w **11.cpp, 13.cpp, 16.cpp**:

```cpp
Array& insert(T s) {
    ...
    return *this;   // zwraca referencję do samego siebie
}

Array& operator%(T s) { return insert(s); }

// Użycie:
a.insert('A').insert('B') % 'C' % 'D';
```

---

### Schemat 6: Specjalizacja szablonu jako warunek stopu rekurencji

Pojawia się w **18.cpp**:

```cpp
template <int N>  struct Factorial { enum { value = N * Factorial<N-1>::value }; };
template <>       struct Factorial<0> { enum { value = 1 }; };  // stop!
```

---

### Schemat 7: `typedef`/`using` + pełna kwalifikacja namespace

```cpp
typedef ::OOP::Array<int> type;                           // 11.cpp
using Type_ptr = ptr<std::pair<Float_t, Float_t>>;        // 5.cpp
```

---

### Schemat 8: Polimorfizm przez wskaźniki do bazy

```cpp
Derived1 d1; Derived2 d2; Derived3 d3;
std::vector<Base*> v = {&d1, &d2, &d3};
for (size_t i = 0; i < v.size(); ++i) {
    s << *v[i];   // wirtualna dispatch → właściwa klasa pochodna
}
```

---

### Schemat 9: CTAD (Class Template Argument Deduction) — C++17

```cpp
// 9.cpp
change(begin(cl2), end(cl2), f3{add_value});
//                            ^^^^^^^^^^^^ — kompilator dedukuje T=int z add_value
// Bez CTAD: f3<int>{add_value}
```

---

### Schemat 10: `static_assert` + `constexpr` jako testy kompilacyjne

```cpp
// 20.cpp
static_assert(array<unsigned, factorial(4)>::size() == 24);
// zamiast unit testów w runtime — weryfikacja w czasie kompilacji
```

---

### Schemat 11: Metoda specjalizowana z dostępem do prywatnych pól (19.cpp)

```cpp
class X {
    template<class T>
    void f(const T& t) {}  // ogólna — nic nie robi z private_
    int private_;
};

template<>
void X::f<int>(const int& t) {  // specjalizacja pełna — ma dostęp do private_!
    private_ = t;
}
```

Specjalizacja pełna metody szablonowej ma dostęp do prywatnych pól klasy, bo jest częścią klasy.

---

## Zestawienie: które zagadnienia w których plikach

| Zagadnienie | Pliki |
|---|---|
| Konstruktor domyślny | 1, 2, 5, 7, 13, 16 |
| Konstruktor parametryczny | 2, 3, 5, 11, 13, 14, 16 |
| Konstruktor kopiujący | 2, 3, 4, 13, 14, 16 |
| Konstruktor przenoszący | 2, 5, 6, 13 |
| Konstruktor delegujący | 2 |
| `explicit` na konstruktorze | 2, 5, 7, 8, 11, 16 |
| `= default` | 1, 4 |
| `= delete` | 2, 4, 5, 7, 14 |
| Destruktor wirtualny | 1 |
| Destruktor z `delete[]` | 11, 16 |
| Destruktor z `delete` | 5, 14 |
| Dziedziczenie proste | 1, 3, 4, 8 |
| Dziedziczenie wielopoziomowe | 4 |
| Dziedziczenie wielokrotne | 1 |
| Wirtualne dziedziczenie (diament) | 1 |
| `protected` konstruktor | 1 |
| Object slicing | 4 |
| Klasy abstrakcyjne (`= 0`) | 3, 4, 8 |
| `virtual`, `override` | 1, 3, 4, 8 |
| `operator<<` globalny | 1, 3, 4, 5 |
| `friend operator<<` | 16 |
| `operator[]` | 11, 16 |
| `operator[]` const | 16 |
| `operator~` | 11 |
| `operator%` | 11 |
| `operator*`, `operator->` | 5, 7 |
| `operator==`, `operator!=` | 7 |
| Kopiujący `operator=` | 13 |
| Przenoszący `operator=` | 5, 13 |
| Operator rzutowania (`operator T()`) | 8 |
| `std::move` | 2, 5, 6, 13, 20 |
| `noexcept` | 5 |
| Szablony funkcji | 5, 6, 9, 10, 16 |
| Szablony klas | 5, 6, 7, 8, 9, 11, 14, 15, 16, 20 |
| Wartości domyślne parametrów szablonu | 5, 15, 16 |
| Specjalizacja pełna szablonu | 18, 19 |
| Specjalizacja częściowa szablonu | 8, 14 |
| Specjalizacja metody szablonowej | 19 |
| Template template parameters | 15 |
| `using value_type` | 5, 11, 14, 15, 16 |
| `typedef` | 11, 14 |
| Wyrażenia lambda bez przechwytywania | 10, 12 |
| Lambda `[a]` (wartość) | 12 |
| Lambda `[&x]` (referencja) | 12 |
| Generyczna lambda `auto` | 12 |
| Funktory | 9 |
| CTAD | 9 |
| `std::for_each` | 10, 12 |
| `std::sort` | 12 |
| Iteratory | 9, 15 |
| `begin()`/`end()` wolne funkcje | 9 |
| `std::vector` | 4, 12 |
| `std::list` | 9 |
| `std::deque` | 15 |
| `std::array` | 6 |
| `std::pair` | 5 |
| `std::unique_ptr` | 6 |
| Własny smart pointer | 5, 7 |
| `namespace` | 11, 17 |
| `using namespace` | 2, 17 |
| `static` składowe klasy | 17 |
| `static constexpr` metoda | 20 |
| `constexpr` funkcja | 20 |
| Metaprogramowanie rekurencja szablonów | 18 |
| `static_assert` | 20 |
| `typename` w szablonach (dependent name) | 15 |
| `__PRETTY_FUNCTION__` | 1, 2, 4, 8, 15 |
| `std::out_of_range` | 16 |
| Ujemne indeksy | 16 |
| Struct Slot (wzorzec pomocniczy) | 16 |
| Operator przecinkowy | 7 |
| `std::initializer_list` | 9 |
| Łańcuchowanie przez `return *this` | 11 |
| Higher-order functions (lambda zwracająca lambdę) | 10 |
