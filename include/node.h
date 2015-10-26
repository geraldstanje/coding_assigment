#ifndef NODE_H
#define NODE_H

#include <unordered_map>
#include <cstdint>

const uint16_t ALPHABET_SIZE = 28;

class node {
  public:
    int16_t value_;
    node *next_[ALPHABET_SIZE];
    bool is_terminal_;
    bool is_end_;
    node();
};

const std::unordered_map<char, char> special_chars = {{'_', 26},
    {'-', 27}
};

bool calc_node_index(const char &key, char &index);

#endif