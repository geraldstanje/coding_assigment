#ifndef TRIE_H
#define TRIE_H

#include "node.h"
#include <string>
#include <cstdint>

class trie {
  private:
    node *root_;
    node *iter_;
    uint16_t size_;
    bool prev_search_;

  private:
    node *create_node();
    void delete_node(node *n);

  public:
    trie();
    ~trie();
    void erase();
    uint16_t size() const;
    bool insert(const std::string key, const int16_t value);
    bool exists_key(std::string::const_iterator begin, std::string::const_iterator end, int16_t &value);
    bool exists_key_store_iter(std::string::const_iterator begin, std::string::const_iterator end, int16_t &value);
};

#endif