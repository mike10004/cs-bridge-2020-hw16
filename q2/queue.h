#ifndef HW16_QUEUE_H
#define HW16_QUEUE_H

#include <vector>
#include <cassert>

const size_t VECTOR_QUEUE_RESET_CAPACITY = 10;

/**
 * Queue implementation that uses a vector to store elements.
 * @tparam T
 */
template<class T>
class VectorQueue {
public:
    VectorQueue() : elements_(), start_(0) {}
    /**
     * Adds an element to the queue.
     * @param element element
     */
    void Push(const T& element);
    /**
     * Removes an element from the queue.
     * @param valid flag that indicates whether removal succeeded; if queue is empty, this will be set to false
     * @return the first element in the queue, or if the queue is empty,
     * a value constructed with the default construct of the element type
     */
    T Pop(bool& valid);
    /**
     * Removes an element from the queue.
     * @return the first element in the queue, or if the queue is empty,
     * a value constructed with the default construct of the element type
     */
    T Pop();

    /**
     * Removes all elements from the queue.
     */
    void Clear();

    /**
     * Checks whether the queue is empty.
     * @return true if and only if the queue is empty
     */
    bool IsEmpty() const;

    /**
     * Get the queue size.
     * @return queue size
     */
    size_t Count() const;

    /**
     * Copies this queue to a vector.
     * @return a vector
     */
    std::vector<T> CopyToVector() const;
private:
    std::vector<T> elements_;
    size_t start_;
    /**
     * Compacts the vector used to store queue elements if this queue is empty.
     */
    void MaybeResize();
};

template<class T>
void VectorQueue<T>::Push(const T &element) {
    elements_.push_back(element);
}

template<class T>
T VectorQueue<T>::Pop(bool &valid) {
    if (IsEmpty()) {
        valid = false;
        return T();
    }
    T first = elements_[start_];
    start_++;
    MaybeResize();
    return first;
}

template<class T>
void VectorQueue<T>::Clear() {
    elements_.clear();
    start_ = 0;
    MaybeResize();
}

template<class T>
bool VectorQueue<T>::IsEmpty() const {
    return Count() == 0;
}

template<class T>
std::vector<T> VectorQueue<T>::CopyToVector() const {
    std::vector<T> copy;
    copy.reserve(Count());
    for (size_t index = start_; index < elements_.size(); index++) {
        copy.push_back(elements_[index]);
    }
    return copy;
}

template<class T>
size_t VectorQueue<T>::Count() const {
    return elements_.size() - start_;
}

template<class T>
void VectorQueue<T>::MaybeResize() {
    if (IsEmpty()) {
        elements_.clear();
        elements_.shrink_to_fit();
        elements_.reserve(VECTOR_QUEUE_RESET_CAPACITY);
        start_ = 0;
    }
}

template<class T>
T VectorQueue<T>::Pop() {
    bool unused;
    return Pop(unused);
}

#endif //HW16_QUEUE_H
