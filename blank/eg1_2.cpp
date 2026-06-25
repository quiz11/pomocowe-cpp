// Nie można używać std::vector, std::array, std::deque itp. kontenerów z STL ZA WYJĄTKIEM STD::PAIR
/* UZUPEŁNIJ 1 */

int main()
{
    using Float_t = double;
    using Test_t = ptr<my_pair<Float_t, Float_t>>;

    Test_t t1{new Test_t::value_type{}};
    // Test_t t2 = t1;                            // BLAD KOMPILACJI
    // Test_t t3; t3 = t1;                        // BLAD KOMPILACJI
    // Test_t t4 = new Test_t::value_type();      // BLAD KOMPILACJI

    std::cout << (*t1).first << ", " << t1->second << "\n";

    (*t1).first = Test_t::value_type::first_type{1};
    t1->second = Test_t::value_type::second_type{3.141};

    std::cout << (*t1).first << ", " << t1->second << "\n";

}
/* output:
0, 0
1, 3.141
*/