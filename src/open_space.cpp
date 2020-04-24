#include <open_space.hpp>

using namespace Space;
Node::Node() : bud(nullptr), next(nullptr), geolocation(std::move(GeoLocation<float>{0.0f, 0.0f})) {}
Node::Node(Node* bud, Node* next) : bud(bud), next(next), geolocation(std::move(GeoLocation<float>{0.0f, 0.0f})) {}
Node::Node(Node* bud, Node* next, int x) : bud(bud), next(next), geolocation(std::move(GeoLocation<float>{0.0f, 0.0f})) {
  setZone(x);
}

Node::Node(Node* bud, Node* next, int x, GeoLocation<float> location, int id) : bud(bud), next(next), geolocation(location), id(id) {
  setZone(x);
}

void Node::setZone(int z) {
  if (z < 4) {
    zone = Space::zones[z];
  }
}

GeoLocation<float> Node::location() {
  return geolocation;
}

void World::toGeoJSON() {
  std::string geoJSONString{"{\
    \"type\": \"FeatureCollection\",\
  \"features\": ["};
  for (auto& node : nodes) {
    geoJSONString += GeoUtil::geoJSONFeature(node.location(), std::to_string(node.id)) + ",\n";
  }
  geoJSONString.erase(geoJSONString.size() - 2);
  geoJSONString += "]}";
  saveFile(geoJSONString, "nodes.json");
}
