#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

// Program ma wytworzyć poniższy output.
// Kod można pisać tylko w wyznaczonych miejscach.

/* 
    MIEJSCE NA KOD 
*/

auto liftToVector(){ // budujemy funkcje która zwróci lambde ktora nastepnie przyjmie 
                     // wartosci x z vektora i zwiekszy je zwracajac do v calosc
    return [](std::vector<int> x){
        for (int& a : x){ // bez & nie zmienimy wartości w x na o 2 większą
            a += 2;
        }
        return x;
    };
}

int main(){

    auto vadd2 = liftToVector();
    std::vector<int> x = {0,9,4};
    auto v = vadd2(x);

    std::for_each(v.begin(), v.end(), [](const int n) {std::cout<< n << ' ';});

    return 0;
}

// 2 11 6