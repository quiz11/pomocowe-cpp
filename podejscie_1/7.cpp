#include <iostream>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

/* 
    MIEJSCE NA KOD 
*/

struct A{
  int i = 1;
};

template <typename T>
struct ptr{
  T* _ptr;

  ptr() : _ptr(nullptr) {}
  explicit ptr(T* ptr) : _ptr(ptr){}

  ptr(const ptr&) = delete;

  T& operator*() const {
    return *_ptr;
  }
  
  T* operator->() const{
    return _ptr;
  }

  bool operator==(const ptr& other) const{
    if (_ptr == other._ptr) return true;
    else return false;
  }

  bool operator!=(const ptr& other) const {
    if (_ptr != other._ptr) return true;
    else return false;
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