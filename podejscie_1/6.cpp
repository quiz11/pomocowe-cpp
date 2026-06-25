#include<iostream>
#include<array>
#include<string>
#include <memory>

// Program ma wytworzyć poniższy output.
// Program ma nie leakować pamięci.
// Kod można pisać tylko w wyznaczonych miejscach.

/* 
    MIEJSCE NA KOD 
*/



void my_print_el(const std::string& s){
    std::cout << s;
}

template <typename T>
void my_print(const T& kontener, const std::string& sep = ";", const std::string& end = ""){
    std::cout << "[";
    for (const auto& el : kontener){
        std::cout << *el << sep;
    }
    std:: cout << "]" << end;
}

template <typename T>
void my_swap(T& a, T& b){
    T temp = std::move(a);
    a = std::move(b);
    b = std::move(temp);
}



int main()
{
  std::array<std::unique_ptr<int>,2> a = {
      std::unique_ptr<int>(new int {1}),
      std::unique_ptr<int>(new int {2})
      };

  my_print_el("----------------\n");
  my_print(a,";"," -> ");
  my_swap(a[0],a[1]);
  my_print(a,";"," -> ");
  my_swap(*a[0],*a[1]);
  my_print(a);
  my_print_el("----------------");
}
//[1;2;] -> [2;1;] -> [1;2;]