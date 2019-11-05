#pragma once


#include <glob.h>
#include "vector"
#include "random"

template <typename T>
struct randomized_queue;


template <typename T>
struct randomized_queue_iterator {
public:

    using iterator_category = std::bidirectional_iterator_tag;

    using value_type = T;

    using difference_type = ptrdiff_t;

    using pointer = T*;

    using reference = T&;

    randomized_queue_iterator(randomized_queue<T> *, int);

    T& operator*();

    randomized_queue_iterator<T> &operator++();

    randomized_queue_iterator<T> &operator--();

    randomized_queue_iterator<T> operator++(int);

    randomized_queue_iterator<T> operator--(int);

    bool operator!=(const randomized_queue_iterator<T>&);

    bool operator==(const randomized_queue_iterator<T>&);


private:
    size_t pos_;
    randomized_queue<T> *queue_;
    std::vector<T> permutation_;
};

template<typename T>
randomized_queue_iterator<T> &randomized_queue_iterator<T>::operator++() {
    pos_++;
    return *this;
}

template<typename T>
randomized_queue_iterator<T> &randomized_queue_iterator<T>::operator--() {
    pos_--;
    return *this;
}

template<typename T>
randomized_queue_iterator<T> randomized_queue_iterator<T>::operator++(int){
    randomized_queue_iterator<T> it = *this;
    ++*this;
    return it;
}

template<typename T>
randomized_queue_iterator<T> randomized_queue_iterator<T>::operator--(int) {
    randomized_queue_iterator<T> it = *this;
    --*this;
    return it;
}

template<typename T>
T &randomized_queue_iterator<T>::operator*() {
    return permutation_[pos_];
}

template<typename T>
randomized_queue_iterator<T>::randomized_queue_iterator(randomized_queue<T> * q, int index) {
    this->queue_ = q;
    this->pos_ = index;
    permutation_ = q->vec_;
    int size_ = q->size();
    for (int i = size_ - 1; i > 0; --i) {
        std::random_device rd;
        std::mt19937 mersenne(rd());
        int j = mersenne() % i;
        std::swap(permutation_[i], permutation_[j]);
    }
}

template<typename T>
bool randomized_queue_iterator<T>::operator==(const randomized_queue_iterator<T> & it) {
    if (pos_ == queue_->size())
        return pos_ == it.pos_ && queue_ == it.queue_;
    if (pos_ == 0)
        return pos_ == it.pos_ && queue_ == it.queue_;
    return pos_ == it.pos_ && queue_ == it.queue_ && permutation_ == it.permutation_;
}

template<typename T>
bool randomized_queue_iterator<T>::operator!=(const randomized_queue_iterator<T> & it) {
    return !(*this == it);
}


template <typename T>
struct randomized_queue {
public:

    typedef randomized_queue_iterator<T> iterator;

    iterator end();

    iterator begin();

    randomized_queue() = default;

    size_t size() const;

    bool empty() const;

    T& sample() const;

    void enqueue(const T&);

    T& front() const;

    T& back() const;

    T& dequeue();

private:

    std::vector<T> vec_;

    friend struct randomized_queue_iterator<T>;
};

template<typename T>
T& randomized_queue<T>::dequeue() {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    int j = mersenne() % size();
    std::swap(vec_[size() - 1], vec_[j]);
    T& res = vec_[size() - 1];
    vec_.pop_back();
    return res;
}

template<typename T>
size_t randomized_queue<T>::size() const {
    return vec_.size();
}

template<typename T>
void randomized_queue<T>::enqueue(const T& elem) {
    vec_.push_back(elem);
}

template<typename T>
T& randomized_queue<T>::front() const {
    return vec_.front();
}

template<typename T>
T& randomized_queue<T>::back() const {
    return vec_.back();
}

template<typename T>
bool randomized_queue<T>::empty() const {
    return vec_.empty();
}

template<typename T>
T &randomized_queue<T>::sample() const {
    std::random_device rd;
    std::mt19937 mersenne(rd());
    int j = mersenne() % size();
    return vec_[j];
}

template<typename T>
typename randomized_queue<T>::iterator randomized_queue<T>::end() {
    return randomized_queue::iterator(this, size());
}

template<typename T>
typename randomized_queue<T>::iterator randomized_queue<T>::begin() {
    return randomized_queue::iterator(this, 0);
}

