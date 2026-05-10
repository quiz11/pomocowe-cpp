#include<iostream>
#include<array>
#include<string>
#include <memory>

// Program ma wytworzyć poniższy output.
// Program ma nie leakować pamięci.

void my_print_el(const std::string &el) {
    std::cout << el;
}

template <size_t N>
void my_print(const std::array<std::unique_ptr<int>, N> &obj, const std::string &separator = ";", const std::string &end = "\n") {
    std::cout << "[";

    for (size_t i = 0; i < N; i++) {
        std::cout << *(obj[i]) << separator;
    }

    std::cout << "]" << end;
}

void my_swap(std::unique_ptr<int> &a, std::unique_ptr<int> &b) {
    int temp = *a;
    *a = *b;
    *b = temp;

    // std::unique_ptr<int> temp = std::move(a);
    // a = std::move(b);
    // b = std::move(temp);
}

void my_swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
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
// ----------------
//[1;2;] -> [2;1;] -> [1;2;]
// ----------------