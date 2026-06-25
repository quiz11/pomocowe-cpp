#include <utility>

constexpr unsigned factorial(unsigned n) {
    if (n == 1) return 1;
    return n * factorial(n-1);
}

template <typename T, unsigned N>
struct array{
    array(){}

    static constexpr unsigned size(){
        return N;
    }
};



int main() {
    array<int,6> a;
    const array<int,factorial(3)> b;
    array<int, factorial(4)> c;
    auto d = std::move(c);
    a=b;
    a=std::move(b);
    static_assert(a.size()==6);

    static_assert(array<unsigned,factorial(4)>::size()==24);
    static_assert(array<unsigned,factorial(3)>::size() == b.size());
    // static_assert(array<int, factorial(4)>::size()==b.size()); //blad kompilacji
}