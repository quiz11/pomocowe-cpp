#include <iostream>

// w całym kodzie można bezpośrednio wywoływać tylko dwie funkcje: printOn i operator <<
// wypisywanie może się odbywać tylko z wykorzystaniem __PRETTY_FUNCTION__ i "\n"
//  __PRETTY_FUNCTION__ zawiera pełną nazwę funkcji w danym miejscu
// Kod można pisać tylko w wyznaczonych miejscach.

/*
    MIEJSCE NA KOD
*/

class B{
  protected:
  B() = default;  // blokujemy konstruktor dla zewnatrz a dla dzieci zostaje

  public:
  virtual std::ostream& printOn(std::ostream& s) const {
  s << __PRETTY_FUNCTION__ << "\n";
  return s;
  }
  
  virtual ~B() = default;
};

class D1 : virtual public B{
  public:
  
  virtual std::ostream& printOn(std::ostream& s) const {
    s << __PRETTY_FUNCTION__ << "\n";
    return s;
  };
};

class D2 : public D1{

};

class D3 : virtual public B{
  public:
  
  virtual std::ostream& printOn(std::ostream& s) const {
    s << __PRETTY_FUNCTION__ << "\n";
    return s;
  };
};

class D4 : public D1, public D3{
  public:
  virtual std::ostream& printOn(std::ostream& s) const {
    B::printOn(s);
    D1::printOn(s);
    D3::printOn(s);
    s << __PRETTY_FUNCTION__ << "\n";
  return s;
  }
};


std::ostream& operator<<(std::ostream& s, const B& b){
  return b.printOn(s);
}


int main(int argc, char *argv[]) {
  // B b; //odkomentowanie powoduje błąd kompilacji, czyli musi być wirtualna
  D1 d1; D2 d2; D3 d3; const D4 d4;
  std::cout << "d1: " << d1 << "d2: " << d2 << "d3: " << d3 << "d4: " << d4;
}

/* Output:
d1: virtual std::ostream& D1::printOn(std::ostream&) const
d2: virtual std::ostream& D1::printOn(std::ostream&) const
d3: virtual std::ostream& D3::printOn(std::ostream&) const
d4: virtual std::ostream& B::printOn(std::ostream&) const
virtual std::ostream& D1::printOn(std::ostream&) const
virtual std::ostream& D3::printOn(std::ostream&) const
virtual std::ostream& D4::printOn(std::ostream&) const
*/
