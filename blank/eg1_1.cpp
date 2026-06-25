// Nie można używać std::vector, std::array, std::deque itp. kontenerów z STL
/* UZUPEŁNIJ 1 */

void print_to_cout( /* UZUPEŁNIJ 2 */ a_v )
{
    for (auto idx = 0; idx < N; ++idx)
    {
        std::cout << "[" << idx << "]: " << a_v[idx] << ", ";
    }
    std::cout << std::endl;
}

int main()
{
    array<int> a {5, 6, 7};
    const array<int> b = a;

    a[array<int>::size - 1] = array<int>::value_type{2};
    a[0] = 3;

    std::cout << "a: "; print_to_cout(a);
    std::cout << "b: "; print_to_cout(b);
}

/* Oczekiwany output:
a: [0] 3, [1] 6, [2] 2
b: [0] 5, [1] 6, [2] 7
*/