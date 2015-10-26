#include "trie.h"
#include "util.h"
#include <iostream>
#include <cassert>
#include <cstdint>

//#define DEBUG

trie::trie(): size_(0), prev_search_(false) {
    root_ = create_node();
    iter_ = nullptr;
}

trie::~trie() {
    erase();
}

uint16_t trie::size() const {
    return size_;
}

node *trie::create_node() {
    node *n = new node;
    return n;
}

void trie::delete_node(node *n) {
    for (uint16_t i = 0; i < ALPHABET_SIZE; i++) {
        if (n->next_[i] != nullptr) {
            delete_node(n->next_[i]);
        }
    }

    delete n;
}

void trie::erase() {
    delete_node(root_);
    root_ = nullptr;
    iter_ = nullptr;
    size_ = 0;
}

bool trie::insert(const std::string key, const int16_t value) {
    node *tmp = root_;

    for (uint16_t i = 0; i < key.size(); i++) {
        char k = 0;

        if (!calc_node_index(key[i], k)) {
            return false;
        }

        if (tmp->next_[k] == nullptr) {
            tmp->next_[k] = create_node();
        }

        tmp->is_end_ = false;
        tmp = tmp->next_[k];
    }

    tmp->is_terminal_ = true;
    tmp->is_end_ = true;
    tmp->value_ = value;
    size_++;
    iter_ = root_;
    return true;
}

// this lookup function uses a pointer called iter_ to store the current trie node, if a key was found in the trie
// in this way we do not start searching from the top of the trie
// if the prev_search_, which is set by exists_key_store_iter did not return a key, the iter_ will be set to the top of the root
// this function returns true, if a key was found. here we differ between two cases
// 1.) terminal found (value_ >= 0)
// 2.) terminal not found (value_ = -1)
// and returns false, if the key was not found, the keyword search takes the next letter in the url string
bool trie::exists_key(std::string::const_iterator begin, std::string::const_iterator end, int16_t &value) {
    if (!prev_search_) {
        iter_ = root_;
    }

    if (iter_ == nullptr) {
        return false;
    }

    for (auto it = begin; it != end; it++) {
        char k = 0;

        if (!calc_node_index(*it, k)) {
            return false;
        }

#ifdef DEBUG
        std::cout << "current trie node: " << *it << std::endl;
#endif

        if (iter_->next_[k] != nullptr) {
            iter_ = iter_->next_[k];
        } else {
            return false; // key not found
        }
    }

    if (iter_ == nullptr) {
        return false;
    } else if (iter_->is_terminal_) {
        value = iter_->value_;
        return true;
    }

    // we found the key in the trie but its not a terminal
    value = -1;
    return true;
}

bool trie::exists_key_store_iter(std::string::const_iterator begin, std::string::const_iterator end, int16_t &value) {
    prev_search_ = exists_key(begin, end, value);
    return prev_search_;
}