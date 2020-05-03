#include <catch.hpp>
#include "../q1/stack.h"

TEST_CASE("Stack_push_one") {
    Stack<int> stack;
    REQUIRE(stack.IsEmpty());
    stack.Push(1);
    REQUIRE_FALSE(stack.IsEmpty());
    int val = stack.Pop();
    REQUIRE(1 == val);
    REQUIRE(stack.IsEmpty());
}

struct Counter {
    explicit Counter(int& destructions) : destructions(destructions) {}
    Counter(const Counter& other) : destructions(other.destructions) {}
    ~Counter() {
        destructions++;
    }
private:
    int& destructions;
};

TEST_CASE("Stack_clear") {
    int num_destructions;
    Stack<Counter> stack;
    Counter a(num_destructions);
    Counter b(num_destructions);
    Counter c(num_destructions);
    stack.Push(a);
    stack.Push(b);
    stack.Push(c);
    stack.Clear();
    REQUIRE(3 == num_destructions);
}

TEST_CASE("Stack_push_two") {
    Stack<int> stack;
    stack.Push(1);
    stack.Push(2);
    int val = stack.Pop();
    REQUIRE(2 == val);
    REQUIRE_FALSE(stack.IsEmpty());
    val = stack.Pop();
    REQUIRE(1 == val);
    REQUIRE(stack.IsEmpty());
}

TEST_CASE("Stack_CopyToVector") {
    Stack<int> stack;
    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    std::vector<int> expected({3, 2, 1});
    std::vector<int> actual = stack.CopyToVector();
    REQUIRE(expected == actual);
}