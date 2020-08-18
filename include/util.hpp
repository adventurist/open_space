#ifndef __UTIL_HPP__
#define __UTIL_HPP__

#include <random>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <range.hpp>


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

inline void saveFile(std::string file_string, std::string filename, std::string directory = "/tmp/") {
  std::string file_path{directory + filename};
  std::ofstream out{file_path.c_str()};
  out << file_string;
}

inline std::vector<std::string> readNodes() {
  std::vector<std::string> node_data{100};
  std::stringstream env_file_stream{};
  for (auto i = 0; i < 100; i++) {
    std::ifstream file_stream{"/tmp/nodes/node" + std::to_string(i)};
    env_file_stream << file_stream.rdbuf();
    node_data.push_back(env_file_stream.str());
    env_file_stream.clear();
  }
  return node_data;
}

inline std::string fetchNodes() {
  std::stringstream env_file_stream{};
  std::ifstream file_stream{"/tmp/current.json"};
  env_file_stream << file_stream.rdbuf();
  return env_file_stream.str();
}
#endif  // __UTIL_HPP__

