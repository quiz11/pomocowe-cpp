#include <iostream>
#include <list>
#include <functional>

// Program ma wytworzyć poniższy output.

template<typename T>
void print_to_if(std::ostream &stream, T begin, T end, std::function<bool(int)> f){
    for (T it = begin; it != end; it++) {
        if (f(*it)) {
            stream << *it << " ";
        }
    }
    stream << '\n';
}

bool f1(int) {
    return true;
}

bool f2(int a) {
    return a % 2 == 0;
}

class f3 {
private:
    int value;

public:
    f3(const int &val) : value{val} {}

    int operator()(int a) {
        return a + value;
    }
};

template <typename T, typename F>
void change(T begin, T end, F f) {
    for (T it = begin; it != end; it++) {
        *it = f(*it);
    }
}

int main(){
    const auto cl = {1,2,3,4,5,6,7};

    print_to_if(std::cout<<"All: ", begin(cl), end(cl), f1);
    print_to_if(std::cout<<"All: ", begin(cl), end(cl), f2);

    int add_value{-1};
    std::list<int> cl2 = {7,6,5,4,3,2,1};
    change(begin(cl2), end(cl2), f3{add_value});
    print_to_if(std::cout << "All  ", begin(cl2), end(cl2), f1);
}
/*
All: 1 2 3 4 5 6 7 
All: 2 4 6 
All  6 5 4 3 2 1 0 
*/