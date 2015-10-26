#include "keyword_matcher.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdint>

keyword_matcher::keyword_matcher(): bag_of_words_size_(0) {
}

bool keyword_matcher::load_bag_of_words(const std::string &filename) {
    std::ifstream file;
    file.open(filename.c_str(), std::ios::in);

    if(!file.is_open()) {
        std::cerr << "file not found" << '\n';
        return false;
    }

    std::string str;
    std::string file_contents;
    while (std::getline(file, str)) {
        trie_.insert(str, bag_of_words_size_);
        bag_of_words_size_++;
    }

    // close file
    file.close();
    return true;
}

void keyword_matcher::load_bag_of_words(const std::vector<std::string> &bag_of_words) {
    if (bag_of_words_size_ > 0) {
        trie_.erase();
        bag_of_words_size_ = 0;
    }

    for (auto i = 0; i < bag_of_words.size(); i++) {
        trie_.insert(bag_of_words[i], i);
        bag_of_words_size_++;
    }
}

std::vector<uint16_t> keyword_matcher::match_keywords(const std::string &url) {
#ifdef BENCHMARKING
    auto start = std::chrono::steady_clock::now();
#endif

    std::vector<uint16_t> vec(bag_of_words_size_, 0);
    uint16_t offset = 0;
    int16_t index = 0;

    for (uint16_t start = 0; start < url.size(); start++) {
        offset = 0;

        for (uint16_t len = 1; len <= url.size() - start; len++) {
            index = 0;

            bool key_exists = trie_.exists_key_store_iter(url.begin() + start + offset, url.begin() + start + len, index);
            if (key_exists && index != -1) {
                vec[index] = 1;
            }

            if (!key_exists) {
                break;
            }

            offset = len;
        }
    }

#ifdef BENCHMARKING
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cerr << std::chrono::duration <double, std::milli> (diff).count() << '\n';
#endif

    return vec;
}