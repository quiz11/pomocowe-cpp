// Nie można używać std::vector, std::array, std::deque itp. kontenerów z STL ZA WYJĄTKIEM STD::PAIR
/* UZUPEŁNIJ 1 */
#include <iostream>

template <typename T1, typename T2> // szablon dla dwóch niezależnych typów
using my_pair = std::pair<T1, T2>; // wnetrze pary użyjemy z biblioteki

template <typename T>
struct ptr{
    T* _ptr;

    using value_type = T; // alias typu dla ::value_type

    ptr() : _ptr(nullptr){}; // kontruktor domyślny dla Test_t t3;

    explicit ptr(T* p) : _ptr(p) {}; // konstruktor blokujacy niejawne konwersje, zapobiega Test_t t4 = new

    ~ptr(){ // destruktor zwalniający wskaznik
        delete _ptr;
    }

    ptr(const ptr& p) = delete; // blokuje kopiowanie
    ptr& operator=(const ptr& p) = delete; // blokowanie kopiowania przez =

    T& operator*(){ // przeciazenie operatora wyłuskania *t1
        return *_ptr;
    }

    T* operator->(){ // przeciążenie operatora dostępu do składowej t1->
        return _ptr;
    }
};



int main()
{
    using Float_t = double;
    using Test_t = ptr<my_pair<Float_t, Float_t>>;

    Test_t t1{new Test_t::value_type{}};
    // Test_t t2 = t1;                            // BLAD KOMPILACJI
    // Test_t t3; t3 = t1;                        // BLAD KOMPILACJI
    // Test_t t4 = new Test_t::value_type();      // BLAD KOMPILACJI

    std::cout << (*t1).first << ", " << t1->second << "\n";

    (*t1).first = Test_t::value_type::first_type{1};
    t1->second = Test_t::value_type::second_type{3.141};

    std::cout << (*t1).first << ", " << t1->second << "\n";

}
/* output:
0, 0
1, 3.141
*/