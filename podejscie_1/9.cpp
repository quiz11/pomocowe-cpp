#include <iostream>
#include <list>
#include <functional>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.


bool f1(int c){
    return true;
}

bool f2(int c){
    return c%2 == 0;
}

template <typename T>
struct f3{
    T _value;
    f3(T& value) : _value(value){}
    
    int operator()(int element) const{
        return element + _value;
    }
};

template <typename It, typename Fun>
void change(It start, It end, Fun f){
    for (auto it = start; it != end; ++it){
        *it = f(*it);
    }
}

template <typename It, typename Fun>
void print_to_if(std::ostream& os, It start, It end, Fun f){
    for (auto it = start; it != end; ++it){
        if (f(*it)){
            os << *it << " ";
        }
    }
    os << "\n";
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