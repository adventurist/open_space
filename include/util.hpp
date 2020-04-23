#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <random>
#include <string>
#include <fstream>


inline int getRandom() {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(1, 4);
  return dist(mt);
}

inline std::string getCWD() {
  char *working_dir_path = realpath(".", NULL);
  return std::string{working_dir_path};
}

inline void saveFile(std::string file_string, std::string filename) {
  std::string file_path{"/tmp/" + filename};
  std::ofstream out{file_path.c_str()};
  out << file_string;
}

#endif  // __UTIL_HPP__

