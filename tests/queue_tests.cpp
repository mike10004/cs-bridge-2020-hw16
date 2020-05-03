#include <catch.hpp>
#include "../q2/queue.h"

TEST_CASE("Queue_push_one") {
    VectorQueue<int> queue;
    REQUIRE(queue.IsEmpty());
    queue.Push(1);
    REQUIRE_FALSE(queue.IsEmpty());
    int count = queue.Count();
    REQUIRE(count == 1);
    int val = queue.Pop();
    REQUIRE(1 == val);
    count = queue.Count();
    REQUIRE(count == 0);
    REQUIRE(queue.IsEmpty());
}

TEST_CASE("Queue_clear") {
    VectorQueue<char> queue;
    queue.Push('a');
    queue.Push('b');
    queue.Push('c');
    queue.Clear();
    REQUIRE(queue.IsEmpty());
}

TEST_CASE("Queue_push_two") {
    VectorQueue<int> queue;
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);
    int val = queue.Pop();
    REQUIRE(1 == val);
    REQUIRE_FALSE(queue.IsEmpty());
    val = queue.Pop();
    REQUIRE(2 == val);
    REQUIRE_FALSE(queue.IsEmpty());
    queue.Pop();
    REQUIRE(queue.IsEmpty());
    bool valid = true;
    queue.Pop(valid);
    REQUIRE_FALSE(valid);
}

TEST_CASE("Queue_CopyToVector") {
    VectorQueue<int> queue;
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);
    queue.Pop();
    std::vector<int> expected({2, 3});
    std::vector<int> actual = queue.CopyToVector();
    REQUIRE(expected == actual);
}