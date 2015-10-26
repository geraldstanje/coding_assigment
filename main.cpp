#include "keyword_matcher.h"
#include "util.h"
#include <cassert>
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>

class argument_parser {
  public:
    std::string url_;
    std::string bag_of_words_path_;
    std::vector<std::string> bag_of_words_;
    bool bag_of_words_from_file;
    bool bag_of_words_from_cmd;

    argument_parser(): bag_of_words_from_file(false), bag_of_words_from_cmd(false) {}
    void parse(std::vector<std::string> allArgs) {
        for (uint16_t i = 1; i < allArgs.size(); i++) {
            if (allArgs[i-1] == "-u") {
                url_ = allArgs[i];
            } else if (allArgs[i-1] == "-f") {
                bag_of_words_path_ = allArgs[i];
                bag_of_words_from_file = true;
            } else if (allArgs[i-1] == "-s") {
                split(allArgs[i].begin(), allArgs[i].end(), bag_of_words_);
                bag_of_words_from_cmd = true;
            }
        }
    }
    bool parse_success() {
        if (url_.empty()) {
            return false;
        } else if (bag_of_words_path_.empty() && bag_of_words_.empty()) {
            return false;
        }
        return true;
    }
};

int main(int argc, char *argv[]) {
    std::vector<std::string> allArgs(argv, argv + argc);

    if (allArgs.size() < 2) {
        std::cerr << "usage: "<< allArgs[0] << " [-u URL] [-s bag of words string] [-f bag_of_words_file]\n";
        return -1;
    }

    argument_parser a;
    a.parse(allArgs);
    if (!a.parse_success()) {
        return -1;
    }

    keyword_matcher m;

    if (a.bag_of_words_from_file) {
        if (!m.load_bag_of_words(a.bag_of_words_path_)) {
            return -1;
        }
    } else if (a.bag_of_words_from_cmd) {
        m.load_bag_of_words(a.bag_of_words_);
    }

    auto vec = m.match_keywords(a.url_);
    print(vec);

    return 0;
}