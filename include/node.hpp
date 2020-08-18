#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <geolocation.hpp>
#include <util.hpp>

#define ZONE_A 'A'
#define ZONE_B 'B'
#define ZONE_C 'C'
#define ZONE_D 'D'

#define TIME_COEFFICIENT 4

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

  GeoLocation<float> const location();

  void moveBy(const GeoLocation<float>& delta);

  void setNext(Node* next_);

  void send(std::string message);

  void receive(std::string incoming_message);

  std::string jsonString();

  friend std::ostream &operator<<(std::ostream& out, const Node& node) {
    out << "Location:    " << node.geolocation.longitude() << " longitude   " << node.geolocation.latitude() << " latitude\n" << "Zone: " << node.zone << "\nBud: " << node.bud << "\nNext: " << node.next << std::endl;
    return out;
  }

  int id;

 private:
  Node*               bud;
  Node*               next;
  Zone                zone;
  std::string         message;
  uint32_t            message_time;
  GeoLocation<float>  geolocation;
};
} // namespace Space

#endif //__NODE_HPP__
