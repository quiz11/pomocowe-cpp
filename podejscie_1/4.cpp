#include <iostream>
#include <vector>

// Program ma wytworzyć poniższy output.
//  __PRETTY_FUNCTION__ zawiera pełną nazwę funkcji w danym miejscu
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
    //     s << *c;

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