#include "realvector.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>

template<class T>
RealVector<T>::RealVector() : logical_size(0), array_size(kInitialSize) {
    elems = new T[array_size];
}

template<class T>
RealVector<T>::RealVector(size_t n, const T& val) : logical_size(n), array_size(n) {
    elems = new T[array_size];
    std::fill(begin(), end(), val);
}

template<class T>
RealVector<T>::~RealVector() {
    delete[] elems;
}

template<class T>
size_t RealVector<T>::size() const {
    return logical_size;
}

template<class T>
bool RealVector<T>::empty() const {
    return size() == 0;
}

template<class T>
T& RealVector<T>::operator[](size_t index) {
    return *(begin() + index);
}

template<class T>
T& RealVector<T>::at(size_t index) {
    if (index >= logical_size) {
        throw std::out_of_range("Out of bounds access of vector");
    }
    return *(begin() + index);
}

template<class T>
void RealVector<T>::insert(size_t pos, const T& elem) {
    if (pos > size()) {
        throw std::out_of_range("Out of bounds access of vector");
    }
    if (logical_size == array_size) {
        grow();
    }
    std::move_backward(begin() + pos, end(), end() + 1);
    elems[pos] = elem;
    ++logical_size;
}

template<class T>
void RealVector<T>::push_back(const T& elem) {
    insert(end(), elem);
}

template<class T>
typename RealVector<T>::iterator RealVector<T>::begin() {
    return elems;
}

template<class T>
typename RealVector<T>::const_iterator RealVector<T>::cbegin() const {
    return elems;
}

template<class T>
typename RealVector<T>::iterator RealVector<T>::end() {
    return begin() + size();
}

template<class T>
typename RealVector<T>::const_iterator RealVector<T>::cend() const {
    return cbegin() + size();
}

template<class T>
void RealVector<T>::grow() {
    array_size *= 2;
    T* new_elems = new T[array_size];
    std::copy(begin(), end(), new_elems);
    delete[] elems;
    elems = new_elems;
}