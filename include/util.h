#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <cstdint>
#include <string>

bool is_alpha(const char &ch);
void print(std::vector<uint16_t> &vec);
void split(std::string::iterator begin, std::string::iterator end, std::vector<std::string> &out);

#endif