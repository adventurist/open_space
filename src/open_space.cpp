#include <open_space.hpp>

using namespace Space;

inline void writeNode(Node n) {
  auto location = n.location();
  saveFile(
    std::string{std::to_string(location.longitude()) + ":" + std::to_string(location.latitude())},
    std::string{"node-" + std::to_string(n.id)}
  );
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

uint8_t World::getTime() {
  return time++;
}

void World::tick() {
  auto time = +getTime();
  std::string node_data{};
  node_data.reserve(30 * nodes.size());
  node_data += "{";
  for (auto&& node : nodes) {
    std::cout << "Previous\n" << node << std::endl;
    GeoLocation<float> delta{GeoUtil::getRandom<float>(1.0f, 5.0f), GeoUtil::getRandom<float>(1.0f, 5.0f)};
    node.moveBy(delta);
    node.send(std::string{"Clock " + time});
    std::cout << "Now\n" << node << std::endl;
    node_data += node.jsonString();
    node_data += ",";
  }
  node_data.pop_back();
  node_data += "}";
  saveFile(node_data, "current.json");
  std::cout << "World time: " << time << std::endl;
}
