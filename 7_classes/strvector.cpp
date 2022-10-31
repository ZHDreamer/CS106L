// dont forget to include the .h file!
// implementation for strvector.cpp goes here!
#include "strvector.h"

#include <algorithm>
#include <cstddef>
#include <stdexcept>

StrVector::StrVector() : logicalSize(0), allocatedSize(kInitialSize) {
    elems = new std::string[allocatedSize];
}

StrVector::StrVector(size_t n, const std::string& val) :
    logicalSize(n), allocatedSize(2 * n) {
    elems = new std::string[allocatedSize];
    std::fill(begin(), end(), val);
}

StrVector::~StrVector() {
    delete[] elems;
}

StrVector::iterator StrVector::begin() {
    return elems;
}

StrVector::iterator StrVector::end() {
    return begin() + size();
}

size_t StrVector::size() {
    return logicalSize;
}

bool StrVector::empty() {
    return size() == 0;
}

std::string& StrVector::at(size_t index) {
    if (index >= size()) {
        throw std::out_of_range("Out of bounds access of vector");
    }
    return *(begin() + index);
}

std::string& StrVector::operator[](size_t index) {
    return *(begin() + index);
}

StrVector::iterator StrVector::insert(iterator pos, const std::string& elem) {
    int index = pos - begin();
    if (allocatedSize == size()) {
        grow();
    }
    pos = index + begin();
    std::copy_backward(pos, end(), end() + 1);
    *pos = elem;
    ++logicalSize;
    return pos;
}

void StrVector::push_back(const std::string& elem) {
    insert(end(), elem);
}

void StrVector::grow() {
    iterator new_elems = new std::string[2 * allocatedSize];
    std::copy(begin(), end(), new_elems);
    delete[] elems;
    allocatedSize *= 2;
    elems = new_elems;
}