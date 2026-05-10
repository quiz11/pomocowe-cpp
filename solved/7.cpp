#include <iostream>

// Program ma wytworzyć poniższy output.

class A {
public:
    int i = 1;
};

template <typename T>
class ptr {
private:
    T *value;

public:
    ptr() : value{nullptr} {}

    explicit ptr(T *p) : value{p} {}

    ptr(const ptr<T> &other) = delete;

    ptr<T> &operator=(const ptr<T> &other) = delete;

    ~ptr() {
        delete value;
    }

    T &operator*() const {
        return *value; 
    }

    T *operator->() const {
        return value;
    }

    bool operator==(const ptr<T> &other) const {
        return this->value == other.value;
    }   

    bool operator!=(const ptr<T> &other) const {
        return !(*this == other);
    }
};

int main() {
    const ptr<A>  a(new A);
    const ptr<A> b;
    ptr<A> c(new A);

//   ptr<A>  _b_error = new A;      // Odkomentowanie powoduje błąd kompilacji 
//   a = a;               // Odkomentowanie powoduje błąd kompilacji 
//   const ptr<A> _c_error = a;     // Odkomentowanie powoduje błąd kompilacji 

    std::cout << (((*a).i, a->i))        << " " << ++c->i << " ";
    std::cout << (a == ptr<A>() ) << " " << (a != b) << "\n";
}

//1 2 0 1