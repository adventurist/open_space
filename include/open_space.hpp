#ifndef __OPEN_SPACE_HPP__
#define __OPEN_SPACE_HPP__

#include <iostream>
#include <vector>
#include <geolocation.hpp>
#include <util.hpp>

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
  Node(Node* bud, Node* next, int x, GeoLocation<float> location, int id);

  void setZone(int z);

  GeoLocation<float> location();
  void moveBy(GeoLocation<float> delta);

  friend std::ostream &operator<<(std::ostream& out, const Node& node) {
    out << "Location:    " << node.geolocation.longitude << " longitude   " << node.geolocation.latitude << " latitude\n" << "Zone: " << node.zone << "\nBud: " << node.bud << "\nNext: " << node.next << std::endl;
    return out;
  }

  int id;

 private:
  Node* bud;
  Node* next;
  Zone zone;
  GeoLocation<float> geolocation;
};

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
