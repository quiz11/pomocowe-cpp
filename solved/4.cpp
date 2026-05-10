#include <iostream>
#include <vector>

// Program ma wytworzyć poniższy output.
// __PRETTY_FUNCTION__ zawiera pełną nazwę funkcji w danym miejscu
// Po odkomentowaniu zakomentowanych linii w main program ma się nie kompilować.

class Base {
public:
    virtual std::ostream &print(std::ostream &stream) const = 0;
};

class Derived1 : public Base {
public:
    std::ostream &print(std::ostream &stream) const override {
        stream << __PRETTY_FUNCTION__;
        return stream;
    }
};

class Derived3;

class Derived2 : public Base {
public:
    Derived2(const Derived3 &other) {}

    std::ostream &print(std::ostream &stream) const override {
        stream << __PRETTY_FUNCTION__;
        return stream;
    }
};

class Derived3 : public Base {
public:
    std::ostream &print(std::ostream &stream) const override {
        stream << __PRETTY_FUNCTION__;
        return stream;
    }
};

std::ostream &operator<<(std::ostream &stream, const Base &obj) {
    obj.print(stream);
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const std::vector<Base*> &vec) {
    stream << "[\n";

    // range-based loop
    for (auto el : vec) {
        stream << *el;
        if (el != vec.back()) {
            stream << ",\n";
        }
    }

    stream << "\n]\n";

    return stream;
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