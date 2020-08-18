#ifndef __OPEN_SPACE_HPP__
#define __OPEN_SPACE_HPP__

#include <iostream>
#include <node.hpp>

namespace Space {
class World {
 public:
  void toGeoJSON();
  Node master_node;
  std::vector<Node> nodes;
  void tick();
 private:
  uint8_t getTime();
  uint8_t time = 0;
};


}  // namespace Space
#endif  // __OPEN_SPACE_HPP__
