#include "vector.hpp"

#include <iostream>

int main() {
    learn::Vector<int> numbers;
    numbers.reserve(4);
    numbers.push_back(7);

    std::cout << "size " << numbers.size() << "\n";
    std::cout << "capacity " << numbers.capacity() << "\n";
    std::cout << "empty " << std::boolalpha << numbers.empty() << "\n";
    std::cout << "first " << numbers.data()[0] << "\n";
    std::cout << "data " << numbers.data() << "\n";

    if (numbers.size() != 1 || numbers.capacity() != 4 || numbers.empty() || numbers.data()[0] != 7) {
        return 1;
    }

    return 0;
}