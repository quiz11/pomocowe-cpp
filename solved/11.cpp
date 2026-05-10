#include <iostream>

// Program ma wytworzyć poniższy output.

namespace OOP {

template <typename T>
class Array {
private:
    T *array;
    size_t capacity;
    size_t len;

public:
    using value_type = T;

    Array(size_t N)  : array{new T[N]}, capacity{N}, len{0} {} 

    ~Array() {
        delete [] array;
    }

    Array &insert(const T &element) {
        if (len + 1 < capacity) {
            this->array[len] = element;
            this->len++;
        }

        return *this;
    }

    Array &operator%(const T &element) {
        return this->insert(element);
    }

    T &operator[](size_t idx) {
        if (idx >= capacity) {
            throw std::runtime_error("Out of bounds access");
        }

        return this->array[idx];
    }

    // unsigned
    size_t operator~() {
        return this->len;
    }

};

}

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