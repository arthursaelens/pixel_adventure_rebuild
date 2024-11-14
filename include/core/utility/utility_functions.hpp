#ifndef UTILITY_FUNCTIONS_HPP
#define UTILITY_FUNCTIONS_HPP

#include "common.hpp"

#include <string>

class Utility {
  public:
    static uint32_t to_hash(const std::string &key) {
        uint32_t hash = 0;
        for (char c : key) {
            hash += c;
            hash += hash << 10;
            hash ^= hash >> 6;
        }
        hash += hash << 3;
        hash ^= hash >> 11;
        hash += hash << 15;
        return hash;
    };
};

#endif
