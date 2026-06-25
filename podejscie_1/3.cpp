// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

/* 
    MIEJSCE NA KOD 
*/
#include <iostream>
#include <string>

class is_printable{
    public:
    virtual std::ostream& printable(std::ostream& s) const = 0;

};

class A : public is_printable{
    public:
    std::string napis;

    A(std::string s) : napis(s){};
    A(A& kopia) : napis(kopia.napis){};

    std::ostream& printable(std::ostream& s) const{
        s << napis;
        return s;
    }

};

class B : public is_printable{
    public:
    int liczba;

    B(int l) : liczba(l){};


    std::ostream& printable(std::ostream& s) const{
        s << liczba;
        return s;
    }

};

std::ostream& operator<<(std::ostream& s, const is_printable& print){
        print.printable(s);
        return s;
}


int main()
{
    A a ("Tekst"); 
    B b {123};
    std::cout<< "a:\t"<<a<<"; b:\t"<<b<<"\n";
    const is_printable &a_r = a; // TO JEST KLASA 
    const is_printable &b_r = b;
    std::cout<< "a_r:\t"<<a_r<<"; b_r:\t"<<b_r<<"\n";
}

/*
a:      Tekst; b:       123
a_r:    Tekst; b_r:     123
*/
