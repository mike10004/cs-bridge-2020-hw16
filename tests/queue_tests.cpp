#include <catch.hpp>
#include "../q2/queue.h"

TEST_CASE("Queue_push_one") {
    VectorQueue<int> queue;
    REQUIRE(queue.IsEmpty());
    queue.Push(1);
    REQUIRE_FALSE(queue.IsEmpty());
    int count = queue.Count();
    REQUIRE(count == 1);
    int val = queue.Front();
    REQUIRE(1 == val);
    val = queue.Pop();
    REQUIRE(1 == val);
    count = queue.Count();
    REQUIRE(count == 0);
    REQUIRE(queue.IsEmpty());
}

TEST_CASE("Queue__IsPacked") {
    VectorQueue<char> queue;
    REQUIRE(queue.IsPacked());
    queue.Push('a');
    queue.Push('b');
    REQUIRE(queue.IsPacked());
    queue.Pop();
    REQUIRE_FALSE(queue.IsPacked());
}

TEST_CASE("Queue_Clear") {
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

TEST_CASE("Queue_useUnusedSlots") {
    VectorQueue<char> queue;
    queue.Push('a');
    queue.Push('b');                    // a b
    REQUIRE(2 == queue.Count());
    REQUIRE('a' == queue.Pop());           // _ b
    REQUIRE(1 == queue.Count());
    std::vector<char> expected({'b'});
    REQUIRE(expected == queue.CopyToVector());
    queue.Push('c');                    // c b
    expected = {'b', 'c'};
    REQUIRE(expected == queue.CopyToVector());
    REQUIRE(2 == queue.GetVectorSize());
    REQUIRE(2 == queue.Count());
    REQUIRE('b' == queue.Pop());           // c _
    REQUIRE(1 == queue.Count());
    queue.Push('d');                    // c d
    REQUIRE(2 == queue.GetVectorSize());
    REQUIRE(2 == queue.Count());
    REQUIRE('c' == queue.Pop());           // _ d
    REQUIRE(1 == queue.Count());
    queue.Push('e');                    // e d
    REQUIRE(2 == queue.GetVectorSize());
    queue.Push('f');
    expected = {'d', 'e', 'f'};
    std::vector<char> actual = queue.CopyToVector();
    REQUIRE(expected == actual);
    REQUIRE(3 == queue.GetVectorSize());
}