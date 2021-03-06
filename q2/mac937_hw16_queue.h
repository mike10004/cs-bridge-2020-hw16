#ifndef HW16_MAC937_HW16_QUEUE_H
#define HW16_MAC937_HW16_QUEUE_H

#include <vector>
#include <cassert>

const size_t VECTOR_QUEUE_RESET_CAPACITY = 10;

/**
 * Queue implementation that uses a vector to store elements.
 * If you know you will have about the same number of enqueues as dequeues,
 * you can specify in the constructor that a "circular array" implementation
 * will be used. The benefit of the circular implementation is that if the
 * underlying vector has space for new elements, it is used most efficiently.
 * The drawback is that an insert can take O(n) time if the underlying vector
 * is full. ("Full" means that the size of the queue equals the size of the
 * underlying vector.)
 * @tparam T element type
 */
template<class T>
class VectorQueue {
public:

    VectorQueue(bool circular) : circular_(circular), elements_(), front_(0), back_(0), count_(0) {}

    VectorQueue() : VectorQueue(false) {}

    /**
     * Adds an element to the back of the queue. In the noncircular implementation,
     * this always adds an element to the vector. In the circular implementation,
     * if there is space vacated by previously dequeued elements, then that space
     * is used; otherwise the ordering of the elements in the underlying vector is
     * normalized and the new element is appended.
     * @param element element
     */
    void Push(const T& element);

    /**
     * Removes an element from the front of the queue.
     * If the queue becomes empty, the underlying vector will
     * have its capacity shrunk to a default size.
     * @return true if queue was not empty and element was popped; false if queue was empty
     */
    bool Pop();

    /**
     * Removes an element from the queue and returns it.
     * This is equivalent to calling Front() and Pop().
     * @return the first element in the queue, or if the queue is empty,
     * a value constructed with the default construct of the element type
     */
    T Dequeue();

    /**
     * Returns a copy of the element at the front of the queue,
     * but does not remove it. If the queue is empty, the value
     * will be the default value for the type.
     * @return element at the front of the queue
     */
    T Front() const;

    /**
     * Removes all elements from the queue. This causes the underlying
     * vector to shrink its capacity, if the queue was not previously
     * empty.
     */
    void Clear();

    /**
     * Checks whether the queue is empty.
     * @return true if and only if the queue is empty
     */
    bool IsEmpty() const;

    /**
     * Gets the queue size.
     * @return number of elements in queue
     */
    size_t Count() const;

private:
    bool circular_;
    std::vector<T> elements_;

    /**
     * Index of the vector element at the front of the queue.
     */
    size_t front_;

    /**
     * Index of the next vector position into which an element will be placed.
     */
    size_t back_;
    size_t count_;

    /**
     * Compacts the vector used to store queue elements if this queue is empty.
     */
    void MaybeResize();

    /**
     * Normalizes the order of elements in the underyling vector. This is
     * only called if this queue is circular, and it only has effect if the
     * queue elements have wrapped around from the last position in the vector
     * to the first.
     * If that is the case, then the elements of the vector are reordered
     * such that the first position in the vector is the front of the queue
     * and the last position in the vector is the back of the queue.
     */
    void NormalizeOrder();
public: // stage: cut
    /**
     * Returns the size of the underlying vector.
     * This is not necessarily the queue size.
     * This function is used internally.
     * @return size of underlying vector
     */
    size_t GetVectorSize() const;

    /**
     * Copies this queue to a vector.
     * @return a vector
     */
    std::vector<T> CopyToVector() const;

};

template<class T>
void VectorQueue<T>::Push(const T &element) {
    if (circular_) {
        if (GetVectorSize() == count_) {
            NormalizeOrder();
            elements_.push_back(element);
        } else {
            if (back_ == elements_.size()) {
                back_ = 0;
            }
            elements_[back_] = element;
        }
    } else {
        elements_.push_back(element);
    }
    back_ = (back_ + 1) % elements_.size();
    count_++;
}

template<class T>
T VectorQueue<T>::Dequeue() {
    T first = Front();
    Pop();
    return first;
}

template <class T>
bool VectorQueue<T>::Pop() {
    if (!IsEmpty()) {
        front_ = (front_ + 1) % elements_.size();
        count_--;
        MaybeResize();
        return true;
    } else {
        return false;
    }
}

template<class T>
void VectorQueue<T>::Clear() {
    elements_.clear();
    front_ = 0;
    back_ = 0;
    count_ = 0;
    MaybeResize();
}

template<class T>
bool VectorQueue<T>::IsEmpty() const {
    return Count() == 0;
}

template<class T>
std::vector<T> VectorQueue<T>::CopyToVector() const {
    std::vector<T> copy;
    copy.reserve(count_);
    for (size_t index = front_; index < elements_.size(); index++) {
        copy.push_back(elements_[index]);
    }
    if (circular_ && back_ <= front_) {
        for (size_t index = 0; index < back_; index++) {
            copy.push_back(elements_[index]);
        }
    }
    return copy;
}

template<class T>
size_t VectorQueue<T>::Count() const {
    return count_;
}

template<class T>
void VectorQueue<T>::MaybeResize() {
    if (IsEmpty()) {
        elements_.clear();
        elements_.shrink_to_fit();
        elements_.reserve(VECTOR_QUEUE_RESET_CAPACITY);
        front_ = 0;
        back_ = 0;
    }
}

template<class T>
size_t VectorQueue<T>::GetVectorSize() const {
    return elements_.size();
}

template<class T>
void VectorQueue<T>::NormalizeOrder() {
    if (!IsEmpty() && back_ <= front_) {
        std::vector<T> new_vector = CopyToVector();
        elements_ = new_vector;
        front_ = 0;
        back_ = elements_.size();
    }
}

template<class T>
T VectorQueue<T>::Front() const {
    if (IsEmpty()) {
        return T();
    }
    T first = elements_[front_];
    return first;
}

#endif //HW16_MAC937_HW16_QUEUE_H
