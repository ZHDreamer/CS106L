#ifndef RealVector_H
#define RealVector_H

#include <algorithm>
#include <string>

template<class T>
class RealVector {
    public:
    // type aliases: this is how the iterator type works! This defines
    // RealVector::iterator
    using iterator = T*;
    using const_iterator = const T*;

    // initial size for our underlying array
    const size_t kInitialSize = 2;
    // constructors
    RealVector();
    RealVector(size_t n, const T& val);
    // destructor
    ~RealVector();

    // interface
    size_t size() const;
    bool   empty() const;

    T& operator[](size_t index);
    T& at(size_t index);

    void insert(size_t pos, const T& elem);
    void push_back(const T& elem);

    // don't forget about accessing iterators!
    iterator       begin();
    const_iterator cbegin() const;
    iterator       end();
    const_iterator cend() const;

    // EXERCISE: add remove!

    private:
    void grow();
    // array where we store our elements
    T* elems;
    // number of elements in our vector
    size_t logical_size;
    // total capacity of underlying array
    size_t array_size;
};

#include "realvector.cpp"

#endif  // RealVector_H