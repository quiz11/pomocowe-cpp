#include <iostream>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

template <typename T>
class B {
private:
    T val;

public:
    using value_type = T;

    B(const T &value) : val{value} {}

    B(const B &other) : val{other.val} {}

    T get() {
        return val;
    }
};

template <typename T>
class B<T*> {
private:
    T *val;

public:
    using value_type = T;

    B(T *value) : val{value} {}

    ~B() {
        delete val;
    }

    B(const B &other) = delete;

    B &operator=(const B &other) = delete;

    T get() {
        return *val;
    }
};

int main()
{
    typedef B<int> int_b;
    typedef B<int*> int_p_b;      //jednak typedef

    int_b a(1);
    int_b a_copy(a);
    int_p_b b(new int_p_b::value_type{2});
    // int_p_b e = b; //error
    // b=b //error
    
    std::cout << "a=" << a.get() << std::endl;
    std::cout << "a_copy=" << a_copy.get()+1 << std::endl;
    std::cout <<" b=" << b.get()+1 << std::endl;
}

// a=1
// a_copy=2
//  b=3