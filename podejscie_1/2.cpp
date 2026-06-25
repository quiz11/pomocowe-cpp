#include <iostream>

// Program ma wytworzyć poniższy output.
//  __PRETTY_FUNCTION__ zawiera pełną nazwę funkcji w danym miejscu
// Po odkomentowaniu zakomentowanych linii w main program ma się nie kompilować.
// Kod można pisać tylko w wyznaczonych miejscach.

/* 
    MIEJSCE NA KOD 
*/
#include <utility>

using namespace std;

class A{
    private:
        int _a;
        int _b;

    public:
        A(int a, int b) : _a(a), _b(b) {
            cout << __PRETTY_FUNCTION__ << ": _a=" << _a << ",_b=" << _b << "\n";
        };

        explicit A(int a) : A(a,0){
            cout << __PRETTY_FUNCTION__ << ": _a=" << _a << ",_b=" << _b << "\n";
        }; // blokuje f

        A() : A(0,0){
            cout << __PRETTY_FUNCTION__ << ": _a=" << _a << ",_b=" << _b << "\n";

        };

        A(const A&) = delete; // blokuje kopiujacy

        A(A&& zrodlo){
            this->_a = zrodlo._a;
            this->_b = zrodlo._b;

            cout << __PRETTY_FUNCTION__ << ": _a=" << _a << ",_b=" << _b << "\n";
        };

};

int main()
{
    cout << "a->"; A a;
    cout << "b->"; A b(1);
    cout << "c->"; A c(1,2);

    cout << "d->"; A d = std::move(c);

    // A e = c;
    // A f = 1;
}

/*
a-> A::A(int,int): _a=0,_b=0
A::A(): _a=0,_b=0
b-> A::A(int,int): _a=1,_b=0
A::A(int): _a=1,_b=0
c-> A::A(int,int): _a=1,_b=2
d-> A::[...]: _a=1,_b=2
*/