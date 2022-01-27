#ifndef STRING_SHARED_PTR_H_
#define STRING_SHARED_PTR_H_

#include "string.hpp"
class string_shared_ptr {
    public:
        string_shared_ptr(int* ptr);
        string_shared_ptr(const string_shared_ptr &source_ptr);
        void reset();
        void operator->();
        ~string_shared_ptr();
};

#endif