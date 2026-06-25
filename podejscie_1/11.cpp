#include <iostream>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

/* 
    MIEJSCE NA KOD 
*/

namespace OOP{ // przestrzeń nazw ponieważ ::OOP::
    template <typename T>
    class Array{
        private:
        T* _data; // tablica na dane
        unsigned _capacity; // pojemnosc max
        unsigned _size; // aktualnie zajeta pojemnosc

        public:
        using value_type = T; // nadpisanie T przez value_type dla maina

        // konstruktor
        explicit Array(unsigned capacity) : _capacity(capacity), _size(0), _data(new T[capacity]){}

        // destruktor zabezpieczajacy wyciek pamieci
        ~Array(){
            delete[] _data;
        }

        // operacja dodania elementu umozliwia wywolywanie po sobie z .
        Array& insert(T s){
            if (_size < _capacity){
                _data[_size] = s;
                _size += 1;
            }
            return *this;
        }

        // operacja dodania elementu poprzez nadpisanie znaku %
        Array& operator%(T s){
            return insert(s);
        }

        // nadpisanie operatora a[0] zwracający wartość
        T& operator[](unsigned index){
            return _data[index];
        }

        // nadpisanie operatora ~ aby zwrocic liczbę elementow
        unsigned operator~() const{
            return _size;
        }

    };
};

int main()
{
    typedef ::OOP::Array<int> type;
    type a(rand() % 100 + 10); // nie trzeba seedować żeby program się wykonał

    a.insert('#' - 1).insert('P') % type::value_type('O') % ('-') % ('E') % ('G') % ('Z') % ('1');

     ++a[0];
    for (unsigned i = 0; i != ~a; i++){
        std::cout << static_cast<char>(a[i]) << (i + 1 != ~a ? '_' : '\n');
    }
}
//#_P_O_-_E_G_Z_1