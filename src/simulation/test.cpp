#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>

int main() {
    std::vector<int> x = {2, 3, 1, 9};

    std::cout << *std::max_element(std::begin(x), std::end(x)) << std::endl;

    return 0;
}