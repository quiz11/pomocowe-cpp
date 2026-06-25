#include <iostream>

// Napisz program który obliczy n-ty wyraz silnii w czasie kompilacji/
// Wypisz wynik na ekran.
// Kod można pisać tylko w wyznaczonych miejscach

// Szablon główny: N! to N * (N-1)!
template <int N>
struct Factorial {
    enum { value = N * Factorial<N - 1>::value }; 
    // lub w nowszym C++: static const int value = N * Factorial<N - 1>::value;
};

// Specjalizacja (warunek stopu): 0! to 1
template <>
struct Factorial<0> {
    enum { value = 1 };
};

int main() {
    std::cout << Factorial<5>::value << std::endl;
}