#include<utility>
#include<iostream>
#include<algorithm>

// Program ma wytworzyć poniższy output.
// Po odkomentowaniu zakomentowanych linii w main program ma się nie kompilować.
// Kod można pisać tylko w wyznaczonych miejscach.

/* 
    MIEJSCE NA KOD 
*/

template <typename T=double>
struct Type_t{
    T _v;
    Type_t() : _v{} {} // konstruktor domyslny, inicjalizuje wartoscia 0.0

    explicit Type_t(T v) : _v(v) {} // blokuje przypisanie =13
};


// zamiast cala strukture to zwraca na strumien tylko _v
template <typename T>
std::ostream& operator<<(std::ostream& os, const Type_t<T>& obj){
    return os << obj._v;
}


template <typename T>
class ptr{
    private:
    T* m_ptr; // przechowuje adres do pamieci (wygenerowanej przez new)

    public:
    using value_type = T; // alias typu dla maina

    ptr() : m_ptr(nullptr){} // konstruktor chroniacy przed przypisaniem surowego wskaznika

    // blokuje możliwość przypadkowego przypisania adresu bez użycia nawiasów klamrowych/okrągłych.
    explicit ptr(T* p) : m_ptr(p){}

    ~ptr() {delete m_ptr;} // destruktor

    ptr(const ptr&) = delete; // blokada kopiowania
    ptr& operator=(const ptr&) = delete; // blokada przypisania

    // konstruktor przenoszacy (dla std::move)
    ptr(ptr&& other) noexcept : m_ptr(other.m_ptr){
        other.m_ptr = nullptr;
    }

    // przenoszacy operator przypisania
    ptr& operator=(ptr&& other) noexcept{
        if (this != other){
            delete m_ptr;
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const {return *m_ptr;}
    T* operator->() const {return m_ptr;}

};


using Float_t = Type_t<>;

int main(){
    using Type_ptr = ptr<std::pair<Float_t, Float_t>>;
    Type_ptr t1 { new Type_ptr::value_type{}};
    // Type_ptr t2 = t1; 
    // Type_ptr t2; t2 = t1;
    // Type_ptr t3 = new Type_ptr::value_type();
    (*t1).first = Type_ptr::value_type::first_type{1};
    t1->second = Type_ptr::value_type::second_type{2.5};
    std::cout<< t1->first._v<<" "<<t1->second<<std::endl;

    Type_ptr t2 = std::move(t1);
    // t2->first = 13; 
    //t2->second = 13;
    const Type_ptr t3 = std::move(t2);
    t3->first = Type_ptr::value_type::first_type{13};
    t3->second = Type_ptr::value_type::second_type{13}; 

    std::cout<< (*t3).first._v<<" "<<(*t3).second<<std::endl;
    return 0;
}

// 1 2.5
// 13 13