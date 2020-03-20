#include <random>
#include <iostream>

int main() {
    std::mt19937 mt_engine(34);

    int n_strategies = 5;
    std::uniform_int_distribution<int> uniform_int_dist(0, n_strategies - 1);

    for (int i = 0; i < 20; ++i) {
        std::cout << uniform_int_dist(mt_engine) << std::endl;
    }

    return 0;
}