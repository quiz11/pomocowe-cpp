#include <iostream>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

/* 
    MIEJSCE NA KOD 
*/

struct Obj{
    virtual void Draw() const = 0; 
};

template <typename T>
struct Box : public Obj{
    T _val;
    
    explicit Box(T val) : _val(val){}

    operator T() const{
        return _val;
    }

    void Draw() const override{
        std::cout << __PRETTY_FUNCTION__;
        std::cout << " --> " << _val << "\n";
    }
};

template <typename T>
struct Box<Box<T>> : public Obj {
    Box<T> _val;
    
    explicit Box(T val) : _val(val){}

    operator Box<T>() const{
        return _val;
    }

    void Draw() const override{
        std::cout << __PRETTY_FUNCTION__;
        std::cout << " --> " << _val << "\n";
    }
};

int main()
{
    Box<int> b_i {3};        
    Obj& r_1 = b_i; 
    r_1.Draw(); 
    int i = b_i;
    Box<double> b_d {3.4} ;
    Obj& r_2 = b_d;
    r_2.Draw(); 
    double d = b_d;
    Box<Box<int>> bb_i {3} ;
    const Obj& r_3 = bb_i;
    r_3.Draw(); 
    Box<int> br_i = bb_i;
    Box<Box<double>> bb_d {3.4} ; 
    const Obj& r_4 = bb_d;
    r_4.Draw();
    Box<double> b_a = bb_d;

    // Box<int> _ = 3; //Odkomentowanie powoduje blad kompilacji

}
/*
void Box<T>::Draw() const [with T = int] --> 3
void Box<T>::Draw() const [with T = double] --> 3.4
void Box<Box<K> >::Draw() const [with T = int] --> 3
void Box<Box<K> >::Draw() const [with T = double] --> 3.4
*/