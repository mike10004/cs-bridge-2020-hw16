// mac937@nyu.edu
// hw16 question 2

#include <cassert>
#include "queue.h"

using namespace std;

int main() {
    VectorQueue<int> queue;
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);
    int val = queue.Dequeue();
    assert(1 == val);
    assert(!queue.IsEmpty());
    val = queue.Dequeue();
    assert(2 == val);
    assert(!queue.IsEmpty());
    queue.Dequeue();
    assert(queue.IsEmpty());
    bool valid = true;
    queue.Dequeue(valid);
    assert(!valid);
    return 0;
}
