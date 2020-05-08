#include <catch.hpp>
#include "../q2/mac937_queue.h"

TEST_CASE("CircularQueue_push_one") {
    VectorQueue<int> queue(true);
    REQUIRE(queue.IsEmpty());
    queue.Push(1);
    REQUIRE_FALSE(queue.IsEmpty());
    int count = queue.Count();
    REQUIRE(count == 1);
    int val = queue.Front();
    REQUIRE(1 == val);
    val = queue.Dequeue();
    REQUIRE(1 == val);
    count = queue.Count();
    REQUIRE(count == 0);
    REQUIRE(queue.IsEmpty());
}

TEST_CASE("CircularQueue__IsPacked") {
    VectorQueue<char> queue(true);
    REQUIRE(queue.GetVectorSize() == queue.Count());
    queue.Push('a');
    queue.Push('b');
    REQUIRE(queue.GetVectorSize() == queue.Count());
    queue.Dequeue();
    REQUIRE_FALSE(queue.GetVectorSize() == queue.Count());
}

TEST_CASE("CircularQueue_Clear") {
    VectorQueue<char> queue(true);
    queue.Push('a');
    queue.Push('b');
    queue.Push('c');
    queue.Clear();
    REQUIRE(queue.IsEmpty());
}

TEST_CASE("CircularQueue_push_two") {
    VectorQueue<int> queue(true);
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);
    int val = queue.Dequeue();
    REQUIRE(1 == val);
    REQUIRE_FALSE(queue.IsEmpty());
    val = queue.Dequeue();
    REQUIRE(2 == val);
    REQUIRE_FALSE(queue.IsEmpty());
    queue.Dequeue();
    REQUIRE(queue.IsEmpty());
    bool popped = queue.Pop();
    REQUIRE_FALSE(popped);
}

TEST_CASE("CircularQueue_pop") {
    VectorQueue<char> q(true);
    q.Push('a');
    REQUIRE(q.Pop());
    REQUIRE(q.IsEmpty());
    REQUIRE_FALSE(q.Pop());

}

TEST_CASE("CircularQueue_CopyToVector") {
    VectorQueue<int> queue(true);
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);
    queue.Dequeue();
    std::vector<int> expected({2, 3});
    std::vector<int> actual = queue.CopyToVector();
    REQUIRE(expected == actual);
}

TEST_CASE("CircularQueue_useUnusedSlots") {
    VectorQueue<char> queue(true);
    queue.Push('a');
    queue.Push('b');                    // a b
    REQUIRE(2 == queue.Count());
    REQUIRE('a' == queue.Dequeue());           // _ b
    REQUIRE(1 == queue.Count());
    std::vector<char> expected({'b'});
    REQUIRE(expected == queue.CopyToVector());
    queue.Push('c');                    // c b
    expected = {'b', 'c'};
    REQUIRE(expected == queue.CopyToVector());
    REQUIRE(2 == queue.GetVectorSize());
    REQUIRE(2 == queue.Count());
    REQUIRE('b' == queue.Dequeue());           // c _
    REQUIRE(1 == queue.Count());
    queue.Push('d');                    // c d
    REQUIRE(2 == queue.GetVectorSize());
    REQUIRE(2 == queue.Count());
    REQUIRE('c' == queue.Dequeue());           // _ d
    REQUIRE(1 == queue.Count());
    queue.Push('e');                    // e d
    REQUIRE(2 == queue.GetVectorSize());
    queue.Push('f');
    expected = {'d', 'e', 'f'};
    std::vector<char> actual = queue.CopyToVector();
    REQUIRE(expected == actual);
    REQUIRE(3 == queue.GetVectorSize());
}