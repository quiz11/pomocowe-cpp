
# ~={orange}Podstawy (wyk. 2 i 3)=~
## **New** i **delete**:
W c++ operacje rezerwacji pamięci wykonuje się za pomocą operatorów new i delete 
- new tworzy nowy obiekt
- delete niszczy stworzony wcześniej obiekt 
Cechy:
- Stworzony obiekt nie posiada nazwy, możemy odwoływać się do niego tylko przez wskaźnik
- Obiekt istnieje od momentu stworzenia do mementu zniszczenia – my decydujemy o tym
- Obiektów nie obowiązują zwykłe zasady ważności – jeśli mamy wskaźnik pokazujący na dany obiekt to mamy również do niego dostęp

```cpp
int *a;
a = new int;
...
delete a;

float *f;
f = new float[100];
...
delete [] f; //stosowane do tablic!!!
```

## **Nazwy:**
- `std::ostream&` - strumień wyjściowy cout (np przy nadpisaniu <<)
- `= delete` - usuwa konstruktor lub metode
- `auto` - deklaruje zmienną automatyczną
- `catch` - łapie wyjątki
- `class` - deklaruje klasę
- `const` - deklaruję zmienna typu stałego
- `const_cast` - rzutowanie uzmienniające stałą
- `delete` - zwalnia pamięć
- `dynamic_cast` - rzutowanie w czasie trwania programu
- `enum` - definiuje typ wyliczeniowy
- `explicit` - w konstruktorze zabrania domyślnych konwersji
- `extern` - definiuje zmienną zewnętrzną
- `friend` - deklaruje przyjaźń
- `goto` - wykonuje skok
- `inline` - wstawia funkcję w linii
- `mutable` - uzmiennia stałą
- `namespace` - przestrzeń nazw
- `new` - alokuje pamięć
- `operator` - tworzy przeładowaną funkcję operatorową
- `private` - deklaruje prywatne składniki i metody klasy
- `protected` - deklaruje zabezpieczone składniki i metody klasy
- `public` - deklaruje publiczne składniki i metody klasy
- `register` - optymalizuje dostęp do zmiennej ze względu na szybkość
- `signed` - określa, że zmienna jest ze znakiem
- `sizeof` - zawraca rozmiar typu lub zmiennej
- `static` - tworzy zmienną która istnieje przez całe wykonywanie się programu
- `static_cast` - operator rzutowanie
- `struct` - tworzy strukturę
- `switch` - wykonuje kod zależny od danej zmiennej
- `template` - tworzy szablon
- `this` - wskaźnik do obecnie używanego obiektu
- `throw` - wyrzuca wyjątek
- `try` - wykonuje kod który może wyrzucić wyjątek
- `typedef` - tworzy synonim do istniejącego typu
- `typeid` - opisuje typ obiektu
- `typename` - w szablonach oznacza że następujący po nim symbol reprezentuje typ (synonim class)
- `union` - tworzy unię
- `unsigned` - deklaruje zmienną bez znaku (np `unsigned int` to liczby dodatnie całkowite)
- `using` - używa przestrzeni nazw
- `virtual` - tworzy funkcję wirtualną
- `volatile` - ostrzega kompilator że zmienna może zostać zmodyfikowana nieoczekiwanie
- `wchar_t` - deklaruje "szeroką" zmienną znakową
- `while` - pętla z wyrażeniem warunkowym
## Typ wyliczeniowy (`enum` - enumeration)

* **Osobny typ całkowity** – pod spodem kompilator traktuje wartości `enum` jako liczby całkowite.
* **Organizowanie informacji** – jest bardzo przydatny, jeśli potrzebujemy w programie przechowywać określony, skończony rodzaj informacji (np. stany aplikacji, dni tygodnia, kolory).
* **Bezpieczeństwo kodu** – wielką zaletą stosowania `enum` jest to, że kompilator „pilnuje”, czy przekazujemy do funkcji poprawny argument (zapobiega to wpisywaniu przypadkowych liczb).

```cpp
enum status {
    start = 0,
    stop = 1,
    error = -1
};
```

```cpp
// Definiujemy stany, w jakich może znajdować się nasza gra
enum GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

// Funkcja, która wykonuje odpowiednie operacje w zależności od stanu
void aktualizujEkran(GameState stan) {
    switch (stan) {
        case MENU:
            break;
        case PLAYING:
            break;
        case PAUSED:
            break;
        case GAME_OVER:
            break;
    }
}

int main() {
    // Kompilator pilnuje, żebyśmy przypisali tylko wartość z GameState
    GameState obecnyStan = MENU;
    
    aktualizujEkran(obecnyStan); // Wypisze: Wyświetlam menu główne...
    // Gracz klika "Start" -> zmieniamy stan
    obecnyStan = PLAYING;
    aktualizujEkran(obecnyStan);
    // Próba przypisania dziwnej wartości (np. obecnyStan = 15;) 
    // skończy się błędem kompilacji. Kompilator nas pilnuje!
    return 0;
}
```

## Modyfikatory zmiennych w C++

### 1. `const` (Stała)

* **Niezmienność** – Obiekty z tym modyfikatorem nie mogą być zmieniane w programie po ich utworzeniu.
* **Inicjalizacja** – Obiekty typu `const` **można (i trzeba) zainicjalizować** w momencie tworzenia, ale później nie można już do nich nic przypisać.

```cpp
const float pi = 3.14159; // Poprawna inicjalizacja stałej
pi = 10;                  // BŁĄD KOMPILACJI! Próba modyfikacji wartości stałej
```

### 2. `register` 
- **Umieszczanie zmiennej w rejestrze** – szybszy dostęp
- **Brak adresu w pamięci** – Ponieważ zmienna ma docelowo znajdować się w rejestrze, **nie można uzyskać adresu takiej zmiennej** (za pomocą operatora `&`). Jeśli spróbujesz pobrać jej adres, kompilator automatycznie przeniesie ją do zwykłej pamięci RAM.

### 3. `mutable`

* **Uzmiennienie stałej** – Słowo kluczowe `mutable` pozwala na modyfikację pola klasy nawet wtedy, gdy cały obiekt tej klasy został oznaczony jako stały (`const`), lub gdy modyfikacja odbywa się wewnątrz metody stałej (`const`).
* **Zastosowanie** – Jest niezwykle przydatne podczas projektowania klas, gdy pewne wewnętrzne dane (np. liczniki, pamięć podręczna/cache) nie zmieniają logicznego stanu obiektu, ale muszą być aktualizowane.
#### Przykład zastosowania: Licznik wywołań (Debugging / Statystyki)

Wyobraź sobie klasę, która przechowuje dane użytkownika. Chcesz mieć stały obiekt tej klasy (żeby nikt nie zmienił imienia), ale jednocześnie chcesz zliczać, ile razy pobrano to imię. Bez `mutable` byłoby to niemożliwe.

```cpp
#include <iostream>
#include <string>
class ProfilUzytkownika {
private:
    std::string imie;
    // Pole logicznie nie zmienia obiektu, służy tylko do statystyk
    mutable int licznikWyswietlen; 

public:
    ProfilUzytkownika(std::string p_imie) : imie(p_imie), licznikWyswietlen(0) {}

    // Metoda jest stała (const) - gwarantuje, że nie zmieni 'imie'
    std::string pobierzImie() const {
        licznikWyswietlen++; // Działa TYLKO dzięki słowu 'mutable'!
        return imie;
    }

    int pobierzLiczbeWyswietlen() const {
        return licznikWyswietlen;
    }
};

int main() {
    // Tworzymy STAŁY obiekt - nie możemy zmienić danych użytkownika
    const ProfilUzytkownika uzytkownik("Jan");

    // uzytkownik.pobierzImie(); -> wywołanie metody const
    std::cout << "Uzytkownik: " << uzytkownik.pobierzImie() << "\n";
    std::cout << "Uzytkownik: " << uzytkownik.pobierzImie() << "\n";

    // Sprawdzamy licznik, który zmienił się mimo stałości obiektu
    std::cout << "Profil wyswietlono: " << uzytkownik.pobierzLiczbeWyswietlen() << " razy.\n";

    return 0;
}
```

### `auto` i `static` (Czas życia i inicjalizacja)

**Podział domyślny:** Obiekty globalne są domyślnie typu `static` (statyczne), a obiekty lokalne typu `auto` (automatyczne).

- **Zmienne automatyczne (`auto`):** Tworzone na stosie w momencie wywołania funkcji i niszczone przy jej opuszczeniu.
	- **Ważne:** Należy najpierw coś do nich zapisać, a dopiero potem czytać. **Nie są automatycznie zerowane** – zawierają przypadkowe śmieci z pamięci!

- **Zmienne statyczne (`static`):** Istnieją przez cały czas działania programu.
    - Są **automatycznie zerowane** przed uruchomieniem programu.

- **Lokalne zmienne statyczne:** ~={9}Obiekty lokalne (wewnątrz funkcji) również można zadeklarować jako statyczne. Służy to m.in. do **zapamiętania wartości zmiennej przy kolejnym wywołaniu funkcji**.=~

## Instrukcja `typedef` (Tworzenie aliasów typów)

- **Tworzenie synonimów:** Pozwala na nadanie dodatkowej, własnej nazwy (aliasu) dla już istniejącego typu danych. **Nie tworzymy nowego typu**, a jedynie alternatywną nazwę dla starego.
- **Przykładowa składnia:**
````cpp
typedef float press; // Od teraz 'press' oznacza dokładnie to samo co 'float'
press a, b, c;       // Deklaracja trzech zmiennych typu float
````

### Zastosowanie w praktyce
Poza ułatwieniem zmian typów, `typedef` drastycznie poprawia czytelność kodu przy skomplikowanych strukturach danych.
#### Przykład 1: Skracanie potwornych nazw typów
Zamiast pisać za każdym razem długie nazwy kontenerów, możemy je skrócić:
```cpp
#include <iostream>
#include <vector>
#include <string>

// Zamiast pisać cały ten długi typ, tworzymy krótki synonim:
typedef std::vector<std::string> ListaSlow;

int main() {
    // Bardzo czytelna i szybka deklaracja:
    ListaSlow mojeMenu = {"Start", "Opcje", "Wyjscie"};
    
    for(const auto& opcja : mojeMenu) {
        std::cout << opcja << "\n";
    }
    
    return 0;
}
```

**Współczesna uwaga (C++11 i nowsze):** Choć `typedef` jest wciąż powszechnie używany i w pełni poprawny, w nowoczesnym C++ częściej stosuje się słowo kluczowe `using`, które robi dokładnie to samo, ale ma bardziej intuicyjną składnię (podobną do przypisywania wartości do zmiennej): 

```cpp
using press = float; // Nowoczesny odpowiednik: typedef float press;
using ListaSlow = std::vector<std::string>;
```

## Operatory
### Bitowe:
- `<<` - przesunięcie w lewo
- `>>` - przesunięcie w prawo
- `|` - suma bitowa (OR)
- `&` - iloczyn bitowy (AND)
- `^` - różnica symetryczna bitów (XOR)
- `~` - negacja bitów (Not)
### Przypisania:
- `+=`
- `-=`
- `*=`
- `/=`
- `%=`
- `>>=`
- `<<=`
- `&=`
- `|=`
- `^=`

### `sizeof(nazwa)`
**Zastosowanie:** Podaje wielkość w bajtach, jaką dany typ lub zmienna zajmuje w pamięci RAM.
**Uniwersalność:** Działa zarówno dla typów wbudowanych (np. `int`, `double`), jak i struktur czy klas zdefiniowanych samodzielnie przez programistę.

```cpp
int liczba = 10;
std::cout << sizeof(int);    // Zazwyczaj wypisze: 4 (bajty)
std::cout << sizeof(liczba); // Równieź wypisze: 4
```

### Rzutowania znane z języka C (niezalecane)

**Składnia:** `(nazwa_typu)obiekt`
**Działanie:** Wymusza na kompilatorze zmianę typu jednej zmiennej na inny (np. ucięcie części ułamkowej liczby).

**Dlaczego są niezalecane w C++?** Rzutowania w stylu C są brutalne – wyłączają kontrolę typów kompilatora, co łatwo prowadzi do trudnych do wykrycia błędów w pamięci. W C++ powinno się zamiast tego używać bezpieczniejszych operatorów rzutowania: `static_cast`, `dynamic_cast`, `const_cast` lub `reinterpret_cast`.

```cpp
double pi = 3.14;
int tylkoCalkowita = (int)pi; // Rzutowanie w stylu C -> obcina do 3
int bezpieczniej = static_cast<int>(pi); // Preferowany styl C++
```

### Przecinek `,` (Operator sekwencji)

**Działanie:** Stosowany do połączenia kilku wyrażeń stojących obok siebie, które mają zostać wykonane po kolei od lewej do prawej.

**Wartość zwracana:** Całość jest traktowana jako jedno duże wyrażenie, a jego końcową wartością jest wynik **najbardziej z prawej strony**.

```cpp
int x = 0;
// Wykona się x++, potem x + 5, a na koniec wynik (6) zostanie przypisany do y
int y = (x++, x + 5); 

std::cout << x; // Wypisze: 1 (bo x++ się wykonało)
std::cout << y; // Wypisze: 6 (wynik ostatniego wyrażenia)
```

_Najczęstsze sensowne zastosowanie to upchnięcie kilku operacji inkrementacji w pętli `for`, np. `for(int i=0, j=10; i < j; i++, j--)`._

### Wyrażenie warunkowe (Operator trójargumentowy)

**Składnia:** `warunek ? wartość_jeśli_prawda : wartość_jeśli_fałsz;`

**Działanie:** Skrócona, jedno-linijkowa wersja instrukcji warunkowej `if-else`, która zwraca konkretną wartość.

```cpp
int x = 10;
int y = 5;

// Czy x jest większe od y? Jeśli tak, zwróć 1, jeśli nie, zwróć 0
int wynik = (x > y) ? 1 : 0; // wynik wyniesie 1
```

##  `switch`

**Ograniczenie typu danych (Kluczowe!):** Wyrażenie `wyr` podawane w nawiasie instrukcji `switch` **może ~={9}być tylko typu `int`** (lub typów, które dają się niejawnie rzutować na `int`, takich jak `char` czy `enum`)=~. Nie można tam bezpośrednio sprawdzać np. napisów `std::string` ani liczb zmiennoprzecinkowych `float`/`double`.

```cpp
switch (wyr) 
{
    case wart1:
        inst1;
		break;
    case wart2:
        inst2; 
        break;
    default:
        inst3;
        break;
}
```

## Przekazywanie argumentów

### 1. Przekazywanie przez wartość (By Value)

Funkcja otrzymuje **kopię** oryginalnej zmiennej. Wszelkie operacje wykonywane wewnątrz funkcji dzieją się na kopii i nie wpływają na zmienną w miejscu wywołania.

- **Wada:** Koszt wydajnościowy – przy dużych obiektach (np. wielkich strukturach czy wektorach) kopiowanie całej zawartości pamięci spowalnia program. 

```cpp
#include <iostream>

void zmienWartosc(int liczba) {
    liczba = 999; // Zmieniamy tylko lokalną kopię
}

int main() {
    int x = 10;
    zmienWartosc(x);
    std::cout << x; // Wypisze: 10 (oryginał się nie zmienił)
    return 0;
}
```

### 2. Przekazywanie przez wskaźnik (By Pointer)

Funkcja otrzymuje adres pamięci, pod którym znajduje się oryginalna zmienna. Za pomocą operatora dereferencji `*` funkcja może bezpośrednio modyfikować oryginał. Jest to styl odziedziczony z języka C.

- **Zaleta:** Brak kopiowania obiektu, możliwość zmiany oryginału. Wskaźnik może przyjąć wartość `nullptr` (brak obiektu).
- **Wada:** Mało czytelna składnia (`*` i `&`) oraz ryzyko błędów (np. próba użycia wskaźnika wskazującego na nieistniejący adres).

```cpp
#include <iostream>

void zmienWartosc(int* wskaźnik) {
    if (wskaźnik != nullptr) {
        *wskaźnik = 999; // Modyfikujemy wartość pod adresem
    }
}

int main() {
    int x = 10;
    zmienWartosc(&x); // Przekazujemy adres zmiennej x za pomocą &
    std::cout << x;   // Wypisze: 999 (oryginał został zmieniony)
    return 0;
}
```

### 3. Przekazywanie przez referencję (By Reference)

Funkcja otrzymuje „alias” (drugą nazwę) oryginalnej zmiennej. Kod wewnątrz funkcji wygląda identycznie jak przy pracy ze zwykłą zmienną, ale każda operacja modyfikuje bezpośrednio zmienną oryginalną.

- **Zaleta:** Brak kopiowania (tak jak wskaźnik) przy jednoczesnym zachowaniu czystej, eleganckiej składni (bez gwiazdek). Referencja **musi** zawsze wskazywać na poprawny obiekt (nie może być pusta jak `nullptr`).    
- **Wada:** Funkcja ma pełny dostęp do modyfikacji zmiennej, co czasem może być niepożądane.

```cpp
#include <iostream>

void zmienWartosc(int& referencja) {
    referencja = 999; // Pracujemy bezpośrednio na oryginale
}

int main() {
    int x = 10;
    zmienWartosc(x); // Składnia wywołania jest czysta, bez żadnych operatorów
    std::cout << x;  // Wypisze: 999 (oryginał został zmieniony)
    return 0;
}
```

### Formy zaawansowane (Dobry nawyk w C++)

W codziennej pracy z C++ bardzo często łączy się referencję z modyfikatorem `const`. Tworzy to tzw. **przekazywanie przez stałą referencję** (`const T&`).

Gwarantuje to najwyższą wydajność (brak kopiowania obiektu) przy jednoczesnym zablokowaniu możliwości edycji (bezpieczeństwo):

```cpp
#include <string>
#include <vector>

// Obiekt std::vector potrafi być gigantyczny. 
// Dzięki 'const &' funkcja działa błyskawicznie i nie ma prawa niczego w nim zmienić.
void wyswietlDane(const std::vector<std::string>& duzaLista) {
    // duzaLista.push_back("test"); -> BŁĄD KOMPILACJI (obiekt jest const)
}
```

### Podsumowanie ściągawka:

- **Typy proste (`int`, `char`, `float`):** Przekazuj przez **wartość** (kopiowanie jest tak tanie, że nie ma sensu kombinować).

- **Obiekty, klasy, struktury (`std::string`, `std::vector`):** Przekazuj przez **stałą referencję** (`const T&`), chyba że funkcja ma za zadanie je zmodyfikować – wtedy przez zwykłą referencję (`T&`).

## Funkcje `inline` (Funkcje rozwijane w miejscu wywołania)

- **Zastosowanie:** Stosuje się je do bardzo krótkich funkcji (posiadających małą liczbę instrukcji). Ma to na celu **przyspieszenie działania programu**, eliminując narzut związany z tradycyjnym wywołaniem funkcji (czyli m.in. odkładaniem danych na stos, skokiem procesora pod inny adres pamięci i powrotem).
  
- **Kiedy zyskujesz najwięcej?** W szczególności przy wielokrotnym, masowym wywoływaniu danej funkcji (np. wewnątrz pętli wykonującej się miliony razy).
  
- **Kluczowy wymóg formalny:** Funkcje typu `inline` **muszą być od razu zdefiniowane** (czyli musisz od razu podać całe ich ciało w klamrach `{}`, a nie tylko sam prototyp/deklarację). Najczęściej umieszcza się je bezpośrednio w plikach nagłówkowych (`.h` / `.hpp`).

Słowo kluczowe `inline` to **sugestia dla kompilatora**, aby w każdym miejscu, gdzie użyjesz tej funkcji, fizycznie "wkleił" jej zawartość bezpośrednio do kodu źródłowego przed kompilacją.

```cpp
#include <iostream>

// Definicja funkcji inline - musi być od razu pełna!
inline int zao(float liczba) {
    return (liczba + 0.5);
}

int main() {
    float x = 4.3;
    
    // Dla kompilatora ten zapis:
    int wynik = zao(x);
    
    // ...zostanie pod maską zamieniony bezpośrednio na:
    // int wynik = (x + 0.5);
    
    std::cout << wynik; // Wypisze: 4
    return 0;
}
```

## Przeładowanie funkcji a argumenty domniemane (domyślne)

- **Przeładowanie funkcji (Overloading):** Tworzenie kilku funkcji o tej samej nazwie, ale z inną listą argumentów (różne typy lub ich liczba). Kompilator sam decyduje, którą funkcję wywołać na podstawie przekazanych wartości.

- **Argumenty domniemane (Default arguments):** Pozwalają na przypisanie domyślnej wartości dla argumentu (np. `float = 0`), dzięki czemu użytkownik może, ale nie musi podawać tego parametru przy wywołaniu.

```cpp
void fun(float);            // Wersja 1: Przyjmuje jeden float
void fun(char);             // Wersja 2: Przyjmuje jeden znak
void fun(int, float = 0);   // Wersja 3: Przyjmuje int oraz opcjonalny float (domyślnie 0)
```
### Przykłady wywołań:

- `fun(1.1);` $\rightarrow$ Wywoła **Wersję 1** (`fun(float)`), ponieważ podano liczbę zmiennoprzecinkową.

- `fun('A');` $\rightarrow$ Wywoła **Wersję 2** (`fun(char)`), ponieważ podano znak w apostrofach.

- `fun(2);` $\rightarrow$ Wywoła **Wersję 3** (`fun(int, float = 0)`). Przekazano tylko jedną liczbę całkowitą, więc drugi parametr przyjmie domyślną wartość `0`.

- `fun(2, 2.2);` $\rightarrow$ Wywoła **Wersję 3** (`fun(int, float)`), nadpisując domyślne zero wartością `2.2`.
  
### Pułapka i konflikt (Niejednoznaczność / Ambiguity)

Slajd zwraca uwagę na kluczowy problem: **Dlaczego w tym zestawie nie może istnieć funkcja `void fun(int);`?**

Jeśli dopiszemy taką funkcję, a następnie w kodzie wywołamy:

```cpp
fun(2); // Kompilator zgłasza BŁĄD!
```

Kompilator znajdzie się w sytuacji patowej i nie będzie wiedział, co ma zrobić (nastąpi tzw. _ambiguous call_):

1. Z jednej strony idealnie pasuje nowa funkcja `void fun(int);`.
   
2. Z drugiej strony idealnie pasuje wersja `void fun(int, float = 0);`, w której pominięto drugi argument.

# ~={orange}Klasy (wyk. 4)=~

## Wskaźnik `this` w C++

Wskaźnik `this` to ukryty, specjalny wskaźnik dostępny **wewnątrz każdej nienatycznej metody klasy**. Pokazuje on bezpośrednio na **ten konkretny obiekt (instancję klasy)**, na rzecz którego metoda została aktualnie wywołana.
### 1. Po co w ogóle istnieje `this`? (Zagadka pamięciowa)

Wyobraź sobie, że tworzysz klasę `Punkt` i powołujesz do życia trzy osobne obiekty (np. `p1`, `p2`, `p3`). Każdy z nich ma swoje własne, unikalne zmienne w pamięci RAM (własne współrzędne `x` oraz `y`).

Jednak kod funkcji składowej (np. `Set(...)`) **jest umieszczany w pamięci komputera tylko raz**, aby nie marnować pamięci RAM na kopiowanie tego samego kodu maszynowego.

Skoro kod funkcji jest jeden, to skąd funkcja w trakcie działania programu wie, że ma zmienić `x` należące do obiektu `p1`, a nie do `p2`?

**Odpowiedź ze slajdu:** Kompilator pod maską "oszukuje" i po cichu przekazuje do wnętrza funkcji dodatkowy, niewidzialny argument – właśnie wskaźnik `this` zawierający adres obiektu, który wywołał funkcję.
### 2. Czym `this` różni się od zapisu `obiekt.zmienna`?

Kluczowa różnica polega na **miejscu (kontekście)**, w którym piszesz swój kod.
- **Zapis `obiekt.zmienna` (Zewnętrzny):** Stosujesz go **poza klasą** (np. w funkcji `main`), kiedy masz w ręku konkretną zmienną obiektową i chcesz dobrać się do jej publicznych pól lub metod za pomocą operatora kropki `.`.

- **Zapis `this->zmienna` (Wewnętrzny):** Stosujesz go **wewnątrz metod klasy**. Wewnątrz klasy obiekt nie zna swojej własnej nazwy z funkcji `main` (nie wie, czy nazywa się `p1` czy `p2`). Zna siebie samego wyłącznie jako `this`. Ponieważ `this` jest wskaźnikiem (adresem), do pól dobieramy się operatorem strzałki `->`, a nie kropki.

### Porównanie w kodzie:

```cpp
class Punkt {
public:
    float x;
    float y;

    void zeruj() {
        // JESTEŚMY WEWNĄTRZ KLASY:
        this->x = 0; // 'this->' wskazuje na obiekt, który nas wywołał
    }
};

int main() {
    // JESTEŚMY POZA KLASĄ:
    Punkt p1; 
    p1.x = 10;   // Używamy kropki, bo mamy jawną nazwę obiektu 'p1'
    p1.zeruj();  // Pod maską kompilator zamienia to na: zeruj(&p1); -> 'this' w środku to adres p1
}
```

### 3. Kiedy musimy jawnie użyć `this`?

Zazwyczaj kompilator sam domyślnie domyśla się, o co chodzi i nie trzeba pisać `this->`. Zapis `x = 5;` wewnątrz klasy automatycznie oznacza `this->x = 5;`.
Istnieje jednak jeden kluczowy moment, w którym **musisz** go użyć: **konflikt nazw (zasłanianie pól)**. Zjawisko to występuje, gdy argumenty przekazywane do funkcji nazywają się dokładnie tak samo, jak pola w Twojej klasie:

```cpp
void Punkt::Set(float x, float y) 
{
    // x = x; // GŁUPI BŁĄD! Przypisujesz lokalny argument do samego siebie. Pole klasy nie drgnie.
    
    this->x = x; // JAWNE ROZRÓŻNIENIE:
    this->y = y; // 'this->x' to pole w klasie, a samo 'x' to argument z nawiasu.
}
```
### 4. Ważna cecha wskaźnika `this`

Oznacza to, że jest on stałym wskaźnikiem (dokładniej: `T* const`). Możesz za jego pomocą bez problemu modyfikować wartości pól obiektu (`this->x = 5;`), ale **nie możesz zmienić samego adresu, na który ten wskaźnik patrzy**. Próba wykonania operacji typu `this = nullptr;` lub przestawienia go na inny obiekt skończy się natychmiastowym błędem kompilacji.

Ten slajd tłumaczy pojęcie **składnika statycznego** (zmiennej statycznej klasy) w programowaniu obiektowym w C++.

Najprościej mówiąc: o ile zwykłe zmienne w klasie należą do konkretnego obiektu (każdy obiekt ma swoją kopię), o tyle **składnik statyczny należy do całej klasy jako ogółu i jest współdzielony przez wszystkie obiekty**.

Oto szczegółowe rozbicie informacji ze slajdu na zrozumiałe porcje:

## `static`

- **Jedna dana dla wszystkich:** Zmienna statyczna istnieje w pamięci RAM **tylko w jednym egzemplarzu**. Jeśli zmienisz jej wartość w jednym obiekcie, zmieni się ona automatycznie we wszystkich pozostałych.
    
- **Niezależność od obiektów:** Ta zmienna rodzi się w pamięci, zanim w ogóle utworzysz jakikolwiek obiekt tej klasy, i istnieje nawet wtedy, gdy nie powołasz do życia ani jednego obiektu.
    
- **Koniec z potworkami globalnymi:** Zamiast tworzyć niebezpieczne zmienne globalne (dostępne dla każdego z każdego miejsca w programie), zamykasz taką zmienną wewnątrz klasy. Daje to porządek i bezpieczeństwo.

### 1. Deklaracja i specyficzny wymóg C++ (Definicja)

Składnik statyczny deklarujesz wewnątrz klasy przy użyciu słowa `static`:

```cpp
class Przedmiot {
public:
    static int licznikPrzedmiotow; // DEKLARACJA - mówimy kompilatorowi, że taka zmienna istnieje
};
```

Samo napisanie `static int` wewnątrz klasy to za mało. Kompilator C++ musi wiedzieć, gdzie fizycznie w pamięci zarezerwować na to miejsce. Dlatego **musisz** napisać tzw. definicję poza klasą (najczęściej w pliku `.cpp`):

```cpp
// DEFINICJA w zakresie pliku (poza klasą):
int Przedmiot::licznikPrzedmiotow = 0; 
```

- **Prywatne zmienne statyczne:** Slajd wspomina, że zmienna statyczna może być prywatna (`private`). Wtedy inicjalizujesz ją dokładnie tak samo (poza klasą w zakresie pliku), ale w dalszej części programu dostęp do niej będą miały już wyłącznie metody z wnętrza tej klasy.

### 2. Jak się do tego odwołać? (Sposoby użycia)
Slajd wymienia trzy metody, ale jedna z nich jest najważniejsza:

1. `klasa::skladnik` $\rightarrow$ **Najczęstszy i preferowany sposób.** Ponieważ zmienna należy do klasy, odwołujesz się do niej po prostu za pomocą nazwy klasy i operatora zasięgu `::`. Nie potrzebujesz do tego żadnego obiektu!
   
2. `obiekt.skladnik` $\rightarrow$ Działa, ale jest mylące, bo sugeruje, że dana cecha należy tylko do tego jednego obiektu.
   
3. `wskaznik->skladnik` $\rightarrow$ Działa analogicznie jak z obiektem, ale przez wskaźnik.

### Sensowny przykład: Globalny licznik obiektów

Wyobraź sobie, że chcesz kontrolować, ile obiektów danej klasy aktualnie istnieje w grze (np. ile potworów żyje na mapie). Zwykła zmienna nie zda egzaminu, ale `static` sprawdzi się idealnie:

```cpp
#include <iostream>

class Potwor {
public:
    // Deklaracja zmiennej statycznej współdzielonej przez wszystkie potwory
    static int iloscZywych;

    Potwor() {
        iloscZywych++; // Gdy rodzi się potwór, zwiększamy wspólny licznik
    }
    ~Potwor() {
        iloscZywych--; // Gdy potwór ginie, zmniejszamy wspólny licznik
    }
};

// Obowiązkowa definicja poza klasą
int Potwor::iloscZywych = 0;

int main() {
    std::cout << "Na start: " << Potwor::iloscZywych << "\n"; // Wypisze: 0

    Potwor *p1 = new Potwor();
    Potwor *p2 = new Potwor();

    // Odwołujemy się elegancko przez nazwę klasy Potwor::
    std::cout << "Po stworzeniu: " << Potwor::iloscZywych << "\n"; // Wypisze: 2

    delete p1; // Jeden potwór ginie
    std::cout << "Po zabiciu jednego: " << Potwor::iloscZywych << "\n"; // Wypisze: 1

    delete p2;
    return 0;
}
```

### Modern C++ ratuje sytuację: Słowo kluczowe `inline` (od C++17)

Jeżeli denerwuje Cię konieczność pisania definicji poza klasą, współczesny standard C++17 przyniósł genialne rozwiązanie. Możesz dodać słowo kluczowe **`inline`** bezpośrednio wewnątrz klasy.
Wtedy definicja poza klasą **nie jest już potrzebna**:

```cpp
class Potwor {
public:
    // Dzięki 'inline' kompilator sam zajmie się rezerwacją pamięci 
    // i inicjalizacją zmiennej w odpowiednim miejscu pod maską!
    inline static int iloscZywych = 0; 
};

int main() {
    // Kod działa od strzała, bez żadnego dopisywania linijek poza klasą!
    Potwor::iloscZywych = 5; 
    return 0;
}
```

## Statyczna funkcja składowa (Metoda statyczna klasy)

Skoro wiemy już, czym jest zmienna statyczna, czas na **funkcję statyczną**. To funkcja umieszczona wewnątrz klasy, która – podobnie jak zmienna statyczna – **należy do całej klasy, a nie do konkretnego obiektu**.
### 1. Do czego służy i jak ją wywołać?

- **Główny cel:** Wykorzystuje się ją przede wszystkim do operowania na składowych statycznych (zmiennych statycznych) tej samej klasy.

- **Wywołanie bez obiektu:** Możesz ją wywołać na rzecz konkretnego obiektu, ale **przede wszystkim wywołuje się ją bezpośrednio na rzecz samej klasy** (używając operatora `::`), bez potrzeby tworzenia jakichkolwiek obiektów.

```cpp
// Wywołanie bez powoływania żadnego obiektu do życia:
NazwaKlasy::funkcjaStatyczna();
```

### 2. Dwa krytyczne ograniczenia metod statycznych (Kluczowe!)

- **Brak wskaźnika `this`:** Ponieważ funkcja statyczna może być wywołana bez żadnego obiektu (z poziomu samej klasy), kompilator **nie wysyła do niej wskaźnika `this`**. Ta funkcja po prostu nie wie, na rzecz jakiego obiektu miałaby działać.
 
- **Zakaz używania nie-statycznych składowych:** Konsekwencją braku `this` jest to, że **z wnętrza funkcji statycznej nie możesz odwołać się do zwykłych pól i metod klasy**.

 💡 **Prosta analogia:** Wyobraź sobie klasę `Czlowiek`. Zwykłe pole to `wzrost` (każdy ma swój własny). Statyczne pole to `srednia_dlugosc_zycia` (jedna wspólna dana dla całej ludzkości).
 
 - Statyczna funkcja `pobierzSredniaDlugoscZycia()` może działać w pustym pokoju bez żadnego człowieka – po prostu zwraca ogólną daną.

 - Gdybyś spróbował w tej funkcji zapytać o `wzrost`, kompilator zapyta: _"Ale czyj wzrost? Przecież nie podano mi żadnego konkretnego człowieka!"_. Dlatego to wygeneruje błąd. 

### Sensowny przykład w kodzie

Nawiążmy do naszego wcześniejszego licznika potworów. Chcemy sprawdzić, ile potworów żyje, ale w bezpieczny sposób (gdy licznik jest prywatny).

```cpp
#include <iostream>

class Potwor {
private:
    inline static int iloscZywych = 0; // Prywatna zmienna statyczna
    int zdrowie = 100;                 // Zwykła, nie-statyczna zmienna

public:
    Potwor() { iloscZywych++; }

    // STATYCZNA FUNKCJA SKŁADOWA
    static int pobierzIloscZywych() {
        // zdrowie = 50; // BŁĄD KOMPILACJI! Nie-statyczne pole 'zdrowie' wymaga obiektu!
        return iloscZywych; // POPRAWNIE: Może operować na statycznym polu
    }
};

int main() {
    // Nie mamy na mapie ani jednego potwora, a funkcja już działa!
    std::cout << "Zywe potwory: " << Potwor::pobierzIloscZywych() << "\n"; // Wypisze: 0

    Potwor p1;
    Potwor p2;

    std::cout << "Po spawnie: " << Potwor::pobierzIloscZywych() << "\n"; // Wypisze: 2
    return 0;
}
```

### 3. Zastępstwo dla funkcji z języka C

Ostatni punkt slajdu mówi, że funkcje statyczne zastępują funkcje globalne znane z języka C. W czystym programowaniu obiektowym stara się unikać "luźnych" funkcji globalnych pływających w projekcie bez żadnej kontroli. Jeśli jakaś funkcja narzędziowa logicznie wiąże się z danym tematem (np. funkcje matematyczne), zamyka się je jako funkcje statyczne wewnątrz dedykowanej klasy.

