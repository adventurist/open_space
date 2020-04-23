#include <open_space.hpp>

using namespace Space;
Node::Node() : bud(nullptr), next(nullptr) {}
Node::Node(Node* bud, Node* next) : bud(bud), next(next) {}
Node::Node(Node* bud, Node* next, int x) : bud(bud), next(next) {
  setZone(x);
}

void Node::setZone(int z) {
  if (z < 4) {
    zone = Space::zones[z];
  }
}

