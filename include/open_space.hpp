#ifndef __OPEN_SPACE_HPP__
#define __OPEN_SPACE_HPP__

#include <iostream>
#include <vector>
#include <geolocation.hpp>

#define ZONE_A 'A'
#define ZONE_B 'B'
#define ZONE_C 'C'
#define ZONE_D 'D'

using Zone = char;

namespace Space {
inline Zone zones[4] = {ZONE_A, ZONE_B, ZONE_C, ZONE_D};

class Node {
 public:
  Node();
  Node(Node* bud, Node* next);
  Node(Node* bud, Node* next, int x);
  Node(Node* bud, Node* next, int x, GeoLocation<float> location);

  void setZone(int z);

  friend std::ostream &operator<<(std::ostream& out, const Node& node) {
    out << "Location:    " << node.geolocation.longitude << " longitude   " << node.geolocation.latitude << " latitude\n" << "Zone: " << node.zone << "\nBud: " << node.bud << "\nNext: " << node.next << std::endl;
    return out;
  }


 private:
  Node* bud;
  Node* next;
  Zone zone;
  GeoLocation<float> geolocation;
};

class World {
 public:
  Node master_node;
  std::vector<Node> nodes;
};
}  // namespace Space
#endif  // __OPEN_SPACE_HPP__
