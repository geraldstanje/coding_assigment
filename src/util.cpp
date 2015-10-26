#include "util.h"
#include <iostream>
#include <algorithm>

bool is_alpha(const char &ch) {
    if (!((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A'))) {
        return false;
    }
    return true;
}

void print(std::vector<uint16_t> &vec) {
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<uint16_t>(std::cout));
}

void split(std::string::iterator begin, std::string::iterator end, std::vector<std::string> &out) {
    auto start = begin;

    for (auto it = begin; it != end; it++) {
        if (it+1 == end) {
            out.insert(out.end(), {start, it+1});
        } else if (*it == ',') {
            out.insert(out.end(), {start, it});
            start = it+1;
        }
    }
}