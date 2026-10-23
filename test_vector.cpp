#include "vector.hpp"

#include <cstddef>
#include <iostream>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <type_traits>

struct NoDefault {
    NoDefault() = delete;
};

struct NoDestroy {
    ~NoDestroy() = delete;
};

struct alignas(64) Aligned {
    char byte;
};

struct Big {
    unsigned char bytes[256];
};

static_assert(sizeof(Big) == 256);
static_assert(learn::Vector<Big>::max_size() < std::numeric_limits<std::size_t>::max());
static_assert(learn::Vector<Big>::max_size() == std::numeric_limits<std::size_t>::max() / sizeof(Big));

static_assert(!std::is_copy_constructible_v<learn::Vector<int>>);
static_assert(!std::is_copy_assignable_v<learn::Vector<int>>);
static_assert(!std::is_move_constructible_v<learn::Vector<int>>);
static_assert(!std::is_move_assignable_v<learn::Vector<int>>);

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

static void test_reserve_builds_nothing() {
    learn::Vector<NoDefault> row;
    row.reserve(4);

    CHECK(row.size() == 0);
    CHECK(row.capacity() == 4);
    CHECK(row.empty());
    CHECK(row.data() != nullptr);
}

static void test_reserve_ends_nothing() {
    learn::Vector<NoDestroy> row;
    row.reserve(3);

    CHECK(row.size() == 0);
    CHECK(row.capacity() == 3);
}

static void test_reserve_alignment() {
    learn::Vector<Aligned> row;
    row.reserve(3);

    CHECK(row.data() != nullptr);
    CHECK(reinterpret_cast<std::uintptr_t>(row.data()) % 64 == 0);
}

static void test_reserve_keeps_a_big_enough_row() {
    learn::Vector<int> row;
    row.reserve(4);
    int* first = row.data();

    row.reserve(4);
    CHECK(row.data() == first);
    CHECK(row.capacity() == 4);

    row.reserve(2);
    CHECK(row.data() == first);
    CHECK(row.capacity() == 4);

    row.reserve(0);
    CHECK(row.data() == first);
    CHECK(row.capacity() == 4);
    CHECK(row.size() == 0);
    CHECK(row.empty());
}

static void test_reserve_replaces_a_smaller_row() {
    learn::Vector<int> row;
    row.reserve(2);
    int* first = row.data();

    row.reserve(8);
    CHECK(row.capacity() == 8);
    CHECK(row.size() == 0);
    CHECK(row.data() != first);
    CHECK(row.data() != nullptr);
}

static void test_reserve_rejects_a_count_that_cannot_fit() {
    learn::Vector<Big> row;

    bool threw = false;
    try {
        row.reserve(learn::Vector<Big>::max_size() + 1);
    } catch (const std::length_error&) {
        threw = true;
    }

    CHECK(threw);
    CHECK(row.size() == 0);
    CHECK(row.capacity() == 0);
    CHECK(row.data() == nullptr);

    row.reserve(2);
    Big* first = row.data();
    threw = false;
    try {
        row.reserve(learn::Vector<Big>::max_size() + 1);
    } catch (const std::length_error&) {
        threw = true;
    }

    CHECK(threw);
    CHECK(row.size() == 0);
    CHECK(row.capacity() == 2);
    CHECK(row.data() == first);
    CHECK(row.empty());
}

static void test_two_rows_are_not_one_row() {
    learn::Vector<int> first;
    learn::Vector<int> second;
    first.reserve(1);
    second.reserve(1);

    CHECK(first.data() != second.data());
}

int main() {
    test_empty_int();
    test_empty_builds_nothing();
    test_reserve_builds_nothing();
    test_reserve_ends_nothing();
    test_reserve_alignment();
    test_reserve_keeps_a_big_enough_row();
    test_reserve_replaces_a_smaller_row();
    test_reserve_rejects_a_count_that_cannot_fit();
    test_two_rows_are_not_one_row();

    if (failures != 0) {
        std::cerr << failures << " failed\n";
        return 1;
    }

    std::cout << "ok\n";
    return 0;
}