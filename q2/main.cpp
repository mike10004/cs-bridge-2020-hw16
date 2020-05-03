// mchaberski@novetta.com
// hw16 question 2

#include <cassert>
#include "queue.h"

using namespace std;

int main() {
    VectorQueue<int> queue;
    queue.Push(1);
    queue.Push(2);
    queue.Push(3);
    int val = queue.Pop();
    assert(1 == val);
    assert(!queue.IsEmpty());
    val = queue.Pop();
    assert(2 == val);
    assert(!queue.IsEmpty());
    queue.Pop();
    assert(queue.IsEmpty());
    bool valid = true;
    queue.Pop(valid);
    assert(!valid);
    return 0;
}
