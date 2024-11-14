#ifndef GAMEOBJECT_SYSTEM_HPP
#define GAMEOBJECT_SYSTEM_HPP

#include "core/game_object/game_object.hpp"
#include "core/system/system.hpp"

#include <map>

class GameObjectSystem : public System {
  public:
    GameObjectSystem(const std::string &name, std::map<uint64_t, GameObject *> &gameobjects);
    void update(float delta_time);

  private:
    std::map<uint64_t, GameObject *> &gameobjects;
};

#endif
