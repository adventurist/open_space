#include <open_space.hpp>
#include <range.hpp>
#include <util.hpp>
#include <vector>
#include <thread>
#include <chrono>
#include <cstring>

using namespace Space;
World* world;
void create(void);
void run(void);

int main(int argc, char** argv) {
  if (argc > 1 && strcmp(argv[1], "--daemon") == 0) {
    for (;;) {
      run();
      std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
  } else {
     run();
  }
  return 0;
}

World create(World* world) {
  world->nodes.clear();
  world->nodes.push_back(Node{});
  for (const auto& i : range<int>{1, 100}) {
    world->nodes.push_back(Node{
      &world->nodes.at(i - 1),
      &world->master_node,
      getRandom(),
      GeoUtil::getLocation(),
      i
    });
  }
  return std::move(*world);
}

void run() {
  world = new World{};
  World active_world = create(world);
  for (;;) {
    active_world.tick();
    active_world.toGeoJSON();
  }
  delete world;
}
