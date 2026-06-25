#include <iostream>

// Co wypisze się na ekran?

struct MyStruct {
    static int j;
    const static int i = 5;
    int a;
};

int i = 10;
int MyStruct::j = i + 1;
int j = i + 1;

namespace exam {
    static int i = 1;
}

int main() {
    MyStruct A;

    A.a = j + i;
    int i = 15;

    using namespace exam;

    std::cout << i << '\n';
    std::cout << ::i << '\n';
    std::cout << MyStruct::j << '\n';
    std::cout << j << '\n';
    std::cout << A.a << std::endl;
}