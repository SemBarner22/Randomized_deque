#pragma once


#include <glob.h>
#include "list"

template <typename T>
struct deque {
public:

    typedef typename std::list<T>::iterator iterator;

    iterator begin();

    iterator end();

    deque() = default;

    ~deque() = default;

    size_t size() const;

    bool empty() const;

    void push_back(const T&);

    void push_front(const T&);

    T& front() const;

    T& back() const;

    void pop_back();

    void pop_front();

private:
    std::list<T> list_;
};

template<typename T>
void deque<T>::pop_back() {
    list_.pop_back();
}

template<typename T>
void deque<T>::pop_front() {
    list_.pop_front();
}

template<typename T>
void deque<T>::push_back(const T& elem) {
    list_.push_back(elem);
}

template<typename T>
size_t deque<T>::size() const {
    return list_.size();
}

template<typename T>
void deque<T>::push_front(const T& elem) {
    list_.push_front(elem);
}

template<typename T>
T& deque<T>::front() const {
    return list_.front();
}

template<typename T>
T& deque<T>::back() const {
    return list_.back();
}

template<typename T>
bool deque<T>::empty() const {
    return list_.empty();
}

template <typename T>
typename std::list<T>::iterator deque<T>::begin() {
    return list_.begin();
}

template <typename T>
typename std::list<T>::iterator deque<T>::end() {
    return list_.end();
}