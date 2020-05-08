#ifndef HW16_MAC937_STACK_H
#define HW16_MAC937_STACK_H

#include <cassert>
#include <vector>
#include <iostream>

template<class T>
struct StackNode {
public:
    StackNode(const T& content, StackNode<T>* under) : content(content), under(under) {}
    T content;
    StackNode<T>* under;
};

template<class T>
class Stack {
public:
    Stack() : top_(nullptr) {}
    ~Stack();
    void Push(const T& element);
    T Pop(bool& valid);
    T Pop();
    void Clear();
    bool IsEmpty() const;
    std::vector<T> CopyToVector() const;
    Stack(Stack<T>& other);
private:
    StackNode<T>* top_;
    Stack<T>& operator=(const Stack<T>& other);
};

template<class T>
Stack<T>::~Stack() {
    Clear();
}

template<class T>
void Stack<T>::Push(const T &element) {
    StackNode<T>* new_top = new StackNode<T>(element, top_);
    top_ = new_top;
}

template<class T>
T Stack<T>::Pop(bool& valid) {
    if (top_ == nullptr) {
        valid = false;
        return T();
    }
    valid = true;
    StackNode<T>* top = top_;
    T top_value = top->content;
    top_ = top->under;
    delete top;
    return top_value;
}

template<class T>
T Stack<T>::Pop() {
    bool valid;
    return Pop(valid);
}

template<class T>
void Stack<T>::Clear() {
    while (top_ != nullptr) {
        StackNode<T>* top = top_;
        top_ = top->under;
        delete top;
    }
}

template<class T>
bool Stack<T>::IsEmpty() const {
    return top_ == nullptr;
}

template<class T>
std::vector<T> Stack<T>::CopyToVector() const {
    std::vector<T> items;
    for (StackNode<T>* current = top_; current != nullptr; current = current->under) {
        items.push_back(current->content);
    }
    return items;
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if (this == &other) {
        return *this;
    }
    Clear();
    Stack<T> temp;
    for (StackNode<T>* current = other.top_; current != nullptr; current = current->under) {
        temp.Push(current->content);
    }
    for (StackNode<T>* current = temp.top_; current != nullptr; current = current->under) {
        Push(current->content);
    }
    return *this;
}

template<class T>
Stack<T>::Stack(Stack<T> &other) {
    *this = other;
}


#endif //HW16_MAC937_STACK_H
