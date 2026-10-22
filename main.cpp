#include "vector.hpp"

#include <iostream>

int main() {
    learn::Vector<int> numbers;

    std::cout << "size " << numbers.size() << "\n";
    std::cout << "capacity " << numbers.capacity() << "\n";
    std::cout << "empty " << std::boolalpha << numbers.empty() << "\n";
    std::cout << "data " << numbers.data() << "\n";

    if (numbers.size() != 0 || numbers.capacity() != 0 || !numbers.empty() || numbers.data() != nullptr) {
        return 1;
    }

    return 0;
}