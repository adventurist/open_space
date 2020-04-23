#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <random>

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(1, 4);

int getRandom() { return dist(mt); }

#endif  // __UTIL_HPP__

