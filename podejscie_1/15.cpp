#include<iostream>
#include<deque>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

template <typename T = int, template <typename...> class StorageType = std::deque>
class fifo {
    private:
    StorageType<T> _storage;
    
    public:
    using storage_type = StorageType<T>;

    fifo(){std::cout << __PRETTY_FUNCTION__ << "\n";}

    void push(const T& item) {
        _storage.push_back(item);
    }

    T get(){
        T front_item = _storage.front();
        _storage.pop_front();
        return front_item;
    }

    size_t size() const{
        return _storage.size();
    }

    typename storage_type::const_iterator begin() const{
        return _storage.begin();
    }

    typename storage_type::const_iterator end() const{
        return _storage.end();
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
  fifo<T, StorageType>::fifo() [with T = int, StorageType = std::deque]
  0
  4
  1,2,3,4,
*/