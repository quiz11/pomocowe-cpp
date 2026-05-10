#include <iostream>
#include <stdexcept>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

template <typename T = int>
class box {
private:
    T val;

public:
    using value_type = T;

    box() = default;

    box(const T &value) : val{value} {}

    T &value() {
        return val;
    }
};

template<typename T, size_t N = 3>
class array {
private:
    T collection[N];

public:
    using value_type = T;

    array(std::initializer_list<T> list) {
        size_t i = 0;
        for (const T &elem : list) {
            collection[i] = elem;
            i++;
        }
    }

    array(const array &other) {
        for (size_t i = 0; i < N; i++) {
            collection[i] = other.collection[i];
        }
    }

    size_t size() {
        return N;
    }

    T &operator[](const int &idx) {
        if (idx >= 0 && idx < N) {
            return collection[idx];
        }
        else if (idx < 0 && idx >= -N) {
            return collection[N + idx];
        }
        else {
            throw std::runtime_error{"Out of bounds"};
        }
    }

    T operator[](const int &idx) const {
        if (idx >= 0 && idx < N) {
            return collection[idx];
        }
        else if (idx < 0 && idx >= -N) {
            return collection[N + idx];
        }
        else {
            throw std::runtime_error{"Out of bounds"};
        }
    }
};

template <typename T, size_t N>
void print(const array<T, N> & to_print) {
    for (size_t i = 0; i < N; i++) {
        std::cout << to_print[i].value() << " ";
    }

    std::cout << '\n';
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