#include "trie.h"
#include "keyword_matcher.h"
#include <cassert>
#include <iostream>
#include <vector>

class test_data {
  public:
    std::string key_;
    int16_t value_;
    test_data(std::string key, int16_t value): key_(key), value_(value) {}
};

bool compare(const std::vector<uint16_t> &vec1, const std::vector<uint16_t> &vec2) {
    if (vec1.size() != vec2.size()) {
        return false;
    }

    for (int i = 0; i < vec1.size(); i++) {
        if (vec1[i] != vec2[i]) {
            return false;
        }
    }

    return true;
}
int main() {
    // unit test for trie
    trie t;

    std::vector<test_data> test_set = {{"hello", 2},
        {"he", 33},
        {"hel", 333},
        {"bi", 3},
        {"help", 1},
        {"bmw", 55},
        {"porsche", 1000}
    };
    int16_t index = 0;

    for (int i = 0; i < test_set.size(); i++) {
        t.insert(test_set[i].key_, test_set[i].value_);
    }

    for (int i = 0; i < test_set.size(); i++) {
        assert(t.exists_key(test_set[i].key_.begin(), test_set[i].key_.end(), index) == true);
        assert(index == test_set[i].value_);
    }

    assert(t.exists_key_store_iter(test_set[1].key_.begin(), test_set[1].key_.end(), index) == true);
    assert(index == test_set[1].value_);

    std::string str = "hel";
    assert(t.exists_key_store_iter(str.begin(), str.end(), index) == false);

    str = "bm";
    assert(t.exists_key_store_iter(str.begin(), str.end(), index) == true);
    assert(index == -1);

    // unit test for keyword_matcher
    keyword_matcher m;

    m.load_bag_of_words(std::vector<std::string> {"he", "hel", "hi", "be"});
    auto vec = m.match_keywords("http://hello.com");
    assert(compare(vec, std::vector<uint16_t> {1,1,0,0}) == true);

    vec = m.match_keywords("http://hellobello.com");
    assert(compare(vec, std::vector<uint16_t> {1,1,0,1}) == true);

    return 0;
}