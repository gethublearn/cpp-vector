#include "vector.hpp"

#include <iostream>

struct NoDefault {
    NoDefault() = delete;
};

static int failures = 0;

static void check(bool condition, const char* text, int line) {
    if (!condition) {
        std::cerr << "fail:" << line << " " << text << "\n";
        ++failures;
    }
}

#define CHECK(condition) check((condition), #condition, __LINE__)

static void test_empty_int() {
    learn::Vector<int> numbers;

    CHECK(numbers.size() == 0);
    CHECK(numbers.capacity() == 0);
    CHECK(numbers.empty());
    CHECK(numbers.data() == nullptr);

    const learn::Vector<int> same;
    CHECK(same.size() == 0);
    CHECK(same.capacity() == 0);
    CHECK(same.empty());
    CHECK(same.data() == nullptr);
}

static void test_empty_builds_nothing() {
    learn::Vector<NoDefault> row;

    CHECK(row.size() == 0);
    CHECK(row.capacity() == 0);
    CHECK(row.empty());
    CHECK(row.data() == nullptr);
}

int main() {
    test_empty_int();
    test_empty_builds_nothing();

    if (failures != 0) {
        std::cerr << failures << " failed\n";
        return 1;
    }

    std::cout << "ok\n";
    return 0;
}