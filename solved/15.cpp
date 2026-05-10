#include<iostream>
#include<deque>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

// template template parameters

template <typename T = int, template <typename U = T, typename Allocator = std::allocator<U>> typename StorageType = std::deque>
class fifo {
private:
    StorageType<> collection;

public:
    using storage_type = StorageType<>;
    using value_type = typename storage_type::value_type;

    fifo() {
        std::cout << __PRETTY_FUNCTION__ << '\n';
    }

    fifo(const fifo &other) : collection{other.collection} {}

    void push (const T &elem) {
        collection.push_back(elem);
    }

    T &get() {
        T &t = collection.front();
        collection.pop_front();
        return t;
    }

    size_t size() {
        return collection.size();
    }

    auto begin() {
        return collection.begin();
    }

    auto end() {
        return collection.end();
    }
};

int main(){
    fifo<> ft;
    for(int i: {0,1,2,3,4})
        ft.push(i);

    fifo<int, std::deque> f = ft;

    std::cout << f.get() << "\n";
    std::cout << f.size() << "\n";

    for(fifo<>::storage_type::const_iterator i = f.begin(); i != f.end(); ++i)
        std::cout << *i << ",";

    std::cout << std::endl;
}
/*
  Wynik:
  fifo<T, StorageType>::fifo() [with T = int; StorageType = std::deque]
  0
  4
  0,1,2,3,
*/




