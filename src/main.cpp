#include <open_space.hpp>
#include <range.hpp>
#include <util.hpp>
#include <vector>

using namespace Space;
World* world;
void create(void);

int main(int argc, char** argv) {
  world = new World{};
  create();

  for (const auto& node : world->nodes) {
    std::cout << node << "\n\n" << std::endl;
  }

  return 0;
}

void create() {
  world->nodes.clear();
  world->nodes.push_back(Node{});
  for (const auto& i : range<int>{1, 100000}) {
    world->nodes.push_back(Node{
      &world->nodes.at(i - 1),
      &world->master_node,
      getRandom(),
      GeoUtil::getLocation()
    });
  }
}

