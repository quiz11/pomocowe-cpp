// Nie można używać std::vector, std::array, std::deque itp. kontenerów z STL
/* UZUPEŁNIJ 1 */
#include <iostream>
#include <initializer_list>

int N;

template<typename T> // w celu obslugi szablonu <int>
struct array{
    T* data;
    inline static int size;

    using value_type = T;

    array(std::initializer_list<T> init){   // konstruktor z listą inicjalizacyjną bo {5, 6, 7}
        size = init.size();
        N = size;
        data = new T[size];
        int i = 0;
        for (const auto& val : init){
            if (i < size){
                data[i] = val;
                i++;
            }
        }
    }

    ~array() { // destruktor RuleOf3 (1/3)
        delete[] data;
    }

    array(const array& other) { // konstruktor kopiujacy głęboko aby zachować osobne wersje array (2/3)
        data = new T[size]; // alokuje nowa pamiec dla kopii
        for (int i=0; i<size; ++i){
            data[i] = other.data[i]; // kopiujemy wartosc a nie wskaznik
        }
    }

    array& operator=(const array& other){ // operator przypisania kopiujacego np. a=b (3/3)
        if (this != &other){ // guard przed przypisaniem do samego siebie
            for(int i=0; i<size; ++i){
                data[i] = other.data[i];
            }
        }
        return *this;
    }; 

    T& operator[](int i){ // operator dostepy [] dla a[i] = val;
        return data[i];
    }

    const T& operator[](int i) const{ // staly operator [] aby obsluzyc wywolanie a[i] = val;
         return data[i];
    }

};

// int N = array<int>::size;
/**/
void print_to_cout(/**/const array<int>& /**/ a_v )
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