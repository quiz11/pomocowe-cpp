#include <iostream>
#include <stdexcept>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

template <typename T = int>
struct box {
    using value_type = T;
    T value;

    // Konstruktor
    box(T val = T{}) : value(val) {}

    // Przeładowanie operatora <<, żeby std::cout umiał wypisać box
    friend std::ostream& operator<<(std::ostream& os, const box& b) {
        return os << b.value;
    }
};

// 2. Szablon inteligentnej tablicy (ręczne zarządzanie pamięcią)
template <typename T>
class array {
private:
    // Struktura pomocnicza "Slot" pozwala ominąć brak <initializer_list>.
    // Przechwytuje ona pojedyncze argumenty przekazane w klamrach {}.
    struct Slot {
        T value;
        bool valid;

        // Pusty slot (dla argumentów, których nie podano)
        Slot() : valid(false), value{} {}

        // Slot z wartością (używamy szablonu U, aby int np. 5 automatycznie stał się boxem)
        template <typename U>
        Slot(const U& val) : value(val), valid(true) {}
    };

    T* _data;   // Wskaźnik na surową pamięć
    int _size;  // Rozmiar tablicy

public:
    using value_type = T;

    // Konstruktor przyjmujący wartości z {}. 
    // Dodajemy kilka slotów, żeby obsłużyć {5, 6, 7} i ewentualnie więcej.
    array(Slot s1 = {}, Slot s2 = {}, Slot s3 = {}, Slot s4 = {}, Slot s5 = {}) {
        Slot slots[] = {s1, s2, s3, s4, s5};
        
        // 1. Zliczamy ile argumentów faktycznie przekazano
        _size = 0;
        for (int i = 0; i < 5; ++i) {
            if (slots[i].valid) _size++;
        }

        // 2. Alokujemy pamięć
        if (_size > 0) {
            _data = new T[_size];
            int idx = 0;
            for (int i = 0; i < 5; ++i) {
                if (slots[i].valid) {
                    _data[idx++] = slots[i].value;
                }
            }
        } else {
            _data = nullptr;
        }
    }

    // Konstruktor kopiujący (NIEZBĘDNY, gdy zadeklarowano: const array<box<>> b = a;)
    array(const array& other) : _size(other._size) {
        if (_size > 0) {
            _data = new T[_size];
            for (int i = 0; i < _size; ++i) {
                _data[i] = other._data[i];
            }
        } else {
            _data = nullptr;
        }
    }

    // Destruktor (zapobiega wyciekom pamięci)
    ~array() {
        delete[] _data;
    }

    // Zwraca rozmiar tablicy
    int size() const {
        return _size;
    }

    // Operator [] z obsługą ujemnych indeksów (Python-style) dla elementów modyfikowalnych
    T& operator[](int index) {
        if (index < 0) {
            index += _size; // Zamienia np. -1 na indeks ostatniego elementu
        }
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Indeks poza zakresem!"); // Używamy stdexcept
        }
        return _data[index];
    }

    // Operator [] dla obiektów const (np. przy wypisywaniu tablicy b)
    const T& operator[](int index) const {
        if (index < 0) {
            index += _size;
        }
        if (index < 0 || index >= _size) {
            throw std::out_of_range("Indeks poza zakresem!");
        }
        return _data[index];
    }
};

// 3. Globalna funkcja wypisująca
template <typename T>
void print(const array<T>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

int main()
{
    array<box<>> a = {5, 6, 7}; // Inicjalizacja tablicy z wartościami
    const array<box<>> b = a;   // Kopiowanie tablicy

    a[-1] = array<box<>>::value_type{2}; // Ustawienie wartości w ostatnim elemencie
    a[-a.size()] = box<>::value_type{3}; // Ustawienie wartości w pierwszym elemencie

    print(a); // Wydrukowanie tablicy a
    print(b); // Wydrukowanie tablicy b
}

// 3 6 2
// 5 6 7