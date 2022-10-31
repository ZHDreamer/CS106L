// in case mutliple files in a project include strvector,
// this instruction says only compile this file once!
#ifndef STRVECTOR_H
#define STRVECTOR_H

#include <algorithm>
#include <cstddef>
#include <string>

class StrVector {
    public:
    // type alias (this is how iterator types work!)
    using iterator = std::string*;

    // define an initial size for your underlying array
    const size_t kInitialSize = 2;

    // constructors and destructor
    StrVector();
    StrVector(size_t n, const std::string& val);
    ~StrVector();

    iterator begin();
    iterator end();

    size_t size();
    bool   empty();

    std::string&       at(size_t index);
    std::string&       operator[](size_t index);
    const std::string& operator[](size_t index) const;

    iterator insert(iterator pos, const std::string& elem);
    void     push_back(const std::string& elem);

    private:
    void grow();

    std::string* elems;
    int          logicalSize;
    int          allocatedSize;
};

#endif  // STRVECTOR_H
