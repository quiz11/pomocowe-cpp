#include <iostream>

// Program ma wytworzyć poniższy output.

class Obj {
public:
    virtual void Draw() const = 0;
};

template <typename T>
class Box : public Obj {
private:
    T value;

public:
    explicit Box(const T &val) : value{val} {}

    void Draw() const override {
        std::cout << __PRETTY_FUNCTION__ << " --> " << value << '\n';
    }
    
    operator T() {
        return value;
    }

    friend std::ostream &operator<<(std::ostream &stream, const Box<T> &obj) {
        stream << obj.value;
        return stream;
    }
};

template <typename K>
class Box<Box<K>> : public Obj {
private:
    Box<K> value;
    
public:
    explicit Box(const K &val) : value{val} {}

    
    void Draw() const {
        std::cout << __PRETTY_FUNCTION__ << " --> " << value << '\n';
    }

    operator Box<K>() {
        return value;
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

    // Box<int> _ = 3; //Odkomentowanie powoduje b��d kompilacji

}
/*
void Box<T>::Draw() const [with T = int] --> 3
void Box<T>::Draw() const [with T = double] --> 3.4
void Box<Box<K> >::Draw() const [with K = int] --> 3
void Box<Box<K> >::Draw() const [with K = double] --> 3.4
*/