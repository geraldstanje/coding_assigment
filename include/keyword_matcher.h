#ifndef KEYWORD_MATCHER_H
#define KEYWORD_MATCHER_H

#include "trie.h"
#include <vector>
#include <cstdint>

class keyword_matcher {
  private:
    uint16_t bag_of_words_size_;
    trie trie_; // stores the keyword as a key + index as a value, the index refers to the bag_of_words vector index

  public:
    keyword_matcher();
    bool load_bag_of_words(const std::string &filename);
    void load_bag_of_words(const std::vector<std::string> &bag_of_words);
    std::vector<uint16_t> match_keywords(const std::string &url);
};

#endif