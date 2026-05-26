#include <iostream>

// Dopisując kod tylko we wskazanych miejsach, spraw aby program
// wypisał podany poniżej output

class X { 
public:
    X() : private_(1) {}

    template<class T>
    void f( const T& t ) { /*...*/ }

    int value() { return private_; }

private: 
    int private_; 
};

/*
    MIEJSCE NA KOD
*/

int main() {
    X x;
    std::cout << x.value() << '\n';

    /*
        MIEJSCE NA KOD
    */

    std::cout << x.value() << std::endl;
}

// 1
// 2