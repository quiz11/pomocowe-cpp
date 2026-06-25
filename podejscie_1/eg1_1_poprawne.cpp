// Nie można używać std::vector, std::array, std::deque itp. kontenerów z STL
/* UZUPEŁNIJ 1 */
#include <iostream>

template <typename T>
struct array{
    static constexpr int size = 3; // static aby obsluzyc ::size 

    using value_type = T;

    T data[size];   // Zwykła tablica w stylu C. Ponieważ struct nie ma konstruktora, zadziała agregat dla {5, 6, 7} utomatycznie obsluzy wywolania dla kolejnych wartosci bez potrzeby pisania konstruktorow i zarzadzania new i delete

    T& operator[](int i){   // zwraca referencje aby moc nadpisac wartosc np. a[0] = 3;
        return data[i];
    }

    const T& operator[](int i) const { // zwraca stala referencje aby czytac z const array<int> b
        return data[i];                // const przed T& blokuje wywolanie b[0] = 4 bo jest tylko do odczytu
    }

};

template <typename T, int N = array<T>::size>
void print_to_cout( const array<T>& a_v )
{
    for (auto idx = 0; idx < N; ++idx)
    {
        std::cout << "[" << idx << "]: " << a_v[idx] << ", ";
    }
    std::cout << std::endl;
}

int main()
{
    array<int> a {5, 6, 7};
    const array<int> b = a;

    a[array<int>::size - 1] = array<int>::value_type{2};
    a[0] = 3;

    std::cout << "a: "; print_to_cout(a);
    std::cout << "b: "; print_to_cout(b);
}

/* Oczekiwany output:
a: [0] 3, [1] 6, [2] 2
b: [0] 5, [1] 6, [2] 7
*/