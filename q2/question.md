# Question 2

Although a queue is "best" implemented with a list, it can be implemented with 
a vector if you take into account the starting position of the queue.  For 
example, if five elements are pushed onto the queue, the start of the queue is 
at position zero and the end is at position 4.  If we, then, pop two elements, 
the start would be at position 2 and the end at position 4.  The two "popped" 
elements are not really removed from the vector, and that avoids the O(N) time 
problem for the pop function.

Implement a class which uses a vector to store the queue.  Be mindful of 
performance, such that if the queue is empty, the size of the underlying 
vector is "reset."
