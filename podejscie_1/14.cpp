#include <iostream>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

/*
    MIEJSCE NA KOD
*/

template <typename T>
class B{
    private:
    T _b;
    public:
    using value_type = T;

    B(T b) : _b(b){}
    
    B(const B& b) : _b(b._b){};

    T get() {
        return _b;
    }

};

template <typename T>
class B<T*>{
    private:
    T* _b;

    public:
    using value_type = T;

    B(T* b) : _b(b){}

    T get(){
        return *_b;
    }

    ~B(){
        delete _b;
    }

    B(const B&) = delete;
    B(const B&&) = delete;
 
};

int main()
{
    typedef B<int> int_b;
    typedef B<int*> int_p_b;        //jednak typedef

    int_b a(1);
    int_b a_copy(a);
    int_p_b b(new int_p_b::value_type{2});
    // int_p_b e = b; //error
    // b=b; //error
    
    std::cout << "a=" << a.get() << std::endl;
    std::cout << "a_copy=" << a_copy.get()+1 << std::endl;
    std::cout <<" b=" << b.get()+1 << std::endl;
}

// a=1
// a_copy=2
//  b=3