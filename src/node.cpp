#include <node.hpp>

namespace Space {
Node::Node()
: bud(nullptr),
  next(nullptr),
  geolocation(std::move(GeoLocation<float>{0.0f, 0.0f})) {}

Node::Node(Node* bud, Node* next)
: bud(bud),
  next(next),
  geolocation(std::move(GeoLocation<float>{0.0f, 0.0f})) {}

Node::Node(Node* bud, Node* next, int x)
: bud(bud),
  next(next),
  geolocation(std::move(GeoLocation<float>{0.0f, 0.0f})) {
    setZone(x);
  }

Node::Node(Node* bud, Node* next, int x, GeoLocation<float> location, int id)
: bud(bud),
  next(next),
  geolocation(location), id(id) {
    setZone(x);
  }

void Node::setZone(int z) {
  if (z < 4) {
    zone = Space::zones[z];
  }
}

void Node::setNext(Node* next_) {
  next = next_;
}

void Node::send(std::string outgoing_message) {
  auto delta = GeoLocation<float>::measureDistance(location(), next->location());
  auto distance = delta.latitude() + delta.longitude();
  message_time = +distance * TIME_COEFFICIENT;

  next->receive(outgoing_message);
}

void Node::receive(std::string incoming_message) {
  message = incoming_message;
}

void Node::moveBy(const GeoLocation<float>& delta) {
  geolocation + delta;
}

std::string Node::jsonString() {
  return std::string{
    std::to_string(id) + ":[" +
    std::to_string(geolocation.longitude()) + "," +
    std::to_string(geolocation.latitude()) + "]"
  };
}

GeoLocation<float> const Node::location () {
  return geolocation;
}

} // namespace Space
