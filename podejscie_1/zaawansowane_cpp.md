# Zaawansowane zagadnienia C++ — szczegółowe notatki

---

## Spis treści

1. [Template Template Parameters](#1-template-template-parameters)
2. [Smart Pointery — `std::unique_ptr`](#2-smart-pointery--stdunique_ptr)
3. [Własny Smart Pointer — implementacja od zera](#3-własny-smart-pointer--implementacja-od-zera)
4. [Przeciążanie operatorów `*` i `->`](#4-przeciążanie-operatorów--i--)
5. [Rule of Three / Five / Zero — kiedy usuwać konstruktor kopiujący i `operator=`](#5-rule-of-three--five--zero)
6. [Double Free — jak powstaje i jak mu zapobiegać](#6-double-free--jak-powstaje-i-jak-mu-zapobiegać)
7. [Operatory konwersji `operator T()`](#7-operatory-konwersji-operator-t)
8. [`explicit` — kontrola niejawnych konwersji](#8-explicit--kontrola-niejawnych-konwersji)

---

## 1. Template Template Parameters

### Co to jest?

Normalny parametr szablonu to **typ** (np. `typename T`) lub **wartość** (np. `int N`).  
**Template template parameter** to parametr, który sam jest **szablonem klasy** — czyli przekazujesz nie konkretny typ (np. `std::deque<int>`), ale sam "przepis na klasę" (np. `std::deque`).

### Motywacja — problem bez template template

Wyobraź sobie klasę kolejki, która ma konfigurowalny wewnętrzny kontener:

```cpp
// PODEJŚCIE 1 — bez template template:
// Przekazujesz gotowy typ: trzeba powtarzać parametr T dwa razy!
template <typename T, typename StorageType>
class fifo_bad {
    StorageType _storage;  // StorageType to np. std::deque<int>
};

// Użycie — musisz dwa razy pisać int:
fifo_bad<int, std::deque<int>> f1;   // redundantne! T=int i deque<int> — int dwa razy
fifo_bad<int, std::vector<int>> f2;  // znowu int dwa razy
```

Problem: `T` i typ w `StorageType` muszą być zgodne — kompilator tego nie wymusza, możesz napisać:
```cpp
fifo_bad<double, std::deque<int>> f_bug;  // T=double, ale storage trzyma int — BUG!
```

### Rozwiązanie — template template parameter

```cpp
// PODEJŚCIE 2 — z template template:
// Przekazujesz "szablon kontenera", nie gotowy typ
template <
    typename T = int,
    template <typename...> class StorageType = std::deque
    // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // StorageType to szablon klasy, który sam przyjmuje typename...
    // std::deque, std::vector, std::list — wszystkie pasują
>
class fifo {
    StorageType<T> _storage;  // kompilator SAM instancjonuje: std::deque<int>
    // ^^^^^^^^ — nie możesz tu popełnić błędu z typem!
};

// Użycie — T podajesz tylko raz:
fifo<> f1;                       // T=int, StorageType=std::deque (domyślne)
fifo<int> f2;                    // T=int, StorageType=std::deque
fifo<int, std::deque> f3;        // jawnie oba
fifo<double, std::vector> f4;    // T=double, StorageType=std::vector<double>
// fifo<double, std::deque<int>> // BŁĄD — deque<int> to nie szablon, to gotowy typ!
```

### Pełny przykład z metodami

```cpp
#include <iostream>
#include <deque>
#include <vector>
#include <list>

template <
    typename T = int,
    template <typename...> class StorageType = std::deque
>
class Queue {
private:
    StorageType<T> _data;

public:
    // alias — dostępny z zewnątrz jako Queue<int>::storage_type
    using storage_type = StorageType<T>;

    void push(const T& val) {
        _data.push_back(val);
    }

    T pop() {
        T front = _data.front();
        _data.pop_front();
        return front;
    }

    bool empty() const { return _data.empty(); }
    std::size_t size() const { return _data.size(); }

    // Eksponujemy iteratory wewnętrznego kontenera
    // UWAGA: "typename" jest OBOWIĄZKOWE — kompilator nie wie czy
    // storage_type::const_iterator to typ czy wartość statyczna
    typename storage_type::const_iterator begin() const { return _data.begin(); }
    typename storage_type::const_iterator end()   const { return _data.end();   }
};

int main() {
    Queue<> q1;                    // Queue<int, std::deque>
    Queue<double, std::vector> q2; // Queue<double, std::vector>
    Queue<std::string, std::list> q3;

    q1.push(1); q1.push(2); q1.push(3);
    std::cout << q1.pop() << "\n"; // 1 (FIFO)

    // Iteracja po wewnętrznym kontenerze:
    q1.push(99);
    for (Queue<>::storage_type::const_iterator it = q1.begin(); it != q1.end(); ++it) {
        std::cout << *it << " ";   // 2 3 99
    }
}
```

### Schemat: kiedy używać

```
Używaj template template gdy:
  klasa posiada wewnętrzny kontener STL (storage)
  i chcesz pozwolić użytkownikowi wybrać ten kontener
  bez zmuszania go do podawania T dwa razy.
```

---

## 2. Smart Pointery — `std::unique_ptr`

### Problem: ręczne zarządzanie pamięcią jest niebezpieczne

```cpp
// Klasyczny kod z new/delete — pełen pułapek:
void f() {
    int* p = new int{42};

    if (cos_sie_nie_udalo()) {
        return;          // WYCIEK! delete nigdy nie zostanie wywołany
    }

    throw std::runtime_error("błąd");  // WYCIEK! delete nigdy nie zostanie wywołany

    delete p;            // tylko w "szczęśliwej ścieżce"
}
```

### `std::unique_ptr` — RAII (Resource Acquisition Is Initialization)

`unique_ptr` to opakowanie na surowy wskaźnik, które **automatycznie wywołuje `delete`** w swoim destruktorze — nieważne czy wychodzimy z funkcji normalnie, przez `return`, czy przez wyjątek.

```cpp
#include <memory>

void f() {
    std::unique_ptr<int> p = std::make_unique<int>(42);
    // p jest na stosie. Kiedy f() się kończy (z jakiegokolwiek powodu),
    // destruktor p jest wołany automatycznie → delete

    if (cos_sie_nie_udalo()) {
        return;   // OK — destruktor p wywoła delete
    }

    throw std::runtime_error("błąd");  // OK — stack unwinding wywoła destruktor p
    // delete p — nie trzeba pisać!
}
```

### Tworzenie

```cpp
// Preferowany sposób (C++14):
auto p1 = std::make_unique<int>(42);
auto p2 = std::make_unique<std::string>("hello");
auto p3 = std::make_unique<MyClass>(arg1, arg2);  // przekazuje argumenty do konstruktora

// Starszy sposób (C++11, nadal poprawny):
std::unique_ptr<int> p4(new int{42});
std::unique_ptr<int> p4 = std::unique_ptr<int>(new int{42}); // to samo

// Pusty (nullptr):
std::unique_ptr<int> p5;          // p5 = nullptr
std::unique_ptr<int> p6{nullptr}; // to samo
```

### Dlaczego `make_unique` a nie `new`?

```cpp
// BEZ make_unique — subtelny wyciek pamięci możliwy:
f(std::unique_ptr<int>(new int{1}), g());
// Kompilator może wykonać: new int{1} → g() → unique_ptr(...)
// Jeśli g() rzuci wyjątek — mamy wyciek!

// Z make_unique — bezpieczne:
f(std::make_unique<int>(1), g());
// new i opakowanie w unique_ptr to jedna nierozerwalna operacja
```

### Zakaz kopiowania — tylko przenoszenie

`unique_ptr` modeluje **wyłączną własność** (ang. *exclusive ownership*). Tylko jeden `unique_ptr` może posiadać dany zasób w danej chwili.

```cpp
auto p1 = std::make_unique<int>(42);

// auto p2 = p1;          // BŁĄD KOMPILACJI — kopiowanie zabronione
// auto p2(p1);           // BŁĄD KOMPILACJI

// Przenoszenie jest OK — własność przechodzi z p1 do p2:
auto p2 = std::move(p1);
// p1 == nullptr teraz (nie ma już własności)
// p2 posiada int{42}

std::cout << (p1 == nullptr);  // true
std::cout << *p2;              // 42
```

### Podstawowe operacje

```cpp
auto p = std::make_unique<int>(42);

// Dereferencja — jakbyś miał zwykły wskaźnik:
std::cout << *p;          // 42
*p = 100;

// Dostęp do składowych (gdy T to klasa):
auto ps = std::make_unique<std::string>("hello");
std::cout << ps->size();  // 5
std::cout << (*ps)[0];    // 'h'

// Sprawdzenie czy nie jest nullptr:
if (p) { /* p nie jest null */ }
if (p != nullptr) { /* to samo */ }

// Dostęp do surowego wskaźnika (BEZ przejmowania własności):
int* raw = p.get();       // p nadal jest właścicielem!
// NIE rób: delete raw;  — double free!

// Oddanie własności (unique_ptr staje się nullptr):
int* raw2 = p.release();  // teraz TY odpowiadasz za delete raw2
delete raw2;

// Reset — usuwa stary obiekt, opcjonalnie ustawia nowy:
p.reset();                // delete starego int, p = nullptr
p.reset(new int{99});     // delete starego (nullptr), p wskazuje na 99
```

### `unique_ptr` z tablicami

```cpp
// Dla tablic — specjalizacja unique_ptr<T[]>
auto arr = std::make_unique<int[]>(10);  // tablica 10 intów
arr[0] = 42;
arr[5] = 99;
// Destruktor wywoła delete[] arr (nie delete arr!)
// Nie ma operator* ani operator->
```

### `unique_ptr` w kontenerach i funkcjach

```cpp
// W wektorze — przechowywanie polimorficznych obiektów bez wycieków:
std::vector<std::unique_ptr<Base>> objects;
objects.push_back(std::make_unique<Derived1>());
objects.push_back(std::make_unique<Derived2>());

for (const auto& obj : objects) {
    obj->virtual_method();  // polimorfizm działa
}
// Kiedy vector jest niszczony — wszystkie unique_ptr zwalniają pamięć

// Przekazywanie do funkcji:
void take_ownership(std::unique_ptr<int> p) {
    // p jest właścicielem
}  // tutaj p jest niszczony → delete

void borrow(const std::unique_ptr<int>& p) {
    // tylko pożyczamy — nie przenosimy własności
    std::cout << *p;
}

void borrow_raw(int* p) {
    // jeszcze prostszy borrow — przekazujemy surowy wskaźnik
    std::cout << *p;
}

auto p = std::make_unique<int>(42);
// take_ownership(p);          // BŁĄD — trzeba przenieść
take_ownership(std::move(p));  // OK — p jest teraz nullptr
// borrow(p);                  // BŁĄD — p jest nullptr!

auto p2 = std::make_unique<int>(42);
borrow(p2);                    // OK — p2 nadal jest właścicielem
borrow_raw(p2.get());          // OK — p2 nadal jest właścicielem
```

---

## 3. Własny Smart Pointer — implementacja od zera

Implementacja własnego smart pointera to ćwiczenie z wielu zagadnień naraz. Zbudujemy go krok po kroku.

### Krok 1 — Szkielet i podstawowe pola

```cpp
template <typename T>
class UniquePtr {
private:
    T* _ptr;   // surowy wskaźnik — to jedyne pole

public:
    // Alias — pozwala użytkownikowi pisać UniquePtr<int>::value_type
    using value_type = T;
};
```

### Krok 2 — Konstruktory

```cpp
template <typename T>
class UniquePtr {
private:
    T* _ptr;

public:
    using value_type = T;

    // (a) Konstruktor domyślny — pusty wskaźnik
    UniquePtr() : _ptr(nullptr) {}

    // (b) Konstruktor z surowego wskaźnika
    // MUSI być explicit — wyjaśnienie w sekcji 8
    explicit UniquePtr(T* ptr) : _ptr(ptr) {}

    // (c) Konstruktor z nullptr (wygoda)
    UniquePtr(std::nullptr_t) : _ptr(nullptr) {}
};
```

**Dlaczego `explicit` na konstruktorze z `T*`?**

```cpp
UniquePtr<int> p = new int{42};   // BEZ explicit: OK (niebezpieczne! nieoczekiwana konwersja)
UniquePtr<int> p = new int{42};   // Z explicit:   BŁĄD (co chcemy osiągnąć)
UniquePtr<int> p{new int{42}};    // Z explicit:   OK (jawne, świadome)
UniquePtr<int> p(new int{42});    // Z explicit:   OK (jawne, świadome)
```

### Krok 3 — Destruktor (serce zarządzania pamięcią)

```cpp
~UniquePtr() {
    delete _ptr;  // bezpieczne nawet gdy _ptr == nullptr
}
// delete nullptr jest no-op — nie trzeba sprawdzać if (_ptr != nullptr)
```

### Krok 4 — ZAKAZ kopiowania (bo to UniquePtr, nie SharedPtr!)

```cpp
// Jeśli NIE zabronimy kopiowania — kompilator wygeneruje domyślne:
// UniquePtr(const UniquePtr& other) : _ptr(other._ptr) {}
// To katastrofa! Dwa obiekty wskazują na tę samą pamięć → double free

UniquePtr(const UniquePtr&) = delete;
UniquePtr& operator=(const UniquePtr&) = delete;
```

### Krok 5 — Przenoszenie (zamiast kopiowania)

```cpp
// Konstruktor przenoszący
UniquePtr(UniquePtr&& other) noexcept : _ptr(other._ptr) {
    other._ptr = nullptr;  // KLUCZOWE: odbieramy własność od "other"
    // Teraz "other" nie wskazuje na nic — jego destruktor wywoła delete nullptr = no-op
}

// Przenoszący operator przypisania
UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (this != &other) {             // guard przed self-assignment: p = std::move(p)
        delete _ptr;                  // zwolnij SWOJE stare zasoby
        _ptr = other._ptr;            // przejmij zasoby od other
        other._ptr = nullptr;         // odbierz własność od other
    }
    return *this;
}
```

### Krok 6 — Operatory dostępu (`*` i `->`)

```cpp
// operator* — dereferencja, zwraca referencję do obiektu
T& operator*() const {
    // w produkcyjnym kodzie: assert(_ptr != nullptr);
    return *_ptr;
}

// operator-> — dostęp do składowej, zwraca surowy wskaźnik
// Kompilator automatycznie wywoła -> na zwróconym wskaźniku
T* operator->() const {
    return _ptr;
}
```

### Krok 7 — Operatory pomocnicze

```cpp
// Konwersja do bool — sprawdzenie czy nie jest nullptr
explicit operator bool() const {
    return _ptr != nullptr;
}

// Porównanie z nullptr
bool operator==(std::nullptr_t) const { return _ptr == nullptr; }
bool operator!=(std::nullptr_t) const { return _ptr != nullptr; }

// Dostęp do surowego wskaźnika (bez oddawania własności)
T* get() const { return _ptr; }

// Zwolnienie własności — caller przejmuje odpowiedzialność za delete
T* release() {
    T* tmp = _ptr;
    _ptr = nullptr;
    return tmp;
}

// Reset — usuń stary, opcjonalnie wstaw nowy
void reset(T* new_ptr = nullptr) {
    delete _ptr;       // usuń stary
    _ptr = new_ptr;    // wstaw nowy (lub nullptr)
}
```

### Krok 8 — Kompletna implementacja

```cpp
#include <iostream>
#include <utility>   // std::move

template <typename T>
class UniquePtr {
private:
    T* _ptr;

public:
    using value_type = T;

    // Konstruktory
    UniquePtr() noexcept : _ptr(nullptr) {}
    explicit UniquePtr(T* ptr) noexcept : _ptr(ptr) {}
    UniquePtr(std::nullptr_t) noexcept : _ptr(nullptr) {}

    // Destruktor
    ~UniquePtr() { delete _ptr; }

    // Zakaz kopiowania
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    // Przenoszenie
    UniquePtr(UniquePtr&& other) noexcept : _ptr(other._ptr) {
        other._ptr = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete _ptr;
            _ptr = other._ptr;
            other._ptr = nullptr;
        }
        return *this;
    }

    // Operatory dostępu
    T& operator*()  const { return *_ptr;  }
    T* operator->() const { return _ptr;   }

    // Konwersja do bool
    explicit operator bool() const { return _ptr != nullptr; }

    // Porównania z nullptr
    bool operator==(std::nullptr_t) const { return _ptr == nullptr; }
    bool operator!=(std::nullptr_t) const { return _ptr != nullptr; }

    // Dostęp do surowego wskaźnika
    T* get() const { return _ptr; }

    // Oddanie własności
    T* release() {
        T* tmp = _ptr;
        _ptr = nullptr;
        return tmp;
    }

    // Reset
    void reset(T* new_ptr = nullptr) {
        delete _ptr;
        _ptr = new_ptr;
    }
};

// Funkcja pomocnicza (jak std::make_unique)
template <typename T, typename... Args>
UniquePtr<T> make_unique_ptr(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}
```

### Krok 9 — Użycie

```cpp
struct Point {
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    void print() const { std::cout << "(" << x << "," << y << ")\n"; }
};

int main() {
    // Tworzenie
    UniquePtr<int> p1{new int{42}};
    UniquePtr<Point> p2{new Point{3, 4}};
    auto p3 = make_unique_ptr<int>(99);

    // Dostęp
    std::cout << *p1;      // 42
    *p1 = 100;
    p2->print();           // (3,4)
    std::cout << (*p2).x;  // 3

    // Sprawdzenie
    if (p1) { std::cout << "p1 nie jest null\n"; }

    // Przenoszenie
    UniquePtr<int> p4 = std::move(p1);
    // p1 jest teraz nullptr, p4 posiada int{100}
    std::cout << (p1 == nullptr);  // true

    // auto p5 = p4;   // BŁĄD KOMPILACJI — kopiowanie zabronione

    // Kiedy p2, p3, p4 wychodzą poza zakres — automatycznie wywołują delete
}
```

---

## 4. Przeciążanie operatorów `*` i `->`

### `operator*` — operator dereferencji

```
Sygnatura:  T& operator*() const;
            ^^               ^^^^^
            referencja       const bo nie modyfikujemy _ptr (tylko obiekt na który wskazuje)
            do obiektu
```

Zwraca **referencję** (nie wartość!) do obiektu wskazywanego przez pointer.

```cpp
template <typename T>
class Ptr {
    T* _ptr;
public:
    // Wersja zwracająca T& — pozwala na modyfikację obiektu:
    T& operator*() { return *_ptr; }

    // Wersja const — gdy sam Ptr jest const, zwraca const T&:
    const T& operator*() const { return *_ptr; }
    // Obie wersje razem tworzą pełny "const-correct" smart pointer
};

Ptr<int> p{new int{42}};
*p = 100;       // modyfikacja — wywoła T& operator*()
std::cout << *p; // odczyt — może wywołać obie wersje

const Ptr<int> cp{new int{42}};
// *cp = 100;   // BŁĄD — const Ptr, wywoła const T& operator*()
std::cout << *cp;  // OK — odczyt
```

**Subtelność: `const Ptr<T>` vs `Ptr<const T>`**

```cpp
const Ptr<int> p1{new int{42}};
// _ptr nie może być zmieniony (const na ptr)
// ALE obiekt wskazywany przez _ptr może być zmieniany!
*p1 = 100;   // OK jeśli operator*() zwraca T& (nie const T&)

Ptr<const int> p2{new const int{42}};
// *p2 = 100;  // BŁĄD — int jest const
```

### `operator->` — operator dostępu do składowej

```
Sygnatura:  T* operator->() const;
            ^^              ^^^^^
            surowy          const bo nie modyfikujemy _ptr
            wskaźnik
```

**KLUCZOWE:** Musi zwrócić surowy wskaźnik (lub obiekt z własnym `operator->`). Kompilator automatycznie wywołuje `->` na zwróconym wskaźniku.

```cpp
template <typename T>
class Ptr {
    T* _ptr;
public:
    T* operator->() const { return _ptr; }
};

struct Foo {
    int x = 42;
    void bar() { std::cout << "bar!\n"; }
};

Ptr<Foo> p{new Foo{}};

// Co faktycznie robi kompilator gdy widzisz p->x:
p->x;
// to jest dokładnie równoważne:
(p.operator->())->x;
// czyli: zwróć _ptr, a potem zrób ->x na surowym wskaźniku

p->bar();    // wywoła p.operator->() → zwraca Foo* → Foo*->bar()
(*p).bar();  // identyczny efekt przez operator*
```

### Oba operatory razem — pełny przykład

```cpp
#include <iostream>

struct BankAccount {
    double balance;
    std::string owner;

    BankAccount(std::string name, double bal)
        : owner(std::move(name)), balance(bal) {}

    void deposit(double amount) { balance += amount; }
    void print() const {
        std::cout << owner << ": " << balance << "\n";
    }
};

template <typename T>
class Handle {
    T* _ptr;
public:
    explicit Handle(T* p) : _ptr(p) {}
    ~Handle() { delete _ptr; }

    Handle(const Handle&) = delete;
    Handle& operator=(const Handle&) = delete;
    Handle(Handle&& o) noexcept : _ptr(o._ptr) { o._ptr = nullptr; }

    T& operator*()  { return *_ptr; }
    T* operator->() { return  _ptr; }
    const T& operator*()  const { return *_ptr; }
    const T* operator->() const { return  _ptr; }
};

int main() {
    Handle<BankAccount> acc{new BankAccount{"Jan Kowalski", 1000.0}};

    // przez operator->:
    acc->deposit(500.0);
    acc->print();          // Jan Kowalski: 1500

    // przez operator*:
    (*acc).deposit(100.0);
    (*acc).print();        // Jan Kowalski: 1600

    // modyfikacja pola bezpośrednio:
    acc->balance = 9999.0;
    std::cout << (*acc).balance;  // 9999
}
```

---

## 5. Rule of Three / Five / Zero

### Zasada Zero

Jeśli klasa **nie zarządza żadnymi zasobami** (nie ma surowych wskaźników, uchwytów pliku itp.), to kompilator wygeneruje wszystkie specjalne funkcje składowe poprawnie — **nie definiuj żadnej z nich**.

```cpp
class Point {
    double x, y;
public:
    Point(double x, double y) : x(x), y(y) {}
    // NIE piszemy destruktora, kopiującego, przenoszącego — kompilator zrobi to dobrze
};
```

### Zasada Trzech (Rule of Three) — C++03

Jeśli musisz zdefiniować **którekolwiek** z poniższych, musisz zdefiniować **wszystkie trzy**:

1. **Destruktor** (`~MyClass()`)
2. **Konstruktor kopiujący** (`MyClass(const MyClass&)`)
3. **Kopiujący operator przypisania** (`MyClass& operator=(const MyClass&)`)

**Dlaczego? Wygenerowane automatycznie będą błędne.**

```cpp
// Klasa zarządzająca tablicą — zła implementacja (tylko destruktor):
class BadArray {
    int* _data;
    int  _size;
public:
    BadArray(int size) : _size(size), _data(new int[size]) {}
    ~BadArray() { delete[] _data; }
    // Brak konstruktora kopiującego i operator= !!!
};

void problem() {
    BadArray a(10);
    BadArray b = a;   // Kompilator generuje: b._data = a._data
                      // Teraz a i b wskazują na TĄ SAMĄ pamięć!
}
// Kiedy funkcja się kończy:
// 1. Destruktor b: delete[] b._data → pamięć zwolniona
// 2. Destruktor a: delete[] a._data → to samo co b._data → DOUBLE FREE! → crash
```

**Poprawna implementacja — zasada trzech:**

```cpp
class GoodArray {
    int* _data;
    int  _size;
public:
    // Konstruktor
    GoodArray(int size) : _size(size), _data(new int[size]) {}

    // 1. Destruktor
    ~GoodArray() {
        delete[] _data;
        _data = nullptr;  // defensywnie
    }

    // 2. Konstruktor kopiujący — GŁĘBOKA kopia (deep copy)
    GoodArray(const GoodArray& other) : _size(other._size), _data(new int[other._size]) {
        for (int i = 0; i < _size; i++) {
            _data[i] = other._data[i];  // kopiujemy wartości, nie wskaźnik!
        }
    }

    // 3. Kopiujący operator przypisania
    GoodArray& operator=(const GoodArray& other) {
        if (this == &other) return *this;  // self-assignment guard!

        delete[] _data;                    // zwolnij SWOJE stare zasoby

        _size = other._size;
        _data = new int[_size];           // alokuj nową pamięć
        for (int i = 0; i < _size; i++) {
            _data[i] = other._data[i];    // kopiuj wartości
        }

        return *this;
    }
};
```

### Zasada Pięciu (Rule of Five) — C++11

Do zasady trzech dodajemy dwa elementy z semantyki przenoszenia:

4. **Konstruktor przenoszący** (`MyClass(MyClass&&)`)
5. **Przenoszący operator przypisania** (`MyClass& operator=(MyClass&&)`)

```cpp
class ModernArray {
    int* _data;
    int  _size;
public:
    ModernArray(int size) : _size(size), _data(new int[size]) {}

    // 1. Destruktor
    ~ModernArray() { delete[] _data; }

    // 2. Konstruktor kopiujący
    ModernArray(const ModernArray& other) : _size(other._size), _data(new int[other._size]) {
        std::copy(other._data, other._data + _size, _data);
    }

    // 3. Kopiujący operator=
    ModernArray& operator=(const ModernArray& other) {
        if (this == &other) return *this;
        delete[] _data;
        _size = other._size;
        _data = new int[_size];
        std::copy(other._data, other._data + _size, _data);
        return *this;
    }

    // 4. Konstruktor przenoszący
    ModernArray(ModernArray&& other) noexcept
        : _size(other._size), _data(other._data) {
        other._data = nullptr;  // "steal" — odbieramy zasoby
        other._size = 0;
    }

    // 5. Przenoszący operator=
    ModernArray& operator=(ModernArray&& other) noexcept {
        if (this == &other) return *this;
        delete[] _data;          // zwolnij SWOJE stare zasoby
        _data = other._data;     // przejmij cudze zasoby
        _size = other._size;
        other._data = nullptr;   // zostaw other w poprawnym stanie
        other._size = 0;
        return *this;
    }
};
```

### Kiedy `= delete` zamiast implementacji?

Gdy klasa zarządza **unikalnym** zasobem (np. `unique_ptr`-like), kopiowanie nie ma sensu. Zamiast pisać błędną implementację — **usuń kopiowanie**:

```cpp
class UniqueResource {
    FILE* _file;
public:
    explicit UniqueResource(const char* path) : _file(fopen(path, "r")) {}
    ~UniqueResource() { if (_file) fclose(_file); }

    // Kopiowanie nie ma sensu — dwa obiekty nie mogą "posiadać" tego samego pliku
    UniqueResource(const UniqueResource&) = delete;
    UniqueResource& operator=(const UniqueResource&) = delete;

    // Przenoszenie ma sens — przenosimy własność
    UniqueResource(UniqueResource&& other) noexcept : _file(other._file) {
        other._file = nullptr;
    }
    UniqueResource& operator=(UniqueResource&& other) noexcept {
        if (this != &other) {
            if (_file) fclose(_file);
            _file = other._file;
            other._file = nullptr;
        }
        return *this;
    }
};
```

### Tabela decyzji

| Sytuacja | Destruktor | Kopiujący | Przenoszący |
|---|---|---|---|
| Brak zasobów | nie pisz | nie pisz | nie pisz |
| Deep copy (np. tablica) | `~` usuwa | kopiuj głęboko | "ukradnij" + `= nullptr` |
| Unikalna własność (plik, socket) | `~` zamyka | `= delete` | przenieś + `= nullptr` |
| Obserwator (nie posiada) | nie pisz | domyślny | domyślny |

---

## 6. Double Free — jak powstaje i jak mu zapobiegać

### Jak powstaje double free?

**Przypadek 1 — płytka kopia:**

```cpp
class Zly {
    int* p;
public:
    Zly() : p(new int{42}) {}
    ~Zly() { delete p; }
    // Brak kopiującego → kompilator generuje: Zly(const Zly& o) : p(o.p) {}
};

{
    Zly a;
    Zly b = a;   // b.p == a.p — TEN SAM wskaźnik!
}
// Destruktor b: delete b.p → OK
// Destruktor a: delete a.p → to samo co b.p → DOUBLE FREE → undefined behavior
```

**Przypadek 2 — self-assignment bez guard:**

```cpp
Zly& operator=(const Zly& other) {
    delete p;          // usuwamy stary
    p = other.p;       // kopiujemy wskaźnik
    return *this;
}

Zly a;
a = a;   // this == &other!
         // delete p → p usunięty
         // p = other.p → p = już-usunięty wskaźnik!
         // Destruktor: delete p → DOUBLE FREE (a raczej użycie zwolnionej pamięci)
```

**Przypadek 3 — przenoszenie bez zerowania:**

```cpp
// Zły konstruktor przenoszący:
Zly(Zly&& other) : p(other.p) {
    // BRAK: other.p = nullptr;
}

Zly a;
Zly b = std::move(a);
// Destruktor b: delete b.p → OK
// Destruktor a: delete a.p → to samo co b.p → DOUBLE FREE
```

### Remedium — wzorzec poprawnego zarządzania zasobami

```cpp
class Dobry {
    int* p;
public:
    Dobry() : p(new int{42}) {}

    // 1. Destruktor
    ~Dobry() { delete p; }

    // 2. Konstruktor kopiujący — GŁĘBOKA KOPIA
    Dobry(const Dobry& other) : p(new int{*other.p}) {}
    //                                   ^^^^^^^^^^
    //                                   kopiujemy WARTOŚĆ, nie wskaźnik!

    // 3. operator= — z SELF-ASSIGNMENT GUARD
    Dobry& operator=(const Dobry& other) {
        if (this == &other) return *this;   // guard!
        *p = *other.p;    // kopiujemy wartość (możemy też: delete; p = new...)
        return *this;
    }

    // 4. Konstruktor przenoszący — z ZEROWANIEM
    Dobry(Dobry&& other) noexcept : p(other.p) {
        other.p = nullptr;   // KLUCZOWE — one pointer, one owner
    }

    // 5. Przenoszący operator= — z SELF-ASSIGNMENT GUARD i ZEROWANIEM
    Dobry& operator=(Dobry&& other) noexcept {
        if (this != &other) {      // guard przed self-move
            delete p;              // zwolnij własne zasoby
            p = other.p;           // przejmij cudze
            other.p = nullptr;     // zeruj źródło
        }
        return *this;
    }
};
```

### Reguła złotego wskaźnika

> **Jeden zasób — jeden właściciel.**  
> W danej chwili tylko jeden obiekt powinien "posiadać" (i być odpowiedzialny za zwolnienie) danego zasobu.  
> Przenoszenie = transfer własności. Kopiowanie = tworzenie nowej kopii zasobu.

---

## 7. Operatory konwersji `operator T()`

Pozwalają obiektowi klasy niejawnie (lub jawnie z `explicit`) konwertować się do innego typu.

### Podstawowa składnia

```cpp
class Temperatura {
    double _celsjusz;
public:
    explicit Temperatura(double c) : _celsjusz(c) {}

    // Konwersja do double — zwraca _celsjusz
    operator double() const {
        return _celsjusz;
    }

    // Konwersja do Fahrenheit (jako osobny typ dla przykładu)
    // można też po prostu zwrócić wartość skalowaną
};

Temperatura t{100.0};
double d = t;           // operator double() wywoływany niejawnie
std::cout << d;         // 100.0
std::cout << t + 5.0;   // też działa! t konwertuje się do double
```

### Konwersja do `bool` — najczęstszy przypadek

```cpp
class Plik {
    FILE* _f;
public:
    explicit Plik(const char* path) : _f(fopen(path, "r")) {}
    ~Plik() { if (_f) fclose(_f); }

    // Konwersja do bool — true jeśli plik otwarty poprawnie
    // explicit by uniknąć: int x = plik; (nie chcemy tego!)
    explicit operator bool() const {
        return _f != nullptr;
    }
};

Plik p("dane.txt");
if (p) { ... }            // OK — explicit operator bool w kontekście if działa
bool b = (bool)p;         // OK — jawne rzutowanie
bool b2 = static_cast<bool>(p);  // OK
// int x = p;             // BŁĄD (dzięki explicit) — nie chcemy tego!
// double d = p;          // BŁĄD (dzięki explicit)
```

**Uwaga:** W kontekstach boolean (warunek `if`, `while`, `&&`, `||`, `!`, `?:`) `explicit operator bool()` jest wywoływany automatycznie — to wyjątek od reguły explicit.

### Konwersja z szablonu do konkretnego typu

Wzorzec z zadania `8.cpp` (Box):

```cpp
template <typename T>
struct Box {
    T _val;
    explicit Box(T val) : _val(val) {}

    // Konwersja Box<T> → T
    operator T() const {
        return _val;
    }
};

// Specjalizacja dla Box<Box<T>>
template <typename T>
struct Box<Box<T>> {
    Box<T> _val;

    explicit Box(T val) : _val(val) {}  // przyjmuje T, nie Box<T>!

    // Konwersja Box<Box<T>> → Box<T>
    operator Box<T>() const {
        return _val;
    }
};

Box<int> b1{42};
int x = b1;              // operator int() — niejawna konwersja

Box<Box<int>> bb{42};
Box<int> b2 = bb;        // operator Box<int>() — niejawna konwersja
int y = bb;              // UWAGA: to działa przez łańcuch konwersji:
                         // Box<Box<int>> → Box<int> → int
```

### Niebezpieczeństwo niejawnych konwersji bez `explicit`

```cpp
class Liczba {
    int _val;
public:
    Liczba(int v) : _val(v) {}  // nie-explicit konstruktor
    operator int() const { return _val; }  // nie-explicit konwersja
};

void foo(int x) { std::cout << x; }
void bar(Liczba x) { }

Liczba n{42};
foo(n);      // OK (zamierzony): konwersja Liczba → int
bar(5);      // OK (zamierzony): konwersja int → Liczba (przez konstruktor)

// ALE — zaskakujące zachowanie:
int a = n + n;   // n + n → int + int (oba konwertowane!) = 84
Liczba b = 5;    // konstruktor Liczba(int) wywoływany niejawnie!
if (n == 42) { } // działa bo Liczba → int → porównanie
```

### Łańcuch konwersji — ważna zasada

C++ pozwala na **co najwyżej jedną** niejawną konwersję zdefiniowaną przez użytkownika:

```cpp
struct A { A(int) {} };
struct B { B(A) {} };

void f(B) {}

f(42);    // BŁĄD — wymagałoby int→A→B (dwie konwersje!)
f(A{42}); // OK — jedna konwersja A→B
```

---

## 8. `explicit` — kontrola niejawnych konwersji

### `explicit` przy konstruktorach

Bez `explicit` konstruktor jednoargumentowy staje się "konwerterem" — kompilator może go użyć automatycznie wszędzie gdzie oczekuje się danego typu.

```cpp
class Haslo {
    std::string _s;
public:
    // BEZ explicit:
    Haslo(std::string s) : _s(s) {}
    // Z explicit:
    // explicit Haslo(std::string s) : _s(s) {}
};

void zaloguj(Haslo h) { /* ... */ }

// BEZ explicit — zaskakujące:
zaloguj("tajne123");       // niejawna konwersja string→Haslo — mogło być niezamierzone
std::string s = "tajne";
zaloguj(s);                // też działa — niejawna konwersja

// Z explicit:
zaloguj("tajne123");       // BŁĄD KOMPILACJI — explicit blokuje niejawną
zaloguj(Haslo{"tajne123"}); // OK — jawna konwersja
```

### `explicit` przy konstruktorach smart pointerów

To kluczowy wzorzec, który pojawia się w każdym smart pointerze:

```cpp
template <typename T>
class UniquePtr {
    T* _ptr;
public:
    // BEZ explicit:
    // UniquePtr(T* ptr) : _ptr(ptr) {}
    // To pozwalałoby na:
    // UniquePtr<int> p = new int{42};  // niejawna konwersja int* → UniquePtr<int>
    // To jest NIEBEZPIECZNE — skąd wiemy że ten wskaźnik powinien być zarządzany?

    // Z explicit:
    explicit UniquePtr(T* ptr) : _ptr(ptr) {}
    // UniquePtr<int> p = new int{42};  // BŁĄD — explicit blokuje =
    // UniquePtr<int> p{new int{42}};   // OK — jawne
    // UniquePtr<int> p(new int{42});   // OK — jawne
};
```

### `explicit` przy operatorach konwersji

```cpp
class SmartBool {
    bool _val;
public:
    explicit SmartBool(bool v) : _val(v) {}

    // BEZ explicit — niebezpieczne:
    operator bool() const { return _val; }
    // Pozwala na: int x = smart_bool; (niezamierzone!)
    // Pozwala na: smart_bool + 5 (konwertuje do bool, potem do int = 1+5 = 6!)

    // Z explicit — bezpieczne:
    explicit operator bool() const { return _val; }
    // if (smart_bool) { }  — OK (kontekst bool jest wyjątkiem)
    // int x = smart_bool;  — BŁĄD
};
```

### Różne scenariusze z `explicit`

```cpp
class Vec2 {
public:
    double x, y;

    // explicit na 1-arg konstruktorze
    explicit Vec2(double scalar) : x(scalar), y(scalar) {}

    // non-explicit na 2-arg (nie ma sensu jako konwerter — więc explicit nieistotne)
    Vec2(double x, double y) : x(x), y(y) {}

    // explicit na operatorze konwersji
    explicit operator double() const { return std::sqrt(x*x + y*y); }
};

void draw(Vec2 v) {}

Vec2 a{3.0, 4.0};              // OK — 2-arg konstruktor
Vec2 b{5.0};                   // OK — explicit, ale jawna inicjalizacja
// Vec2 c = 5.0;               // BŁĄD — explicit blokuje "="
draw({1.0, 2.0});              // OK — niejawna inicjalizacja aggregate-style
// draw(5.0);                  // BŁĄD — explicit blokuje niejawną konwersję

double len = (double)a;         // OK — jawne rzutowanie
double len2 = static_cast<double>(a);  // OK — jawne
// double len3 = a;             // BŁĄD — explicit operator double blokuje niejawne
```

### Reguła: kiedy używać `explicit`

| Sytuacja | `explicit`? | Powód |
|---|---|---|
| Konstruktor 1-arg tworzący "wartość" (np. `Temperatura(double)`) | TAK | Nie chcemy niejawnych konwersji liczbowych |
| Konstruktor smart pointera z surowego wskaźnika | TAK | Własność zasobu powinna być jawna |
| Konstruktor z `nullptr_t` | NIE | `p = nullptr;` jest czytelne i pożądane |
| `operator bool()` | TAK | Chroni przed arytmetyką na obiektach |
| `operator double/int()` (wartość liczbowa) | Zależy | Jeśli ryzyko nieoczekiwanej arytmetyki — TAK |
| Konstruktor 2+ arg (nie jest konwerterem) | Bez znaczenia | Kompilator i tak nie użyje go jako konwertera |

---

## Podsumowanie wzorców

### Kompletny wzorzec własnego smart pointera

```
UniquePtr<T>:
  ✓ using value_type = T
  ✓ UniquePtr()                            — nullptr
  ✓ explicit UniquePtr(T*)                 — z surowego wskaźnika
  ✓ ~UniquePtr()                           — delete _ptr
  ✗ UniquePtr(const UniquePtr&) = delete   — zakaz kopiowania
  ✗ operator=(const UniquePtr&) = delete   — zakaz kopiującego przypisania
  ✓ UniquePtr(UniquePtr&&) noexcept        — przenosi + zeruje źródło
  ✓ operator=(UniquePtr&&) noexcept        — guard + zwalnia stare + przenosi + zeruje
  ✓ T& operator*() const                  — dereferencja
  ✓ T* operator->() const                 — dostęp do składowej
  ✓ explicit operator bool() const         — sprawdzenie null
  ✓ T* get() const                         — surowy wskaźnik (bez oddawania własności)
  ✓ T* release()                           — oddanie własności
  ✓ void reset(T* = nullptr)               — reset
```

### Wzorzec template template parameter

```
template <
    typename T = DefaultType,
    template <typename...> class Container = std::deque
>
class MyClass {
    Container<T> _storage;            // kompilator instancjonuje: std::deque<T>
    using storage_type = Container<T>;

    typename storage_type::iterator begin() { return _storage.begin(); }
    //^^^^^^^
    // obowiązkowe — kompilator nie wie czy to typ czy wartość
};
```
