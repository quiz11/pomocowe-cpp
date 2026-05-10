#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

// Program ma wytworzyć poniższy output.

std::function<std::vector<int>(const std::vector<int> &)> liftToVector() {
    return [] (const std::vector<int> &vec) {
        std::vector<int> output;

        for (auto &e : vec) {
            output.push_back(e + 2);
        }

        return output;
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