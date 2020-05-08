#ifndef HW16_QUEUE_H
#define HW16_QUEUE_H

#include <vector>
#include <cassert>

const size_t VECTOR_QUEUE_RESET_CAPACITY = 10;

/**
 * Queue implementation that uses a vector to store elements.
 * This is a "circular array" implementation, in the Weiss terminology.
 * @tparam T element type
 */
template<class T>
class VectorQueue {
public:
    /**
     * Constructs an instance.
     */
    VectorQueue() : elements_(), start_(0), last_(0), count_(0) {}
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
     * Returns a copy of the element at the front of the queue,
     * but does not remove it. If the queue is empty, the value
     * will be the default value for the type.
     * @return element at the front of the queue
     */
    T Front() const;

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

private:
    std::vector<T> elements_;
    size_t start_;
    size_t last_;
    size_t count_;
    /**
     * Compacts the vector used to store queue elements if this queue is empty.
     */
    void MaybeResize();
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
     * Returns true if the size of the vector is equal to the queue size.
     * @return true if packed
     */
    bool IsPacked() const;

    /**
     * Copies this queue to a vector.
     * @return a vector
     */
    std::vector<T> CopyToVector() const;

};

template<class T>
void VectorQueue<T>::Push(const T &element) {
    if (IsPacked()) {
        NormalizeOrder();
        elements_.push_back(element);
    } else {
        if (last_ == elements_.size()) {
            last_ = 0;
        }
        elements_[last_] = element;
    }
    last_ = (last_ + 1) % elements_.size();
    count_++;
}

template<class T>
T VectorQueue<T>::Pop(bool &valid) {
    if (IsEmpty()) {
        valid = false;
        return T();
    }
    T first = elements_[start_];
    start_ = (start_ + 1) % elements_.size();
    count_--;
    MaybeResize();
    return first;
}

template<class T>
void VectorQueue<T>::Clear() {
    elements_.clear();
    start_ = 0;
    last_ = 0;
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
    copy.reserve(Count());
    for (size_t index = start_; index < elements_.size(); index++) {
        copy.push_back(elements_[index]);
    }
    if (last_ <= start_) {
        for (size_t index = 0; index < last_; index++) {
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
        start_ = 0;
        last_ = 0;
    }
}

template<class T>
T VectorQueue<T>::Pop() {
    bool unused;
    return Pop(unused);
}

template<class T>
bool VectorQueue<T>::IsPacked() const {
    return GetVectorSize() == Count();
}

template<class T>
size_t VectorQueue<T>::GetVectorSize() const {
    return elements_.size();
}

template<class T>
void VectorQueue<T>::NormalizeOrder() {
    if (!IsEmpty() && last_ <= start_) {
        std::vector<T> new_vector = CopyToVector();
        elements_ = new_vector;
        start_ = 0;
        last_ = elements_.size();
    }
}

template<class T>
T VectorQueue<T>::Front() const {
    if (IsEmpty()) {
        return T();
    }
    T first = elements_[start_];
}

#endif //HW16_QUEUE_H