Doskonałym przykładem z biblioteki standardowej (choćby w Java czy C#) lub bibliotek matematycznych C++ są klasy typu `Math`:

```cpp
// Zamiast luźnej funkcji globalnej, mamy elegancko zamkniętą metodę statyczną:
double wynik = Math::sin(3.14); 
```

## Funkcje składowe typu `const` (Metody tylko do odczytu)

Modyfikator `const` dopisany na końcu deklaracji metody to kontrakt z kompilatorem. Oznacza on, że dana operacja ma charakter wyłącznie **obserwacyjny** – pobiera informacje z wnętrza obiektu, ale nie wprowadza w nim absolutnie żadnych modyfikacji.

### 1. Istota i zasada działania bezpiecznych metod

Kiedy oznaczasz metodę słowem `const`, dajesz gwarancję, że nie zmieni ona stanu zmiennych instancyjnych. Próba przypisania nowej wartości do jakiegokolwiek pola wewnątrz takiego kodu wygeneruje natychmiastowy błąd na etapie budowania programu.

- **Wyjątek od reguły:** Wyjątkiem są zmienne oznaczone słowem kluczowym `mutable`. Jeśli pole klasy posiada ten modyfikator, wolno je edytować nawet wewnątrz teoretycznie zablokowanej metody stałej (przydatne np. do prowadzenia wewnętrznych liczników odwiedzin czy obsługi pamięci podręcznej).
### 2. Praca z niezmiennymi obiektami

W programowaniu bardzo często tworzy się obiekty, których stan ma pozostać nienaruszony przez cały czas ich życia. Jeśli zadeklarujesz instancję jako stałą:

C++

```
const Samochod mojAuto("Czarny");
```

Kompilator nakłada na nią całkowitą blokadę ochronną. Na rzecz tak utworzonego obiektu **możesz wywołać wyłącznie te metody, które na samym końcu swojej definicji posiadają słowo `const`**. Gdyby program pozwolił na uruchomienie zwykłej metody, istniałoby ryzyko, że zmodyfikuje ona zablokowane dane.

### 3. Poprawny zapis w kodzie

Słowo kluczowe `const` musi znaleźć się na samym końcu sygnatury metody – zaraz po nawiasach z parametrami, a przed klamrą otwierającą ciało funkcji:

```cpp
class KontoBankowe {
private:
    double saldo;

public:
    // Ta metoda TYLKO zwraca wartość, nie modyfikuje jej -> dopisujemy const
    double pobierzSaldo() const {
        // saldo = 1000000; // BŁĄD! Kompilator na to nie pozwoli
        return saldo;
    }

    // Ta metoda zmienia stan konta -> NIE MOŻE mieć const
    void wplacPieniadze(double kwota) {
        saldo += kwota;
    }
};
```

### 4. Specjalne traktowanie cyklu życia obiektu

Bardzo ważną regułą konstrukcyjną jest to, że **konstruktory oraz destruktory pod żadnym pozorem nie mogą być oznaczone jako `const`**.

Dlaczego ma to sens?

- **Konstruktor** ze swojej natury służy do narodzin obiektu i ustawienia jego początkowych wartości (czyli fizycznie zapisuje i modyfikuje czystą pamięć). Blokada `const` uniemożliwiłaby jego działanie.
    
- **Destruktor** odpowiada za proces niszczenia, czyszczenia zasobów i zamykania wskaźników, co również bezpośrednio wpływa na strukturę obiektu tuż przed jego usunięciem z RAM-u.

## Funkcje zaprzyjaźnione `friend`

Specjalny mechanizm w C++, który pozwala złamać podstawową zasadę hermetyzacji (ukrywania danych). Dają one wybranej, zewnętrznej funkcji pełny wgląd we wszystkie prywatne (`private`) i chronione (`protected`) zakamarki klasy.

### 1. Kim jest "przyjaciel" klasy?

- **Pełne uprawnienia:** Funkcja zaprzyjaźniona to zewnętrzna funkcja, która **nie należy do klasy** (nie jest jej metodą składową), ale ma prawo czytać i modyfikować jej ukryte zmienne.
    
- **Wielokrotna przyjaźń:** Jedna funkcja może być przyjacielem kilku różnych klas jednocześnie. To świetne rozwiązanie, gdy funkcja musi połączyć lub porównać ściśle ukryte dane dwóch różnych typów obiektów.
    
- **Brak wskaźnika `this`:** Ponieważ nie jest to funkcja należąca do klasy, kompilator **nie przekazuje do niej wskaźnika `this`**. Aby zmodyfikować jakiś obiekt, funkcja zaprzyjaźniona musi go najpierw otrzymać jako zwykły argument (najlepiej przez referencję).
    
### 2. Jak zadeklarować przyjaźń w kodzie?

Aby funkcja stała się przyjacielem, klasa musi jawnie "wpuścić ją do środka", deklarując ją za pomocą słowa kluczowego `friend`.

- **Miejsce w klasie:** Słowo `friend` możesz wpisać w dowolnym miejscu wewnątrz klasy. Nie ma znaczenia, czy zrobisz to w sekcji `public`, `protected`, czy `private` – jej działanie i uprawnienia będą dokładnie takie same.
    
```cpp
class Bohater {
private:
    int punktyZycia = 100;

    // Klasa deklaruje: "Ta zewnętrzna funkcja jest moim przyjacielem"
    friend void ulecz(Bohater& b); 
};

// Zwykła funkcja globalna (NIE należy do klasy Bohater)
void ulecz(Bohater& b) {
    b.punktyZycia = 100; // Działa! Ma dostęp do sekcji private dzięki 'friend'
}
```

### 3. Gdzie napisać kod takiej funkcji?

- **Definicja poza klasą:** Klasyczna droga – w klasie dajesz tylko krótką deklarację `friend...`, a całe mięso funkcji piszesz normalnie w pliku `.cpp`.
    
- **Definicja wewnątrz klasy:** Możesz napisać całą funkcję bezpośrednio wewnątrz klamer klasy. Staje się ona wtedy automatycznie funkcją typu **`inline`** (rozwijaną w miejscu wywołania).
    
    - _Pamiętaj jednak o pułapce:_ Mimo że fizycznie jej kod leży wewnątrz klasy, **dalej pozostaje ona zwykłą funkcją zewnętrzną**, a nie metodą składową! Wywołuje się ją normalnie: `ulecz(mojBohater);`, a nie `mojBohater.ulecz();`.

### 4. Przeładowanie nazw oraz przyjaźń między klasami

- **Dopasowanie sygnatury (Przeładowanie):** Jeśli w programie masz kilka funkcji o tej samej nazwie (np. trzy różne funkcje `drukuj()`), przyjacielem klasy stanie się **tylko ta jedna konkretna**, której typy i liczba parametrów w nawiasie idealnie pasują do deklaracji umieszczonej po słowie `friend`.
    
- **Metoda innej klasy jako przyjaciel:** Przyjacielem nie musi być wyłącznie "luźna" funkcja globalna. Możesz sprawić, że konkretna metoda należąca do `Klasy A` będzie miała pełny dostęp do prywatnych danych `Klasy B`.

```cpp
class KlasaB; // Zapowiedź klasy

class KlasaA {
public:
    void operacja(KlasaB& obiektB); // Ta metoda będzie przyjacielem
};

class KlasaB {
private:
    int tajneDane;
    // Tylko ta jedna wybrana metoda z KlasyA dostaje klucz do sekretów KlasyB
    friend void KlasaA::operacja(KlasaB& obiektB);
};
```

## Przyjaźń klas
### 1. Jak to działa mechanicznie? (Zasada relacji)

Jeśli `Klasa A` deklaruje w swoim wnętrzu, że `Klasa B` jest jej przyjacielem, to każda metoda napisana w `Klasie B` może bez problemu czytać i modyfikować prywatne zmienne `Klasy A`.

#### Ważne cechy tej relacji, które musisz znać:

- **Przyjaźń jest jednostronna:** Jeśli `Klasa A` ufa `Klasie B` (`friend class B;`), to nie oznacza automatycznie, że `Klasa B` ufa `Klasie A`.
    
- **Przyjaźń nie jest przechodnia:** Jeśli `A` przyjaźni się z `B`, a `B` przyjaźni się z `C`, to `C` **nie ma** dostępu do `A`.
    
- **Przyjaźń nie jest dziedziczona:** Klasy potomne (dziedziczące) nie przejmują automatycznie praw przyjaźni swoich rodziców.

### 2. Sensowny przykład: Silnik graficzny (Renderer i Tekstura)

Wyobraź sobie system wyświetlania grafiki. Masz klasę `Tekstura`, która trzyma w sekcji `private` surowe dane o pikselach oraz unikalny identyfikator z karty graficznej (żeby nikt z zewnątrz przypadkowo ich nie popsuł).

Z drugiej strony masz klasę `Renderer`, która odpowiada za narysowanie wszystkiego na ekranie i potrzebuje natychmiastowego, szybkiego dostępu do tych prywatnych danych tekstury.

```cpp
#include <iostream>
#include <string>

// 1. ZAPOWIEDŹ KLASY (Forward declaration)
// Musimy uprzedzić kompilator, że klasa Tekstura w ogóle istnieje,
// ponieważ używamy jej w parametrze metody klasy Renderer.
class Tekstura;

class Renderer {
public:
    void narysujNaEkranie(const Tekstura& tex) {
        // Ta metoda dobiera się bezpośrednio do pól private klasy Tekstura!
        std::cout << "Renderuję obiekt: " << tex.nazwaPliku << "\n";
        std::cout << "Pobieram ID pamięci VRAM: " << tex.idGpu << "\n";
    }
};

class Tekstura {
private:
    std::string nazwaPliku;
    int idGpu;

public:
    Tekstura(std::string plik, int id) : nazwaPliku(plik), idGpu(id) {}

    // 2. DEKLARACJA PRZYJAŹNI KLAS
    // Przekazujemy pełne uprawnienia CAŁEJ klasie Renderer
    friend class Renderer;
};

int main() {
    Tekstura tlo("las.png", 4096);
    Renderer silnikGraficzny;

    // Renderer bez problemu odczyta prywatne dane tekstury
    silnikGraficzny.narysujNaEkranie(tlo);

    // Próba zrobienia tego bezpośrednio w main() wyrzuci błąd:
    // std::cout << tlo.idGpu; // BŁĄD! main() nie jest przyjacielem Tekstury

    return 0;
}
```

### Podsumowanie dla programisty:

- **Kiedy stosować?** Kiedy dwie lub więcej klas ściśle ze sobą współpracują i tworzą jeden spójny podsystem (tak jak w przykładzie wyżej – system renderowania, albo klasa `Macierz` i klasa `Wektor`).
    
- **Zaleta:** Poprawa wydajności (brak konieczności pisania i wywoływania dziesiątek funkcji typu _getter_ i _setter_) przy jednoczesnym zachowaniu czystości kodu dla reszty programu (zewnętrzny użytkownik w `main` nadal ma zablokowany dostęp).

## 1. Tablice obiektów (Tworzenie i dostęp)

- **Zachowanie jak typy wbudowane:** Obiekty stworzonych przez Ciebie klas możesz bez problemu przechowywać w tablicach, dokładnie tak samo jak zwykłe liczby `int` czy `float`.
    
- **Składnia:** Dostęp do konkretnego elementu i jego pól uzyskujesz za pomocą operatora indeksowania `[]` oraz kropki `.`:
    
```cpp
CPoint a[10];       // Tworzy tablicę 10 obiektów klasy CPoint
a[0].skladnik = 1;  // Dobiera się do pola 'skladnik' w PIERWSZYM obiekcie tablicy
```

## 2. Inicjalizacja tablicy obiektów za pomocą listy

Kiedy chcesz od razu na starcie nadać obiektom w tablicy konkretne wartości, używasz listy inicjalizacyjnej w klamrach `{}`.

- **Rola przecinka:** Musisz pamiętać, że w tym przypadku główny przecinek oddziela od siebie **całe osobne obiekty** (czyli wywołania ich konstruktorów), a nie pojedyncze zmienne wewnątrz tych obiektów.

```cpp
// Zakładamy, że klasa CPoint ma konstruktor CPoint(int x, int y)
CPoint tab[3] = { CPoint(1, 2), CPoint(3, 4), CPoint(5, 6) };
// Przecinki między nawiasami oddzielają 3 osobne obiekty!
```

- _Z wyjątkiem agregatów:_ Slajd wspomina o agregatach (np. prostych strukturach w stylu C, które nie mają jawnych konstruktorów). Dla nich składnia pozwala na zagnieżdżone klamry: `Punkt t[2] = { {1, 2}, {3, 4} };`.

## 3. Wskaźniki i referencje do obiektów

Tak jak do zwykłych zmiennych, możesz tworzyć wskaźniki i referencje nakierowane na konkretne obiekty (również te siedzące wewnątrz tablicy).

```cpp
CPoint obj;
CPoint& ref = obj;   // Referencja (alias) do obiektu
CPoint* wsk = &obj;  // Wskaźnik przechowujący adres obiektu

wsk->skladnik = 5;  // Praca przez wskaźnik wymaga strzałki '->'
```

## 4. Dynamiczne tablice obiektów (`new[]`) i krytyczny wymóg konstruktora

Jeżeli tworzymy tablicę obiektów reprezentowaną przez wskaźnik przy pomocy operatora `new`, to dana klasa **musi zawierać domyślny (bezargumentowy) konstruktor**!

### Dlaczego to jest absolutnie obowiązkowe?

Kiedy piszesz w kodzie linijkę zamawiającą dynamiczną tablicę w pamięci na stercie (heap):

```cpp
CPoint* tablica = new CPoint[100];
```

Kompilator natychmiast rezerwuje w pamięci RAM miejsce na 100 obiektów. Zaraz po rezerwacji pamięci, komputer musi te obiekty jakoś "powołać do życia" – czyli uruchomić dla każdego z nich konstruktor.

Ponieważ tworzysz całą tablicę naraz, **nie masz fizycznie możliwości przekazania unikalnych argumentów** (np. współrzędnych X i Y) osobno dla każdego z tych 100 obiektów w momencie wywołania `new[]`. Kompilator jest zmuszony uruchomić konstruktor, który nie wymaga żadnych danych wejściowych. Jeśli nie napiszesz w swojej klasie konstruktora domyślnego, program zgłosi błąd kompilacji i nie da się go uruchomić.

- **Brak zwykłej inicjalizacji:** Jak mówi ostatnia podkropka slajdu, przy dynamicznej alokacji `new CPoint[100]` nie można w prosty sposób użyć tradycyjnej listy inicjalizacyjnej w klamrach, tak jak robiliśmy to przy tablicach statycznych. Wszystkie obiekty w dynamicznej tablicy na start zostaną stworzone dokładnie w taki sam sposób – za pomocą konstruktora domyślnego.

## Struktura `struct`

Struktura to inaczej klasa, w której przez domniemanie wszystkie składniki i metody są publiczne

### Definicja:
```cpp
struct nazwa { 
	int i; 
	int j; 
}; 

class nazwa { 
public: 
	int i; 
	int j; 
};
```

## Unia `union`

Unia to bardzo specyficzna struktura danych odziedziczona z języka C. Przypomina klasyczną strukturę (`struct`), ale ma jedną fundamentalną różnicę w sposobie zarządzania pamięcią RAM.

Oto szczegółowe wyjaśnienie haseł ze slajdu i mechaniki działania unii.

### Istota unii (Jedno wspólne pudełko)

- **Współdzielenie pamięci:** Unia umożliwia przechowywanie w tym samym obszarze pamięci obiektów różnych typów. Jednak w danym momencie możesz w niej trzymać **tylko jedną wybraną zmienną**. Zaprzepaszcza to poprzednią wartość.
    
- **Rozmiar w pamięci:** W zwykłej strukturze rozmiar to suma rozmiarów wszystkich jej pól. W unii wszystkie pola nakładają się na siebie w pamięci RAM. Dlatego **unia zajmuje w pamięci dokładnie tyle miejsca, ile zajmuje jej największy składnik**.
    
```cpp
union Nazwa {
    int i;    // powiedzmy: 4 bajty
    long l;   // powiedzmy: 8 bajtów (największy)
    char c;   // powiedzmy: 1 bajt
}; 
```

Cała ta unia w pamięci RAM zajmie dokładnie **8 bajtów** (rozmiar typu `long`), ponieważ wszystkie trzy zmienne zaczynają się od tego samego adresu pamięci.

### Krytyczna zasada użytkowania i niebezpieczeństwo

Należy pamiętać, że po zapisaniu do unii obiektu jakiegoś typu należy odczytywać ten sam typ.

Kompilator C++ nie pilnuje tego, co aktualnie znajduje się w unii. Jeśli do powyższej unii zapiszesz liczbę całkowitą (`i = 500`), a linijkę niżej spróbujesz odczytać to jako znak (`c`), program nie zgłosi błędu – po prostu zinterpretuje surowe bity liczby `500` jako kod znaku ASCII. Doprowadzi to do totalnego chaosu w danych (tzw. _Undefined Behavior_).

```cpp
Przyklad u;
u.i = 65; // Zapisujemy int

// BŁĄD LOGICZNY (choć się skompiluje):
std::cout << u.c; // Wypisze literę 'A', bo 65 to kod ASCII dla 'A'. 
                  // Surowe bajty zostały błędnie zinterpretowane!
```

### 3. Unia anonimowa

Unia anonimowa to unia, która **nie posiada nadanej nazwy typu ani nazwy zmiennej**. Służy do stworzenia zmiennych, które współdzielą pamięć, ale w kodzie zachowują się jak zupełnie zwyczajne, luźne zmienne lokalne.

- **Brak operatora kropki:** Do jej pól odwołujemy się bezpośrednio po nazwie pola, pomijając kropkę.

```cpp
int main() {
    // Unia anonimowa wewnątrz funkcji:
    union {
        int kod;
        char litera;
    };

    kod = 10;      // Bezpośredni dostęp (brak u.kod)
    litera = 'z';  // Nadpisuje pamięć, w której przed chwilą był 'kod'
}
```

### 4. Dlaczego obecnie jest "raczej niestosowana"?

Jak słusznie zauważa przedostatni punkt slajdu, we współczesnym C++ unii w czystej postaci praktycznie się już nie używa. Są ku temu dwa powody:

1. **Brak bezpieczeństwa:** Łatwo o pomyłkę przy odczycie złego typu danych.
    
2. **Ograniczenia obiektowe:** W klasycznej unii nie można było w bezpieczny sposób przechowywać skomplikowanych obiektów (np. `std::string` czy `std::vector`), które posiadają własne konstruktory i destruktory.
    

#### Co stosuje się zamiast unii?

W nowoczesnym C++ (od standardu C++17) unie zostały całkowicie wyparte przez bezpieczny typ **`std::variant`**. Działa on bardzo podobnie (pozwala trzymać jedną z kilku zadeklarowanych wartości), ale pod maską sam pilnuje i wie, jaki typ danych tam aktualnie siedzi, nie pozwalając na błędny odczyt:

```cpp
#include <variant>
#include <string>

// Nowoczesny, bezpieczny odpowiednik unii:
std::variant<int, std::string> bezpiecznePudelko;
bezpiecznePudelko = "Tekst"; // Kompilator wie, że teraz w środku jest string
```


## Pola bitowe

Pola bitowe to zaawansowany mechanizm strukturalny, który pozwala programiście na **zarządzanie pamięcią komputera na poziomie pojedynczych bitów**, a nie całych bajtów.

### Istota pól bitowych

- **Precyzyjny rozmiar:** Zwykle najmniejsza zmienna, jaką możemy stworzyć (np. `char`), zajmuje w pamięci cały 1 bajt (8 bitów). Pola bitowe pozwalają zadeklarować zmienną wewnątrz klasy lub struktury, która zajmie np. dokładnie 1 bit, 2 bity albo 5 bitów.
    
- **Składnia z dwukropkiem:** Rozmiar zmiennej w bitach określa się, stawiając dwukropek `:` po nazwie zmiennej, a następnie wpisując pożądaną liczbę bitów.

```cpp
class Port {
    unsigned int read   : 1; // Zmienna 'read' zajmuje dokładnie 1 bit
    unsigned int status : 2; // Zmienna 'status' zajmuje dokładnie 2 bity
};
```

### Co to oznacza w praktyce?

- Pole `read` (1 bit) może przyjąć tylko $2^1 = 2$ wartości: `0` lub `1` (idealne do flag typu prawda/fałsz).
    
- Pole `status` (2 bity) może przyjąć $2^2 = 4$ wartości: `0`, `1`, `2` lub `3`.
    
- Gdyby te zmienne były zwykłymi `unsigned int`, każda z nich zajmowałaby po 4 bajty (w sumie 8 bajtów = 64 bity). Dzięki polom bitowym kompilator upakuje je obok siebie w obrębie **jednego wspólnego bajtu** (lub jednego słowa maszynowego), drastycznie oszczędzając pamięć.
    

### 2. Kiedy i po co się to stosuje?

Jak wskazuje trzeci punkt slajdu, w zwykłych aplikacjach biznesowych raczej się tego nie używa, ponieważ pamięć RAM jest dzisiaj tania i pojemna. Pola bitowe są jednak niezastąpione w dwóch obszarach:

1. **Obsługa specjalistycznej aparatury / Mikrokontrolery (Embedded):** Gdy programujesz elektronikę (np. Arduino, STM32, systemy w samochodzie), rejestry procesora sterujące fizycznymi nóżkami układu scalonego są zorganizowane dokładnie jako pojedyncze bity. Pola bitowe pozwalają na wygodne mapowanie tych rejestrów.
    
2. **Protokoły sieciowe i formaty plików:** Kiedy liczy się każdy bit wysyłany przez sieć (np. w nagłówkach pakietów internetowych TCP/IP), dane celowo upakowuje się bez strat przestrzeni.
    
### 3. Wielki minus: Zależność od implementacji (Brak przenośności)

Przedostatni punkt slajdu ostrzega: _„Dużo zależy od implementacji”_. Standard języka C++ pozostawia kompilatorom sporą dowolność w tym, jak fizycznie ułożą te bity w pamięci RAM. To sprawia, że kod używający pól bitowych może zachować się inaczej po zmianie kompilatora (np. z GCC na MSVC).

# ~={orange}Konstruowanie obiektów klas (wyk. 5)=~

## 1. Istota i cechy konstruktora

**Konstruktor** to unikalna funkcja składowa klasy, wywoływana automatycznie przez system w momencie powoływania obiektu do życia.

- **Zadanie:** Nadawanie polom obiektu bezpiecznych, początkowych wartości (inicjalizacja stanu początkowego).
    
- **Cechy formalne (Żelazne zasady):**
    - Nazywa się **dokładnie tak samo jak klasa**.
    - **Nie zwraca żadnego typu** (nie piszemy przed nim nawet `void`).
    - Może być **przeładowany** – klasa może mieć wiele konstruktorów różniących się zestawem przyjmowanych argumentów.
    - **Nigdy** nie może być typu `static` ani `virtual`.
    - Może tworzyć obiekty posiadające modyfikatory `const` (stałe) oraz `volatile` (możliwy do nieoczekiwanej zmiany w trakcie programu.
## 2. Konstruktor domniemany (Domyślny / Bezargumentowy)
**Konstruktor domniemany** to taki, który system potrafi uruchomić **bez podawania jakichkolwiek danych wejściowych**.
- **Jak go uzyskać?**
    1. Może w ogóle nie przyjmować parametrów: `Postac();`
    2. Może mieć parametry, ale **wszystkie** posiadają przypisane wartości domyślne: `Postac(int pz = 100);`
        
- **Ważna cecha:** Klasa może posiadać **tylko jeden** konstruktor domniemany. Gdyby istniały dwa, kompilator przy próbie zapisu `Postac p;` nie wiedziałby, który uruchomić.
### Pułapka automatycznego generatora kompilatora

- **Zasada 1:** Jeśli napiszesz klasę i nie stworzysz w niej **żadnego** własnego konstruktora, kompilator pod maską automatycznie wygeneruje za Ciebie pusty konstruktor domyślny.
    
- **Zasada 2 (Pułapka):** Jeśli zdefiniujesz **chociaż jeden** swój własny konstruktor (np. przyjmujący argument), kompilator uznaje, że przejmujesz kontrolę nad klasą i **nie wygeneruje** wersji domyślnej.

```cpp
class Hero {
public:
    // Posiadamy tylko konstruktor argumentowy:
    Hero(std::string name) {} 
};

int main() {
    // Hero h1; // BŁĄD KOMPILACJI! Brak konstruktora domyślnego.
    Hero h2("Thor"); // OK
}
```
## 3. Sposoby wywoływania konstruktorów (Czas życia i zasięg obiektów)

Czas wykonania konstruktora oraz moment narodzin obiektu zależą od tego, gdzie i w jaki sposób go zadeklarujesz.
### A. Obiekty lokalne automatyczne

- **Kiedy powstają:** Gdy program wchodzi do bloku kodu (np. wnętrza funkcji lub pętli) i napotyka ich deklarację.
    
- **Kiedy giną:** Automatycznie w momencie opuszczenia tego bloku (napotkania klamry zamykającej `}`).

```cpp
void funkcja() {
    Hero h; // Konstruktor wykonuje się TUTAJ
} // h automatycznie umiera TUTAJ (zwalnia pamięć na stosie)
```

### B. Obiekty lokalne statyczne

- **Kiedy powstają:** Raz, na samym początku programu (przed uruchomieniem funkcji `main()`).
    
- **Zasięg i czas życia:** Widoczny tylko w bloku, w którym go stworzono (zakres ważności), ale żyje w pamięci przez cały okres działania aplikacji.

```cpp
void licznik() {
    static Hero boss; // Konstruktor wykona się przed main()!
}
```

### C. Obiekty globalne

- **Kiedy powstają:** Identycznie jak lokalne statyczne – przed pierwszą linijką `main()`.
    
- **Zasięg i czas życia:** Żyją przez cały czas pracy programu, a dostęp do nich ma **cały plik kodu**.

### D. Obiekty dynamiczne (Tworzone operatorem `new`)

- **Kiedy powstają:** Dokładnie w momencie wywołania słowa kluczowego `new`.
    
- **Czas życia:** Od `new` do momentu, kiedy programista jawnie wywoła operator `delete`.

```cpp
void wyciek() {
    Hero* wsk = new Hero("Loki"); // Alokacja i konstruktor
    // zapomnieliśmy o delete wsk;
} // Wskaźnik wsk ginie, ale obiekt "Loki" nadal bezużytecznie siedzi w pamięci RAM!
```

### Pełny przykład kodu do przeanalizowania

```cpp
#include <iostream>
#include <string>

class Postac {
private:
    std::string imie;
    int hp;

public:
    // 1. Konstruktor domniemany (dzięki wartościom domyślnym)
    Postac(std::string p_imie = "Nieznajomy", int p_hp = 100) {
        imie = p_imie;
        hp = p_hp;
        std::cout << "Konstruktor: Narodził się " << imie << "\n";
    }

    // 2. Przeładowanie konstruktora (inna wersja)
    Postac(int p_hp) {
        imie = "Bezimienny Wojownik";
        hp = p_hp;
        std::cout << "Konstruktor przeciążony: Wojownik z HP = " << hp << "\n";
    }
};

// Obiekt globalny - wywoła się przed main()
Postac g_gracz("Globalny", 500); 

int main() {

    Postac p1;                 // Wywoła domyślny -> Nieznajomy (100)
    Postac p2("Artas", 250);   // Wywoła domyślny z własnymi parametrami
    Postac p3(80);             // Wywoła przeładowany (Wojownik)

    {
        std::cout << "--- Wchodzimy do bloku ---\n";
        Postac pLokalna("Krótkodystansowiec");
        std::cout << "--- Wychodzimy z bloku ---\n";
    } // pLokalna niszczy się w tym miejscu

    std::cout << "--- Tworzymy obiekt dynamiczny ---\n";
    Postac* pDynamiczna = new Postac("Dynamiczny", 999);

    delete pDynamiczna; // Bez tego obiekt żyłby po zakończeniu main()!
    std::cout << "--- Koniec main() ---\n";
    return 0;
}
```

## Lista inicjalizacyjna konstruktora

**Lista inicjalizacyjna** to specjalna sekcja konstruktora, która służy do nadawania wartości polom klasy **zanim** jeszcze wykona się właściwy kod zawarty w ciele (klamrach `{}`) konstruktora.

### 1. Dwa etapy tworzenia obiektu

Gdy wywołujesz konstruktor, powołanie zmiennych do życia zawsze odbywa się w dwóch krokach:

1. **Etap 1: Inicjalizacja składników** – komputer rezerwuje miejsce i nadaje polom wartości początkowe. To tutaj działa lista inicjalizacyjna.
    
2. **Etap 2: Wykonanie instrukcji w ciele** – wykonuje się kod między klamrami `{...}`. To nie jest inicjalizacja, lecz zwykłe przypisanie wartości do obiektów, które już wcześniej zostały domyślnie stworzone.
    

> ⚠️ **Haczyk rekrutacyjny (Funkcje wirtualne?!):** Slajd pyta o funkcje wirtualne w ciele konstruktora. Pamiętaj: wewnątrz ciała konstruktora mechanizm funkcji wirtualnych **nie działa poprawnie** (wywoła się wersja metody z klasy aktualnie budowanej, a nie z klasy pochodnej), ponieważ obiekt nie jest jeszcze w pełni uformowany!

### 2. Kiedy lista inicjalizacyjna jest absolutnie obowiązkowa?

W przypadku zwykłych zmiennych (np. `int x;`) możesz wybrać, czy nadasz wartość na liście inicjalizacyjnej, czy w ciele. Istnieją jednak sytuacje, gdzie **zwykłe przypisanie w ciele wygeneruje błąd kompilacji**:

#### A. Stałe pola (`const`)

Pola z przydomkiem `const` muszą otrzymać wartość w momencie narodzin. Ponieważ w ciele konstruktora obiekt już istnieje, przypisanie tam wartości (`zmienna = 5;`) traktowane jest jako nielegalna modyfikacja stałej.

#### B. Referencje jako pola klasy (`int& ref;`)

Referencja w C++ musi zostać związana z obiektem w chwili jej utworzenia. Nie da się stworzyć „pustej” referencji i przypisać jej czegoś w klamrach konstruktora.

### 3. Jak zapisać listę inicjalizacyjną? (Składnia)

Listę tworzymy, stawiając **dwukropek `:`** zaraz po nawiasie z argumentami konstruktora. Następnie wymieniamy nazwy pól, a w nawiasach okrągłych `()` lub klamrowych `{}` przekazujemy wartości:

```cpp
class NazwaKlasy {
private:
    const int zm_const; // Obowiązkowo na liście
    double zm_zwykla;   // Opcjonalnie na liście

public:
    // Składnia z obrazka:
    NazwaKlasy(int a, double f) : zm_const(a), zm_zwykla(f) 
    {
        // Ciało konstruktora może być zupełnie puste! {}
    }
};
```

### 4. Ważne zasady i ograniczenia z drugiego slajdu

- **Pola nie-const:** Na liście inicjalizacyjnej jak najbardziej mogą (a ze względów wydajnościowych nawet powinny) znaleźć się zwykłe pola bez modyfikatora `const`.
    
- **Zakaz dla pól `static`:** Lista inicjalizacyjna **nie może** inicjalizować zmiennych statycznych. Dlaczego? Ponieważ zmienna statyczna należy do całej klasy i rodzi się przed obiektem. Konstruktor działa na poziomie jednego obiektu, więc nie może ustawiać wspólnej zmiennej globalnej klasy na tej liście.
    
- **Elastyczność argumentów:** Wartość przekazywana w nawiasie nie musi być czystą zmienną. Może to być skomplikowane wyrażenie matematyczne, a nawet wywołanie zewnętrznej funkcji (np. `: zm_zwykla(obliczPierwiastek(f))`).
### Dlaczego warto używać listy inicjalizacyjnej zawsze? (Wydajność)

Jeśli polem Twojej klasy jest obiekt innej skomplikowanej klasy (np. `std::string tekst;`), to:

- **Użycie ciała:** System najpierw tworzy pusty napis (konstruktor domyślny), a potem w klamrach usuwa go i kopiuje nowy tekst (operator przypisania). Wykonujesz dwie ciężkie operacje.
    
- **Użycie listy:** Obiekt od razu rodzi się z docelowym tekstem (konstruktor kopiujący). Działa to znacznie szybciej!

## Tworzenie obiektów ze składnikiem z innej klasy (Kompozycja)

### 1. Inicjalizacja obiektów wewnętrznych

- **Rola listy inicjalizacyjnej:** Jeśli chcesz nadać konkretne wartości początkowe obiektowi, który jest składową innej klasy, **musisz** to zrobić na liście inicjalizacyjnej konstruktora głównego.
    
- **Scenariusz A (Brak jawnego konstruktora):** Jeśli dla wewnętrznego obiektu nie podasz żadnych parametrów na liście inicjalizacyjnej, kompilator automatycznie spróbuje wywołać jego **konstruktor domyślny** (bezargumentowy).
    
- **Scenariusz B (Krytyczny przypadek - Brak konstruktora domyślnego):** Jeżeli klasa wewnętrzna posiada wyłącznie konstruktory parametryczne (wymaga podania danych, by powstać) i nie ma wersji domyślnej, to jej inicjalizacja **obowiązkowo musi** znaleźć się na liście inicjalizacyjnej. W przeciwnym razie program wyrzuci błąd kompilacji.

### 2. Kolejność wywoływania konstruktorów i destruktorów

To flagowe pytanie na każdym kolokwium z programowania obiektowego. Kiedy tworzymy obiekt złożony, jego elementy rodzą się i giną w ściśle określonej sekwencji.

#### Reguła konstrukcji (Od szczegółu do ogółu):

Konstruktory obiektów wewnętrznych wykonują się **zanim** ruszy kod głównego konstruktora klasy nadrzędnej. Najpierw muszą powstać części składowe, żeby cały obiekt mógł zostać prawidłowo uformowany.

#### W jakiej kolejności powstają składniki?

O kolejności decyduje **miejsce ich zadeklarowania w klasie** (od góry do dołu), a nie to, w jakiej kolejności programista wpisał je na liście inicjalizacyjnej!

#### Reguła destrukcji (Odwrotnie):

Destruktory wywołują się w **dokładnie odwrotnej kolejności**. Najpierw niszczony jest obiekt główny (nadrzędny), a dopiero potem po kolei rozpadają się jego części składowe (od dołu do góry deklaracji).

### Praktyczny przykład do analizy i nauki

Przeanalizujmy komputer składający się z procesora. Zobaczmy na własne oczy kolejność komunikatów na ekranie:

```cpp
#include <iostream>
#include <string>

class Procesor {
public:
    Procesor(std::string model) {
        std::cout << "[1] Konstruktor Procesora: " << model << "\n";
    }
    ~Procesor() {
        std::cout << "[A] Destruktor Procesora\n";
    }
};

class Komputer {
private:
    // Składniki deklarowane od góry do dołu:
    Procesor cpu; 
    int ram;

public:
    // Lista inicjalizacyjna: obowiązkowo przekazujemy model do cpu
    Komputer(std::string modelCPU, int pojemnoscRAM) : cpu(modelCPU), ram(pojemnoscRAM) 
    {
        std::cout << "[2] Konstruktor Komputera (główny)\n";
    }
    
    ~Komputer() {
        std::cout << "[B] Destruktor Komputera (główny)\n";
    }
};

int main() {
    {
        std::cout << "--- Tworzymy komputer ---\n";
        Komputer mojPC("Intel i9", 32);
        std::cout << "--- Komputer działa ---\n";
    } // Tutaj mojPC opuszcza blok kodu i ginie
    
    return 0;
}
```

#### Wynik działania programu (Dokładna sekwencja):

```
--- Tworzymy komputer ---
[1] Konstruktor Procesora: Intel i9   <-- Najpierw rodzi się część wewnętrzna
[2] Konstruktor Komputera (główny)   <-- Potem wykonuje się kod całości
--- Komputer działa ---
[B] Destruktor Komputera (główny)     <-- Przy destrukcji najpierw ginie całość...
[A] Destruktor Procesora              <-- ...a na samym końcu jej części składowe
```

## Konstruktor kopiujący

**Konstruktor kopiujący** to unikalny rodzaj konstruktora, który służy do tworzenia nowego obiektu jako **dokładnej kopii** innego, istniejącego już obiektu tej samej klasy.

### 1. Jak wygląda w kodzie? (Składnia)

Zgodnie z pierwszym slajdem, konstruktor kopiujący musi przyjmować jako argument **referencję** do obiektu tej samej klasy:

C++

```
klasa::klasa(const klasa& oryginal);
```

- **Dlaczego referencja (`&`) jest absolutnie obowiązkowa?** Gdybyśmy spróbowali przekazać argument przez wartość (`klasa(klasa oryginal)`), program musiałby... zrobić kopię tego argumentu, żeby przekazać go do funkcji. A żeby zrobić kopię, musiałby wywołać konstruktor kopiujący, który znów przekazywałby przez wartość i musiałby zrobić kolejną kopię. Program wpadłby w nieskończoną pętlę i zawiesiłby komputer (wywołał _stack overflow_).
    
- **Dlaczego `const`?** Po pierwsze, przy kopiowaniu nie chcemy zmienić danych w oryginalnym obiekcie. Po drugie, jak mówi drugi slajd, jeśli oryginalny obiekt został zadeklarowany jako stała (`const`), wersja bez tego przydomka w parametrze wyrzuci błąd i nie pozwoli go skopiować.
    

### 2. Kiedy komputer wywołuje go sam z siebie?

Konstruktor kopiujący odpala się automatycznie w trzech sytuacjach (dwie z nich wymienia drugi slajd):

1. **Jawne klonowanie obiektu:** Kiedy tworzysz nowy obiekt i od razu przypisujesz mu stary.
    ```cpp
    Punkt p1(10, 20);
    Punkt p2 = p1; // Wywołanie konstruktora kopiującego!
    ```

2. **Przekazywanie do funkcji przez wartość:** Gdy funkcja przyjmuje obiekt bez znaku `&`.
    ```cpp
    void pokazPunkt(Punkt p); // Tutaj w momencie wywołania robi się ukryta kopia za pomocą tego konstruktora
    ```
    
3. **Zwracanie z funkcji przez wartość:** Gdy funkcja kończy się zwróceniem obiektu.
    
    ```cpp
    Punkt stworzPunkt() { Punkt p; return p; } // Klonuje obiekt na zewnątrz
    ```
    
### 3. Płytka kopia vs Głęboka kopia (Kiedy domyślny działa źle?)

Pierwszy slajd wspomina: _„Jeżeli nie zostanie przez nas zdefiniowany to kompilator stworzy go sam”_.

Domyślny konstruktor kopiujący robi tzw. **kopiowanie płytkie (Shallow Copy)** – bezmyślnie przepisuje bajt po bajcie wartość każdego pola.

#### Kiedy domyślny konstruktor wystarczy?

Gdy klasa zawiera tylko proste zmienne (`int`, `float`, `double`, `std::string`). Wtedy automatyczny konstruktor jest idealny i nie ma sensu pisać go ręcznie.

#### A kiedy jest NIEZBĘDNY?

Gdy klasa zarządza **dynamiczną pamięcią (wskaźnikami utworzonymi przez `new`)**. Płytka kopia skopiuje sam adres wskaźnika, a nie dane, do których on prowadzi!

#### Przykład katastrofy przy płytkiej kopii:

Wyobraź sobie klasę, która rezerwuje w tablicy dynamicznej miejsce na imię bohatera:

```cpp
class Bohater {
public:
    char* imie;
    Bohater(const char* tekst) {
        imie = new char[100];
        strcpy(imie, tekst);
    }
    ~Bohater() { delete[] imie; } // Destruktor zwalnia pamięć
};
```

Jeśli wykonasz płytką kopię:

```
Bohater b1("Geralt");
Bohater b2 = b1; // Domyślny konstruktor kopiujący!
```

Teraz `b1.imie` oraz `b2.imie` **wskazują na ten sam, jeden adres w pamięci RAM!** Gdy program się skończy:

1. Destruktor `b2` usunie pamięć pod tym adresem.
    
2. Destruktor `b1` spróbuje usunąć ten sam adres sekundę później $\rightarrow$ **Program wywali błąd (Crash / Double Free Error)**.

#### Rozwiązanie – Ręczna Głęboka Kopia (Deep Copy):

Musimy sami napisać konstruktor kopiujący, który zarezerwuje _nowy, osobny kawałek pamięci_ i przepisze tam litery:

```cpp
// Nasz poprawny konstruktor kopiujący
Bohater::Bohater(const Bohater& oryginal) {
    imie = new char[100];          // 1. Rezerwujemy własną pamięć RAM
    strcpy(this->imie, oryginal.imie); // 2. Przepisujemy zawartość tekstową
}
```

Dzięki temu `b1` i `b2` mają swoje własne, niezależne tablice w pamięci i program działa stabilnie!

## Konstruktor przenoszący

**Konstruktor przenoszący** to mechanizm wprowadzony w standardzie C++11. Zamiast tworzyć głęboką, kosztowną kopię danych z jednego obiektu do drugiego (czyli rezerwować nową pamięć i przepisywać zawartość), konstruktor przenoszący po prostu **"kradnie" (przejmuje) wskaźniki** do pamięci RAM od obiektu tymczasowego.

### 1. Referencja do r-wartości (`&&`)

Konstruktor przenoszący rozpoznaje się po podwójnym znaku ampersandu `&&`:

```cpp
klasa::klasa(klasa&& tymczasowy);
```

Ten zapis oznacza **referencję do r-wartości (rvalue reference)**.

- **Czym jest r-wartość?** To obiekt tymczasowy, nienazwany, który istnieje tylko przez ułamek sekundy podczas wyznaczania wartości wyrażenia (np. wynik operacji `a++`, tymczasowy obiekt zwrócony z funkcji, czy wynik dodawania napisów). Ponieważ ten obiekt i tak zaraz zostanie zniszczony przez system, możemy bezkarnie zabrać jego zasoby.
    
### 2. Intuicyjna analogia: Kopiowanie vs Przenoszenie

- **Kopiowanie (Głębokie):** Masz segregator z dokumentami (obiekt A). Aby mieć obiekt B, kupujesz nowy segregator i kserujesz kartka po kartce całą zawartość. Masz dwa identyczne segregatory. Kosztowało to dużo czasu i papieru.
    
- **Przenoszenie:** Widzisz segregator, który ktoś zaraz wyrzuci do niszczarki (obiekt tymczasowy). Zamiast cokolwiek kserować, podchodzisz, przepisujesz na swój nowy segregator plakietkę z adresem zawartości, a stary pusty segregator zostaje wyrzucony. **Operacja polega na przepięciu wskaźnika i trwa ułamek sekundy.**
    
### 3. Jak to wygląda w kodzie? (Przykład do nauki)

Nawiązując do naszej wcześniejszej klasy obsługującej pamięć dynamiczną, zobacz, jak elegancko pisze się konstruktor przenoszący:

```cpp
#include <iostream>
#include <utility> // dla std::move

class Kontener {
public:
    int* dane;
    int rozmiar;

    // Zwykły konstruktor
    Kontener(int r) : rozmiar(r) {
        dane = new int[rozmiar];
    }

    // KONSTRUKTOR PRZENOSZĄCY (Move Constructor)
    Kontener(Kontener&& zrodlo) noexcept {
        // 1. Kradniemy wskaźnik i rozmiar ze źródła
        this->dane = zrodlo.dane;
        this->rozmiar = zrodlo.rozmiar;

        // 2. Bardzo ważne: Czyścimy źródło! 
        // Jeśli tego nie zrobimy, destruktor obiektu tymczasowego usunie NASZE dane!
        zrodlo.dane = nullptr;
        zrodlo.rozmiar = 0;
        
        std::cout << "Zadziałał konstruktor przenoszący! Przejęto pamięć.\n";
    }

    ~Kontener() {
        delete[] dane; // Jeśli dane to nullptr, delete[] nic nie zrobi (bezpiecznie)
    }
};

int main() {
    Kontener k1(100000); // Ciężki obiekt

    // Funkcja std::move() wymusza potraktowanie k1 jako r-wartości (wartości tymczasowej)
    Kontener k2 = std::move(k1); 
    
    // W tym momencie k2 błyskawicznie przejął tablicę 100k elementów.
    // k1 jest teraz pusty (k1.dane to nullptr).
    
    return 0;
}
```

### Podsumowanie dla programisty:

- **Zaleta:** Gigantyczny wzrost wydajności aplikacji. Przypisując lub zwracając z funkcji ogromne kontenery (np. `std::vector` z milionem elementów), program nie wykonuje żadnej alokacji pamięci na stercie, tylko przepisuje surowy adres wskaźnika.
    
- **Zasada czyszczenia:** Konstruktor przenoszący **musi wyzerować wskaźniki w obiekcie źródłowym** (`zrodlo.dane = nullptr`), w przeciwnym razie jego destruktor zwolni pamięć, którą właśnie przejęliśmy.


## „Nazwane konstruktory” (_Named Constructor Idiom_)

### 1. Problem ze „zwykłymi” konstruktorami

Zwykłe konstruktory w C++ mają dwie spore wady:

1. **Muszą nazywać się tak samo jak klasa:** Nie możesz nadać im unikalnej nazwy, która opisywałaby, _w jaki sposób_ obiekt jest tworzony.
    
2. **Rozróżnianie tylko po typach argumentów (Przeładowanie):** Jeśli chcesz stworzyć punkt na płaszczyźnie, możesz to zrobić za pomocą współrzędnych kartezjańskich $(X, Y)$ lub współrzędnych biegunowych $(Promień, Kąt)$. Ponieważ w obu przypadkach przekazujesz dwie liczby zmiennoprzecinkowe `double`, **nie da się** napisać dwóch osobnych zwykłych konstruktorów, bo miałyby identyczną sygnaturę!
    
```cpp
// BŁĄD! Kompilator nie odróżni tych konstruktorów:
Punkt(double x, double y);
Punkt(double promien, double kat);
```

### 2. Jak działa technika _Named Constructor Idiom_?

Zamiast walczyć z przeładowaniem konstruktorów, robimy sprytny unik:

1. **Chowamy tradycyjne konstruktory:** Umieszczamy je w sekcji `private` lub `protected`. Od teraz nikt spoza klasy nie może napisać `Punkt p(1, 2);`.
    
2. **Tworzymy publiczne, statyczne metody narzędziowe:** Metody te mają unikalne nazwy słowne, przyjmują parametry, tworzą pod maską obiekt (bo będąc wewnątrz klasy mają dostęp do prywatnego konstruktora) i zwracają gotowy obiekt.
    
### 3. Klasa finalna (Blokada dziedziczenia)

> W ten sposób można stworzyć klasę finalną tzn. taką, po której się nie da dziedziczyć.

**Dlaczego to działa?** Klasa pochodna (potomna) podczas swoich narodzin musi jako pierwszą rzecz uruchomić konstruktor swojej klasy-rodzica. Ponieważ zamknęliśmy wszystkie konstruktory w sekcji `private`, żadna inna klasa nie ma do nich dostępu – próba odziedziczenia po takiej klasie zakończy się natychmiastowym błędem kompilacji.

### Praktyczny przykład do nauki (Współrzędne punktu)

```cpp
#include <iostream>
#include <cmath>

class Punkt {
private:
    double x, y;

    // 1. Ukrywamy konstruktor przed światem zewnętrznym
    Punkt(double g_x, double g_y) : x(g_x), y(g_y) {}

public:
    // 2. NAZWANE KONSTRUKTORY (Publiczne metody statyczne)
    
    static Punkt OdKartezjanskich(double x, double y) {
        return Punkt(x, y); // Tworzy i zwraca obiekt bezpośrednio
    }

    static Punkt OdBiegunowych(double promien, double kat_radiany) {
        double wyliczone_x = promien * cos(kat_radiany);
        double wyliczone_y = promien * sin(kat_radiany);
        return Punkt(wyliczone_x, wyliczone_y);
    }

    void Wyswietl() const {
        std::cout << "X: " << x << ", Y: " << y << "\n";
    }
};

int main() {
    // Punkt p(1.0, 2.0); // BŁĄD! Konstruktor jest prywatny.

    // Wywołanie jest niezwykle czytelne i intuicyjne dla programisty:
    Punkt p1 = Punkt::OdKartezjanskich(5.0, 3.0);
    Punkt p2 = Punkt::OdBiegunowych(10.0, 0.5); // 0.5 radiana

    p1.Wyswietl();
    p2.Wyswietl();

    return 0;
}
```

### Podsumowanie ściągawka:

- **Zaleta 1:** Kod w `main` staje się niesamowicie czytelny (`Punkt::OdKartezjanskich` mówi samo za siebie).
    
- **Zaleta 2:** Bezpieczeństwo – całkowicie eliminujemy ryzyko, że programista pomyli kolejność lub znaczenie subtelnych parametrów w przeładowanych konstruktorach.

## Destruktory

### 1. Charakterystyka i żelazne zasady destruktora

- **Nazewnictwo:** Nazywa się dokładnie tak samo jak klasa, ale jego nazwę poprzedza znak tyldy (`~`), np. `~Punkt();`.
    
- **Brak typu zwracanego:** Podobnie jak konstruktor, nie zwraca absolutnie nic (nie piszemy przed nim żadnego typu, nawet `void`).
    
- **Brak parametrów:** Destruktor **nie przyjmuje żadnych argumentów** w nawiasie.
    
- **Zakaz przeładowania:** Ponieważ nie przyjmuje parametrów, klasa może posiadać **tylko jeden destruktor**. Nie da się go przeciążyć.
    
### 2. Kiedy destruktor odpala się automatycznie?

Moment wywołania zależy wprost od sposobu, w jaki utworzono obiekt:

- **Dla obiektów automatycznych (na stosie):** Wywołuje się sam, gdy program opuszcza blok kodu `{}`, w którym dany obiekt został zadeklarowany.
    
- **Dla obiektów dynamicznych (na stercie):** Wywołuje się tylko i wyłącznie wtedy, gdy programista jawnie użyje słowa kluczowego **`delete`** na wskaźniku do tego obiektu.

### 3. Kiedy napisanie destruktora jest absolutnie obowiązkowe?

Jeśli Twoja klasa zawiera jedynie proste typy (`int`, `double`, `float`) lub gotowe obiekty biblioteki standardowej (`std::string`, `std::vector`), kompilator sam wygeneruje domyślny, pusty destruktor i to w zupełności wystarczy.

**Zasada ze slajdu (Słowo „musi” w cudzysłowie):**

Jeśli w konstruktorze lub jakiejkolwiek innej metodzie rezerwujesz pamięć dynamiczną za pomocą słowa **`new`** (lub `new[]`), to Twój destruktor **musi** jawnie zwolnić tę pamięć za pomocą **`delete`** (lub `delete[]`).

W przeciwnym razie po zniszczeniu obiektu wskaźnik zniknie, ale zarezerwowany obszar pamięci RAM zostanie zablokowany aż do zamknięcia całej aplikacji – powstanie tak zwany **wyciek pamięci** (_memory leak_).

### 4. Pułapka: Jawne wywołanie destruktora

> Jawne wywołanie destruktora wykonuje polecenia w nim zawarte, ale nie niszczy samego obiektu.

W C++ technicznym błędem (poza ekstremalnymi przypadkami tzw. _Placement new_) jest ręczne wywoływanie destruktora w ten sposób: `obiekt.~Klasa();`.

Jeśli to zrobisz, komputer wykona kod czyszczący, który zapisałeś w środku funkcji, ale **sam obiekt (jego struktura i pamięć) nadal będzie istniał w systemie!** Co gorsza, gdy obiekt naturalnie dojdzie do końca swojego bloku kodu, system spróbuje wywołać destruktor _po raz drugi_, co natychmiast doprowadzi do awarii i zaorania programu (_Double Free Error_).

### Praktyczny przykład do nauki (Zarządzanie pamięcią)

```cpp
#include <iostream>

class TablicaDynamiczna {
private:
    int* wskaznikNaDane;
    int rozmiar;

public:
    // Konstruktor zamawia pamięć dynamiczną na stercie (heap)
    TablicaDynamiczna(int r) : rozmiar(r) {
        wskaznikNaDane = new int[rozmiar]; 
        std::cout << "Konstruktor: Przydzielono pamiec na " << rozmiar << " elementow.\n";
    }

    // DESTRUKTOR: Sprząta bałagan po konstruktorze
    ~TablicaDynamiczna() {
        delete[] wskaznikNaDane; // Zwalniamy tablicę z RAM-u
        std::cout << "Destruktor: Pamiec zostala bezpiecznie zwolniona.\n";
    }
};

int main() {
    {
        std::cout << "--- Wejscie do bloku ---\n";
        TablicaDynamiczna tab(50); // Uruchamia się konstruktor
        std::cout << "--- Wyjscie z bloku ---\n";
    } // W tym miejscu 'tab' umiera. Automatycznie odpala się jej DESTRUKTOR.

    std::cout << "--- Koniec programu ---\n";
    return 0;
}
```

## Tablice obiektów – Inicjalizacja i warianty konstrukcji

Jak zachowuje się kompilator, kiedy tworzymy tablicę zawierającą wiele obiektów. Sposób inicjalizacji zależy od tego, jak zbudowana jest klasa (czy jest agregatem) oraz gdzie alokujemy pamięć (statycznie czy dynamicznie).

### 1. Kiedy klasa (tablica) jest agregatem?

**Agregat** (_aggregate_) to uproszczony typ danych, który strukturą przypomina tradycyjne rekordy z języka C. Slajd podaje twarde warunki, jakie klasa musi spełnić, by być agregatem:

- **Brak sekcji `private` i `protected`** – wszystkie pola muszą być publiczne (`public`).
    
- **Brak jakichkolwiek własnych konstruktorów** napisanych przez programistę.
    
- **Brak klas podstawowych** – klasa nie może po niczym dziedziczyć.
    
- **Brak funkcji wirtualnych** (`virtual`).
    
#### Jak inicjalizujemy agregaty?

Możemy użyć uproszczonej, klamrowej metody, przypisując wartości bezpośrednio do publicznych pól struktur, pomijając wywołania konstruktorów:

```cpp
struct PunktAgregat {
    int x;
    int y;
};

// Inicjalizacja tablicy agregatów:
PunktAgregat tab[2] = { {1, 2}, {3, 4} }; // Czysto, prosto i bezpośrednio
```

### 2. Kiedy klasa NIE jest agregatem

Jeśli klasa posiada choćby jedno pole prywatne lub własny konstruktor, przestaje być agregatem. Wtedy przy tworzeniu zwykłej (statycznej) tablicy musimy jawnie wywołać konstruktory dla każdego elementu:

```cpp
class PunktKlasyczny {
private:
    int x, y;
public:
    PunktKlasyczny(int g_x, int g_y) : x(g_x), y(g_y) {}
};

// Inicjalizacja wymaga jawnego wywołania konstruktorów:
PunktKlasyczny tab[2] = { PunktKlasyczny(1, 2), PunktKlasyczny(3, 4) };
```

### 3. Tablica tworzona dynamicznie operatorem `new[]`

To kluczowy przypadek, który bardzo często pojawia się na testach automatycznych:

- **Brak jawnej inicjalizacji:** Kiedy rezerwujesz tablicę dynamiczną za pomocą `new Klasa[rozmiar]`, nie możesz po klamrach dopisać listy startowej z unikalnymi wartościami.
    
- **Wymóg konstruktora domniemanego (domyślnego):** Ponieważ kompilator musi stworzyć całą tablicę obiektów naraz i nie zna unikalnych wartości dla każdego z nich, **musi** wywołać konstruktor bezargumentowy. Jeśli Twoja klasa go nie ma, kod się nie skompiluje!

```cpp
// Kompilator rezerwuje pamięć i dla każdego ze 100 obiektów 
// natychmiast odpala konstruktor domyślny:
PunktKlasyczny* dynamicznaTablica = new PunktKlasyczny[100]; 
```

### 4. Nowoczesny standard: Ujednolicona inicjalizacja (C++11 i nowsze)

Ostatni punkt slajdu wspomina o rewolucji, jaką przyniósł standard C++11 wprowadzając klasę szablonową **`std::initializer_list<T>`**.

Dzięki temu mechanizmowi nowoczesny C++ pozwala pisać konstruktory, które potrafią przyjąć dowolnie długą listę elementów w klamrach `{}` i bezpiecznie przepisać ją np. do wewnętrznej tablicy dynamicznej lub kontenera. W ten sposób działają współczesne tablice dynamiczne, czyli `std::vector`:

```cpp
#include <vector>

// Ujednolicona składnia inicjalizacji (Uniform Initialization) działa dla wszystkiego:
std::vector<int> liczby = { 10, 20, 30, 40, 50 }; // Dowolna liczba elementów dzięki initializer_list!
```

### Niejawne deklaracje kompilatora (Zasada pięciu / Zasada sześciu)

![[Pasted image 20260618181620.png]]

Ta tabela to jeden z najważniejszych i najbardziej technicznych tematów w zaawansowanym C++. Pokazuje ona, **jakie specjalne funkcje składowe kompilator wygeneruje automatycznie pod maską**, w zależności od tego, co Ty jako programista zadeklarujesz w swojej klasie.
### 1. Słowniczek pojęć (Nagłówki tabeli)

Tabela analizuje **6 specjalnych funkcji składowych**:
1. **default constructor** – konstruktor domyślny (`Klasa();`)
2. **destructor** – destruktor (`~Klasa();`)
3. **copy constructor** – konstruktor kopiujący (`Klasa(const Klasa&);`)
4. **copy assignment** – kopiujący operator przypisania (`Klasa& operator=(const Klasa&);`)
5. **move constructor** – konstruktor przenoszący (`Klasa(Klasa&&);`)
6. **move assignment** – przenoszący operator przypisania (`Klasa& operator=(Klasa&&);`)

**Oznaczenia w polach:**
- **`defaulted`** – kompilator sam automatycznie wygeneruje tę funkcję pod maską.
- **`not declared`** – kompilator jej NIE utworzy (będzie niedostępna).
- **`user declared`** – to oznacza wersję napisaną jawnie przez Ciebie.
- **`deleted`** – kompilator jawnie zablokuje tę funkcję (jej użycie wywoła błąd kompilacji).
### 2. Kluczowe reguły i zależności (Jak czytać tę tabelę)

#### Reguła A: Święty spokój (Wiersz 1: "Nothing")
Gdy piszesz najprostszą możliwą klasę i nie deklarujesz w niej kompletnie nic (żadnych konstruktorów, destruktorów, operatorów), kompilator jest super pomocny. **Generuje automatycznie wszystkie 6 funkcji (`defaulted`)**. Klasa działa "od strzała" i potrafi się kopiować oraz przenosić.

#### Reguła B: Każdy własny konstruktor blokuje domyślny (Wiersz 2: "Any constructor")
Jeśli napiszesz **jakikolwiek** konstruktor (np. `Punkt(int x, int y);`), kompilator natychmiast uznaje, że wiesz, co robisz, i **NIE wygeneruje konstruktora domyślnego (`not declared`)**. Wszystkie pozostałe mechanizmy (kopiowanie, przenoszenie, destruktor) nadal generuje sam.

#### Reguła C: Pułapka semantyki przenoszenia (Czerwone i szare pola)

Spójrz na wiersze **destructor**, **copy constructor** i **copy assignment**. Te trzy funkcje tworzą tzw. _Zasadę Trzech_.

- Jeśli napiszesz własny destruktor lub własne kopiowanie, kompilator automatycznie **NIE wygeneruje funkcji przenoszących (`not declared`)**.
    
- Współczesny C++ traktuje to zachowanie jako przestarzałe (stąd czerwony kolor pól). Jeśli klasa wymaga ręcznego sprzątania pamięci, to domyślne, ślepe przenoszenie mogłoby zepsuć program.

#### Reguła D: Jawnym przenoszeniem zabijasz kopiowanie (Wiersze ostatnie: "move")

To najbardziej restrykcyjna zasada. Jeśli napiszesz chociaż jedną funkcję przenoszącą (`move constructor` lub `move assignment`):

- Kompilator automatycznie **usuwa i blokuje operacje kopiowania (`deleted`)**!
    
- **Dlaczego?** Skoro programista uznał, że klasa potrzebuje specjalnego, dedykowanego mechanizmu przenoszenia zasobów (np. kradzieży wskaźników), to domyślne, płytkie kopiowanie bajt po bajcie na 100% doprowadziłoby do katastrofy (np. _Double Free Error_). Jeśli chcesz mieć i kopiowanie, i przenoszenie, musisz oba napisać ręcznie.
### Praktyczne podsumowanie dla programisty (_Zasada Pięciu_)

Ta tabela to techniczne uzasadnienie słynnej **Zasady Pięciu** (Rule of Five) w nowoczesnym C++:

> **Zasada Pięciu:** Jeśli Twoja klasa zarządza zasobami (np. dynamiczną pamięcią wskaźnikową) i musisz napisać choćby jeden element z poniższej listy: 
> 1. Ręczny destruktor
> 2. Ręczny konstruktor kopiujący
> 3. Ręczny kopiujący operator przypisania
> 
> To z automatu (patrz tabela) zablokujesz lub popsujesz semantykę przenoszenia. Dlatego **musisz napisać (lub jawnie zadeklarować) wszystkie 5 funkcji**, aby klasa była bezpieczna i wydajna:
> 
> 1. Konstruktor przenoszący 
> 2. Przenoszący operator przypisania

Możesz wymusić na kompilatorze przywrócenie domyślnego zachowania za pomocą słowa kluczowego `= default;`:

Możesz wymusić na kompilatorze usunięcie dostępu za pomocą słowa kluczowego `= delete;`:

```cpp
class MojaKlasa {
public:
    ~MojaKlasa(); // Nasz destruktor (blokuje przenoszenie)

    // Odblokowujemy przenoszenie z powrotem zgodnie z tabelą:
    MojaKlasa(MojaKlasa&&) = default;
    MojaKlasa& operator=(MojaKlasa&&) = default;
};
```

## Wskaźniki do składników klas i metod

To jeden z najbardziej specyficznych i rzadziej spotykanych tematów w C++. Opisuje mechanizm, w którym wskaźnik **nie pokazuje na konkretny adres w pamięci RAM**, ale definiuje "względną ścieżkę" do pola lub funkcji wewnątrz abstrakcyjnej struktury klasy.

### 1. Zwykły wskaźnik vs Wskaźnik do składowej klasy

- **Zwykły wskaźnik (do konkretnego obiektu):** Jeśli masz już stworzony konkretny obiekt w pamięci, możesz pobrać bezpośredni adres jego publicznego pola. Działa to jak klasyczny wskaźnik z języka C:
    
    ```cpp
    int *a = &obiekt.skladnik_int; // Pokazuje na realny, fizyczny adres w RAM
    ```
    
- **Wskaźnik do składowej klasy (`::*`):** To jest kluczowa nowość ze slajdu. Taki wskaźnik **nie wie, jaki obiekt ma modyfikować**. On opisuje jedynie przesunięcie (ang. _offset_) – czyli informację: _"jak daleko od początku struktury klasy leży dana zmienna"_. Dzięki temu możesz stworzyć wskaźnik uniwersalny, a konkretny obiekt podstawić dopiero przy wywołaniu.
#### Składnia deklaracji:

```cpp
// Typ_Zmiennej Nazwa_Klasy::*Nazwa_Wskaźnika = &Nazwa_Klasy::Pole;
int K::*wsk = &K::skladnik_int;
```

### 2. Wskaźniki do składowych statycznych (`static`)

> Wskaźniki do składników statycznych mogą być tylko zwykłymi wskaźnikami.

**Dlaczego?** Zmienna statyczna nie leży wewnątrz struktury obiektu. Ona żyje w pamięci globalnej programu jako jedna wspólna dana. Dlatego do pola `static` nie używa się składni `::*`, lecz zwykłego, klasycznego wskaźnika: `int* wskStatyczny = &Klasa::poleStatyczne;`.

### 3. Wskaźnik do funkcji składowej (Metody klasy)

W analogiczny sposób możemy zapisać adres metody należącej do klasy, by wywołać ją elastycznie później. Składnia wymaga dodatkowych nawiasów, aby kompilator nie pomylił jej ze zwracanym typem wskaźnikowym:

```cpp
// Deklaracja wskaźnika do funkcji, która przyjmuje float i zwraca int:
int (K::*wskMetody)(float);

// Przypisanie adresu metody:
wskMetody = &K::mojaMetoda;
```

### 4. Jak tego używać w kodzie? Operators `.*` oraz `->*`

Skoro wskaźnik reprezentuje tylko ogólne "przesunięcie", to aby go użyć, musimy fizycznie podać obiekt. Służą do tego specjalne, rzadkie operatory:

- `.*` – używany, gdy pracujemy na zwykłym obiekcie.
    
- `->*` – używany, gdy pracujemy na wskaźniku do obiektu.

```cpp
K obiekt;
K* wskaznikNaObiekt = &obiekt;

// Wywołanie zmiennej przez wskaźnik do składowej:
obiekt.*wsk = 5;
wskaznikNaObiekt->*wsk = 10;

// Wywołanie metody przez wskaźnik do metody:
(obiekt.*wskMetody)(3.14f);
```

### 5. Nowoczesny standard (C++17): Wybawienie w postaci `std::invoke`

Z powodu potwornej, mało czytelnej składni pełnej nawiasów (jak widać powyżej), standard C++17 wprowadził ujednoliconą funkcję narzędziową **`std::invoke()`**.

Ostatni punkt slajdu zaleca jej używanie, ponieważ całkowicie ukrywa ona przed programistą skomplikowane operatory `.*` czy `->*`. Składnia staje się czysta i identyczna dla każdego rodzaju wskaźnika:

```cpp
#include <functional> // Wymagane dla std::invoke

int main() {
    K obiekt;
    int K::*wskPola = &K::skladnik_int;
    int (K::*wskMetody)(float) = &K::mojaMetoda;

    // Nowoczesny i czytelny sposób z C++17:
    std::invoke(wskPola, obiekt) = 42;          // Ustawianie pola
    std::invoke(wskMetody, obiekt, 3.14f);      // Wywołanie metody
    
    return 0;
}
```
### Podsumowanie do nauki:

- **Po co to jest?** Do zaawansowanych mechanizmów (np. pisania systemów refleksji, mapowania baz danych ORM czy systemów zdarzeń/callbacków), gdzie funkcja musi dynamicznie decydować, na której właściwości obiektu ma przeprowadzić operację.
    
- **Tablice wskaźników:** Jak wspomina slajd, możesz stworzyć tablicę takich wskaźników, co pozwala np. w pętli uruchomić serię różnych metod na rzecz jednego obiektu.

## Konwersje typów (Casting i konwersje obiektowe)

Konwersja typów to proces przekształcania wartości jednego typu na inny. W języku C++ proces ten staje się znacznie bardziej skomplikowany niż w tradycyjnym C, ponieważ dotyczy nie tylko typów prostych (jak `int` na `float`), ale również całych obiektów klas.

### 1. Podział podstawowy: Konwersje jawne i niejawne

- **Konwersja niejawna (Implicit conversion):** Automatyczna operacja wykonywana przez kompilator pod maską, bez wyraźnej prośby ze strony programisty.
    
- **Konwersja jawna (Explicit conversion / Casting):** Świadome, wymuszone przez programistę rzutowanie jednego typu na drugi za pomocą odpowiednich operatorów.
    

> ⚠️ **Zasada ogólna:** Konwersje dla typów obiektowych (klas) **muszą** zostać jawnie zaprogramowane przez twórcę klasy. Kompilator nie domyśli się, jak zmienić obiekt klasy `Uzytkownik` na typ `std::string`, dopóki sam mu tego nie rozpiszesz.

### 2. Kiedy dochodzi do konwersji niejawnych?

Kompilator wykonuje autonomiczną konwersję w kilku kluczowych sytuacjach:

1. **Wywołanie funkcji:** Gdy typ argumentu przekazanego w nawiasie nie pasuje idealnie do deklaracji, ale istnieje jednoznaczna droga konwersji (np. przekazanie `int`, podczas gdy funkcja oczekuje `float`).
    
2. **Instrukcja `return`:** Gdy funkcja ma zwrócić np. `double`, a Ty zwracasz zmienną typu `int`.
    
3. **Działanie operatorów:** Przy operacjach matematycznych (np. `5 + 3.14`). Kompilator sprowadza oba operandy do wspólnego, bezpieczniejszego typu (w tym przypadku `5` zamienia się na `5.0`).
    
4. **Instrukcje warunkowe (`if`, `switch`, `while`, `for`):** Wyrażenia w nawiasach są automatycznie sprowadzane do typu logicznego `bool`.
    
5. **Wyrażenia inicjalizujące:** Zapis typu `float x = 10;`.

> 💡 **Zasada do nauki:** Należy unikać pisania kodu, który opiera się na nietypowych konwersjach niejawnych. Kod staje się wtedy nieczytelny i podatny na trudne do wyłapania błędy logiczne.

### 3. Konwersja w stronę obiektu: Konstruktor konwertujący

Jeśli chcesz, aby system potrafił automatycznie zamienić jakiś typ (np. `int`) na obiekt Twojej klasy, używasz **konstruktora jednoargumentowego** (lub takiego, który ma jeden wymagany argument, a reszta ma wartości domyślne).

```cpp
class Zespolona {
public:
    double rzeczywista, urojona;
    
    // Konstruktor konwertujący: pozwala zamienić double na obiekt Zespolona
    Zespolona(double r) : rzeczywista(r), urojona(0.0) {}
};
```

### Pułapki i ograniczenia konstruktorów konwertujących:

- Nie można napisać konstruktora konwertującego dla typu wbudowanego ani dla obcych, gotowych klas (musisz mieć dostęp do kodu modyfikowanej klasy).
    
>  **Słowo kluczowe `explicit` (Krytyczne!):** Domyślnie jednoargumentowy konstruktor pozwala na konwersję _niejawną_. Jeśli napiszesz `Zespolona z = 5;`, kompilator po cichu uruchomi ten konstruktor. Aby to zablokować i wymusić tylko konwersje jawne, przed konstruktorem **musisz dopisać słowo `explicit`**.

```cpp
class Specjalna {
public:
    explicit Specjalna(int x) {} // Blokuje niejawne: Specjalna s = 5;
};
```

### 4. Konwersja z obiektu na inny typ: Funkcja konwertująca

Jeśli chcesz wykonać ruch w drugą stronę – czyli wyciągnąć z obiektu typ prosty lub obiekt innej klasy – stosujesz **operator konwersji (funkcję konwertującą)**.
#### Cechy formalne operatora konwersji:

- Musi być funkcją składową (metodą) klasy.
    
- **Nie posiada określonego typu zwracanego** (sam fakt, jak się nazywa, określa co zwraca).
    
- Zawsze zwraca typ taki, jak nazwa operatora.
    
- Nie przyjmuje żadnych argumentów i **powinna być oznaczona jako `const`**.
    
- Jest dziedziczona przez klasy potomne i może być wirtualna.
    

```cpp
class Ulamek {
private:
    int licznik = 3, mianownik = 4;
public:
    // Funkcja konwertująca obiekt klasy Ulamek na zwykły typ float:
    operator float() const {
        return (float)licznik / mianownik;
    }
};
```

### Nowoczesne podejście (C++11 / C++20):

- **W C++11** wprowadzono możliwość dopisania `explicit` również przed operatorem konwersji (`explicit operator float() const;`). Blokuje to przypadkowe, niejawne rzutowania.
    
- **W C++20** wprowadzono wersję warunkową: `explicit(wyrażenie_boolowskie) operator T();`, gdzie blokada aktywuje się tylko wtedy, gdy podany warunek logiczny zostanie spełniony.

## 5. Projektowanie konwersji: Którą drogę wybrać?

Slajdy dają jasne wytyczne architektoniczne:
1. **Do typu wbudowanego (np. klasy na `int`):** Stosuj wyłącznie _funkcję konwertującą_ (operator konwersji) wewnątrz swojej klasy.
    
2. **Między dwiema klasami (Klasa A na Klasę B):** * Napisz funkcję konwertującą w klasie A, lub...
    
    - Napisz konstruktor konwertujący w klasie B (używaj tego sposobu tylko wtedy, gdy klasa A jest zamknięta i nie możesz jej edytować).
        
3. **Ważne ostrzeżenie:** **Nigdy nie definiuj obu metod jednocześnie!** Jeśli klasa A ma operator konwersji na B, a klasa B ma konstruktor przyjmujący A, kompilator przy próbie niejawnego rzutowania zgłosi błąd niejednoznaczności i zablokuje program.

> 🛠️ **Zasada dobrego stylu:** Nie mnóż operatorów konwersji bez potrzeby. Bezpieczniej i czytelniej jest napisać zwykłą publiczną metodę o nazwie typu `.toDynamicString()` lub `.asInt()`, niż polegać na ukrytych automatycznych operatorach.

### 6. Jawne rzutowania w C++ (Konwersje jawne)

C++ odziedziczył po języku C tradycyjne rzutowanie w nawiasie: `(int)zmienna;`. Jest ono jednak wysoce niezalecane, ponieważ działa "na ślepo" i potrafi brutalnie złamać zabezpieczenia systemu typów.

W zamian C++ wprowadza trzy bezpieczne, specjalistyczne operatory rzutowania:

### A. `static_cast<typ>(zmienna)` – Najważniejszy i najczęstszy

- Służy do standardowych, logicznych konwersji (np. `float` na `int`, konwersje wskaźników w bezpiecznej hierarchii dziedziczenia klas).
    
- Uwzględnia budowę klas i sprawdza poprawność typów w trakcie kompilacji.

### B. `const_cast<typ>(zmienna)` – Ściąganie blokady stałości

- Służy **wyłącznie** do modyfikowania lub usuwania przydomka `const` (lub `volatile`) ze wskaźnika lub referencji.
    
- Pozwala przekazać stały obiekt do starej funkcji, która nie ma oznaczenia `const`, ale wiemy, że nie zepsuje danych.

### C. `reinterpret_cast<typ>(zmienna)` – Rzutowanie surowych bitów

- Najbardziej niebezpieczny operator. Nakazuje kompilatorowi traktować surowe bity w pamięci RAM tak, jakby były zupełnie innym typem danych (np. zamiana wskaźnika na obiekt na surową liczbę `unsigned int`).
    
- Wykorzystywany głównie przy programowaniu niskopoziomowym lub sterownikach urządzeń. Nie wykonuje żadnych logicznych przekształceń danych.

## Przestrzenie nazw `namespace`

**Przestrzeń nazw** to mechanizm służący do logicznego grupowania klas, funkcji oraz zmiennych w pakiety i komponenty.

### 1. Po co stosujemy przestrzenie nazw?

Głównym celem jest **unikanie konfliktów nazw**. Wyobraź sobie sytuację, w której piszesz dużą grę i tworzysz klasę `Bohater`. Jednocześnie pobierasz zewnętrzną bibliotekę sieciową, w której autor również stworzył klasę `Bohater`. Bez przestrzeni nazw kompilator zgłosi błąd, ponieważ nie potrafi odróżnić tych dwóch struktur. Zamknięcie ich w osobnych obszarach całkowicie rozwiązuje ten problem.

- **Dowolność podziału:** Wewnątrz przestrzeni można umieszczać dowolne symbole (funkcje, zmienne, klasy, struktury).
    
- **Rozbicie na pliki:** Elementy należące do tej samej przestrzeni nazw mogą być fizycznie rozrzucone w wielu różnych plikach źródłowych `.cpp` i nagłówkowych `.hpp`. Kompilator zbierze je w jedną logiczną całość.
    

### 2. Dostęp do symboli (Składnia)

Aby wyciągnąć element z przestrzeni nazw, musimy użyć nazwy tej przestrzeni oraz **operatora zakresu `::`**:

```cpp
namespace A {
    class Nazwa {}; 
}

int main() {
    A::Nazwa obiekt; // Pełna ścieżka dostępu
}
```

### 3. Sposoby upraszczania składni

Pisanie przed każdą funkcją pełnej ścieżki (np. `std::cout`, `std::string`, `std::vector`) bywa uciążliwe. C++ pozwala na skrócenie zapisu na trzy sposoby:

#### A. Deklaracja `using` (Punktowa)

Wprowadza do bieżącego bloku kodu **tylko jeden wybrany symbol**. Od tej pory staje się on synonimem pełnej ścieżki.

```cpp
using OOP::Point;
Point p1; // Kompilator wie, że chodzi o OOP::Point
```

#### B. Dyrektywa `using namespace` (Hurtowa)

Wprowadza **wszystkie symbole** z danej przestrzeni bezpośrednio do bieżącego bloku kodu. Są one traktowane tak, jakby były zmiennymi i funkcjami globalnymi.

```cpp
using namespace OOP;
// Wszystkie klasy i funkcje z OOP są teraz dostępne bez prefiksów!
```

#### C. Alias przestrzeni nazw (Skrót nazwy)

Przydatny, gdy przestrzenie nazw są głęboko zagnieżdżone i mają bardzo długie, skomplikowane nazwy.

```cpp
namespace skrot = nested_name::ns_name;
```

### ⚠️ Ważne ostrzeżenia i pułapki egzaminacyjne

- **Możliwość dwuznaczności:** Jeśli użyjesz `using namespace A;` oraz `using namespace B;`, a w obu tych przestrzeniach znajduje się funkcja `uruchom()`, to przy próbie wywołania samego `uruchom();` kompilator zgłosi błąd niejednoznaczności.
    
- **ZAKAZ w plikach nagłówkowych:** > **Żelazna zasada stylu:** Nigdy nie umieszczaj instrukcji `using namespace` w plikach nagłówkowych (`.h` / `.hpp`).
    
Jeśli wpiszesz `using namespace std;` w pliku `.h`, to każdy programista, który dołączy Twój nagłówek za pomocą `#include`, zostanie "zanieczyszczony" całą biblioteką standardową i straci ochronę przed konfliktami nazw. Dyrektywę `using` stosuj wyłącznie lokalnie wewnątrz plików źródłowych `.cpp` lub konkretnych funkcji.
    
## Obiekty stałe jako zmienne `mutable`

Modyfikator `const` nałożony na obiekt gwarantuje, że żadne pole tego obiektu nie zostanie zmienione, a programista może wywoływać na nim wyłącznie metody z przydomkiem `const`. Czasami jednak zachodzi potrzeba złamania tej zasady dla pojedynczych zmiennych składowych. Służy do tego słowo kluczowe **`mutable`**.

### 1. Kiedy pojawia się problem?

Wyobraź sobie klasę, która czyta dane z pliku tekstowego. Obiekt tej klasy jest logicznie stały (`const`), ponieważ reprezentuje ten sam, niezmienny plik na dysku. Plik ma określoną liczbę wierszy, ale nie znamy jej w czasie kompilacji – dowiemy się tego dopiero w trakcie działania programu, kiedy po raz pierwszy przeczytamy plik i zliczymy linijki.

Gdybyśmy chcieli zapisać tę policzoną liczbę wierszy do pola wewnątrz obiektu stałego, kompilator wyrzuciłby błąd.

### 2. Rozwiązanie: Modyfikator `mutable`

Oznaczenie pola słowem `mutable` sprawia, że **może być ono modyfikowane nawet wewnątrz stałych funkcji składowych (`const`) oraz na rzecz stałych obiektów**.

- **Logiczna stałość:** Zmiana pola `mutable` nie wpływa na ogólną, logiczną stałość obiektu z punktu widzenia użytkownika zewnętrznego (obiekt dla świata nadal zachowuje się jak niezmienny).

```cpp
#include <iostream>

class CzytnikPlikow {
private:
    std::string sciezka;
    
    // Pole mutable: pozwala na modyfikację wewnątrz metod const
    mutable int liczbaWierszy = -1; 

public:
    CzytnikPlikow(std::string s) : sciezka(s) {}

    // Metoda jest const (obserwator), ale modyfikuje pole mutable
    int pobierzLiczbeWierszy() const {
        if (liczbaWierszy == -1) {
            // Symulacja liczenia wierszy w pliku
            liczbaWierszy = 150; // Działa tylko dzięki mutable!
        }
        return liczbaWierszy;
    }
};

int main() {
    const CzytnikPlikow plik("dane.txt"); // Obiekt jest w pełni STAŁY
    
    // Wywołanie metody const zmienia pod maską pole mutable:
    std::cout << "Liczba wierszy: " << plik.pobierzLiczbeWierszy() << "\n";
    
    return 0;
}
```

### Zastosowanie w praktyce:

Słowo `mutable` stosuje się najczęściej do mechanizmów technicznych ukrytych przed użytkownikiem klasy:

- **Pamięć podręczna (Cache):** Tak jak w przykładzie powyżej – obliczamy coś raz, a potem pamiętamy wynik.
    
- **Liczniki statystyk:** Zliczanie, ile razy dana metoda `const` została wywołana w programie.
    
- **Wątki i sekcje krytyczne (`std::mutex`):** Blokowanie zasobów w klasie za pomocą muteksów musi odbywać się również w metodach odczytujących dane (`const`), dlatego muteksy w klasach niemal zawsze deklaruje się jako `mutable std::mutex`.

# ~={orange}Przeładowanie operatorów=~

### Przeładowywanie operatorów

**Przeładowywanie operatorów** to mechanizm w C++, który pozwala nadać istniejącym operatorom (takim jak `+`, `-`, `*`, `<<`, `==`) nowe znaczenie, gdy są one używane w kontekście obiektów naszych własnych klas. Zamiast pisać nieczytelne metody typu `u1.dodaj(u2)`, możemy po prostu napisać `u1 + u2`.

### 1. Reguły i twarde ograniczenia (Czego NIE wolno zmieniać)

Mimo dużej swobody, standard C++ narzuca sztywne granice:
- **Nie wymyślisz nowych symboli* 
    
- **Nie zmienisz priorytetów ani łączności:** Operator `*` zawsze będzie wykonywał się przed operatorem `+`, a przypisanie `=` zawsze wiąże od prawej do lewej.
    
- **Nie zmienisz arności (argumentowości):** Operator dwuargumentowy (np. `+`) zawsze musi przyjmować dwa operandy. Operator jednoargumentowy (np. `!`) zawsze przyjmuje jeden.
    
- **Zawsze zachowują wersję automatyczną:** Następujące operatory są generowane automatycznie przez kompilator dla każdej klasy: przypisanie `=`, pobranie adresu `&`, oraz zarządzanie pamięcią `new` i `delete`.
### Operatory, których NIE MOŻNA przeładować (Ważne na testy!):

- `.` (kropka – dostęp do składowych)
    
- `.*` (dostęp do składowych przez wskaźnik)
    
- `::` (operator zakresu)
    
- `?:` (operator warunkowy)
### 2. Funkcja operatorowa jako metoda składowa klasy

Gdy przeładowujesz operator wewnątrz klasy jako jej metodę, obiekt po lewej stronie operatora staje się automatycznie wykonawcą tej metody (reprezentuje go ukryty wskaźnik `this`).

- **Zasada jednego argumentu mniej:** Ponieważ lewy operand to `this`, funkcja operatorowa w nawiasie przyjmuje o **jeden parametr mniej** niż w wersji globalnej.
    
    - Dla operatora dwuargumentowego (`+`): przyjmuje tylko **jeden** parametr (prawy operand).
        
    - Dla operatora jednoargumentowego (`!`): przyjmuje **zero** parametrów.
        
- **Ograniczenia:** Nie może być funkcją statyczną (`static`), ponieważ musi mieć dostęp do `this`.
    
- **Wymóg lewej strony:** Lewym operandem **musi** być obiekt tej konkretnej klasy.

```cpp
class Wektor {
public:
    int x, y;
    // Operator dwuargumentowy jako metoda klasy (przyjmuje tylko prawy operand)
    Wektor operator+(const Wektor& prawy) const {
        return Wektor{this->x + prawy.x, this->y + prawy.y};
    }
};

// Pod maską: w1 + w2  ==>  w1.operator+(w2)
```

> ⚠️ **Tylko jako metody:** Operatory `=`, `()`, `[]`, oraz `->` **muszą** być zadeklarowane wyłącznie jako metody składowe klasy. Nie mogą być funkcjami globalnymi.

### 3. Funkcja operatorowa jako funkcja globalna

Alternatywnym sposobem jest napisanie luźnej funkcji poza strukturą klasy.

- **Pełna lista argumentów:** Funkcja globalna nie posiada wskaźnika `this`. Musi przyjąć w nawiasie pełną liczbę operandów (dwa dla operatorów binarnych, jeden dla unarnych).
    
- **Kwestia przyjaźni (`friend`):** Funkcja globalna nie musi być zaprzyjaźniona z klasą, o ile klasa udostępnia publiczne metody do odczytu danych (tzw. gettery). Jeśli jednak musi bezpośrednio czytać prywatne pola klasy, należy wewnątrz klasy dodać przedrostek `friend`.
    
- **Rozszerzanie obcych klas:** Pozwala na definiowanie operatorów dla klas, których kodu nie możemy edytować (np. klas bibliotecznych). Klasycznym przykładem jest przeładowanie operatora przesunięcia bitowego `<<` do współpracy z `std::cout`:

```cpp
// Przeładowanie globalne dla: std::cout << wektor;
std::ostream& operator<<(std::ostream& strumien, const Wektor& w) {
    strumien << "[" << w.x << ", " << w.y << "]";
    return strumien;
}
```

### 4. Problem przemienności (Kluczowy wybór metody)

Slajd pt. "Przemienność" pokazuje najważniejszy powód, dla którego programista decyduje się na wybór funkcji globalnej zamiast metody klasy.

Wyobraź sobie klasę `Fraction` (Ułamek), dla której chcesz przeładować mnożenie przez zwykłą liczbę całkowitą `int`:

### Scenariusz A: Operator jako metoda klasy

Definiujesz w klasie: `Fraction Fraction::operator*(int i);`

- Zapis `aFraction * 2` zadziała idealnie $\rightarrow$ pod maską: `aFraction.operator*(2)`.
    
- Zapis `2 * aFraction` wygeneruje **BŁĄD KOMPILACJI**, ponieważ liczba `2` nie jest obiektem klasy `Fraction` i nie potrafi wywołać metody `.operator*()`.
    

### Scenariusz B: Rozwiązanie przez funkcję globalną

Aby zapewnić pełną przemienność mnożenia, musisz dopisać dedykowaną **funkcję globalną**, w której zamieniasz argumenty miejscami w nawiasie:

C++

```
class Fraction {
    // ...
};

// Ta funkcja globalna ratuje sytuację, gdy liczba stoi po LEWEJ stronie:
Fraction operator*(int i, const Fraction& K) {
    // wykonaj mnożenie i zwróć wynik
}
```

#### Przykład 1: Klasa `Pieniadz` (Dodawanie int/double do obiektu)

Wyobraź sobie klasę obsługującą finanse. Chcesz móc dodać do kwoty zwykłą premię zapisaną jako `double`.
```cpp
#include <iostream>

class Pieniadz {
private:
    double kwota;
public:
    Pieniadz(double k) : kwota(k) {}

    void wyswietl() const { std::cout << kwota << " PLN\n"; }

    // Zezwalamy funkcjom globalnym na zaglądanie do prywatnego pola 'kwota'
    friend Pieniadz operator+(const Pieniadz& p, double d);
    friend Pieniadz operator+(double d, const Pieniadz& p);
};

// Scenariusz A: Portfel + Liczba (np. portfel + 50.0)
Pieniadz operator+(const Pieniadz& p, double d) {
    return Pieniadz(p.kwota + d);
}

// Scenariusz B: Liczba + Portfel (np. 50.0 + portfel)
// Tutaj uzyskujemy przemienność!
Pieniadz operator+(double d, const Pieniadz& p) {
    // Sprytny trik: zamiast przepisywać logikę, 
    // wywołujemy po prostu Scenariusz A, bo wiemy że on już działa!
    return p + d; 
}

int main() {
    Pieniadz portfel(100.0);

    Pieniadz opcja1 = portfel + 50.50; // Działa Scenariusz A
    Pieniadz opcja2 = 50.50 + portfel; // Działa Scenariusz B (Przemienność!)

    opcja1.wyswietl(); // 150.5 PLN
    opcja2.wyswietl(); // 150.5 PLN
}
```

#### Przykład 2: Klasa `String` (Łączenie napisów – Obiekt + `const char*`)

To klasyka z biblioteki standardowej (`std::string`). Chcesz móc bez problemu łączyć swój własny obiekt tekstowy ze zwykłym tekstem w cudzysłowie.

- **Opcja A (Metoda klasy):** `mojString + " tekst"` działoby bez problemu.
    
- **Opcja B (Przemienność):** `"tekst " + mojString` wywali błąd, bo surowy wskaźnik tekstowy `const char*` nie posiada metod.

Rozwiązujemy to ponownie parą funkcji globalnych:
```cpp
class MojaStrona {
    // ... wewnątrz klasy ...
    friend std::string operator+(const MojaStrona& obj, const char* tekst);
    friend std::string operator+(const char* tekst, const MojaStrona& obj);
};
```

### Przykład 3: Klasa `Wektor2D` i mnożenie przez skalar (Liczba)

W fizyce i grafice komputerowej przemienność jest obowiązkowa przy mnożeniu wektora przez liczbę (skalowanie długości). Mnożenie wektora $[2, 3]$ przez liczbę $4$ musi dawać dokładnie to samo, co $4$ pomnożone przez $[2, 3]$.

```cpp
#include <iostream>

class Wektor2D {
public:
    double x, y;
    Wektor2D(double x, double y) : x(x), y(y) {}

    // Metoda klasy załatwia nam sprawę: Wektor * Liczba
    Wektor2D operator*(double skalar) const {
        return Wektor2D(x * skalar, y * skalar);
    }
};

// FUNKCJA GLOBALNA załatwia nam przemienność: Liczba * Wektor
// Nie musi być friend, bo x i y są publiczne!
Wektor2D operator*(double skalar, const Wektor2D& wektor) {
    // Przekierowujemy wywołanie do metody klasy (zamieniamy kolejność na działającą)
    return wektor * skalar; 
}

int main() {
    Wektor2D v(2.0, 5.0);

    Wektor2D v1 = v * 3.0;   // Wywoła metodę klasy
    Wektor2D v2 = 3.0 * v;   // Wywoła funkcję globalną (Przemienność!)
    
    // Oba wektory mają teraz prawidłowe współrzędne [6.0, 15.0]
}
```
### Ściągawka do wyboru sposobu implementacji:

| **Sytuacja**                                                         | **Preferowany sposób** | **Dlaczego?**                                                                                           |
| -------------------------------------------------------------------- | ---------------------- | ------------------------------------------------------------------------------------------------------- |
| Modyfikuje lewy operand (np. `+=`, `-=`, `=`)                        | **Metoda klasy**       | Ściśle powiązana z obiektem, intuicyjny dostęp do `this`.                                               |
| Operatory unarne (np. `!`, `-` jednostkowy)                          | **Metoda klasy**       | Czysta składnia bezparametrowa.                                                                         |
| Lewy operand jest innego typu niż klasa (np. `std::ostream`, `int`)  | **Funkcja globalna**   | Niemożliwe do zaimplementowania jako metoda własnej klasy (lewa strona determinuje właściciela metody). |
| Chcemy uzyskać przemienność (np. `Obiekt * int` oraz `int * Obiekt`) | **Funkcja globalna**   | Pozwala na swobodne zadeklarowanie typów po lewej i prawej stronie w argumentach funkcji.               |
### Ważna uwaga: Konwersje niejawne a Przemienność

Jeżeli Twoja klasa posiada **konstruktor konwertujący** (np. jednoargumentowy konstruktor przyjmujący `int` bez słowa `explicit`), to pisanie operatorów jako **funkcji globalnych** daje dodatkowy, potężny bonus.

Jeśli masz funkcję globalną:
```cpp
Fraction operator+(const Fraction& lewy, const Fraction& prawy);
```

I spróbujesz napisać: `Fraction wynik = 5 + mojUlemek;` Kompilator zauważy, że liczba `5` stoi na pozycji argumentu typu `Fraction`. Ponieważ jest to funkcja globalna, kompilator automatycznie przekształci to pod maską w: `Fraction wynik = Fraction(5) + mojUlemek;`

Gdybyś ten operator napisał jako **metodę klasy**, taka automatyczna konwersja dla lewej strony **nigdy by nie zaszła**, bo lewa strona musi być nienagannym obiektem na starcie. To kolejny powód, dla którego operatory matematyczne (`+`, `-`, `*`, `/`) niemal zawsze projektuje się jako **funkcje globalne**.

## Operatory, które muszą być funkcjami składowymi – Kompletne notatki

W języku C++ istnieją cztery specyficzne operatory, których **nie wolno** przeładować jako funkcji globalnych. Projektanci języka zdecydowali, że ich działanie jest tak mocno powiązane z tożsamością konkretnego obiektu, że **muszą być zadeklarowane wyłącznie jako metody składowe klasy**. Są to operatory: `=`, `[]`, `()` oraz `->`.

## 1. Kopiujący operator przypisania (`operator=`)

Służy do nadpisania zawartości już istniejącego obiektu danymi z innego obiektu tej samej klasy (np. `obiektA = obiektB;`).

- **Automatyczne generowanie:** Kompilator domyślnie tworzy go sam. Przepisuje on dane składowa po składowej (płytka kopia).
    
- **Kiedy płytka kopia to błąd?** Jeśli klasa zawiera wskaźniki do pamięci dynamicznej (`new`), domyślne przypisanie skopiuje tylko surowe adresy, co doprowadzi do awarii programu przy niszczeniu obiektów.
    
- **Kiedy kompilator go NIE wygeneruje automatycznie?**
>   - Gdy klasa posiada pole będące stałą (`const`).
  > - Gdy klasa posiada pole będące referencją (`&`).
 >  - Gdy klasa zawiera inny obiekt (lub dziedziczy po klasie), który ma swój operator przypisania w sekcji `private`.
        
- **Brak dziedziczenia:** Operator `=` nie jest dziedziczony przez klasy potomne w tradycyjny sposób.
    
- **Struktura kodu:** Prawidłowo napisany, ręczny operator przypisania łączy w sobie:
    1. **Część destruktorową:** zwolnienie pamięci, którą obiekt aktualnie zajmuje.
    2. **Część konstruktorową:** alokacja nowej pamięci i głębokie skopiowanie nowych danych.
    3. **Zabezpieczenie przed przypisaniem do samego siebie** (np. `w = w;`).

```cpp
class Tablica {
private:
    int* dane;
    int rozmiar;
public:
    // Klasyczna, bezpieczna struktura operatora=
    Tablica& operator=(const Tablica& zrodlo) {
        if (this == &zrodlo) return *this; // Zabezpieczenie przed samoprzypisaniem

        delete[] dane; // 1. Część destruktorowa
        
        rozmiar = zrodlo.rozmiar;
        dane = new int[rozmiar]; // 2. Część konstruktorowa
        for(int i=0; i<rozmiar; ++i) dane[i] = zrodlo.dane[i];

        return *this; // Zwracamy referencję Tablica&, by móc pisać: a = b = c;
    }
};
```

## 2. Przenoszący operator przypisania (`operator=`) – Nowy `operator=`

Wprowadzony w C++11. Wywoływany automatycznie, gdy po prawej stronie znaku `=` stoi **wartość tymczasowa (rvalue)**, czyli obiekt, który system za chwilę i tak bezpowrotnie zniszczy.

```cpp
class_name& class_name::operator=(class_name&& tymczasowy);
```

- **Mechanika działania:** Zamiast kserować dane, operator ten błyskawicznie **"kradnie" (przepina) wskaźniki** do zasobów od obiektu tymczasowego, a obiekt źródłowy pozostawia pusty (wyzerowany).
    
- **Kiedy jest generowany automatycznie?** Tylko w idealnej sytuacji, gdy programista nie napisał własnego konstruktora kopiującego, przenoszącego, operatora przypisania ani destruktora (zgodnie z macierzą deklaracji kompilatora).
    
- **Optymalizacja `std::memmove`:** Jeśli obiekt jest tzw. "trywialny" (nie posiada funkcji wirtualnych ani skomplikowanych klas bazowych), kompilator optymalizuje przenoszenie całej tablicy obiektów do superszybkiej operacji niskopoziomowego kopiowania bloków pamięci.

## 3. Operator indeksowania (`operator[]`)

Używany najczęściej przy budowaniu własnych kontenerów, kolekcji lub bezpiecznych tablic dynamicznych.

- **Zasada działania:** Powinien wiernie naśladować zachowanie zwykłych tablic wbudowanych.
    
- **Wymóg zwracania referencji:** Aby operator pozwalał zarówno na odczyt, jak i na modyfikację elementu pod danym indeksem, musi zwracać **referencję** (`&`) do obiektu.

```cpp
// Definicja wewnątrz klasy:
int& operator[](unsigned int i) {
    return dane[i]; 
}

// Dzięki referencji int& możliwe są oba zapisy:
int x = tab[5]; // Odczyt
tab[5] = 20;    // Zapis/Modyfikacja
```

## 4. Operator wywołania funkcji (`operator()`)

Niezwykle elastyczny operator, który pozwala traktować zwykły obiekt klasy tak, jakby był tradycyjną funkcją. Klasę posiadającą ten operator nazywamy **funktorem** (obiektem funkcyjnym).

- **Dowolna liczba parametrów:** Jako jedyny z operatorów może przyjmować kompletnie dowolną liczbę argumentów (w tym zero).
    
- **Tablice wielowymiarowe:** Może służyć jako zamiennik indeksowania dla macierzy lub tablic wielowymiarowych, obchodząc ograniczenie operatora `[]`, który przyjmuje tylko jeden indeks.
    ```cpp
    macierz(1, 2, 3) = 10.5; // Wywołanie operatora (int, int, int)
    ```
    
- **Współpraca z STL:** Funktory są fundamentem algorytmów biblioteki standardowej (np. do precyzyjnego sortowania obiektów, filtrowania danych jako predykaty).
    

### 5. Operator dostępu do składowych przez wskaźnik (`operator->`)

Używany rzadko w klasach biznesowych, ale stanowi absolutny fundament techniczny podczas tworzenia tzw. **inteligentnych wskaźników** (_smart pointers_, np. `std::unique_ptr` czy `std::shared_ptr`).

- **Zastosowanie:** Przeładowuje się go w klasach, które z założenia mają udawać i opakowywać zachowanie tradycyjnych, surowych wskaźników, dając przy tym bezpieczeństwo automatycznego zarządzania pamięcią.

```cpp
#include <iostream>

class InteligentyWskaźnik {
private:
    int* surowyWskaznik;
public:
    InteligentyWskaźnik(int* p) : surowyWskaznik(p) {}
    ~InteligentyWskaźnik() { delete surowyWskaznik; }

    // Przeładowanie operatora ->
    int* operator->() {
        return surowyWskaznik;
    }
};
```

Chcemy stworzyć klasę `SmartPointer`, która będzie zachowywać się dokładnie tak jak zwykły wskaźnik, czyli pozwoli nam wywołać metody ukrytego obiektu za pomocą strzałki (`->`).

```cpp
#include <iostream>
#include <string>

class Samochod {
private:
    std::string marka;
public:
    Samochod(std::string m) : marka(m) {}
    
    void odpalSilnik() {
        std::cout << marka << ": Wrrr! Silnik odpala.\n";
    }
};

// Klasa opakowująca, która udaje wskaźnik
class SmartPointer {
private:
    Samochod* surowyWskaznik; // Prawdziwy, surowy wskaźnik pod maską
public:
    SmartPointer(Samochod* s) : surowyWskaznik(s) {}

    // Destruktor automatycznie zwalnia pamięć! Koniec z wyciekami pamięci.
    ~SmartPointer() {
        delete surowyWskaznik;
        std::cout << "[SmartPointer]: Pamięć została automatycznie posprzątana.\n";
    }

    // PRZEŁADOWANIE OPERATORA ->
    // Musi zwracać surowy wskaźnik do obiektu, na rzecz którego wywołamy metodę
    Samochod* operator->() {
        return surowyWskaznik;
    }
};

int main() {
    // Tworzymy nasz inteligentny wskaźnik na stercie (heap)
    SmartPointer autoWsk(new Samochod("Toyota"));

    // Dzięki przeładowaniu operatora -> używamy obiektu klasy SmartPointer 
    // DOKŁADNIE TAK, jakby był zwykłym wskaźnikiem!
    autoWsk->odpalSilnik(); 

    // Pod maską kompilator interpretuje ten zapis jako:
    // (autoWsk.operator->())->odpalSilnik();

    std::cout << "--- Koniec funkcji main() ---\n";
    return 0; 
    // Tutaj 'autoWsk' umiera automatycznie, odpala się destruktor SmartPointer, 
    // który sam bezpiecznie usuwa obiekt "Toyota" z pamięci RAM!
}
```

### Jak to działa (Wyjaśnienie dla kompilatora):

Gdy piszesz `autoWsk->odpalSilnik();`, kompilator widzi, że `autoWsk` nie jest surowym wskaźnikiem, lecz obiektem klasy. Sprawdza więc, czy klasa ma zdefiniowany `operator->()`.

Ten operator zwraca surowy wskaźnik (`Samochod*`), do którego kompilator **ponownie (automatycznie)** aplikuje operator strzałki, ostatecznie wywołując metodę `odpalSilnik()`.

```
Toyota: Wrrr! Silnik odpala.
--- Koniec funkcji main() ---
[SmartPointer]: Pamięć została automatycznie posprzątana.
```

### 1. Operatory pre- i post-inkrementacji (`++`, `--`)

Kompilator C++ musi jakoś odróżnić zapis preinkrementacji (`++obiekt`) od postinkrementacji (`obiekt++`). Oba operatory mają ten sam symbol, dlatego wprowadzono sprytne rozróżnienie na poziomie sygnatury funkcji.

### A. Preinkrementacja (`++obj`)

Działa jak klasyczny operator jednoargumentowy. Modyfikuje obiekt i **zwraca referencję** do już zmienionego obiektu. Jest bardzo szybka wydajnościowo.

```cpp
// Jako metoda klasy:
Point& Point::operator++() {
    this->x++;
    return *this; // Zwraca zmodyfikowany obiekt przez referencję
}
```

### B. Postinkrementacja (`obj++`)

Aby kompilator wiedział, że chodzi o wersję "po fakcie", sztucznie zadeklarowano ten operator jako dwuargumentowy, dodając do nawiasu **nieużywany parametr typu `int`** (tzw. _dummy parameter_).

```cpp
// Sygnatura ze slajdu:
Point Point::operator++(int) {
    Point tymczasowy = *this; // 1. Musimy zapisać kopię stanu SPRZED zmiany
    this->x++;                // 2. Modyfikujemy właściwy obiekt
    return tymczasowy;        // 3. Zwracamy stary stan przez WARTOŚĆ
}
```

> ⚠️ **Ważna uwaga optymalizacyjna:** Jak zaznaczono na slajdzie, wersja postinkrementacyjna tworzy wewnętrznie **obiekt tymczasowy**, który jest zwracany przez wartość (czyli uruchamia się konstruktor kopiujący/przenoszący). Z tego powodu w pętlach (np. dla iteratorów) zawsze zaleca się stosowanie preinkrementacji: `++it` zamiast `it++`, aby unikać marnowania pamięci i czasu procesora na zbędne kopie.

## 2. Operatory strumieniowe (`<<` i `>>`)

Służą do integracji Twoich klas z operacjami wejścia/wyjścia (np. wypisywanie stanu obiektu przez `std::cout` lub wczytywanie danych przez `std::cin`).

- **Dlaczego MUSZĄ być funkcjami globalnymi?** Gdy piszesz `std::cout << mojObiekt;`, lewym operandem (właścicielem operacji) jest `std::cout`, czyli obiekt klasy `std::ostream` z biblioteki standardowej. Nie możesz dopisać metody do gotowej klasy bibliotecznej, dlatego operator implementuje się jako wolną funkcję globalną.
    
- **Kwestia przyjaźni (`friend`):** Ponieważ funkcja globalna musi wypisać wewnętrzne zmienne obiektu, najczęściej wewnątrz swojej klasy nadajesz jej status przyjaciela:

```cpp
class Point {
private:
    int x, y;
public:
    Point(int x, int y) : x(x), y(y) {}

    // Deklaracja przyjaźni:
    friend std::ostream& operator<<(std::ostream& strumien, const Point& p);
};

// Implementacja globalna:
std::ostream& operator<<(std::ostream& strumien, const Point& p) {
    strumien << "(" << p.x << ", " << p.y << ")";
    return strumien; // Zwracamy strumień, by móc je łączyć: cout << p1 << p2;
}
```

- **Uniwersalność:** Jak wspomina slajd, tak napisany operator automatycznie działa zarówno ze standardowym wyjściem konsoli (`std::cout`), jak i z plikami tekstowymi (`std::ofstream`).

Definiowanie operatora `<<` jako `friend` wewnątrz klasy jest bardzo popularne, ponieważ pozwala na **niezwykle zwięzły zapis** – łączysz deklarację przyjaźni, oznaczenie funkcji jako `inline` oraz jej pełną implementację w jednym krótkim bloku kodu. Jeśli program ma problem z jej znalezieniem, wystarczy dopisać jej prototyp (samą linijkę z średnikiem) jako zwykłą funkcję globalną na zewnątrz klasy.

### 3. Operatory `new` i `delete`

Przeładowanie tych operatorów pozwala przejąć pełną kontrolę nad tym, _w jaki sposób_ system przydziela i zwalnia surową pamięć RAM na stercie dla obiektów Twojej klasy.
#### Charakterystyka techniczna:

- **Zawsze są statyczne (`static`):** Nawet jeśli nie dopiszesz słowa `static`, kompilator traktuje te operatory jako statyczne. Dlaczego? Ponieważ w momencie wywołania `new`, obiekt jeszcze fizycznie nie istnieje, więc funkcja nie mogłaby otrzymać wskaźnika `this`.
    
- **Sygnatury globalne i lokalne:**
    ```cpp
    void* operator new(size_t sz);    // Alokuje 'sz' bajtów pamięci, zwraca surowy wskaźnik void*
    void operator delete(void* m);    // Zwalnia pamięć pod adresem 'm'
    ```
### Po co przeładowywać `new` i `delete`?

1. **Prowadzenie statystyk:** Możesz monitorować zużycie pamięci w aplikacji, zliczać alokacje lub szukać wycieków pamięci.
    
2. **Optymalizacja wydajności (Memory Pools):** Zamiast za każdym razem prosić powolny system operacyjny o małe porcje pamięci, możesz jednorazowo zarezerwować duży blok pamięci (wcześniej zdefiniowana pamięć), a Twój autorski `operator new` będzie błyskawicznie wydzielał z niego kawałki dla nowych obiektów.

# ~={orange} Dziedziczenie=~

**Dziedziczenie** to jeden z trzech fundamentów programowania obiektowego (obok hermetyzacji i polimorfizmu). Umożliwia ono zdefiniowanie nowej klasy na podstawie klasy już istniejącej. Pozwala to na ponowne wykorzystanie napisanego wcześniej kodu oraz budowanie logicznych hierarchii obiektów.

## 1. Pojęcia podstawowe i sposób zapisu

- **Klasa bazowa / podstawowa** (_Base class / Parent class_): Klasa, z której czerpiemy zmienne i metody. To ogólny wzorzec (np. `Pojazd`).
    
- **Klasa pochodna** (_Derived class / Child class_): Nowa klasa, która powstaje na bazie klasy podstawowej. Automatycznie staje się osobnym, pełnoprawnym typem danych (np. `Samochod`).

### Składnia zapisu dziedziczenia:

W najprostszym przypadku dziedziczenie zapisujemy za pomocą dwukropka `:` po nazwie nowej klasy, wskazując modyfikator dostępu oraz nazwę klasy bazowej.

```cpp
// Definicja klasy bazowej
class Baza {
public:
    int x;
};

// Klasa 'Nowa' dziedziczy publicznie po klasie 'Baza'
class Nowa : public Baza {
public:
    int y; // nowe, dodatkowe pole składowe
};
```

> ⚙️ **Różnica między `class` a `struct`:** > * Jeśli użyjesz słowa **`class Nowa : Baza`**, a nie podasz jawnie modyfikatora, kompilator zastosuje **dziedziczenie prywatne (`private`)**.
> 
> - Jeśli użyjesz słowa **`struct Nowa : Baza`**, domyślnym trybem będzie **dziedziczenie publiczne (`public`)**.
>     

## 2. Możliwości i rozszerzenia klasy pochodnej

Klasa pochodna otrzymuje "w spadku" wszystkie składniki i metody klasy bazowej. Na ich podstawie może:

1. **Definiować dodatkowe pola danych:** Rozbudowywać strukturę obiektu. _Uwaga:_ Nie ma fizycznej możliwości usunięcia ze struktury pól, które już istnieją w klasie bazowej.
    
2. **Definiować nowe metody:** Dodawać unikalne zachowania, których baza nie posiadała. _Uwaga:_ Nie da się usunąć metody z bazy, ale można sprawić, by była niedostępna dla użytkownika końcowego.
    
3. **Przeformułować (nadpisać / nadbudować) istniejące metody:** Napisać własną wersję metody, która istnieje w klasie bazowej.
    
    - **Zasłanianie nazw (Scope nesting):** Klasa pochodna tworzy zagnieżdżony zakres ważności. Jeśli w klasie pochodnej napiszesz metodę o identycznej nazwie jak w bazie, stara metoda zostanie "zasłonięta" (ukryta).
        
    - **Polimorfizm:** Powiązany z nadpisywaniem metod wirtualnych (`virtual`), o czym traktują kolejne sekcje zaawansowane.

## 3. Zarządzanie dostępem (Dopełnienie sekcji `protected`)

Gdy w grę wchodzi dziedziczenie, tradycyjny podział na `public` i `private` przestaje wystarczać. Pojawia się trzeci modyfikator: **`protected` (chroniony)**.

| **Modyfikator w klasie bazowej** | **Czy ma dostęp klasa pochodna (dziecko)?** | **Czy ma dostęp świat zewnętrzny (np. funkcja main)?** |
| -------------------------------- | ------------------------------------------- | ------------------------------------------------------ |
| **`public`**                     | **TAK**                                     | **TAK**                                                |
| **`protected`**                  | **TAK**                                     | **NIE** (Działa jak private dla obcych)                |
| **`private`**                    | **NIE**                                     | **NIE**                                                |

- **Prywatne składniki bazy:** Klasa pochodna **dziedziczy je**, ale **nie ma do nich bezpośredniego dostępu** (nie może ich zmodyfikować po nazwie). Może nimi operować wyłącznie za pomocą publicznych lub chronionych metod, które odziedziczyła po bazie (np. poprzez gettery i settery).
    
- **Modyfikator `protected`:** Został stworzony specjalnie na potrzeby dziedziczenia. Zabezpiecza dane przed światem zewnętrznym, ale pozwala dzieciom na swobodną, bezpośrednią pracę na tych zmiennych.
    
## 4. Specyfikatory dziedziczenia (Tabela trybów)

To, w jaki sposób odziedziczone składniki będą widoczne dla świata zewnętrznego z poziomu klasy pochodnej, zależy od **modyfikatora użytego przy deklaracji dziedziczenia** (`: public Baza`, `: protected Baza`, `: private Baza`).

### Opis mechaniczny trybów:

- **Dziedziczenie `public` (Najczęstsze):** Zachowuje stan nienaruszony. Wszystko co było publiczne w bazie, jest publiczne w dziecku. Chronione w bazie $\rightarrow$ chronione w dziecku.
    
- **Dziedziczenie `protected`:** Działa jak filtr "ściągający w dół". Wszystko co było publiczne lub chronione w bazie, w klasie pochodnej staje się **chronione (`protected`)**. Świat zewnętrzny traci do nich bezpośredni dostęp.
    
- **Dziedziczenie `private` (Domyślne dla klas):** Pełna izolacja. Wszystkie publiczne i chronione składniki klasy bazowej stają się wewnątrz klasy pochodnej **prywatne (`private`)**. Jeśli stworzysz kolejną klasę, która będzie dziedziczyć po dziecku, ta kolejna klasa nie dostanie już nic z pierwotnej bazy.
## 5. Deklaracje dostępu (`using`)

Jeśli użyłeś dziedziczenia prywatnego lub chronionego, większość metod z klasy bazowej została ukryta przed światem. Jeśli chcesz, aby **kilka wybranych metod** z klasy bazowej odzyskało swój pierwotny, publiczny status widoczności, stosujesz **deklarację dostępu za pomocą słowa kluczowego `using`** (starsze standardy dopuszczały samą nazwę metody, nowoczesny C++ wymaga `using`).

- **Zasada:** Deklaracja dostępu może jedynie **przywrócić** (powtórzyć) poziom dostępu, jaki zmienna miała w klasie bazowej. Nie może go samowolnie zwiększyć (np. zrobić ze składnika `private` bazy elementu `public`).
    
- **Przeładowanie nazw:** Wpisanie nazwy metody przywraca od razu wszystkie jej przeładowane wersje (nie rozróżniamy parametrów).
    
```cpp
class UkrytaBaza {
public:
    void funkcjaA() {}
    void funkcjaB() {}
};

// Dziedziczenie prywatne ukrywa wszystko
class MojaKlasa : private UkrytaBaza {
public:
    // Przywracamy widoczność publiczną tylko dla funkcjaA
    using UkrytaBaza::funkcjaA; 
};

int main() {
    MojaKlasa mk;
    mk.funkcjaA(); // OK - przywrócone do public
    // mk.funkcjaB(); // BŁĄD! Nadal ukryte (private)
}
```

## 6. Elementy niedziedziczone (Zasada konstrukcji i destrukcji)

To krytyczna informacja na egzaminy: **Trzy specjalne funkcje składowe nie są dziedziczone w klasie pochodnej**. Zamiast tego, klasa pochodna musi zarządzać nimi w specyficzny sposób.

### A. Konstruktory

Klasa pochodna nie przejmuje konstruktorów klasy bazowej (chyba że jawnie użyjesz dyrektywy `using Baza::Baza;` od C++11).

- **Mechanika uruchamiania:** Konstruktor klasy pochodnej odpowiada za inicjalizację swoich własnych, nowych zmiennych, ale **zanim** to zrobi, **musi wywołać konstruktor klasy bazowej**, aby prawidłowo zbudować fundament obiektu.
    
- Jeśli klasa bazowa ma tylko konstruktor parametryczny, musisz go jawnie wywołać na liście inicjalizacyjnej:
    
```cpp
class Rodzic {
public:
    Rodzic(int x) {} // Brak konstruktora domyślnego
};

class Dziecko : public Rodzic {
public:
    // Obowiązkowe przekazanie parametru do konstruktora bazy:
    Dziecko(int a, int b) : Rodzic(a) {} 
};
```

Kiedy powołujesz do życia obiekt klasy pochodnej, komputer nie potrafi zbudować go "w całości" samodzielnie. Najpierw musi stworzyć fundament, czyli wywołać konstruktor klasy podstawowej.

#### Żelazne reguły:

- **Obowiązek wywołania:** W konstruktorze klasy pochodnej musisz jawnie wywołać na liście inicjalizacyjnej konstruktor klasy bazowej, przekazując mu odpowiednie parametry.
    
- **Kiedy można pominąć jawne wywołanie?** Tylko w dwóch sytuacjach:
    
    1. Gdy klasa podstawowa nie ma zapisanego żadnego konstruktora (wtedy kompilator sam wywoła ukryty konstruktor domyślny).
        
    2. Gdy klasa podstawowa ma własny konstruktor domyślny (bezargumentowy). Kompilator wywoła go wtedy automatycznie po cichu.
        
- **Konstruktory klas bezpośrednich:** Na liście inicjalizacyjnej klasy pochodnej możesz umieścić wyłącznie konstruktor bazy **bezpośredniej** (czyli leżącej dokładnie o jeden poziom wyżej w hierarchii). Jeśli klasa `C` dziedziczy po `B`, a `B` dziedziczy po `A`, to klasa `C` wywołuje na liście tylko `B(...)`. Klasa `B` z kolei odpowiada za wywołanie `A(...)`.

```cpp
class A {
public:
    A(int param) {} // Brak konstruktora domyślnego!
};

class B : public A {
public:
    // Musimy jawnie przekazać wartość do klasy A na liście inicjalizacyjnej
    B() : A(10) {
        // Kod konstruktora klasy B wykonuje się DOPIERO PO konstruktorze A
    }
};
```

### B. Konstruktor kopiujący w klasie pochodnej

Podobnie jak przy zwykłym konstruktorze, jeśli nie napiszesz własnego konstruktora kopiującego w klasie pochodnej, kompilator automatycznie wygeneruje go za Ciebie.
### Automatyczne zachowanie kompilatora:

Wygenerowany automatycznie konstruktor kopiujący klasy pochodnej zachowa się wzorowo:

1. Najpierw wywoła konstruktor kopiujący klasy bazowej, przekazując mu referencję do kopiowanego obiektu.
    
2. Następnie skopiuje (składnik po składniku) nowe pola dodane w klasie pochodnej.
    

#### Kiedy kompilator NIE wygeneruje go automatycznie?

Automatyczne generowanie zostanie zablokowane, jeśli:

- Klasa bazowa (rodzic) ma swój konstruktor kopiujący ukryty w sekcji `private` (jest niedostępny).
    
- Klasa pochodna zawiera jako pole obiekt innej klasy, która zablokowała kopiowanie. _W takich sytuacjach kompilator zgłosi błąd, a Ty musisz napisać konstruktor kopiujący ręcznie._

#### Pułapka nienaruszalności (`const`):

Slajd wspomina, że aby kompilator poprawnie generował kopie obiektów stałych (`const`), konstruktory kopiujące w całej hierarchii powinny bezwzględnie przyjmować argument przez stałą referencję:

```cpp
Klasa::Klasa(const Klasa& zrodlo);
```

### C. Przepisywanie składnik po składniku (Operator przypisania `=`)

Operator przypisania działa niemal identycznie pod względem logicznym jak konstruktor kopiujący, ale operuje na obiektach, które już fizycznie istnieją.
#### Automatyczne zachowanie:

Domyślny, wygenerowany przez kompilator operator przypisania dla dziecka uruchomi operator przypisania z klasy bazowej, a potem przepisze nowe składniki.

#### Kiedy automatyczny operator przypisania NIE zadziała?

Kompilator **zrezygnuje z automatycznego wygenerowania** operatora `=`, jeśli w klasie pochodnej pojawi się choćby jeden z tych czterech elementów:

1. Klasa posiada pole będące **stałą** (`const`) – stałej nie można nadpisać po stworzeniu.
    
2. Klasa posiada pole będące **referencją** (`&`) – referencji nie można przepiąć na inny obiekt po jej zainicjalizowaniu.
    
3. Klasa bazowa (rodzic) ma swój operator przypisania zadeklarowany jako prywatny (`private`).
    
4. Klasa pochodna zawiera w sobie obiekt innej zewnętrznej klasy z prywatnym operatorem przypisania.
    

> 💡 **Złota zasada:** Jeżeli automatyczny operator przypisania wygenerowany przez kompilator działa poprawnie i bezpiecznie (ponieważ nie używasz w klasie surowych wskaźników i pamięci dynamicznej `new`), **nie ma najmniejszego sensu definiować go ręcznie**. Pozwól kompilatorowi wykonać optymalizację.

### D. Destruktory

Destruktory nie są dziedziczone. Klasa pochodna tworzy swój własny destruktor.

- **Kolejność czyszczenia:** Przy niszczeniu obiektu najpierw wykonuje się kod destruktora klasy pochodnej (dziecka), a dopiero po nim automatycznie odpala się destruktor klasy bazowej (rodzica).
    
- _Zapamiętaj:_ Destrukcja przebiega w kolejności **dokładnie odwrotnej** do konstrukcji.

## Istota konwersji w górę (_Upcasting_)

**Wskaźnik lub referencja** wskazujące na obiekt klasy pochodnej mogą zostać **niejawnie (automatycznie)** przekształcone na wskaźnik lub referencję do klasy podstawowej.

> ⚠️ **Twardy warunek:** Ta automatyczna konwersja działa **tylko i wyłącznie przy dziedziczeniu publicznym (`public`)**. Jeśli dziedziczenie byłoby prywatne, kompilator zablokuje tę operację.

```cpp
class Rodzic {};
class Dziecko : public Rodzic {};

int main() {
    Dziecko mojeDziecko;
    
    // Automatyczna konwersja (Upcasting):
    Rodzic& refRodzica = mojeDziecko;  // OK! Referencja do bazy wskazuje na dziecko.
    Rodzic* wskRodzica = &mojeDziecko; // OK! Wskaźnik bazowy przechowuje adres dziecka.
}
```

###  Gdzie i kiedy dochodzi do tych konwersji automatycznych?

Slajdy wymieniają cztery naturalne sytuacje w programie, w których kompilator dokona takiego rzutowania bez naszej ingerencji:

1. **Przesyłanie argumentów do funkcji:** Jeśli funkcja została zaprojektowana tak, aby przyjąć wskaźnik lub referencję do klasy podstawowej (np. uniwersalna funkcja `rysujKsztalt(Ksztalt& k)`), możesz do niej bez problemu podać obiekt klasy pochodnej (np. `Kolo`).
    
2. **Zwracanie rezultatu z funkcji:** Jeśli funkcja w swojej sygnaturze deklaruje, że zwraca wskaźnik do klasy nadrzędnej (`Rodzic*`), jej ciało może bezpiecznie skończyć się linijką `return new Dziecko();`.
    
3. **Przeładowanie operatorów:** Zachowuje się identycznie jak wywołanie funkcji (lewy lub prawy operand zostanie automatycznie rzutowany w górę).
    
4. **Wyrażenia inicjalizujące:** Do konstruktora kopiującego klasy podstawowej, który spodziewa się referencji do innego rodzica (`const Rodzic&`), można bezpiecznie przekazać referencję do obiektu klasy pochodnej (`Dziecko`).
    
### Kluczowe ograniczenie: Pracujemy tylko na adresach!

Na drugim slajdzie znajduje się fundamentalna uwaga dla całego programowania obiektowego:

> Obiekty klas pochodnych mogą być traktowane jak obiekty swych klas podstawowych **tylko wtedy, gdy pracujemy na ich adresach (wskaźnikach lub referencjach)**.

### Co się stanie, jeśli zignorujemy tę zasadę i spróbujemy przepisać obiekt przez wartość? (Zjawisko _Object Slicing_)

Jeśli spróbujesz przypisać obiekt klasy pochodnej bezpośrednio do czystej zmiennej klasy podstawowej (bez znaku `&` lub `*`):

```cpp
Dziecko d;
Rodzic r = d; // Przypisanie przez wartość!
```

Dojdzie do tzw. **obcięcia obiektu (_Object Slicing_)**. Kompilator skopiuje do zmiennej `r` tylko te dane i metody, które mieszczą się w klasie `Rodzic`. Wszystkie dodatkowe, unikalne zmienne i funkcje, które rozbudowałeś w klasie `Dziecko`, zostaną bezpowrotnie odcięte i wyrzucone. Obiekt całkowicie traci swoją tożsamość dziecka.

### Krytyczne ostrzeżenie egzaminacyjne 

Ostatni punkt drugiego slajdu to klasyczny haczyk z testów wielokrotnego wyboru:

> 🔴 **UWAGA:** Do funkcji spodziewającej się adresu tablicy obiektów klasy podstawowej **nie można** wysłać adresu tablicy obiektów klasy pochodnej!

#### Dlaczego to jest całkowicie zabronione, skoro jedno dziecko pasuje do jednego rodzica?

Wynika to z czystej matematyki i sposobu, w jaki komputer rozplanowuje pamięć RAM dla tablic.

Klasa pochodna `Dziecko` jest niemal zawsze **większa w bajtach** niż klasa podstawowa `Rodzic`, ponieważ dodaje nowe pola składowe (np. `Rodzic` zajmuje 8 bajtów, a rozbudowane `Dziecko` zajmuje 24 bajty).

Gdy przesyłasz do funkcji tablicę, przesyłasz jedynie adres jej **pierwszego elementu**. Kiedy funkcja (która myśli, że dostała tablicę mniejszych `Rodziców`) spróbuje przeskoczyć do indeksu `[1]`, wykona skok o długość struktury `Rodzic` (czyli o 8 bajtów). Ponieważ w pamięci leżą tam duże obiekty `Dziecko` (co 24 bajty), wskaźnik wyląduje w samym środku danych pierwszego dziecka! Doprowadzi to do natychmiastowego zniszczenia struktury pamięci, błędnego odczytu i awarii programu (_Undefined Behavior_).
# ~={orange}Funkcje wirtualne=~ (wyk. 7)

Dopiero słowo kluczowe **`virtual`** pozwala w pełni wykorzystać potencjał obiektowości, wprowadzając mechanizm **polimorfizmu (wielopostaciowości)** oraz **dynamicznego wiązania metod**.

## 1. Istota problemu: Wskaźnik bazowy na obiekt pochodny

Jak już wiemy z poprzedniego tematu (_Upcasting_), wskaźnik typu klasy podstawowej (np. `Pojazd*`) może legalnie przechowywać adres obiektu klasy pochodnej (np. `Samochod`).

Slajdy przypominają tę intuicyjną analogię:

- **W górę hierarchii (Prawda):** Każdy `Samochod` czy `Maluch` jest rodzajem `Pojazdu`, więc wskaźnik `Pojazd*` może na nie pokazywać.
    
- **W dół hierarchii (Fałsz):** Sytuacja odwrotna nie jest prawdziwa. Mając wskaźnik `Samochod*`, nie możemy przypisać mu ogólnego `Pojazdu`, ponieważ tym pojazdem mógłby okazać się rower albo hulajnoga.
    

Co się jednak stanie, gdy przez ten ogólny wskaźnik spróbujemy wywołać metodę, którą dziecko napisało po swojemu?

## 2. Różnica między funkcją zwykłą a wirtualną

To najważniejsze porównanie z całego wykładu, decydujące o zachowaniu programu:

### A. Wywołanie funkcji zwykłej

Jeśli metoda w klasie bazowej **nie jest wirtualna**, kompilator podejmuje decyzję o wywołaniu kodu na podstawie **typu wskaźnika**, a nie rzeczywistego obiektu, który pod nim siedzi.

- Mając wskaźnik `Pojazd* wsk = new Samochod();` i wywołując `wsk->trab();`, uruchomi się kod z klasy `Pojazd`. Klasa pochodna zostaje zignorowana.
    
### B. Wywołanie funkcji wirtualnej

Jeśli dodasz przydomek **`virtual`** przed deklaracją metody w klasie bazowej, kompilator rezygnuje z podejmowania decyzji na etapie kompilacji. Program dopiero w trakcie działania aplikacji (w run-time) **sprawdza, czym naprawdę jest obiekt**, na który patrzy wskaźnik, i uruchamia właściwą, nadpisaną wersję metody.

- Mając wskaźnik `Pojazd* wsk = new Samochod();` i wywołując `wsk->trab();`, program zobaczy: _"Aha, ten pojazd to tak naprawdę samochód!"_ i uruchomi kod z klasy `Samochod`.
    
## 3. Dziedziczenie wirtualności

Ostatni slajd zwraca uwagę na bardzo wygodną regułę:

> Dodanie przymiotnika `virtual` przy funkcji składowej w klasie podstawowej mówi, że od tego momentu **wszystkie dalsze pokolenia będą tę funkcję mieć wirtualną**.

Gdy klasa bazowa raz oznaczy metodę jako wirtualną, w klasach pochodnych (dzieciach, wnukach itd.) słowo `virtual` staje się opcjonalne (współcześnie dobrą praktyką jest dopisywanie tam słowa `override`).

### Twardy warunek dziedziczenia wirtualności:

Metoda w klasie pochodnej zostanie uznana za wirtualnego następcę tylko wtedy, gdy jej sygnatura jest **identyczna** z bazą. Musi posiadać:

1. Dokładnie taką samą nazwę.
    
2. Dokładnie takie same parametry w nawiasie.
    
3. Dokładnie taki sam typ zwracany.
    
### Praktyczny przykład do nauki

Slajd wspomina, że funkcje wirtualne _"w znakomity sposób ułatwiają i upraszczają pracę nad projektem"_. Zobaczmy to na klasycznym przykładzie gry:

```cpp
#include <iostream>
#include <vector>

class Przeciwnik {
public:
    // Słowo 'virtual' zmienia wszystko:
    virtual void atakuj() {
        std::cout << "Przeciwnik wykonuje podstawowy atak.\n";
    }
    virtual ~Przeciwnik() = default; // Dobra praktyka: wirtualny destruktor
};

class Ork : public Przeciwnik {
public:
    void atakuj() override { // override informuje, że nadpisujemy funkcję wirtualną
        std::cout << "Ork uderza wielkim toporem!\n";
    }
};

class Smok : public Przeciwnik {
public:
    void atakuj() override {
        std::cout << "Smok zieje żywym ogniem!\n";
    }
};

int main() {
    // Tworzymy tablicę uniwersalnych wskaźników bazowych:
    std::vector<Przeciwnik*> armia;
    
    armia.push_back(new Ork());
    armia.push_back(new Smok());
    armia.push_back(new Przeciwnik());

    std::cout << "--- RUNDA BITWY ---\n";
    // Dzięki polimorfizmowi możemy zarządzać całą armią jedną prostą pętlą!
    for (Przeciwnik* p : armia) {
        p->atakuj(); // Magia virtual: każdy zaatakuje po swojemu!
    }

    // Sprzątanie pamięci
    for (Przeciwnik* p : armia) delete p;
    return 0;
}
```
#### Wynik w konsoli:

```
--- RUNDA BITWY ---
Ork uderza wielkim toporem!
Smok zieje żywym ogniem!
Przeciwnik wykonuje podstawowy atak.
```

Bez słowa `virtual` pętla wypisałaby trzy razy "Przeciwnik wykonuje podstawowy atak", całkowicie ignorując fakt, że w pamięci znajdował się Ork i Smok.

# ~={orange}Polimorfizm=~
## 1. Istota polimorfizmu (Wielość form)

Polimorfizm polega na wykazywaniu przez metodę różnych form działania w zależności od tego, jaki typ obiektu jest aktualnie wskazywany.

- **To nie funkcja jest polimorficzna, lecz jej wywołanie:** Sama definicja metody wirtualnej w kodzie niczego nie zmienia. Magia polimorfizmu aktywuje się dopiero w momencie jej uruchomienia przez wskaźnik.


Wyobraź sobie uniwersalny wskaźnik `Shape* shape;` (Kształt). Jedna, krótka linijka kodu:

```cpp
shape->Rys();
```

W zależności od kontekstu (tego, co podstawisz pod wskaźnik) wywoła zupełnie inną funkcję:

- Jeśli `shape = new Shape();` $\rightarrow$ wykona się `Shape::Rys()`
    
- Jeśli `shape = new Circ();` (Koło) $\rightarrow$ wykona się `Circ::Rys()`
    
- Jeśli `shape = new Rec();` (Prostokąt) $\rightarrow$ wykona się `Rec::Rys()`
    
## 2. Mechanizm działania: Wczesne vs Późne wiązanie

Aby polimorfizm mógł zaistnieć, komputer musi zmienić sposób łączenia wywołania funkcji z jej fizycznym adresem w pamięci RAM.

### A. Wczesne wiązanie (Early Binding / Wiązanie statyczne)

- **Kiedy zachodzi:** Dla wszystkich zwykłych (niewirtualnych) funkcji.
    
- **Jak działa:** Już na etapie kompilacji kodu program dokładnie wie, pod jaki adres pamięci skoczyć, by wykonać funkcję. Decyzja zapada sztywno na podstawie typu wskaźnika.
    

### B. Późne wiązanie (Late Binding / Wiązanie dynamiczne)

- **Kiedy zachodzi:** Dla funkcji oznaczonych jako `virtual`.
    
- **Jak działa:** Kompilator na etapie budowania programu nie wstawia konkretnego adresu funkcji. Zamiast tego generuje specjalny kod pomocniczy, który dopiero w ułamku sekundy przed wywołaniem (w trakcie działania programu) sprawdza ukrytą tablicę wirtualną obiektu (`vtable`) i dynamicznie wybiera właściwy adres metody.
    

### Wyjątki: Kiedy funkcja wirtualna używa szybkiego, wczesnego wiązania?

Trzeci slajd wymienia sytuacje, w których kompilator "wie na 100%", o którą wersję chodzi, więc rezygnuje z powolnego dynamicznego sprawdzania:

1. **Wywołanie na rzecz fizycznego obiektu (`obiekt.funkcja()`):** Skoro nie używasz wskaźnika, obiekt nie może być polimorficzny – typ jest znany bezpośrednio.
    
2. **Jawne użycie operatora zakresu (`wskaznik->Klasa::funkcja()`):** Kiedy sam twardo rozkazujesz, z której klasy metodę uruchomić.
    
3. **Wywołanie z wnętrza konstruktora lub destruktora (Czerwony tekst!):** Podczas budowania lub niszczenia obiektu bazy, część odpowiadająca za klasę pochodną (dziecko) jeszcze nie powstała lub została już zniszczona. Dlatego w konstruktorze/destruktorze bazy funkcje wirtualne zawsze wiążą się statycznie z klasą bazową.
    
## 3. Zalety polimorfizmu (Pożytek)

- **Ekstremalna rozszerzalność kodu:** Twój program staje się otwarty na nowe moduły. Jeśli za rok postanowisz dodać do systemu nowy kształt (np. `Triangle`), nie musisz modyfikować pętli rysujących ani funkcji w głównym pliku. Po prostu dopisujesz klasę, a mechanizm późnego wiązania sam ją obsłuży.
    
- **Eliminacja instrukcji wyboru:** Całkowicie znika potrzeba pisania nieczytelnych konstrukcji typu `if-else` czy `switch(typ_ksztaltu)`, które ręcznie sprawdzałyby, jak narysować dany obiekt.
    
## 4. Wady polimorfizmu (Dlaczego nie wszystko jest wirtualne?)

Drugi slajd wprost odpowiada na pytanie, dlaczego w C++ (w przeciwieństwie do Javy czy C#) metody nie są wirtualne z urzędu. Polimorfizm jest okupiony konkretnym kosztem sprzętowym:

1. **Koszt czasowy (Wydajność):** Dynamiczne wyszukiwanie adresu w tablicy wirtualnej (`vtable`) przed każdym wywołaniem metody trwa minimalnie dłużej niż bezpośredni, sztywny skok w pamięci.
    
2. **Koszt pamięciowy (Rozmiar obiektów):** Każda klasa posiadająca choć jedną funkcję wirtualną musi przechowywać wewnątrz każdego swojego obiektu dodatkowy, ukryty wskaźnik do tablicy wirtualnej (`vptr`). Powoduje to, że obiekty stają się fizycznie większe (zwykle o rozmiar jednego wskaźnika, czyli 4 lub 8 bajtów w systemach 64-bitowych).
    
### Praktyczny przykład do analizy i nauki

Oto kompletny kod prezentujący elastyczność polimorfizmu oraz zjawisko wymuszonego wczesnego wiązania:

```cpp
#include <iostream>
#include <vector>

class Shape {
public:
    virtual void Rys() const {
        std::cout << "Rysuje abstrakcyjny Ksztalt.\n";
    }
};

class Circ : public Shape {
public:
    void Rys() const overrid e {
        std::cout << "Rysuje Kolo (Circ).\n";
    }
};

class Rec : public Shape {
public:
    void Rys() const override {
        std::cout << "Rysuje Prostokat (Rec).\n";
    }
};

int main() {
    // Tworzymy wektor uniwersalnych wskaźników
    std::vector<Shape*> tablicaKsztaltow;
    
    tablicaKsztaltow.push_back(new Circ());
    tablicaKsztaltow.push_back(new Rec());
    tablicaKsztaltow.push_back(new Shape());

    std::cout << "--- 1. Wywolania polimorficzne (Pozne wiazanie) ---\n";
    for (Shape* s : tablicaKsztaltow) {
        s->Rys(); // Komputer decyduje w run-time na podstawie obiektu
    }

    std::cout << "\n--- 2. Wymuszone wczesne wiazanie ---\n";
    // Pobieramy wskaźnik na Kolo (Circ), ale rozkazujemy wywołać wersję bazową:
    tablicaKsztaltow[0]->Shape::Rys(); 

    // Czyszczenie pamięci
    for (Shape* s : tablicaKsztaltow) delete s;
    return 0;
}
```

#### Wynik w konsoli:

```
--- 1. Wywolania polimorficzne (Pozne wiazanie) ---
Rysuje Kolo (Circ).
Rysuje Prostokat (Rec).
Rysuje abstrakcyjny Ksztalt.

--- 2. Wymuszone wczesne wiazanie ---
Rysuje abstrakcyjny Ksztalt.
```

## Klasa abstrakcyjna

**Klasa abstrakcyjna** to klasa, która służy wyłącznie jako ogólny wzorzec (szablon) dla innych klas. Nie reprezentuje ona żadnego konkretnego, istniejącego fizycznie obiektu z realnego świata, lecz pojęcie ogólne (np. _Pojazd_, _FiguraGeometryczna_, _Pracownik_).

### 1. Czym charakteryzuje się klasa abstrakcyjna?

- **Zakaz tworzenia instancji:** Nie można utworzyć samodzielnego obiektu takiej klasy za pomocą operatora `new` czy deklaracji statycznej. Próba napisania `Figura f;` skończy się natychmiastowym błędem kompilacji.
    
- **Cel istnienia:** Tworzy się je wyłącznie po to, aby inne, bardziej szczegółowe klasy mogły po nich **dziedziczyć** wspólne cechy i wymuszać konkretne zachowania.
    
- **Klasy „niedokończone”:** Slajd nazywa je tak, ponieważ zawierają deklaracje pewnych uniwersalnych zachowań, ale celowo nie posiadają kodu (implementacji), który opisywałby, jak te zachowania zrealizować.

### 2. Czyste funkcje wirtualne

To kluczowy mechanizm techniczny. Klasa staje się abstrakcyjna w ułamku sekundy, gdy zadeklarujesz w niej przynajmniej jedną **czystą funkcję wirtualną**.

Czystą funkcję tworzy się poprzez dopisanie specyficznej końcówki **`= 0;`** na końcu sygnatury metody wirtualnej:

```cpp
virtual void rysuj() = 0; // Czysta funkcja wirtualna (Pure virtual)
```

Zapis `= 0;` oznacza dla kompilatora: _"Ta klasa nie wie i nie interesuje jej, jak narysować figurę. Jednak każda zwykła klasa, która po niej odziedziczy, **musi** napisać własne ciało dla metody rysuj(), inaczej program się nie skompiluje"_.

### Praktyczny przykład do nauki (Modelowanie figur)

```cpp
#include <iostream>

// KLASA ABSTRAKCYJNA (ponieważ ma przynajmniej jedną czystą funkcję wirtualną)
class Figura {
public:
    // Każda figura ma kolor, to cecha wspólna
    std::string kolor;

    // Czysta funkcja wirtualna - brak implementacji tutaj!
    virtual void rysuj() = 0; 

    // Wirtualny destruktor - obowiązkowy przy polimorfizmie i klasach abstrakcyjnych
    virtual ~Figura() = default; 
};

// Zwykła klasa pochodna (Konkretna)
class Kolo : public Figura {
public:
    void rysuj() override {
        std::cout << "Rysuje idealnie okragle Kolo.\n"; // Implementacja pozostawiona klasie pochodnej
    }
};

class Kwadrat : public Figura {
public:
    void rysuj() override {
        std::cout << "Rysuje Kwadrat o czterech rownych bokach.\n";
    }
};

int main() {
    // Figura f; // BŁĄD! Klasa abstrakcyjna - nie stworzysz obiektu!

    // Jednak wskaźniki polimorficzne typu bazowego działają wspaniale:
    Figura* f1 = new Kolo();
    Figura* f2 = new Kwadrat();

    f1->rysuj(); // Wypisze: Rysuje idealnie okragle Kolo.
    f2->rysuj(); // Wypisze: Rysuje Kwadrat o czterech rownych bokach.

    delete f1;
    delete f2;
    return 0;
}
```

### Podsumowanie ściągawka:

- **Po co to robimy?** Aby zagwarantować stuprocentową spójność w projekcie. Projektując klasę abstrakcyjną `Figura` z czystą funkcją `rysuj()`, dajesz jasny kontrakt całemu zespołowi programistów: _"Ktokolwiek będzie dodawał do naszej gry nową figurę (np. Trójkąt), jest zmuszony przez kompilator do napisania funkcji rysującej"_.
    
- **Interfejsy:** Klasę, która zawiera _wyłącznie_ czyste funkcje wirtualne i nie ma żadnych zmiennych składowych, w świecie programowania obiektowego nazywa się **Interfejsem**.

## Kontrola dziedziczenia: `override` i `final`

Standard C++11 wprowadził dwa niezwykle ważne słowa kluczowe (technicznie: identyfikatory ze specjalnym znaczeniem): **`override`** oraz **`final`**. Służą one do jawnej kontroli tego, jak funkcje wirtualne oraz całe klasy zachowują się w procesie dziedziczenia.

### 1. Słowo kluczowe `override` (Ochrona przed literówkami)

Aby funkcja w klasie pochodnej nadpisała funkcję wirtualną z klasy bazowej, jej sygnatura (nazwa, argumenty, stałość `const`) musi być **identyczna**.

Jeśli programista popełnił najmniejszy błąd (np. pomylił typ argumentu z `int` na `float` albo zapomniał dopisać `const`), kompilator przed C++11 uznawał, że... tworzysz **zupełnie nową, niezależną funkcję**, zamiast nadpisywać starą. Polimorfizm przestawał działać, a program nie zgłaszał żadnego błędu.

Dopisanie **`override`** na końcu deklaracji funkcji zmusza kompilator do twardego sprawdzenia: _"Drogi kompilatorze, upewnij się, że w klasie bazowej istnieje identyczna funkcja wirtualna, którą właśnie nadpisuję. Jeśli jej nie ma – zgłoś błąd kompilacji"_.

#### Przykład błędu i ochrony przez `override`:

```cpp
class Rodzic {
public:
    virtual void zrobCos(int x) const {}
};

class Dziecko : public Rodzic {
public:
    // BŁĄD PROGRAMISTY: brak 'const' na końcu sprawia, że to nowa funkcja.
    // Dzięki słowu 'override' kompilator natychmiast zaprotestuje i wskaże błąd!
    void zrobCos(int x) override {} 
};
```

> 💡 **Uwaga ze slajdu:** Powtarzanie słowa `virtual` w klasie pochodnej (np. `virtual void zrobCos() override;`) jest technicznie poprawne, ale **niezalecane**. Zaciemnia kod – nowoczesny, dobry design nakazuje używać wyłącznie słowa `override`.

### 2. Słowo kluczowe `final` stosowane do METOD

Czasami jako projektant architektury klas chcesz postawić twardą granicę: _"Ta funkcja wirtualna została już idealnie zdefiniowana w tym miejscu hierarchii i zabraniam kolejnym pokoleniom (klasom potomnym) jej nadpisywania"_.

Dopisanie **`final`** przy funkcji wirtualnej blokuje możliwość jej dalszego przesłaniania w kolejnych podklasach.

```cpp
class Szef {
public:
    virtual void obliczPremie() final {} // Koniec, nikt niżej tego nie zmieni!
};

class Pracownik : public Szef {
public:
    // BŁĄD KOMPILACJI! Próba nadpisania metody oznaczonej jako final.
    void obliczPremie() override {} 
};
```

### 3. Słowo kluczowe `final` stosowane do KLAS

`final` można nałożyć również na **całą klasę** (dopisując je bezpośrednio po nazwie klasy w jej nagłówku). Oznacza to całkowity **zakaz dziedziczenia po tej klasie**.

- Jest to idealne narzędzie do zamykania bibliotek oraz optymalizacji wydajnościowej (kompilator wiedząc, że klasa jest finalna, może zastosować tzw. _dewirtualizację_, czyli zamienić powolne wywołania polimorficzne na błyskawiczne, bezpośrednie skoki w pamięci RAM).

```cpp
// Ta klasa jest ostateczna i kompletna
class SystemBezpieczenstwa final {
    // ...
};

// BŁĄD KOMPILACJI! Nie można dziedziczyć po klasie oznaczonej jako final.
class ZhakowanySystem : public SystemBezpieczenstwa {
    // ...
};
```

### Podsumowanie ściągawka:

- **`override`**: Dopisuj **zawsze i bezwzględnie** przy każdej metodzie w klasie pochodnej, która ma nadpisywać funkcję wirtualną z bazy. To Twój najlepszy darmowy test poprawności kodu.
    
- **Metoda `final`**: Blokuje możliwość ponownego nadpisania konkretnej metody w klasach-wnukach.
    
- **Klasa `final`**: Blokuje możliwość stworzenia jakiejkolwiek klasy potomnej (całkowity zakaz dziedziczenia).

## Identyfikacja typów w czasie działania programu: Mechanizm RTTI

Ten slajd porusza bardzo zaawansowany problem architektoniczny, który pojawia się jako bezpośredni skutek uboczny stosowania polimorfizmu. Dotyczy on sytuacji, w której celowo ukryliśmy prawdziwy typ obiektu za ogólnym wskaźnikiem bazowym (np. `Kształt*`), ale w pewnym specyficznym miejscu programu **musimy dowiedzieć się, z jaką podklasą mamy do czynienia**.
### 1. Problem: Utrata informacji o typie rzeczywistym

Gdy wrzucasz różne obiekty pochodne do jednej tablicy wskaźników klasy bazowej, dochodzi do uogólnienia. Z punktu widzenia kompilatora każdy element tej tablicy to po prostu surowy adres klasy bazowej.

#### Kiedy pojawia się potrzeba odzyskania tej informacji:

Wyobraź sobie grę strategiczną, w której masz tablicę wskaźników typu `Jednostka*`. Przeprowadzasz pętlę i wydajesz rozkaz ruchu. Wszystkie jednostki idą (polimorfizm).

Nagle gracz klika przycisk specjalny _"Zatankuj paliwo"_. Ta operacja ma sens **tylko dla obiektów klasy `Czołg`**, a dla zwykłego `Piechura` jest niedozwolona. Musisz sprawdzić, który ze wskaźników `Jednostka*` kryje pod maską obiekt `Czołg`, aby zyskać dostęp do jego unikalnych, niepolimorficznych metod (np. `.uzupelnijPaliwo()`).
### 2. Wybaczający mechanizm RTTI (_Run-Time Type Information_)

**RTTI** to wbudowany w kompilator C++ system, który nakazuje programowi pamiętać i przechowywać ukrytą informację o strukturze oraz faktycznej tożsamości klasy każdego obiektu w trakcie działania aplikacji (w run-time).

> ⚠️ **Twardy warunek RTTI:** Mechanizm ten działa **wyłącznie dla klas polimorficznych**, czyli takich, które posiadają w swojej strukturze przynajmniej jedną funkcję wirtualną (wtedy informacja o typie jest powiązana z tablicą wirtualną `vtable`).

Zgodnie ze slajdem, dzięki RTTI możemy zrealizować dwa scenariusze:

#### Scenariusz A: Bezpieczna próba przekształcenia (`dynamic_cast`)

Pozwala spróbować rzutować wskaźnik bazowy w dół hierarchii (_Downcasting_) na konkretną klasę pochodną.

- Jeśli wskaźnik rzeczywiście pokazywał na dany obiekt dynamiczny, rzutowanie się udaje i dostajemy prawidłowy adres.
    
- Jeśli wskaźnik pokazywał na coś innego (np. próbowaliśmy rzutować `Piechura` na `Czołg`), operator nie wywala programu, tylko **zwraca bezpieczną wartość `nullptr`**.

#### Scenariusz B: Ustalić i porównać klasę obiektu (`typeid`)

Operator `typeid` pozwala bezpośrednio pobrać unikalny identyfikator klasy obiektu i sprawdzić, czy dwa wskaźniki reprezentują dokładnie tę samą podklasę.

### Praktyczny przykład do nauki (Identyfikacja jednostek)

```cpp
#include <iostream>
#include <vector>
#include <typeinfo> // Wymagane do używania operatora typeid

class Jednostka {
public:
    virtual void ruszaj() { std::cout << "Jednostka maszeruje...\n"; }
    virtual ~Jednostka() = default; // Gwarantuje polimorfizm i poprawne działanie RTTI
};

class Zolnierz : public Jednostka {};

class Czolg : public Jednostka {
public:
    void zatankuj() { std::cout << "Czolg zostal zatankowany do pelna!\n"; }
};

int main() {
    // Tablica uogólnionych wskaźników
    std::vector<Jednostka*> armia = { new Zolnierz(), new Czolg(), new Zolnierz() };

    std::cout << "--- Proba zatankowania calej armii ---\n";
    for (Jednostka* j : armia) {
        // 1. Korzystamy z RTTI za pomocą dynamic_cast (Próba konwersji w dół)
        Czolg* potencjalnyCzolg = dynamic_cast<Czolg*>(j);

        if (potencjalnyCzolg != nullptr) {
            // Sukces! To był czołg, możemy wywołać unikalną metodę
            potencjalnyCzolg->zatankuj();
        } else {
            std::cout << "Ta jednostka nie potrzebuje ropy.\n";
        }

        // 2. Korzystamy z RTTI za pomocą typeid (Sprawdzenie dokładnej klasy)
        if (typeid(*j) == typeid(Zolnierz)) {
            std::cout << "-> Potwierdzono: to jest dokladnie struktura Zolnierz.\n";
        }
    }

    // Czyszczenie pamięci
    for (Jednostka* j : armia) delete j;
    return 0;
}
```

#### Wynik w konsoli:

```
--- Proba zatankowania calej armii ---
Ta jednostka nie potrzebuje ropy.
-> Potwierdzono: to jest dokladnie struktura Zolnierz.
Czolg zostal zatankowany do pelna!
Ta jednostka nie potrzebuje ropy.
-> Potwierdzono: to jest dokladnie struktura Zolnierz.
```
## Rzutowanie `dynamic_cast`

`dynamic_cast` to najbardziej zaawansowany i jedyny w pełni **dynamiczny** (sprawdzany w run-time) operator rzutowania w C++. Służy do bezpiecznego rzutowania w dół hierarchii dziedziczenia (_Downcasting_), czyli do konwersji wskaźnika lub referencji klasy bazowej na klasę pochodną.

### 1. Dwa warianty użycia: Wskaźniki vs Referencje

Slajd zwraca uwagę na kluczową różnicę w zachowaniu `dynamic_cast` w zależności od tego, czy pracujemy na wskaźnikach, czy na referencjach. Kiedy rzutowanie jest niemożliwe (bo obiekt w rzeczywistości nie jest klasą, na którą próbujemy go rzutować):

- **Wariant wskaźnikowy (`Klasa*`):** Rzutowanie nie generuje błędu krytycznego. Operator po cichu zwraca **`nullptr`**. Programista musi to sprawdzić instrukcją `if`.
    
- **Wariant referencyjny (`Klasa&`):** Referencja w C++ nie może być "pusta" (nie istnieje pojęcie _null reference_). Dlatego, jeśli rzutowanie referencji się nie powiedzie, system natychmiast **wyrzuca wyjątek `std::bad_cast`** (zdefiniowany w nagłówku `<typeinfo>`), który trzeba przechwycić blokiem `try-catch`.
    
```cpp
// 1. Rzutowanie referencji (wymaga obsługi wyjątków)
try {
    Dziecko& d = dynamic_cast<Dziecko&>(obiektBazowy);
    d.fun(); // Bezpośrednie wywołanie metody z poziomu zrzutowanej referencji
} catch (const std::bad_cast& e) {
    std::cout << "Obiekt nie jest klasy Dziecko! Złapano: " << e.what() << "\n";
}
```

### 2. Kaskadowe wywoływanie metod inline

Jak wskazuje drugi punkt slajdu, składnia C++ pozwala na natychmiastowe, bezpośrednie wywołanie metody na wyniku rzutowania, bez tworzenia lokalnej zmiennej:

```cpp
dynamic_cast<Klasa&>(obiekt).fun();
```

Mechanizm ten jest przydatny, gdy potrzebujemy jednorazowo "strzelić" w unikalną metodę klasy pochodnej. Trzeba jednak pamiętać, że w przypadku referencji, jeśli obiekt nie będzie właściwego typu, ta linijka rzuci wyjątek i przerwie działanie bieżącego bloku kodu.

### 3. Koszt sprzętowy: Dlaczego `dynamic_cast` ma narzut czasowy?

Slajd zawiera bardzo ważną uwagę wydajnościową:

> Z rzutowaniem `dynamic_cast` związany jest dodatkowy narzut czasowy w stosunku do `static_cast`.

- **`static_cast`** przeprowadza rzutowanie całkowicie na etapie kompilacji (_compile-time_). Kompilator ufa programiście "na słowo", przez co w gotowym programie operacja ta wykonuje się w zerowym czasie (to po prostu surowa interpretacja adresu).
    
- **`dynamic_cast`** musi fizycznie zabezpieczyć program przed awarią struktury pamięci. W trakcie działania programu (w _run-time_) komputer musi odpytać mechanizm RTTI, wejść do tablicy wirtualnej (`vtable`) obiektu, przeanalizować całe drzewo dziedziczenia i sprawdzić, czy konwersja jest legalna. To wymaga wykonania kilkunastu-kilkudziesięciu dodatkowych instrukcji procesora.
    
### Kompleksowy przykład do nauki (Wskaźnik vs Referencja)

```cpp
#include <iostream>
#include <typeinfo> // Wymagane dla std::bad_cast

class Pojazd { public: virtual ~Pojazd() = default; }; // Baza polimorficzna
class Rower : public Pojazd {};
class Samochod : public Pojazd {
public:
    void wlaczKlimatyzacje() { std::cout << "Klimatyzacja chlodzi!\n"; }
};

void obsluzWskaznik(Pojazd* p) {
    // Wariant wskaźnikowy: zwraca nullptr w przypadku porażki
    if (Samochod* s = dynamic_cast<Samochod*>(p)) {
        s->wlaczKlimatyzacje();
    } else {
        std::cout << "[Wskaznik]: To nie jest samochod, nic nie robie.\n";
    }
}

void obsluzReferencje(Pojazd& p) {
    // Wariant referencyjny: rzuca wyjątek std::bad_cast w przypadku porażki
    try {
        // Bezpośrednie wywołanie metody na wyniku rzutowania (zgodnie ze slajdem)
        dynamic_cast<Samochod&>(p).wlaczKlimatyzacje();
    } 
    catch (const std::bad_cast& e) {
        std::cout << "[Referencja]: Zlapano std::bad_cast! Obiekt nie pasuje.\n";
    }
}

int main() {
    Rower mojRower;
    Samochod mojSamochod;

    std::cout << "--- Test 1: Samochod ---\n";
    obsluzWskaznik(&mojSamochod);
    obsluzReferencje(mojSamochod);

    std::cout << "\n--- Test 2: Rower ---\n";
    obsluzWskaznik(&mojRower);
    obsluzReferencje(mojRower);

    return 0;
}
```

#### Wynik w konsoli:

Plaintext

```
--- Test 1: Samochod ---
Klimatyzacja chlodzi!
Klimatyzacja chlodzi!

--- Test 2: Rower ---
[Wskaznik]: To nie jest samochod, nic nie robie.
[Referencja]: Zlapano std::bad_cast! Obiekt nie pasuje.
```

## Przekazywanie funkcji lub metody jako argumentu

Przekazywanie funkcji lub metod klas jako argumentów do innych funkcji to fundamentalny krok do pisania elastycznego kodu w C++. Sposób zapisu różni się drastycznie w zależności od tego, czy przekazujesz **zwykłą funkcję** (lub statyczną metodę klasy), czy **zwykłą metodę klasy** (która potrzebuje konkretnego obiektu, by działać).

### 1. Przekazywanie zwykłej funkcji (lub metody `static`)

Zwykłe funkcje oraz metody oznaczone jako `static` nie są powiązane z żadnym konkretnym obiektem. Przekazuje się je bardzo prosto. Masz do wyboru trzy podejścia:

#### Sposób A: Nowoczesny i zalecany (`std::function` z C++11)

To najbardziej uniwersalny i czytelny sposób w nowoczesnym C++. Musisz dołączyć nagłówek `<functional>`.

```cpp
#include <iostream>
#include <functional> // Wymagane!

// Funkcja, która przyjmuje inną funkcję jako argument
// Sygnatura std::function<TypZwracany(TypyArgumentow)>
void UruchomOperacje(int a, int b, std::function<int(int, int)> operacja) {
    std::cout << "Wynik operacji: " << operacja(a, b) << "\n";
}

int Dodaj(int x, int y) { return x + y; }

class Kalkulator {
public:
    static int Pomnoz(int x, int y) { return x * y; } // Metoda statyczna
};

int main() {
    UruchomOperacje(5, 3, Dodaj);               // Przekazanie zwykłej funkcji
    UruchomOperacje(5, 3, Kalkulator::Pomnoz);  // Przekazanie metody statycznej
}
```

### Sposób B: Klasyczny wskaźnik na funkcję (Styl C)

Tradycyjny sposób, który nie wymaga żadnych nagłówków, ale ma dość skomplikowaną składnię pełną nawiasów:

```cpp
// Definicja wskaźnika jako argumentu: Typ_Zwracany (*Nazwa_Wskaznika)(Typy_Argumentow)
void UruchomKlasycznie(int a, int b, int (*wskMetody)(int, int)) {
    std::cout << "Wynik: " << wskMetody(a, b) << "\n";
}
```

### 2. Przekazywanie zwykłej metody klasy (Pointer-to-member)

Zwykła metoda klasy różni się od zwykłej funkcji tym, że **ukrywa wskaźnik `this`**. Żeby komputer mógł ją uruchomić, musi wiedzieć, **na rzecz którego obiektu** ma to zrobić.

### Nowoczesny standard (C++17): `std::invoke`

Współcześnie do uruchamiania przekazanych metod klas używa się funkcji `std::invoke`. Dzięki niej składnia staje się przejrzysta.

```cpp
#include <iostream>
#include <functional>

class Gracz {
private:
    std::string imie;
public:
    Gracz(std::string i) : imie(i) {}
    
    void Krzycz(std::string tekst) const {
        std::cout << imie << " krzyczy: " << tekst << "!\n";
    }
};

// Funkcja przyjmuje:
// 1. Referencję do obiektu, na którym wykonamy metodę
// 2. Wskaźnik do metody klasy Gracz, która zwraca void i przyjmuje std::string
void WywolajDlaGracza(const Gracz& g, void (Gracz::*wskMetody)(std::string) const, std::string wiadomosc) {
    // C++17: std::invoke ukrywa trudną składnię i wykonuje metodę na obiekcie 'g'
    std::invoke(wskMetody, g, wiadomosc);
}

int main() {
    Gracz g1("Arthur");
    
    // Przekazujemy obiekt, adres metody klasy (&Klasa::Metoda) oraz argument tekstowy
    WywolajDlaGracza(g1, &Gracz::Krzycz, "Za wolnosc");
    
    return 0;
}
```

### Starszy sposób (Przed C++17)

Jeśli Twój kompilator nie obsługuje C++17, wewnątrz funkcji zamiast `std::invoke` musiałbyś użyć specyficznego operatora `.*` (lub `->*` jeśli obiekt byłby wskaźnikiem):

```cpp
void WywolajStarszymSposobem(const Gracz& g, void (Gracz::*wskMetody)(std::string) const, std::string wiadomosc) {
    (g.*wskMetody)(wiadomosc); // Wymaga dodatkowych nawiasów wokół obiektu i wskaźnika
}
```

## 3. Sprytna alternatywa: Wyrażenia lambda (C++11)

Jeżeli funkcja, do której przekazujesz argument, przyjmuje `std::function`, możesz całkowicie pominąć skomplikowane wskaźniki do metod klas i "opakować" wywołanie metody w bezpieczną, elastyczną **lambdę** (funkcję anonimową).

To najpopularniejsze podejście w komercyjnym programowaniu:

```cpp
#include <iostream>
#include <functional>

class Silnik {
public:
    void Uruchom() { std::cout << "Silnik: Wrrr!\n"; }
};

void WykonajWyzwalacz(std::function<void()> bezpiecznik) {
    bezpiecznik(); // Po prostu uruchamiamy przekazaną operację
}

int main() {
    Silnik s;

    // Przekazujemy lambdę, która przechwytuje obiekt 's' przez referencję [&s] 
    // i wewnątrz swojego ciała bezpiecznie wywołuje jego metodę.
    WykonajWyzwalacz([&s]() { s.Uruchom(); });

    return 0;
}
```

### Podsumowanie ściągawka dla programisty:

1. Do zwykłych funkcji używaj **`std::function<TypZwracany(Argumenty)>`**.
    
2. Do metod klas przekazuj wskaźnik typu **`Typ (Klasa::*Nazwa)(Argumenty)`**, a wewnątrz funkcji wykonuj go za pomocą **`std::invoke`** (C++17).
    
3. Pamiętaj, że przekazując metodę klasy, funkcja odbierająca musi w jakiś sposób otrzymać też **obiekt** (lub wskaźnik do obiektu), na którym ta metoda ma się odpalić.

## Zapytanie o typ (`typeid`)

Ostatnim elementem mechanizmu RTTI (_Run-Time Type Information_) jest operator **`typeid`**. Służy on do bezpośredniego sprawdzania, pobierania informacji oraz porównywania dokładnego typu zmiennej lub obiektu w trakcie działania programu (_run-time_).

### 1. Podstawowe cechy i składnia operatora `typeid`

- **Wymagany nagłówek:** Aby móc korzystać z tego mechanizmu, na samej górze pliku musisz jawnie dołączyć bibliotekę standardową **`<typeinfo>`**.
    
- **Zwracany typ:** Operator `typeid(...)` zwraca referencję do stałego obiektu klasy **`std::type_info`**. Obiekt ten przechowuje unikalne dane o typie wygenerowane przez kompilator.
    
- **Wypisywanie nazwy typu (`.name()`):** Metoda `.name()` wywołana na obiekcie `std::type_info` zwraca tekstową reprezentację nazwy typu/klasy (jako `const char*`).
    
    > ⚠️ **Pułapka egzaminacyjna:** Wygląd napisu zwracanego przez `.name()` **zależy wprost od implementacji konkretnego kompilatora** (nie jest ujednolicony przez standard C++). Na przykład dla klasy `MojaKlasa`, kompilator MSVC (Visual Studio) może wypisać ładne `"class MojaKlasa"`, podczas gdy GCC (Linux/MinGW) wypisze skrócone `"9MojaKlasa"` (cyfra oznacza liczbę znaków w nazwie – tzw. _name mangling_).
    

### 2. Porównywanie typów za pomocą operatorów `==` i `!=`

Klasa `std::type_info` ma przeciążone operatory logiczne **`==`** oraz **`!=`**. Pozwala to na precyzyjne sprawdzenie, czy dwa obiekty są dokładnie tej samej klasy, lub czy uogólniony wskaźnik skrywa konkretny typ:

```cpp
if (typeid(obj) == typeid(Klasa)) {
    // Kod wykona się TYLKO wtedy, gdy obj jest DOKŁADNIE instancją typu Klasa
}
```

### 3. Różnica w działaniu: Klasy zwykłe vs Klasy polimorficzne

To najważniejszy aspekt techniczny, o który najczęściej pytają profesorowie na kolokwiach. Zachowanie `typeid` zależy od tego, czy przekazany obiekt ma funkcje wirtualne:

- **Dla typów zwykłych i niewirtualnych:** `typeid` podejmuje decyzję w trakcie kompilacji (_Wczesne wiązanie_). Jeśli przekażesz wskaźnik `Baza*`, to `typeid` zawsze powie, że to `Baza`, nawet jeśli pod spodem przypisano obiekt dziecka.
    
- **Dla klas polimorficznych (z metodą `virtual`):** `typeid` działa dynamicznie w trakcie wykonywania programu (_Późne wiązanie_). Rozpakowuje obiekt, sprawdza strukturę RTTI i potrafi wskazać faktyczny typ ukrytego dziecka.
    
### Kompleksowy przykład do nauki

Poniższy kod demonstruje bezpieczne porównywanie typów oraz obrazuje różnice w zachowaniu metody `.name()` dla klas bez wirtualności i z wirtualnością.

```cpp
#include <iostream>
#include <typeinfo> // 1. Obowiązkowy nagłówek

// Zwykłe klasy bez wirtualności (wiązanie statyczne)
class ZwyklaBaza {};
class ZwykleDziecko : public ZwyklaBaza {};

// Klasy polimorficzne (wiązanie dynamiczne dzięki 'virtual')
class PolimorficznaBaza { public: virtual ~PolimorficznaBaza() = default; };
class PolimorficzneDziecko : public PolimorficznaBaza {};

int main() {
    // Tworzymy wskaźniki uogólnione
    ZwyklaBaza* wskZwykly = new ZwykleDziecko();
    PolimorficznaBaza* wskPolimorficzny = new PolimorficzneDziecko();

    std::cout << "--- 1. Prezentacja metody .name() ---\n";
    // UWAGA: dereferencja (*wsk), aby badać obiekt, a nie sam wskaźnik (adres)
    std::cout << "Typ wskZwykly:        " << typeid(*wskZwykly).name() << "\n";
    std::cout << "Typ wskPolimorficzny: " << typeid(*wskPolimorficzny).name() << "\n";

    std::cout << "\n--- 2. Porownywanie typow (==) ---\n";
    
    // Test dla klasy polimorficznej (RTTI zadziała)
    if (typeid(*wskPolimorficzny) == typeid(PolimorficzneDziecko)) {
        std::cout << "Sukces! RTTI wykrylo, ze pod wskaznikiem bazy kryje sie PolimorficzneDziecko.\n";
    }

    // Test dla klasy zwykłej (RTTI NIE zadziała - kompilator widzi tylko typ wskaźnika)
    if (typeid(*wskZwykly) == typeid(ZwykleDziecko)) {
        std::cout << "To sie nie wypisze.\n";
    } else {
        std::cout << "Porazka! Brak wirtualnosci sprawil, ze komputer uznal obiekt za: ZwyklaBaza.\n";
    }

    // Czyszczenie pamięci
    delete wskZwykly;
    delete wskPolimorficzny;
    return 0;
}
```

```
--- 1. Prezentacja metody .name() ---
Typ wskZwykly:        class ZwyklaBaza
Typ wskPolimorficzny: class PolimorficzneDziecko

--- 2. Porownywanie typow (==) ---
Sukces! RTTI wykrylo, ze pod wskaznikiem bazy kryje sie PolimorficzneDziecko.
Porazka! Brak wirtualnosci sprawil, ze komputer uznal obiekt za: ZwyklaBaza.
```

## Mechanizm RTTI i projektowanie klas

Ten slajd dotyczy **dobrych praktyk inżynierii oprogramowania**. Podsumowuje on całą zdobytą wiedzę o RTTI (`typeid`, `dynamic_cast`) i stawia sprawę jasno: mechanizm ten, choć potężny, jest często oznaką **błędu w projekcie architektury klas** i należy go stosować ostatecznymi siłami.

### 1. Dlaczego należy unikać `typeid` w instrukcjach warunkowych?

Slajd wprost ostrzega przed pisaniem konstrukcji warunkowych opartych na sprawdzaniu typu:

> Na pewno nie należy używać instrukcji warunkowych, w których `typeid` służy do określania jaką funkcję wywołać.

Jeśli Twoja pętla lub funkcja sprawdza typ za pomocą `if(typeid(*obj) == typeid(Klasa))`, to **łamiesz fundamentalną zasadę programowania obiektowego** (zasadę OCP – _Open/Closed Principle_).

Gdy za miesiąc dodasz do programu nową klasę pochodną, Twój stary kod przestanie działać, dopóki ręcznie nie dopiszesz kolejnego bloku `else if`. Kod staje się sztywny, trudny w utrzymaniu i podatny na błędy logiczne.

### 2. Prawidłowy design: Słowo kluczowe `virtual` zamiast RTTI

Zamiast ręcznie pytać obiekt o paszport za pomocą RTTI, slajd podaje wzorcowe rozwiązanie architektoniczne:

> Jeżeli tylko jest możliwe to należy używać funkcji wirtualnych i projektować klasy tak, żeby możliwe było wywołanie odpowiedniej funkcji składowej.

Prawidłowo zaprojektowany program opiera się na **czystym polimorfizmie dynamicznym**. Tworzy się uniwersalną metodę wirtualną w klasie bazowej, nadpisuje ją w klasach pochodnych i pozwala mechanizmowi późnego wiązania (`vtable`) automatycznie wybrać właściwą ścieżkę. Kod wykonawczy wywołuje tylko `obiekt->wykonaj()`, nie wiedząc i nie interesując się, z jakim dokładnie dzieckiem pracuje.

### 3. Kiedy RTTI jest dopuszczalne? Wyjątek dla `dynamic_cast`

Ostatni punkt slajdu wskazuje bezpieczniejsze ustępstwo od tej reguły:

> W szczególnym przypadku możemy posłużyć się rzutowaniem `dynamic_cast`.

Istnieją rzadkie sytuacje (np. integracja z zamkniętymi bibliotekami zewnętrznymi lub systemy wtyczek/_plugins_), w których czysty polimorfizm nie wystarcza, ponieważ musisz dostać się do unikalnej, specyficznej metody klasy potomnej, której nie dało się logicznie wyciągnąć do wspólnej bazy. Wtedy użycie `dynamic_cast` jest całkowicie usprawiedliwione – bezpiecznie sprawdza strukturę i pozwala na reakcję, gdy typ się nie zgadza (zwracając `nullptr`).

### Porównanie wzorców: Zły design vs Dobry design

Zobaczmy czarno na białym, jak zmiana myślenia o architekturze eliminuje brzydki kod (tzw. _code smell_):

#### ❌ ZŁY DESIGN (Kod niszczący polimorfizm za pomocą `typeid`):

```cpp
// Próba sterowania zachowaniem obiektów za pomocą instrukcji warunkowych i RTTI
void ZwolnijZasoby(Pracownik* p) {
    if (typeid(*p) == typeid(Programista)) {
        // Musimy rzutować i wymuszać zachowanie specyficzne
        static_cast<Programista*>(p)->zamknijSrodowiskoIDE();
    } else if (typeid(*p) == typeid(Ksiegowy)) {
        static_cast<Ksiegowy*>(p)->wylogujZSystemuERP();
    }
    // Jeśli dojdzie nowy zawód, ta funkcja się posypie!
}
```

#### DOBRY DESIGN (Czysty polimorfizm – rozszerzalny i bezpieczny):

```cpp
class Pracownik {
public:
    // Przenosimy odpowiedzialność na metodę wirtualną w bazie
    virtual void wyczyscStan() = 0; 
    virtual ~Pracownik() = default;
};

class Programista : public Pracownik {
public:
    void wyczyscStan() override { zamknijSrodowiskoIDE(); } // Każdy sprząta po swojemu
};

class Ksiegowy : public Pracownik {
public:
    void wyczyscStan() override { wylogujZSystemuERP(); }
};

// Funkcja wykonawcza staje się banalnie prosta i uniwersalna:
void ZwolnijZasoby(Pracownik* p) {
    p->wyczyscStan(); // Żadnych if-ów, żadnego RTTI, pełny polimorfizm!
}
```

# ~={orange}Dziedziczenie wielokrotne=~

**Dziedziczenie wielokrotne** to zaawansowana cecha języka C++, która pozwala klasie pochodnej dziedziczyć właściwości, pola i metody z **więcej niż jednej klasy bazowej jednocześnie**.

Wiele nowoczesnych języków programowania (np. Java, C#) świadomie zrezygnowało z tej cechy z powodu skomplikowania, pozwalając na dziedziczenie tylko po jednym rodzicu. C++ daje tu jednak programiście pełną (choć wymagającą uwagi) swobodę.

### 1. Sposób zapisu i aspekty formalne (Slajd 1 i 2)

Klasy bazowe na liście pochodzenia oddzielamy po prostu przecinkami. Przed nazwą każdego rodzica **musimy jawnie podać modyfikator dostępu** (`public`, `protected`, `private`).

```cpp
class C : public A, public B { ... };
```

- **Domyślny modyfikator:** Jeśli zapomnisz napisać słowa `public` przed którąś z klas (np. `class C : public A, B`), kompilator dla słowa `class` zastosuje tam domyślnie **dziedziczenie prywatne (`private`)**.
    
- **Unikalność na liście:** Dana klasa bazowa może znaleźć się na liście dziedziczenia **tylko raz**. Nie można napisać `class C : public A, public A`.
    
- **Wymóg pełnej definicji:** Każda klasa, po której dziedziczymy, musi być kompilatorowi w pełni znana (jej ciało musi być zdefiniowane wcześniej). Nie wystarczy sama deklaracja zapowiadająca typu `class A;`.
    

### 2. Konstruktory przy dziedziczeniu wielokrotnym

Konstruktor klasy pochodnej (wielokrotnej) ma obowiązek wywołać na liście inicjalizacyjnej konstruktory wszystkich swoich bezpośrednich klas bazowych.

#### ⚠️ Pułapka egzaminacyjna: Kolejność wywoływania konstruktorów!

Spójrz na kod z trzeciego slajdu:

```cpp
class C : public A, public B {
    C() : B(), A() { ... }
};
```

Programista na liście inicjalizacyjnej zapisał najpierw `B()`, a potem `A()`. Jednak w C++ **kolejność zapisu na liście inicjalizacyjnej nie ma żadnego znaczenia!**

> **Żelazna zasada:** O kolejności uruchamiania konstruktorów decyduje wyłącznie **kolejność, w jakiej klasy bazowe zostały wymienione w nagłówku klasy** (czyli na liście pochodzenia).

W tym przypadku, ponieważ nagłówek to `class C : public A, public B`, jako pierwszy **zawsze** wykona się konstruktor klasy `A`, potem klasy `B`, a na samym końcu kod konstruktora klasy `C`.

### 3. Problem wieloznaczności (Ambiguitet)

Największym problemem dziedziczenia wielokrotnego jest **konflikt nazw**. Zachodzi on wtedy, gdy dwie zupełnie niezależne klasy bazowe posiadają pole lub metodę o dokładnie takiej samej nazwie.

#### Przykład:

Klasa `A` ma pole `int x;`. Klasa `B` również ma pole `int x;`. Klasa `C` dziedziczy po obu.

Gdy wewnątrz klasy `C` spróbujesz napisać:

```cpp
x = 5; // BŁĄD KOMPILACJI! Wieloznaczność (Ambiguity)
```

Kompilator panikuje, ponieważ nie wie, o które `x` Ci chodzi (czy o to z klasy `A`, czy z klasy `B`).

#### Rozwiązanie: Operator zakresu `::`

Aby usunąć wieloznaczność, musisz jawnie wskazać klasę-właściciela za pomocą operatora `::`:

```cpp
A::x = 5; // OK - modyfikujemy x odziedziczone po klasie A
B::x = 10; // OK - modyfikujemy x odziedziczone po klasie B
```

#### 🔥 Bardzo ważny haczyk egzaminacyjny z ostatniego slajdu:

> Najpierw sprawdzana jest jednoznaczność, a dopiero później dostęp!!!

Jeśli pole `A::x` jest publiczne, a pole `B::x` jest **prywatne** (`private`), to intuicja podpowiada, że zapis `x = 5;` powinien automatycznie wybrać publiczne pole z `A` (bo pole z `B` jest i tak niedostępne).

**W C++ tak to nie działa!** Kompilator w pierwszej kolejności ślepo szuka samej nazwy. Widząc dwa dopasowania, natychmiast zgłasza błąd wieloznaczności i przerywa kompilację, zanim w ogóle sprawdzi poziomy dostępu (`public`/`private`).

### Praktyczny przykład do nauki (Kompletny kod)

Oto jak poprawnie zaimplementować strukturę z prezentacji, radząc sobie z kolejnością konstrukcji i wieloznacznością:

```cpp
#include <iostream>

class Aparat {
public:
    int rozdzielczosc = 48; // [Mpx]
    Aparat() { std::cout << "1. Konstruktor klasy Aparat\n"; }
};

class Telefon {
public:
    int rozdzielczosc = 1080; // [px] ekranu - KONFLIKT NAZW!
    Telefon() { std::cout << "2. Konstruktor klasy Telefon\n"; }
};

// Klasa Smartfon łączy cechy obu urządzeń
class Smartfon : public Aparat, public Telefon {
public:
    // Mimo ze w liscie napiszemy Telefon() jako pierwszy, 
    // i tak najpierw wykona sie Aparat(), bo jest pierwszy w naglowku klasy!
    Smartfon() : Telefon(), Aparat() {
        std::cout << "3. Konstruktor klasy Smartfon\n";
    }

    void pokazSpecyfikacje() {
        // std::cout << rozdzielczosc; // BŁĄD! Kompilator nie wie, ktora rozdzielczosc wybrac.
        
        // Rozwiazanie za pomoca operatora zakresu ::
        std::cout << "Rozdzielczosc aparatu: " << Aparat::rozdzielczosc << " Mpx\n";
        std::cout << "Rozdzielczosc ekranu:  " << Telefon::rozdzielczosc << " px\n";
    }
};

int main() {
    Smartfon s;
    std::cout << "--- Obiekt stworzony ---\n";
    s.pokazSpecyfikacje();
    return 0;
}
```

#### Wynik w konsoli:

```
1. Konstruktor klasy Aparat
2. Konstruktor klasy Telefon
3. Konstruktor klasy Smartfon
--- Obiekt stworzony ---
Rozdzielczosc aparatu: 48 Mpx
Rozdzielczosc ekranu:  1080 px
```

## Wieloznacznośc a pokrewieństwo

### 1. Reguła Dominacji i Pokrewieństwo

W tradycyjnym dziedziczeniu wielokrotnym kompilator panikuje (zgłasza błąd _ambiguity_), gdy widzi dwie identyczne nazwy. Istnieje jednak jeden kluczowy wyjątek, który ilustruje pierwszy slajd: **Reguła Dominacji (Dominance Rule)**.

### Dlaczego `Syn` widzi `x` bez błędów?
![[Pasted image 20260620011002.png]]
Spójrz na graf: `Syn` dziedziczy bezpośrednio po klasie `Matka` oraz po klasie `Ojciec`. Klasa `Ojciec` dziedziczy po klasie `Dziadek`. Zarówno `Dziadek`, jak i `Matka` posiadają pole `x`.

Kompilator szuka zmiennej `x`, idąc w górę drzewa dziedziczenia od klasy `Syn`:

- Ścieżka prawa: `Syn` $\rightarrow$ `Matka` (znaleziono `x` na poziomie 1).
    
- Ścieżka lewa: `Syn` $\rightarrow$ `Ojciec` (brak `x`) $\rightarrow$ `Dziadek` (znaleziono `x` na poziomie 2).

Ponieważ `Matka` leży w bezpośrednim zakresie (bliższe pokrewieństwo), jej zmienna `x` **zasłania (dominuje nad)** zmienną `x` z klasy `Dziadek`. Dla kompilatora sprawa jest ewidentna – wybiera bliższą zmienną.

### Skracanie kwalifikatorów

Gdy graf staje się ogromny (jak dolny rysunek: A, B, C, D, E, F, G, H), używanie pełnych ścieżek z operatorami `::` byłoby katorgą. Kompilator pozwala na skróty.
![[Pasted image 20260620011050.png]]
Jeśli wskażesz klasę pośrednią, od której dana gałąź staje się już całkowicie liniowa i jednoznaczna, kompilator bez problemu domyśli się reszty drogi:

```cpp
// Zamiast pisać abstrakcyjne ścieżki przechodzące przez cały graf:
H_obj.C::x == H_obj.A::x; // Ponieważ w tej gałęzi to i tak ta sama zmienna!
```

### 2. Anatomia Problemu Diamentowego

Slajd trzeci pokazuje klasyczny koszmar programisty obiektowego, czyli sytuację, w której dwie klasy pochodne mają wspólnego rodzica, a na dole spina je jedna klasa potomna (Amfibía).
![[Pasted image 20260620011303.png]]
#### Jak wygląda pamięć obiektu `Amfibia` przy ZWYKŁYM dziedziczeniu?

Gdybyśmy zmierzyli rozmiar obiektu `Amfibia` operatorem `sizeof`, zobaczylibyśmy, że jest on gigantyczny. Kompilator układa pamięć RAM dla obiektu `Amfibia` jako dwa niezależne, sklejone ze sobą bloki:

```
[ BLOK SAMOCHODU ]
  - podblok ŚrodekTransportu -> (zmienna: srodek_transportu)
  - unikalne pola Samochodu
[ BLOK ŁODZI ]
  - podblok ŚrodekTransportu -> (zmienna: srodek_transportu) <--- DUPLIKAT!
  - unikalne pola Łodzi
[ POLA AMFIBII ]
```

Mamy **fizyczne zdublowanie danych**. Jeśli `ŚrodekTransportu` zawierałby wielomegabajtową tablicę danych, nasza `Amfibia` marnowałaby mnóstwo pamięci RAM na przechowywanie dwóch identycznych kopii.

### 3. Rozwiązanie: Klasy Wirtualne

Aby scalić te dwa powielone bloki w jeden wspólny obszar, stosujemy **dziedziczenie wirtualne** (`virtual public`).

```cpp
class SrodekTransportu { public: int waga; };

// Słowo 'virtual' zmienia architekturę pamięci klas pośrednich!
class Samochod : virtual public SrodekTransportu {};
class Lodz     : virtual public SrodekTransportu {};

class Amfibia : public Samochod, public Lodz {};
```

### Co się zmienia w pamięci RAM?

Kompilator całkowicie reorganizuje strukturę obiektu. Wyciąga wspólnego przodka (`ŚrodekTransportu`) na sam koniec struktury obiektu jako **jeden, pojedynczy blok**.

Klasy `Samochód` i `Łódź` zamiast posiadać fizyczne zmienne rodzica, otrzymują ukryte wskaźniki **`vbptr` (Virtual Base Pointer)**. Te wskaźniki pokazują komputerowi przesunięcie w pamięci: _"Jeśli chcesz zmienić wagę, skocz na sam koniec obiektu, tam leży nasza wspólna zmienna"_.

```
[ Część Samochodu: zawiera wskaźnik vbptr ] -------\
[ Część Łodzi:     zawiera wskaźnik vbptr ] -------+---> [ JEDYNA, wspólna sekcja ŚrodekTransportu ]
[ Część Amfibii ]                                  |     (zmienna: waga)
```

Dzięki temu `amfibia.waga = 2000;` modyfikuje dokładnie tę samą komórkę pamięci, niezależnie od tego, czy odwołujemy się do niej z perspektywy samochodu, czy łodzi.

## 4. Dziedziczenie Wirtualne i Niewirtualne Jednocześnie
![[Pasted image 20260620011744.png]]
Ostatni slajd prezentuje konstrukcję "hybrydową", która potrafi zagiąć niejednego programistę na rozmowie rekrutacyjnej: klasa `AmfibiaLepsza` dziedziczy po `Amfibii` (która ma już wirtualny środek transportu) oraz **dodatkowo, bezpośrednio i niewirtualnie** po klasie `ŚrodekTransportu`.

#### Ile kopii `ŚrodekTransportu` ma w sobie `AmfibiaLepsza`?

Odpowiedź brzmi: **Dokładnie dwie**.

1. **Kopia Współdzielona (Wirtualna):** Zabezpieczona przez wcześniejszy diament (`Samochod` i `Lodz` dzielą ten sam obszar).
    
2. **Kopia Dedykowana (Niewirtualna):** Dołożona siłowo na samym dole przez `AmfibieLepszą`.

### Po co komu taka struktura?

W czystym projektowaniu aplikacji biznesowych jest to uznawane za błąd architektoniczny. Wykorzystuje się to jednak w zaawansowanym programowaniu systemowym lub przy tworzeniu bibliotek niskopoziomowych, gdy obiekt podrzędny musi mieć:

- Jeden globalny stan urządzenia (współdzielony przez wirtualną bazę),
    
- Jeden osobny, niezależny kanał komunikacyjny/bufor (zapewniony przez dedykowaną, niewirtualną bazę).

### 5. Egzaminacyjny Smaczek: Unikalna zasada konstruktorów

Przy dziedziczeniu wirtualnym dochodzi do drastycznej zmiany **kolejności i odpowiedzialności za wywoływanie konstruktorów**.

W zwykłym dziedziczeniu: `Dziecko` uruchamia `Metodę Rodzica`, a `Rodzic` uruchamia `Dziadka`.

W dziedziczeniu wirtualnym: Ponieważ praprzodek (`ŚrodekTransportu`) jest tylko jeden i jest współdzielony, klasy pośrednie (`Samochod`, `Lodz`) **mają zakaz jego inicjalizacji!**

> 🔴 **Zasada Konstruktora Wirtualnego:** Za wywołanie konstruktora wirtualnej klasy bazowej odpowiada **zawsze i bezpośrednio najniższa klasa w hierarchii (obiekt ostateczny – czyli `Amfibia`)**. Wywołania konstruktora bazy wirtualnej zapisane w klasach `Samochod` i `Lodz` są przez kompilator całkowicie ignorowane.

```cpp
class Amfibia : public Samochod, public Lodz {
public:
    // To Amfibija musi JAWNIE nakarmić konstruktor ŚrodkaTransportu!
    Amfibia(int w) : SrodekTransportu(w), Samochod(), Lodz() {}
};
```

## 1. Reguła Inicjalizacji Klas Wirtualnych sztuczka z `final`

Mówi ona, że za konstrukcję wirtualnej klasy bazowej odpowiada **zawsze i wyłącznie klasa najbardziej pochodna (czyli ta na samym dole hierarchii, którą fizycznie tworzymy)**.

### Dlaczego C++ tak robi?

W dziedziczeniu wielokrotnym typu diament (np. `Amfibia` dziedziczy po `Samochodzie` i `Lodzi`, a te wirtualnie po `SrodkuTransportu`), klasa bazowa jest dokładnie **jedna i wspólna**.

Gdybyśmy pozwolili, aby `Samochod` i `Lodz` inicjalizowały bazę, powstałby konflikt (np. `Samochod` chciałby przekazać do bazy liczbę 4, a `Lodz` liczbę 0). Kompilator ignoruje więc ich listy inicjalizacyjne i zmusza klasę na samym dole (`Amfibia`), aby to ona osobiście wywołała konstruktor praprzodka.

## 2. Rozwiązanie Zagadki: "Co jeszcze jest niezbędne?"

Slajd 1 pyta: skoro wiemy, że klasa najbardziej pochodna musi wywołać konstruktor wirtualnego praprzodka, to jak za pomocą tego mechanizmu stworzyć klasę finalną (taką, po której nie da się dziedziczyć)?

> 💡 **Odpowiedź brzmi:** Niezbędny jest **prywatny konstruktor** klasy bazowej oraz **deklaracja przyjaźni (`friend`)** z klasą, którą chcemy uczynić finalną.

### Jak działa ta genialna blokada? (Krok po kroku)

1. Tworzymy pomocniczą klasę (nazwijmy ją `UstalaczFinalnosci`), której **konstruktor ukrywamy w sekcji `private`**. Nikt z zewnątrz nie może stworzyć tej klasy.
    
2. Tworzymy naszą klasę `KlasaFinalna`. Wewnątrz klasy pomocniczej dajemy jej status przyjaciela (`friend class KlasaFinalna;`).
    
3. `KlasaFinalna` dziedziczy po klasie pomocniczej **wirtualnie** (`virtual private UstalaczFinalnosci`). Ponieważ jest przyjacielem, ma pełne prawo wywołać ten prywatny konstruktor. Klasa działa idealnie, możemy tworzyć jej obiekty.
    
4. Co się stanie, gdy ktoś spróbuje oszukać system i napisać `class Dziecko : public KlasaFinalna`?
    
    Gdy spróbujemy stworzyć obiekt `Dziecko d;`, klasa `Dziecko` staje się **klasą najbardziej pochodną**. Zgodnie z regułą ze slajdu 2, `Dziecko` musi natychmiast **bezpośrednio** wywołać konstruktor wirtualnego praprzodka (`UstalaczFinalnosci`).
    
    I w tym momencie kompilator zgłasza błąd krytyczny: _"Stop! Klasa Dziecko nie jest przyjacielem klasy UstalaczFinalnosci, więc nie ma dostępu do jej prywatnego konstruktora!"_. Dziedziczenie zostało skutecznie zablokowane.
## 3. Pełny przykład kodu (Analiza mechanizmu)

```cpp
#include <iostream>

// 1. Klasa pomocnicza, która trzyma klucz do blokady
class UstalaczFinalnosci {
private:
    // Prywatny konstruktor - nikt obcy go nie uruchomi
    UstalaczFinalnosci() { 
        std::cout << "[Ustalacz]: Konstrukcja bazy wirtualnej\n"; 
    }
    
    // Kluczowy element: dajemy pełne prawa tylko tej jednej klasie
    friend class KlasaFinalna; 
};

// 2. Nasza właściwa klasa - dziedziczy WIRTUALNIE. 
// Może istnieć, bo jest przyjacielem Ustalacza.
class KlasaFinalna : virtual private UstalaczFinalnosci {
public:
    KlasaFinalna() {
        std::cout << "[KlasaFinalna]: Tworzenie obiektu\n";
    }
};

// 3. Próba nielegalnego dziedziczenia
class Dziecko : public KlasaFinalna {
public:
    Dziecko() {
        std::cout << "[Dziecko]: Tworzenie obiektu\n";
    }
};

int main() {
    // A. To zadziała idealnie:
    KlasaFinalna f; 

    // B. TO WYGENERUJE BŁĄD KOMPILACJI:
    // Dziecko d; 
    // Kompilator powie: 'UstalaczFinalnosci::UstalaczFinalnosci()' is private within this context
    // Ponieważ klasa 'Dziecko' próbuje ominąć 'KlasaFinalna' i bezpośrednio odpalić konstruktor Ustalacza!

    return 0;
}
```

### Podsumowanie na egzamin:

- **Zasada działania:** Przejęcie odpowiedzialności za konstruktor wirtualny przez klasę najbardziej pochodną + brak praw dostępu tej klasy do prywatnego konstruktora u praprzodka.
    
- **Po co to wiedzieć w 2026 roku?** Współczesny C++ posiada proste słowo `final` (np. `class KlasaFinalna final {};`), które robi to automatycznie pod maską. Jednak znajomość tego historycznego triku jest koronnym dowodem na to, że programista doskonale rozumie niskopoziomową mechanikę działania pamięci i reguł rządzących dziedziczeniem wirtualnym. 

## Dziedziczenie (Relacja „IS-A”) vs Kompozycja (Relacja „HAS-A”)

Wybór między dziedziczeniem a osadzaniem obiektów (kompozycją) to najważniejsza decyzja projektowa. Złe dopasowanie narzędzia prowadzi do powstania kodu, który jest sztywny i niezwykle trudny w utrzymaniu.

### 1. Dziedziczenie (Relacja "Jest rodzajem..." / _IS-A_)

Dziedziczenie stosujemy tylko wtedy, gdy klasa pochodna jest specyficznym, bardziej wyspecjalizowanym rodzajem klasy bazowej. Klasa pochodna przejmuje wtedy cały interfejs i zachowanie rodzica.

- **Przykłady:**
    
    - `Kwadrat` **jest rodzajem** `FiguryGeometrycznej`.
        
    - `Samochod` **jest rodzajem** `Pojazdu`.
        
    - `Dyrektor` **jest rodzajem** `Pracownika`.
        

```
class Pojazd {
public:
    void jedz() {}
};

// Prawidłowe dziedziczenie - Samochód to pojazd
class Samochod : public Pojazd {
public:
    void otworzBagaznik() {}
};
```

### 2. Kompozycja / Zawieranie (Relacja "Składa się z..." / _HAS-A_)

Kompozycję stosujemy wtedy, gdy jeden obiekt logicznie zawiera w sobie inne obiekty jako swoje części składowe. Zamiast dziedziczyć, po prostu tworzymy pola odpowiednich typów wewnątrz klasy.

- **Przykłady:**
    
    - `Samochod` **składa się z** `Kol`, `Silnika` i `Radia` (Samochód _ma_ silnik, ale silnik _nie jest_ samochodem).
        
    - `Radio` **składa się z** `Tranzystorow`.
        
    - `Komputer` **składa się z** `Procesora` i `PamieciRAM`.
        

```cpp
class Silnik {
public:
    void uruchom() {}
};

class Kolo {};

// Prawidłowa kompozycja - Samochód zawiera komponenty
class Samochod {
private:
    Silnik silnik; // Osadzenie składnika
    Kolo kola[4];  // Osadzenie składnika
public:
    void odpal() {
        silnik.uruchom();
    }
};
```

> 💡 **Projektowy dylemat:** Wybór nie zawsze jest oczywisty. Na przykład: czy klasa `Punkt3D` powinna dziedziczyć po `Punkt2D` i dodać współrzędną $Z$, czy może powinna zawierać w sobie obiekt `Punkt2D`? Matematycznie punkt 3D nie jest po prostu "rodzajem" punktu 2D, dlatego w tym przypadku lepsza okazuje się kompozycja lub stworzenie obu klas niezależnie. W inżynierii oprogramowania istnieje zasada: _„Preferuj kompozycję ponad dziedziczenie”_, ponieważ jest ona bezpieczniejsza i bardziej elastyczna.

## Dobre praktyki i reguły bezpiecznego dziedziczenia

Samo zastosowanie dziedziczenia publicznego nakłada na programistę zestaw technicznych obowiązków, których niedopełnienie grozi wyciekami pamięci lub trudnymi do wykrycia błędami logicznymi.

### 1. Nadpisywanie wyłącznie funkcji wirtualnych

Klasa pochodna powinna przesłaniać (nadpisywać) **tylko te funkcje, które w klasie bazowej zostały jawnie zadeklarowane jako `virtual`**. Przesłonięcie zwykłej funkcji niepolimorficznej niszczy spójność kodu i prowadzi do błędów przy upcastingu (wskaźnik bazowy wywoła starą funkcję, a wskaźnik pochodny nową).

Jeśli projektujesz klasę pochodną i planujesz, że w przyszłości ktoś będzie dziedziczył po niej, Twoje nadpisane funkcje również powinny pozostać wirtualne dla kolejnych pokoleń.
```cpp
#include <iostream>
#include <vector>

// ==========================================
// POKOLENIE 1: DZIADEK (Klasa bazowa)
// ==========================================
class Postac {
public:
    // Tutaj zaczyna się łańcuch wirtualności
    virtual void wykonajAtak() const {
        std::cout << "Postac zadaje podstawowe obrazenia fizyczne.\n";
    }
    virtual ~Postac() = default; 
};

// ==========================================
// POKOLENIE 2: RODZIC (Klasa pochodna, która będzie bazą dla innych)
// ==========================================
class Mag : public Postac {
public:
    // DOBRA PRAKTYKA: 
    // Słowo 'override' zapewnia bezpieczeństwo. W C++ ta metoda AUTOMATYCZNIE 
    // staje się wirtualna dla klas, które odziedziczą po klasie Mag.
    void wykonajAtak() const override {
        std::cout << "Mag rzuca podstawowa kule ognia!\n";
    }
};

// ==========================================
// POKOLENIE 3: WNUK (Klasa pochodna drugiego stopnia)
// ==========================================
class Nekromanta : public Mag {
public:
    // Nekromanta bez problemu nadpisuje metodę, ponieważ Mag utrzymał wirtualność
    void wykonajAtak() const override {
        std::cout << "Nekromanta wskrzesza szkielety i wysysa zycie!\n";
    }
};

int main() {
    std::cout << "--- Dynamiczne wiazanie na roznych poziomach ---\n";

    // Scenariusz A: Wskaźnik typu Dziadek (Postac*) wskazuje na Wnuka
    Postac* p1 = new Nekromanta();
    p1->wykonajAtak(); 
    // Wypisze: "Nekromanta wskrzesza szkielety..." -> Polimorfizm zadziałał idealnie!

    // Scenariusz B: Wskaźnik typu Rodzic (Mag*) wskazuje na Wnuka
    // Ktoś stworzył system obsługujący tylko Magów, ale nasz Nekromanta nadal tam pasuje!
    Mag* p2 = new Nekromanta();
    p2->wykonajAtak(); 
    // Wypisze: "Nekromanta wskrzesza szkielety..." -> Łańcuch nie został przerwany.

    // Czyszczenie pamięci
    delete p1;
    delete p2;
    return 0;
}
```

- **Automatyczne dziedziczenie wirtualności:** W języku C++ obowiązuje zasada: _Raz wirtualna, zawsze wirtualna_. Gdy `Postac` oznaczyła metodę jako `virtual`, to w klasie `Mag` jest ona wirtualna „z urzędu” – nawet jeśli zapomnisz dopisać słowa `virtual` czy `override`.
    
- **Dlaczego powinieneś pisać `override` w klasach pośrednich?** Ponieważ programista, który za dwa lata otworzy Twój plik z klasą `Mag` i zobaczy czystą sygnaturę `void wykonajAtak() const override;`, dostaje od Ciebie jasny komunikat: _„Ta funkcja jest częścią polimorficznego interfejsu. Możesz śmiało po mnie dziedziczyć i napisać własną wersję tej operacji, a mechanizm tablic wirtualnych zadziała bezbłędnie”_.
    
- **Jak można taki łańcuch świadomie przerwać?** Gdybyś w klasie `Mag` uznał, że kula ognia to absolutny szczyt możliwości magicznych i nikt po Tobie nie ma prawa tego zmieniać, dopisałbyś słowo `final`:
    
    ```cpp
    void wykonajAtak() const override final; // Blokuje możliwość nadpisania w klasie Nekromanta
    ```
### 2. Obowiązkowy wirtualny destruktor

Każda klasa bazowa, która posiada choć jedną funkcję wirtualną, **musi posiadać wirtualny destruktor (`virtual ~Klasa() = default;`)**.

Jeśli usuniesz obiekt klasy pochodnej za pomocą wskaźnika typu klasy bazowej, a destruktor nie będzie wirtualny, program uruchomi tylko destruktor bazy. Wszystkie dynamiczne zasoby alokowane przez klasę pochodną zostaną w pamięci RAM, powodując gigantyczny wyciek pamięci.

```cpp
class Baza {
public:
    virtual ~Baza() = default; // Gwarancja bezpieczeństwa dla klas pochodnych
};
```

### 3. Pułapka domyślnych parametrów (Niezwykle ważne!)

To jeden z najgroźniejszych mechanizmów w C++. Funkcje nadpisane w klasie pochodnej **powinny mieć dokładnie te same domyślne wartości parametrów, co w klasie bazowej**.

Dlaczego? Ponieważ w C++ funkcje wirtualne są wiązane dynamicznie (w run-time), ale **domyślne argumenty są podstawiane statycznie (w compile-time)**.

```cpp
class Rodzic {
public:
    virtual void konfiguruj(int x = 10) { std::cout << "Rodzic: " << x << "\n"; }
};

class Dziecko : public Rodzic {
public:
    void konfiguruj(int x = 20) override { std::cout << "Dziecko: " << x << "\n"; }
};

int main() {
    Rodzic* w = new Dziecko();
    w->konfiguruj(); // Wyświetli: "Dziecko: 10" !!!
}
```

_Co tu się stało?_ Kompilator w compile-time widzi wskaźnik `Rodzic*`, więc bierze jego domyślny parametr (`10`). W run-time polimorfizm prawidłowo uruchamia kod klasy `Dziecko`, ale przekazuje mu... wartość `10` zamiast `20`!

### 4. Znaczenie publicznego dziedziczenia

Jedynie **dziedziczenie publiczne (`public`)** reprezentuje w pełni relację generalizacji (czyste _IS-A_).

Pozostałe dwa tryby – dziedziczenie prywatne (`private`) oraz chronione (`protected`) – nie oznaczają logicznego pokrewieństwa typów dla świata zewnętrznego (nie pozwalają na niejawny upcasting). Są one traktowane wyłącznie jako techniczny sposób na **czyste wykorzystanie już istniejącego kodu** klasy bazowej wewnątrz klasy pochodnej (taka ukryta alternatywa dla kompozycji).

# ~={orange}Szablony=~
W silnie typowanych językach, takich jak C++, każda zmienna musi mieć jasno określony typ danych. Choć zapewnia to ogromne bezpieczeństwo, rodzi też spory problem architektoniczny: co zrobić, gdy chcemy napisać funkcję wykonującą **dokładnie to samo zadanie**, ale dla różnych typów danych (np. szukanie większej liczby dla `int`, `double` czy `float`)?

Zanim w C++ pojawiły się szablony, programiści próbowali rozwiązać ten problem za pomocą mechanizmów zapożyczonych z języka C. Skończyło się to technologicznym koszmarem.

## 1. Ślepy przodek: Makrodefinicje przedprocesora (Styl C)

W języku C do uzyskania uniwersalności kodu używano makr preprocesora (`#define`). Makro to nie jest prawdziwa funkcja – to po prostu **mechaniczny nakaz "kopiuj-wklej"** wykonywany na czystym tekście przed właściwą kompilacją.

### Przykład klasycznego makra `max`:

```cpp
#define max(a, b) (((a) < (b)) ? (b) : (a))
```

### Pułapka efektów ubocznych (Destrukcyjne działanie `max(a++, b++)`)

Mechaniczne podstawianie tekstu potrafi całkowicie zniszczyć logikę programu, gdy jako argumenty podamy wyrażenia z inkrementacją.

Wyobraź sobie taki zapis:

```cpp
int a = 5;
int b = 5;
int wynik = max(a++, b++); // Spodziewasz się wyniku 5, a zmienne powinny wzrosnąć do 6.
```

Podczas fazy preprocesora, słowo `max(a++, b++)` zostaje bezmyślnie rozpakowane w czysty tekst:

```cpp
int wynik = (((a++) < (b++)) ? (b++) : (a++));
```

#### Co dzieje się w pamięci RAM podczas wykonywania tej linijki?

1. **Warunek:** Komputer sprawdza `a++ < b++`. Ponieważ to postinkrementacja, do porównania brane są stare wartości: `5 < 5`. Warunek jest **fałszywy**.
    
2. **Inkrementacja I:** Obie zmienne `a` oraz `b` natychmiast rosną o jeden. Obie mają teraz wartość `6`.
    
3. **Wynik:** Ponieważ warunek był fałszywy, wykonuje się sekcja po dwukropku, czyli `(a++)`.
    
4. **Inkrementacja II:** Zmienna `a` (która miała już `6`) zostaje podstawiona do zmiennej `wynik` (czyli `wynik = 6`), po czym **po raz drugi w tej samej linijce rośnie o jeden!**
    

_Ostateczny stan po wykonaniu makra:_ `wynik = 6`, `b = 6`, a `a = 7`! Zmienna `a` uległa podwójnej inkrementacji. To podręcznikowy przykład, dlaczego makra są uznawane za błąd w sztuce i są **całkowicie niezalecane**.

## 2. Nowoczesny wybawca: Szablony w C++ (_Templates_)

Aby raz na zawsze wyeliminować niebezpieczne makra tekstu, w C++ wprowadzono **szablony**. To fundament programowania generycznego (uogólnionego).

### Czym fizycznie jest szablon?

- Szablon **nie jest gotową funkcją ani klasą**. To czysty projekt, wzorzec, forma odlewnicza lub przepis architektoniczny.
    
- Szablon nie generuje żadnego kodu w pliku wykonywalnym, dopóki programista lub kompilator nie wskaże konkretnego typu danych, dla którego ma zostać użyty.
    

### Jak działają szablony? (Instancjowanie)

Gdy piszesz szablon, parametryzujesz go nieznanym typem danych (zwyczajowo nazywanym `T`). Dopiero gdy w kodzie użyjesz tego szablonu dla typu `int`, kompilator budzi się do pracy i **automatycznie generuje w pamięci czystą, bezpieczną funkcję** dla typu `int`. Ten proces nazywamy **instancjowaniem szablonu**.

## 3. Porównanie w kodzie: Bezpieczeństwo szablonu

Zobaczmy, jak ten sam problem podwójnej inkrementacji zachowuje się w starciu z nowoczesnym szablonem C++.

```cpp
#include <iostream>

// Definicja szablonu funkcji. 
// Słowo 'typename T' oznacza: "W tym miejscu podstawimy jakikolwiek poprawny typ"
template <typename T>
T szablonowe_max(T a, T b) {
    return (a < b) ? b : a;
}

int main() {
    int x = 5;
    int y = 5;

    // Wywołujemy szablon. Kompilator automatycznie domyśla się, że T = int.
    // Argumenty x++ oraz y++ są obliczane DOKŁADNIE RAZ przed wejściem do funkcji!
    int wynik = szablonowe_max(x++, y++);

    std::cout << "Wynik: " << wynik << "\n"; // Wypisze: 5 (Prawidłowo)
    std::cout << "X:     " << x << "\n";     // Wypisze: 6 (Prawidłowo - wzrosło raz)
    std::cout << "Y:     " << y << "\n";     // Wypisze: 6 (Prawidłowo - wzrosło raz)

    return 0;
}
```

### Podsumowanie różnic do notatek:

|**Cecha**|**Makrodefinicja (#define)**|**Szablon (template)**|
|---|---|---|
|**Mechanizm działania**|Mechaniczne podstawianie tekstu (preprocesor)|Inteligentne generowanie kodu typu (kompiliator)|
|**Kontrola typów**|Brak – przetwarza wszystko jak tekst|**Pełna kontrola typów** (silne typowanie)|
|**Efekty uboczne (np. `++`)**|Bardzo wysokie ryzyko błędów logicznych|**Całkowicie bezpieczne**|
|**Debugowanie kodu**|Niemożliwe (błędy wskazują na rozwinięte makro)|Możliwe, kompilator precyzyjnie wskazuje typ błędu|
Biblioteka Standardowa C++ (STL) wykorzystuje szablony, aby dostarczyć gotowe, wysoce zoptymalizowane struktury danych (szablony klas) oraz uniwersalne algorytmy (szablony funkcji). Pozwala to na pisanie kodu bezpiecznego typowo, który bez żadnych modyfikacji może przetwarzać zarówno proste typy wbudowane (`int`, `double`), jak i złożone klasy użytkownika.

## Szablony Klas: Kontenery STL

Kontenery różnią się fundamentalnie sposobem zarządzania pamięcią RAM oraz wydajnością poszczególnych operacji.

### 1. Tablica statyczna (`std::array`)

Jest to nowoczesny, bezpieczny zamiennik tradycyjnych tablic wbudowanych w stylu języka C (`int tab[5]`). Szablon ten przyjmuje dwa parametry: typ przechowywanych danych `T` oraz rozmiar `N`.

- **Alokacja na stosie:** Pamięć na elementy rezerwowana jest bezpośrednio na stosie (_stack_), co gwarantuje błyskawiczny dostęp.
    
- **Rozmiar znany w czasie kompilacji:** Rozmiar `N` musi być stałą liczbową znaną podczas budowania programu – nie można go zmienić w trakcie działania aplikacji.
    
- **Bezpieczeństwo typów:** Kontener pozwala na niejawne konwersje elementów podczas przypisywania, o ile są one legalne dla typu bazowego.
![[Pasted image 20260620194914.png]]
```cpp
#include <iostream>
#include <array>

int main() {
    // Definicja tablicy statycznej na 4 elementy typu double
    std::array<double, 4> pomiary = {1.5, 2.7, 3.1, 4.0};

    // Bezpieczny odczyt elementu
    std::cout << "Pierwszy element: " << pomiary[0] << "\n";
    std::cout << "Rozmiar tablicy:  " << pomiary.size() << "\n";
}
```

### 2. Tablica dynamiczna (`std::vector`)

Najbardziej uniwersalny i najczęściej stosowany kontener w C++. Implementuje strukturę tablicy o zmiennym rozmiarze.

- **Alokacja na stercie:** Sam obiekt wektora jest lekki, ale jego elementy fizycznie leżą w pamięci dynamicznej (_heap_).
    
- **Ciągły obszar pamięci:** Wszystkie elementy gwarantowanie leżą w RAM-ie jeden po drugim, co pozwala na błyskawiczne przeszukiwanie i pełną kompatybilność z niskopoziomowymi funkcjami.
    
- **Dynamiczny wzrost (Ważna uwaga):** Wektor rośnie automatycznie w miarę dodawania nowych elementów (`push_back`). Jeśli jednak zabraknie zarezerwowanego miejsca, wektor musi zaalokować nowy, większy blok pamięci, przepisać tam stare elementy, a stary blok zwolnić. Może to powodować chwilowe narzuty wydajnościowe.
    
```cpp
#include <iostream>
#include <vector>

int main() {
    // Dynamiczny wektor przechowujący liczby całkowite
    std::vector<int> liczby;

    liczby.push_back(10); // Rozmiar rośnie dynamicznie
    liczby.push_back(20);

    std::cout << "Rzeczywisty rozmiar: " << liczby.size() << "\n";
}
```

### 3. Dynamiczna tablica znaków (`std::string`)

Klasa obsługująca napisy tekstowe w C++ to w rzeczywistości wyspecjalizowany szablon klasy o nazwie `std::basic_string`, sparametryzowany typem `char`.

- **Struktura wektora:** Pod maską zachowuje się niemal identycznie jak `std::vector<char>`, alokując ciągły blok pamięci na stercie.
    
- **Automatyczne zarządzanie:** Samodzielnie dba o dodawanie znaku końca napisu `\0`, realokację pamięci przy łączeniu tekstów i udostępnia zaawansowane metody wyszukiwania podciągów.
    
```cpp
#include <iostream>
#include <string>

int main() {
    // Pod maską jest to std::basic_string<char>
    std::string tekst = "Witaj";
    tekst += " Swiecie"; // Automatyczna realokacja pamięci dynamicznej

    std::cout << tekst << " (Dlugosc: " << tekst.length() << ")\n";
}
```

## Szablony Funkcji: Algorytmy STL

Algorytmy w STL są całkowicie odseparowane od kontenerów. Mostem łączącym algorytmy z danymi są **iteratory** (obiekty zachowujące się jak inteligentne wskaźniki). Dzięki temu ten sam algorytm potrafi obsłużyć zarówno `std::array`, jak i `std::vector`.

### 1. Algorytm wyszukiwania (`std::find`)

Przeszukuje podany zakres liniowo (element po elemencie), poszukując wartości zgodnej ze wzorcem.

- **Elastyczność zakresu:** Nie musi przeszukiwać całego kontenera – za pomocą iteratorów definiujemy precyzyjnie punkt startowy oraz końcowy.
    
- **Uniwersalność:** Obsługuje dowolne typy danych, o ile posiadają one przeciążony operator porównania `==`.
    
- **Warianty:** Istnieją wersje specjalistyczne, takie jak `std::find_if`, które zamiast sztywnej wartości przyjmują funkcję lub lambdę filtrującą (predykat).
    
```cpp
#include <iostream>
#include <vector>
#include <algorithm> // Wymagane dla algorytmów!

int main() {
    std::vector<int> v = {10, 25, 50, 75};

    // Szukamy liczby 50 w całym zakresie kontenera
    auto wynik = std::find(v.begin(), v.end(), 50);

    if (wynik != v.end()) {
        std::cout << "Znaleziono element pod adresem iteratora.\n";
    }
}
```

### 2. Algorytm sortowania (`std::sort`)

Służy do szybkiego układania elementów w porządku rosnącym lub malejącym.

- **Wymagania sprzętowe:** Działa tylko na kontenerach oferujących swobodny dostęp do pamięci (posiadających tzw. _RandomAccessIterators_, czyli np. `std::array` oraz `std::vector`).
    
- **Domyślne kryterium:** Bez podania dodatkowych argumentów sortuje elementy rosnąco, wykorzystując wbudowany w dany typ danych operator mniejszości `<`.
    
- **Własne kryteria:** Przyjmuje opcjonalny trzeci argument – obiekt funkcyjny, funkcję lub lambdę, definiującą własne zasady porównywania (np. sortowanie od największej do najmniejszej).
    
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {50, 10, 75, 25};

    // Sortowanie domyślne (rosnąco, używa operatora <)
    std::sort(v.begin(), v.end()); 

    // Sortowanie z własnym komparatorem (malejąco)
    std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
}
```

### 3. Algorytm operacji seryjnych (`std::for_each`)

Uruchamia wskazaną funkcję, funktor lub lambdę dla każdego elementu z podanego zakresu danych.

- **Współpraca z pętlami:** W nowoczesnym standardzie C++ jest często stosowany zamiennie z zakresową pętlą `for (auto& element : kontener)`.
    
- **Tryby pracy:** Przekazując element do wnętrza funkcji przez zwykłą wartość, pracujemy w trybie tylko do odczytu. Przekazując go przez referencję (`&`), możemy seryjnie zmodyfikować zawartość całego kontenera.
    
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 2, 3, 4};

    // Wyświetlenie każdego elementu przy użyciu for_each i lambdy
    std::for_each(v.begin(), v.end(), [](int x) {
        std::cout << x << " ";
    });
}
```

## 1. Definiowanie szablonu funkcji i składnia

Szablon funkcji nie jest gotową funkcją, lecz **przepisem**, na podstawie którego kompilator sam wygeneruje odpowiedni kod, gdy zobaczy taką potrzebę. Do jego definiowania używa się słowa kluczowego `template`.

```cpp
// Notacja współczesna (zalecana):
template <typename T>
T min(T a, T b) {
    return (a < b) ? a : b;
}
```

- **`class` vs `typename`**: W starszych standardach C++ używano wyłącznie słowa `class` (np. `template <class T>`). Mogło to być mylące, ponieważ sugerowało, że szablon działa tylko na klasach/strukturach. Nowsza specyfikacja wprowadziła słowo kluczowe `typename`, aby jasno wskazać, że parametrem może być **dowolny typ** — zarówno klasa, jak i surowy typ wbudowany (`int`, `double`, `char`). Współcześnie oba te słowa w nagłówku szablonu działają identycznie.
    
- **Nazewnictwo**: Parametr szablonu (uogólniony typ) można nazwać dowolnie (np. `Typ`), jednak powszechnie przyjętą konwencją programistyczną jest stosowanie pojedynczej, wielkiej litery **`T`** (od _Type_).
    
- **Zasada zasięgu**: Szablon musi zostać zdefiniowany poza innymi funkcjami lub klasami — najczęściej w **zakresie globalnym** lub wewnątrz dedykowanej przestrzeni nazw (_namespace_). Wszystkie szablony z biblioteki standardowej C++ znajdują się w przestrzeni `std`.
## 2. Mechanizm kompilacji i oszczędność kodu

Należy zapamiętać kluczową zasadę: **szablony oszczędzają czas programiście, ale nie zmniejszają objętości kodu wynikowego (binarnego)**.

Sam zapis `template <typename T> void fun() {}` nie powoduje powstania w pamięci ani jednej linijki kodu maszynowego. Kompilator traktuje szablon jak czysty projekt.

Dopiero gdy w programie fizycznie wywołasz funkcję dla konkretnego typu (np. dla `int` oraz dla `double`), kompilator wykonuje tzw. **instancjowanie szablonu** (_template instantiation_). Kseruje on ciało szablonu i podmienia w nim abstrakcyjne `T` na rzeczywisty typ. W gotowym pliku wykonywalnym `.exe` wylądują dwie osobne, niezależne funkcje.

## 3. Wywoływanie funkcji szablonowej i dedukcja typów

#### A. Automatyczna dedukcja typów (niejawna)

Kompilator analizuje typy argumentów przekazanych do funkcji w nawiasach okrągłych i na tej podstawie sam domyśla się, czym jest `T`.
```cpp
int x = 5, y = 10;
auto wynik = min(x, y); // Kompilator widzi dwa inty -> produkuje funkcję min<int>(int, int)
```

> ⚠️ **Haczyk:** Przy automatycznej dedukcji typ zwracany przez funkcję nie ma żadnego znaczenia. Kompilator patrzy **wyłącznie na typy argumentów wejściowych**. Ponadto argumenty muszą pasować do szablonu idealnie — wywołanie `min(5, 4.5)` (czyli `int` oraz `double`) wygeneruje błąd kompilacji, ponieważ kompilator nie wie, czy pod jedno `T` podstawić `int`, czy `double`.
#### B. Jawne wywołanie (parametryzowanie)

Programista może twardo narzucić typ, wpisując go w nawiasach ostrokątnych `<>`. Rozwiązuje to problem różnych typów argumentów, ponieważ kompilator dokona wtedy klasycznej konwersji typów (rzutowania).

```cpp
auto wynik = min<double>(5, 4.5); // Jawne wymuszenie wersji double. Liczba 5 zostanie rzutowana na 5.0
```

## 4. Ograniczenia szablonów i semantyka kodu

Czy szablon napisany dla "dowolnego typu" zadziała dla absolutnie każdego typu w C++? **W ogólności: nie.**

Programista piszący szablon jest odpowiedzialny za logiczny sens jego wnętrza. Jeśli wewnątrz szablonu używasz operatora mniejszości (`a < b`), to ten szablon skompiluje się tylko dla tych typów, które **wiedzą, jak wykonać operację `<`**.

```cpp
class MojaKlasa { public: int wartosc; };

MojaKlasa obj1{5}, obj2{10};
// auto w = min(obj1, obj2); 
// BŁĄD KOMPILACJI! Klasa 'MojaKlasa' nie ma przeładowanego operatora '<'
```

Aby powyższy kod zadziałał, użytkownik musi najpierw jawnie zaimplementować operator `<` wewnątrz swojej klasy.

#### Inne ograniczenia:

- Jeśli wewnątrz szablonu odwołujesz się do konkretnego składnika (np. `a.wyswietl()`), drastycznie uszczuplasz uniwersalność szablonu — zadziała on wyłącznie dla klas posiadających metodę o dokładnie takiej nazwie.
    
- Jawne, sztywne wywoływanie operatorów wewnątrz struktur szablonowych może rodzić błędy interpretacyjne przy starciu z prymitywnymi typami wbudowanymi.

### 5. Unifikacja: Wsparcie dla typów wbudowanych

Aby pisanie szablonów miało głęboki sens, typy wbudowane (takie jak `int`, `double`, `float`) musiały zacząć zachowywać się w oczach kompilatora tak samo jak pełnoprawne klasy/struktury.

Gdyby tak nie było, programista musiałby pisać osobne szablony dla obiektów, a osobne dla prymitywnych zmiennych. Dlatego w C++ wprowadzono **pseudo-konstruktory i pseudo-destruktory dla typów wbudowanych**:

```cpp
// 1. Dopuszczenie wywołania konstrukcji w stylu obiektowym:
int obiekt1(10); // To samo co: int obiekt1 = 10;

// 2. Dopuszczenie jawnej inicjalizacji z jawnym typem:
int obiekt2 = int(5.7); // Bezpieczna konwersja (obcięcie do 5)

// 3. Dopuszczenie bezpośredniego, jawnego wywołania destruktora:
obiekt1.int::~int(); // Składniowo poprawne, choć dla inta nie robi nic fizycznie w pamięci
```

Dzięki temu, że kompilator toleruje te specyficzne, zorientowane obiektowo zapisy na zwykłych zmiennych (np. na `int`), uniwersalny kod szablonu typu:

```cpp
template <typename T>
void stworzIZniszcz() {
    T obiekt = T(); // Wywoła pseudo-konstruktor domyślny (dla int wyzeruje)
    obiekt.~T();    // Wywoła pseudo-destruktor
}
```

skompiluje się i wykona w pełni poprawnie zarówno dla skomplikowanej klasy biznesowej, jak i dla zwykłej liczby `int`.

### Szybkie podsumowanie do powtórki:

1. `typename` i `class` w nagłówku szablonu oznaczają dokładnie to samo.
    
2. Kompilator generuje fizyczny kod funkcji dopiero w momencie jej wywołania (instancjowanie).
    
3. Przy automatycznej dedykcji typów argumenty muszą pasować idealnie (brak automatycznych konwersji). Konwersję można wymusić jawnym zapisem `funkcja<TargetType>(a, b)`.
    
4. Szablon nie zadziała, jeśli typ danych nie obsługuje operacji wymaganych wewnątrz ciała tego szablonu (np. operatora `<`).
    
5. Typy wbudowane mają pseudo-konstruktory i pseudo-destruktory, aby mogły bezproblemowo współpracować z kodem generycznym.
## 1. Wiele parametrów szablonu (Szablony wieloargumentowe)

Szablon funkcji nie musi ograniczać się do jednego uniwersalnego typu `T`. Możesz zadeklarować **dowolną liczbę niezależnych parametrów typów**, oddzielając je przecinkami w nawiasach ostrokątnych `<>`.
### A. Łączenie różnych typów uniwersalnych

Stosujemy to wtedy, gdy parametry wejściowe funkcji mogą (ale nie muszą) różnić się od siebie typem danych.

```cpp
#include <iostream>

// Szablon przyjmuje dwa niezależne typy: T1 oraz T2
template <typename T1, typename T2>
void wyswietlParę(T1 a, T2 b) {
    std::cout << "A: " << a << ", B: " << b << "\n";
}

int main() {
    // Kompilator automatycznie dedukuje: T1 = int, T2 = const char*
    wyswietlParę(100, "Tekst"); 
    
    // Typy mogą być też identyczne: T1 = double, T2 = double
    wyswietlParę(5.5, 3.14); 
}
```

### B. Mieszanie typów szablonowych ze zwykłymi

Szablon funkcji może bez problemu przyjmować obok typów generycznych (`T1`, `T2`) także **klasyczne, sztywne typy danych** (`int`, `float`, `std::string`).

```cpp
// T1 i T2 są uniwersalne, ale 'liczbaPowtorzen' i 'skala' są zawsze takie same
template <typename T1, typename T2>
void procesujDane(T1 a, T2 b, int liczbaPowtorzen, float skala) {
    for(int i = 0; i < liczbaPowtorzen; ++i) {
        // Logika przetwarzania korzystająca ze skali
    }
}
```

## 2. Przeładowywanie szablonów i przypadki szczególne

W C++ możesz legalnie stworzyć **kilka szablonów o dokładnie tej samej nazwie**. Nazywa się to przeładowywaniem szablonów funkcji (_function template overloading_). Jeden szablon może być wtedy bardziej wyspecjalizowanym (węższym) przypadkiem drugiego.

### Analiza konfliktu: Scenariusz z funkcją `max`

Wyobraź sobie, że w tym samym pliku masz zdefiniowane dwa szablony:

```cpp
// Szablon 1: Wymaga, aby oba argumenty były DOKŁADNIE tego samego typu
template <typename Typ> 
Typ max(Typ a, Typ b) { 
    return (a < b) ? b : a; 
}

// Szablon 2: Pozwala, aby argumenty były zupełnie różnych typów
template <typename T1, typename T2> 
T1 max(T1 a, T2 b) { 
    return (a < b) ? b : a; 
}
```

Oba szablony mogą istnieć w programie niezależnie od siebie. Co się jednak stanie, gdy w kodzie wywołasz funkcję, podając dwa identyczne typy, np. `max(1, 2)`?

Dla wywołania `max(1, 2)` (gdzie oba argumenty to `int`):

- Szablon 1 pasuje idealnie (`Typ` = `int`).
    
- Szablon 2 również pasuje idealnie, ponieważ nie ma żadnych przeciwwskazań, aby typ `T1` był dokładnie tym samym typem co `T2` (`T1` = `int`, `T2` = `int`).

### Jak kompilator rozwiązuje ten konflikt? (Zasada Częściowego Uporządkowania)

Kompilator C++ nie zgłosi błędu wieloznaczności. Zastosuje sztywne reguły rozstrzygania mechanizmu nazywanego **Partial Ordering of Function Templates**.

> ⚖️ **Zasada dopasowania:** Kompilator zawsze wybiera szablon, który jest **bardziej wyspecjalizowany (bardziej szczegółowy)** dla danego wywołania.

- Szablon 1 nakłada twardszy warunek: argumenty _muszą_ być równe typem. Jest więc bardziej wyspecjalizowany.
    
- Szablon 2 jest ogólny: przyjmie cokolwiek.
    
Dlatego przy wywołaniu `max(1, 2)` kompilator bezbłędnie wybierze **Szablon 1** i wygeneruje kod bez zgłaszania błędów.

### Kiedy wygra Szablon 2?

Szablon 2 zostanie uruchomiony w ułamku sekundy, gdy podasz argumenty różnych typów, np. `max(5, 4.5)` (czyli `int` oraz `double`).

Dla takiego zapisu Szablon 1 natychmiast odpada (bo typy się różnią i automatyczna dedykcja zawodzi), więc Szablon 2 przejmuje wywołanie jako jedyny pasujący wzorzec.

## 1. Budowanie podstawowych typów pochodnych

Zgodnie z treścią slajdu, typ uogólniony `T` pozwala na tworzenie zmiennych lokalnych oraz operowanie na adresach. Świetnym przykładem jest wspomniana funkcja `swap(a, b)`, która zamienia wartości dwóch zmiennych:

```cpp
template <typename T>
void zamien(T& a, T& b) { // Używamy typu pochodnego: referencji T&
    T tymczasowy = a;     // Tworzymy zwykłą zmienną automatyczną typu T
    a = b;
    b = tymczasowy;
}
```

Wskaźniki (`T* a`) oraz tablice (`T a[10]`) zachowują się przewidywalnie. Jeśli podstawisz `T = int`, otrzymasz kolejno `int*` oraz `int a[10]`.

## 2. Kluczowe zagadnienie: Referencje `&` oraz `&&` w szablonach

W zwykłym kodzie `&` to referencja do istniejącego obiektu (lvalue), a `&&` to referencja do obiektu tymczasowego (rvalue). **W szablonach ta zasada zostaje wywrócona do góry nogami** ze względu na proces dedukcji typów przez kompilator.

Oto trzy fundamentalne przypadki, które musisz znać na egzamin:

### `T&` — Klasyczna referencja lvalue

Jeśli w szablonie funkcji zapiszesz pojedynczy ampersand, zmuszasz kompilator do akceptowania **wyłącznie stałych lub zmiennych obiektów, które mają swoje stałe miejsce w pamięci** (lewostronne wartości — _lvalues_).

```cpp
template <typename T>
void f_lvalue(T& arg) {}

int main() {
    int x = 10;
    f_lvalue(x);  // OK: 'x' to zmienna w pamięci
    // f_lvalue(5); // BŁĄD KRYTYCZNY! Liczba 5 to wartość tymczasowa, nie przypiszesz jej do T&
}
```

### Przypadek B: `T&&` przy dedykcji — Referencja Uniwersalna (_Forwarding Reference_)

To najważniejszy mechanizm nowoczesnego C++. Jeżeli zapiszesz `T&&` bezpośrednio przy parametrze, który kompilator **musi sam wydedukować**, to symbol `&&` przestaje oznaczać referencję rvalue. Staje się **referencją uniwersalną**.

Referencja uniwersalna ma niesamowitą właściwość: **potrafi idealnie dopasować się zarówno do zwykłych zmiennych, jak i do wartości tymczasowych**.

```cpp
template <typename T>
void f_uniwersalna(T&& arg) {} // T&& działa jako referencja uniwersalna

int main() {
    int x = 10;
    f_uniwersalna(x); // OK! Kompilator dopasuje się do zwykłej zmiennej
    f_uniwersalna(5); // OK! Kompilator dopasuje się do wartości tymczasowej
}
```

#### Jak to możliwe? Mechanizm Zwijania Referencji (_Reference Collapsing_)

Gdy przekazujesz obiekt do referencji uniwersalnej, kompilator nakłada na siebie dwie referencje (tą od obiektu i tą z zapisu `T&&`) i zwija je według sztywnych reguł matematycznych:

> - `&` (referencja lvalue) + `&&` $\rightarrow$ **`&`** (wygrywa lvalue)
>     
> - `&&` (referencja rvalue) + `&&` $\rightarrow$ **`&&`**
>     

Jeśli przekażesz zmienną `x` (która jest typu `int&`), kompilator podstawi to pod szablon: `int& &&`, co zwinie się do zwykłego `int&`. Jeśli przekażesz `5` (czyli czysty `int`), szablon przyjmie postać `int&&`.

### Przypadek C: `T&&` BEZ dedukcji — Czysta referencja rvalue

Musisz bardzo uważać na sytuację, w której `&&` pojawia się w klasie szablonowej. Jeśli typ `T` został ustalony już na etapie tworzenia obiektu klasy, to metoda wewnątrz tej klasy przyjmująca `T&&` **nie jest** referencją uniwersalną! Jest zwykłą referencją rvalue i przyjmie tylko wartości tymczasowe.

```cpp
template <typename T>
class Kontener {
public:
    // T jest już znane (ustalone przez klasę). 
    // Ta funkcja NIE dedukuje typu, więc akceptuje TYLKO wartości tymczasowe!
    void dodaj(T&& wartosc) {} 
};

int main() {
    Kontener<int> k; // T zostaje sztywno ustawione na 'int'
    int x = 10;
    
    // k.dodaj(x); // BŁĄD! 'x' jest zwykłą zmienną (lvalue), a funkcja oczekuje rvalue
    k.dodaj(5);   // OK! Liczba 5 to wartość tymczasowa (rvalue)
}
```

## 3. Po co to robimy? (Doskonałe przekazywanie — _Perfect Forwarding_)

Połączenie referencji uniwersalnej `T&&` z dedykcją typów stosuje się w jednym, konkretnym celu inżynieryjnym: aby zrealizować **doskonałe przekazywanie** za pomocą funkcji `std::forward<T>()`.

Dzięki temu pisząc jedną funkcję szablonową, możemy przekazać jej argumenty dalej do innych podsystemów w niezmienionej formie — jeśli obiekt był tymczasowy, zostanie przeniesiony (_move semantics_), a jeśli był zwykłą zmienną, zostanie bezpiecznie skopiowany lub obsłużony przez referencję.

## Przydomki `inline`, `static` oraz `extern` w szablonach

Wprowadzając modyfikatory sterujące wydajnością lub widocznością funkcji (`inline`, `static`, `extern`), należy pamiętać o żelaznej regule składniowej: **przydomek modyfikuje wygenerowaną funkcję, a nie sam szablon**.

### Reguła zapisu:

Modyfikator musi znaleźć się **po** nagłówku `template <...>`, a bezpośrednio **przed** typem zwracanym funkcji.

```cpp
// 🟢 POPRAWNIE: Modyfikujemy funkcję wyprodukowaną z szablonu
template <typename T> 
inline T max(T a, T b) { 
    return (a < b) ? b : a; 
}

// ❌ BŁĄD KOMPILACJI: Próba zadeklarowania "szablonu inline"
inline template <typename T> 
T max(T a, T b); 
```

Identyczna zasada dotyczy słów kluczowych `static` oraz `extern`.

### Odpowiedź na pytanie ze slajdu: Co znaczy, że funkcja jest `static`?

W kontekście globalnym (poza klasami), oznaczenie zwykłej funkcji jako `static` nadaje jej **wewnętrzną widoczność (internal linkage)**. Oznacza to, że funkcja ta jest widoczna i może być używana **tylko i wyłącznie w obrębie jednego pliku źródłowego** (jednostki translacji), w którym została zdefiniowana. Inne pliki projektu nie będą miały do niej dostępu, co zapobiega konfliktom nazw w dużych projektach.

## Funkcje „specjalizowane” (Problem wskaźników tekstowych)

Szablony są genialne, dopóki domyślna logika kodu (np. operator `<`) ma sens dla każdego typu danych. Istnieją jednak sytuacje, w których ślepe wygenerowanie funkcji z szablonu doprowadzi do katastrofy logicznej.

### Klasyczny problem: `max(char*, char*)`

Jeśli użyjesz ogólnego szablonu `max` dla dwóch tradycyjnych napisów w stylu języka C:

```cpp
max("tekst_A", "tekst_B");
```

Kompilator podstawi pod `T` typ `const char*` (wskaźnik na znak). W ciele szablonu wykona się instrukcja:

```cpp
return (a < b) ? b : a;
```

Ponieważ argumentami są wskaźniki, komputer **nie porówna zawartości tekstów alfabetycznie**, lecz porówna **adresy w pamięci RAM**, pod którymi te teksty zostały zapisane! Wynik takiej operacji jest całkowicie losowy i zależy od kaprysu kompilatora.

### Rozwiązanie: Przeładowanie jawne (Specjalizacja)

Aby uratować program, musimy zdefiniować normalną, tradycyjną funkcję o tej samej nazwie, ale dedykowaną specjalnie dla tego jednego problematycznego typu danych. Wykorzystuje ona funkcję `strcmp` do prawidłowego porównywania znaków:

```cpp
#include <iostream>
#include <cstring>

// 1. Ogólny szablon
template <typename T>
T podaj_max(T a, T b) {
    return (a < b) ? b : a;
}

// 2. Normalna funkcja dedykowana dla specyficznego przypadku (Overload)
const char* podaj_max(const char* a, const char* b) {
    // strcmp zwraca wartość > 0, jeśli napis 'a' jest alfabetycznie większy
    return (std::strcmp(a, b) < 0) ? b : a; 
}
```

> ⚠️ **Twardy warunek dopasowania:** Kompilator traktuje typy bardzo rygorystycznie. Jeśli Twoja dedykowana funkcja przyjmuje `char*`, a Ty przekażesz do programu napis stały `const char*`, kompilator uzna, że typy się nie zgadzają i zamiast Twojej bezpiecznej funkcji, z powrotem wybierze ogólny, niebezpieczny szablon. Dopasowanie musi być idealne.

## Algorytm dopasowywania argumentów (Overload Resolution)

Gdy w kodzie wywołujesz funkcję, a kompilator ma do dyspozycji zarówno zwykłe funkcje, jak i szablony o tej samej nazwie, uruchamia wewnętrzny, trzystopniowy proces decyzyjny. Szuka funkcji od najbardziej dopasowanej do najbardziej ogólnej.

### 1. Krok pierwszy: Dopasowanie dokładne (_Exact Match_)

Kompilator w pierwszej kolejności szuka **zwykłej (nieszablonowej) funkcji**, której parametry idealnie, bez żadnych przekształceń odpowiadają typom przekazanym w wywołaniu.

- Jeśli wywołasz `max(5, 10)` (dwa `inty`), a w programie istnieje zwykła funkcja `int max(int, int)`, zostanie ona natychmiast uruchomiona. Szablony są ignorowane.
    
### 2. Krok drugi: Instancjowanie szablonu (_Template Match_)

Jeśli zwykła funkcja nie istnieje, kompilator szuka **szablonu**, z którego da się wyprodukować funkcję pasującą idealnie do wywołania.

- **Twarde ograniczenie:** Na tym etapie kompilator **nie wykonuje żadnych konwersji standardowych**. Jeśli wywołasz `max(5, 4.5)` (czyli `int` oraz `double`), kompilator odrzuci szablon `template<typename T> T max(T, T)`, ponieważ nie potrafi dopasować jednego `T` do dwóch różnych typów bez przeprowadzenia rzutowania.

### 3. Krok trzeci: Konwersje i rzutowania (_Fallback_)

Jeśli powyższe kroki zawiodą, kompilator całkowicie porzuca szablony. Wraca do analizowania zwykłych funkcji i próbuje zastosować **konwersje standardowe** (np. promocja `float` do `double`, rzutowanie `int` na `float`) lub konwersje zdefiniowane przez programistę w klasach, aby dopasować argumenty siłowo.

- Dopiero tutaj wywołanie `max(5, 4.5)` ma szansę zadziałać, jeśli w kodzie znajduje się tradycyjna funkcja `double max(double, double)` — `int 5` zostanie wtedy awaryjnie przekształcony na `double 5.0`.


# __PRETTY_FUNCTION__

**`__PRETTY_FUNCTION__`** to potężne, wbudowane narzędzie kompilatora (konkretnie rozszerzenie wspierane przez **GCC** oraz **Clang**), które służy do zaawansowanego debugowania i logowania kodu.

Gdy kompilator widzi ten identyfikator, automatycznie podstawia w jego miejsce tekst zawierający **pełną, szczegółową sygnaturę funkcji**, w której się aktualnie znajduje.

### Różnica między `__func__`, `__FUNCTION__` a `__PRETTY_FUNCTION__`

W języku C++ masz do dyspozycji kilka podobnych makr/identyfikatorów, ale różnią się one drastycznie ilością zwracanych informacji:

- **`__func__`** (Standard C++11): Zwraca tylko i wyłącznie **samą, surową nazwę** funkcji.
    
- **`__FUNCTION__`** (Starsze rozszerzenie): W większości kompilatorów działa identycznie jak `__func__`.
    
- **`__PRETTY_FUNCTION__`** (Rozszerzenie GCC/Clang): Zwraca typ zwracany, przestrzeń nazw, nazwę klasy, stałość (`const`), a co najważniejsze — **dokładnie podstawione parametry szablonów**.
    

> 💻 **Odpowiednik w świecie Windows (MSVC):** Jeśli pracujesz w środowisku Visual Studio, kompilator Microsoftu nie posiada `__PRETTY_FUNCTION__`. Jego bezpośrednim, identycznie działającym odpowiednikiem jest **`__FUNCSIG__`**.

### Praktyczny przykład: Klasa i Szablon

Zobaczmy, jak zachowuje się ten mechanizm w starciu ze strukturą klasową oraz kodem generycznym (szablonami), które omawialiśmy wcześniej.

```cpp
#include <iostream>
#include <string>

// 1. Uniwersalny szablon funkcji
template <typename T>
void debugujObiekt(T parametr) {
    std::cout << "--- Wywolanie szablonu ---\n";
    std::cout << "Zwykle __func__:    " << __func__ << "\n";
    std::cout << "Potezne __PRETTY__: " << __PRETTY_FUNCTION__ << "\n\n";
}

// 2. Klasa z metoda const
namespace Logistyka {
    class Silnik {
    public:
        void uruchom(int moc, double cisnienie) const {
            std::cout << "--- Wywolanie w klasie ---\n";
            std::cout << __PRETTY_FUNCTION__ << "\n\n";
        }
    };
}

int main() {
    // Test 1: Wywołujemy szablon dla inta oraz dla std::string
    debugujObiekt(5);
    debugujObiekt(std::string("Test"));

    // Test 2: Wywołujemy metodę wewnątrz przestrzeni nazw i klasy
    Logistyka::Silnik s;
    s.uruchom(150, 2.5);

    return 0;
}
```

### Wynik w konsoli (pod kompilatorem GCC / g++):

```
--- Wywolanie szablonu ---
Zwykle __func__:    debugujObiekt
Potezne __PRETTY__: void debugujObiekt(T) [with T = int]

--- Wywolanie szablonu ---
Zwykle __func__:    debugujObiekt
Potezne __PRETTY__: void debugujObiekt(T) [with T = std::string]

--- Wywolanie w klasie ---
void Logistyka::Silnik::uruchom(int, double) const
```

### Dlaczego to jest absolutny hit podczas debugowania?

1. **Widzisz sekcję `[with T = ...]`.** Pisząc uniwersalny kod szablonowy, często w głębi logiki tracisz kontrolę nad tym, jaki typ danych kompilator faktycznie tam wydedukował (szczególnie przy referencjach uniwersalnych `&&`). `__PRETTY_FUNCTION__` pokaże Ci czarno na białym, jaki typ tam siedzi.
    
2. **Widzisz pełny kontekst.** Informacja, że błąd nastąpił w funkcji `uruchom`, niewiele daje, jeśli masz 10 różnych klas z metodą `uruchom`. Zyskujesz pełną ścieżkę: `void Logistyka::Silnik::uruchom(int, double) const`.
    

### ⚠️ Ważna uwaga techniczna (Pułapka łączenia tekstów)

Tradycyjne makra przedprocesora, takie jak `__LINE__` (numer linijki) czy `__FILE__` (nazwa pliku), są surowymi tekstami. Możesz je łączyć z innymi napisami automatycznie:

```cpp
std::cout << "Blad w pliku: " __FILE__ ; // OK
```

`__PRETTY_FUNCTION__` (oraz `__func__`) **nie są makrami przedprocesora**. Pod maską kompilator traktuje je jak ukrytą, automatyczną zmienną lokalną zainicjalizowaną na starcie funkcji:

```cpp
static const char __PRETTY_FUNCTION__[] = "void nazwa_funkcji()...";
```

Dlatego **nie możesz** połączyć jej z innym tekstem bez użycia operatora `<<` lub obiektów typu `std::string`. Zapis `"Funkcja: " __PRETTY_FUNCTION__` wygeneruje błąd kompilacji.




# Zadanie4
## Kod
```cpp
#include <iostream>
#include <vector>
// Program ma wytworzyć poniższy output.
//  __PRETTY_FUNCTION__ zawiera pełną nazwę funkcji w danym miejscu
// Po odkomentowaniu zakomentowanych linii w main program ma się nie kompilować.
// Kod można pisać tylko w wyznaczonych miejscach.
/*
    MIEJSCE NA KOD
*/
class Base{
    public:
    virtual std::ostream& print(std::ostream& s) const = 0;
};

class Derived1 : public Base{
    public:
    Derived1() = default;
    Derived1(const Derived1&) = delete;

    std::ostream& print(std::ostream& s) const{
        s << __PRETTY_FUNCTION__;
        return s;
    }
};

class Derived2 : public Base{
    public:
    Derived2() = default;
    std::ostream& print(std::ostream& s) const override{
        s << __PRETTY_FUNCTION__;
        return s;
    }
};

class Derived3 : public Derived2{
    public:
    std::ostream& print(std::ostream& s) const override{
        s << __PRETTY_FUNCTION__;
        return s;
    }
};

std::ostream& operator<<(std::ostream& s, const Base& obj){
    return obj.print(s);;
}

std::ostream& operator<<(std::ostream& s, std::vector<Base*>& vec){
    s << "[\n";
    // for(Base* c : vec){
    //     s << *c;
    // }
    for (size_t i=0; i<vec.size(); ++i){
        s << *vec[i];
        if(i < vec.size()-1){
            s << ",\n";
        } else {
            s << "\n";
        }
    }
    s << "]";
    return s;
}

int main(){
    Derived1 d1;
    Derived3 d3;
    Derived2 d2 = d3;
    // Derived1 d1_make_err = d2;
  
    // std::vector<Base> v_make_err = {d1, d2, d3};
    std::vector<Base*> v = {&d1, &d2, &d3};

    std::cout << *v.front()<<std::endl;
    std::cout << v;
}

/*Wynik:
virtual std::ostream& Derived1::print(std::ostream&) const
[
virtual std::ostream& Derived1::print(std::ostream&) const,
virtual std::ostream& Derived2::print(std::ostream&) const,
virtual std::ostream& Derived3::print(std::ostream&) const
]
*/
```
## 1. Architektura Klas i Polimorfizm

### Klasa Abstrakcyjna i Interfejs (`Base`)

Klasa `Base` pełni rolę czystego interfejsu. Poprzez zapis `virtual ... = 0;` stworzyliśmy **czystą funkcję wirtualną**.

- **Jak to zadziałało:** Kompilator uniemożliwił stworzenie surowego obiektu typu `Base`. Dzięki temu próba odkomentowania linii `std::vector<Base> v_make_err` natychmiast wyrzuciłaby błąd, chroniąc program przed niepoprawnym zachowaniem.
    

### Dziedziczenie Kaskadowe (Wielopoziomowe)

Stworzyliśmy strukturę, w której `Derived1` oraz `Derived2` dziedziczą po `Base`, a `Derived3` dziedziczą po `Derived2`.

- **Jak to zadziałało:** Wszystkie klasy pochodne zostały zmuszone do nadpisania metody `print`. Słowo kluczowe `override` zapewniło nas, że kompilator pilnował zgodności sygnatur metod (np. obecności `const`).
    

## 2. Pamięć i Cykl Życia Obiektu

### Obcinanie Obiektów (_Object Slicing_)

To najbardziej podstępny mechanizm w zadaniu, zaimplementowany w linii `Derived2 d2 = d3;`.

- **Jak to zadziałało:** Ponieważ przypisaliśmy obiekt `d3` (typ `Derived3`) do zwykłej zmiennej `d2` (typ `Derived2`) bez użycia wskaźnika czy referencji, kompilator dokonał "obcięcia". Skopiował tylko tę część obiektu `d3`, która należała do klasy `Derived2`, a resztę odrzucił.
    
- **Efekt w outputcie:** Obiekt `d2` stracił swoją tożsamość jako `Derived3` i polimorficznie meldował się jako `Derived2::print`. Z kolei wektor wskaźników `std::vector<Base*> v` zachował pełną strukturę obiektów w pamięci RAM.
    

### Jawne usuwanie konstruktorów (`= delete`)

W klasie `Derived1` zablokowaliśmy konstruktor kopiujący poprzez `Derived1(const Derived1&) = delete;`.

- **Jak to zadziałało:** Gdyby ktokolwiek w programie spróbował skopiować obiekt typu `Derived1` przez wartość, kompilacja zostałaby natychmiast przerwana.
    

## 3. Strumienie i Metaprogramowanie

### Przeciążanie operatorów `<<` (Dwa poziomy)

Napisaliśmy dwa zupełnie różne operatory globalne, które idealnie ze sobą współpracowały:

- **Operator dla obiektu (`const Base&`):** Przyjmował referencję do bazy i polimorficznie wywoływał metodę `print`.
    
- **Operator dla kontenera (`std::vector<Base*>&`):** Przyjmował cały wektor wskaźników. Przechodził po nim pętlą, wyłuskiwał wskaźnik (`*vec[i]`) i przekazywał obiekt do tego pierwszego operatora.
    

### Inteligentne formatowanie pętli

W operatorze wektora porzuciliśmy pętlę typu _for-each_ na rzecz klasycznej pętli z indeksem `for (size_t i = 0; i < vec.size(); ++i)`.

- **Jak to zadziałało:** Zastosowaliśmy warunek `if (i < vec.size() - 1)`. Dzięki temu program precyzyjnie wiedział, kiedy dopisać do strumienia przecinek z nową linią (`, \n`), a kiedy postawić samą nową linię (`\n`) dla ostatniego elementu, idealnie odwzorowując makietę wyjściową.
    

### Zwracanie Strumienia przez Referencję (`return s;`)

Zarówno metody `print`, jak i oba operatory `<<` konsekwentnie przyjmowały i zwracały `std::ostream&`.

- **Jak to zadziałało:** Umożliwiło to tzw. **potokowe (łańcuchowe) wywoływanie strumieni** (ang. _stream chaining_), dzięki czemu zapis `std::cout << a << b << c;` jest w ogóle technicznie możliwy w C++.
    

### Dynamiczny podpis kompilatora (`__PRETTY_FUNCTION__`)

Zamiast wpisywać na sztywno teksty w stylu `"Derived1::print"`, użyliśmy rozszerzenia kompilatora.

- **Jak to zadziałało:** Kompilator w fazie budowania programu sam wygenerował pełną, unikalną tekstową sygnaturę metody dla każdej klasy z osobna, co pozwoliło nam gołym okiem zaobserwować, kiedy zadziałał polimorfizm dynamiczny, a kiedy statyczne obcięcie obiektu.