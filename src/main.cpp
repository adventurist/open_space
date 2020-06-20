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
void run(uint32_t lifecycle = INT32_MAX);

int main(int argc, char** argv) {
  world = new World{};

  if (argc > 1 && strcmp(argv[1], "--daemon") == 0) {
    std::thread world_thread{run, INT32_MAX};

    while (world != nullptr) {
      continue;
    }

    if (world_thread.joinable()) {
      world_thread.join();
    }
  }
  run(1);

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

void run(uint32_t lifecycle) {
  World active_world = create(world);
  uint32_t world_index = 0;
  while (world_index++ < lifecycle) {
    active_world.tick();
    active_world.toGeoJSON();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  }
  delete world;
  world = nullptr;
}
