#include <open_space.hpp>

using namespace Space;
Node::Node() : bud(nullptr), next(nullptr), geolocation(std::move(GeoLocation<float>{0.0f, 0.0f})) {}
Node::Node(Node* bud, Node* next) : bud(bud), next(next), geolocation(std::move(GeoLocation<float>{0.0f, 0.0f})) {}
Node::Node(Node* bud, Node* next, int x) : bud(bud), next(next), geolocation(std::move(GeoLocation<float>{0.0f, 0.0f})) {
  setZone(x);
}

Node::Node(Node* bud, Node* next, int x, GeoLocation<float> location) : bud(bud), next(next), geolocation(location) {
  setZone(x);
}

void Node::setZone(int z) {
  if (z < 4) {
    zone = Space::zones[z];
  }
}

