#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "app/component/background_renderer.hpp"
#include "app/game_object/bee.hpp"
#include "app/game_object/character.hpp"
#include "app/game_object/enemy.hpp"
#include "app/game_object/mush.hpp"
#include "app/game_object/pickup.hpp"
#include "app/game_object/tile.hpp"
#include "app/game_object/trunk.hpp"
#include "app/utility/debug_mode.hpp"
#include "app/utility/level_mapper.hpp"
#include "core/component/component.hpp"
#include "core/engine.hpp"

#include <string>
#include <vector>

class Level : public GameObject {
  private:
    BackgroundRenderer *bgr;
    std::vector<std::vector<std::string>> levelData;
    Vector2 startPoint;
    LevelMapper &lm;

    std::vector<Tile *> tiles;
    std::vector<Pickup *> pickups;
    
    Mush* mushy;
    Trunk* trunky;
    Bee* beee;

  public:
    Character *player;
    int levelId;

    void update(float delta_time);
    Level(const std::string &levelFileLocation, const DebugInfo &debug_info);
    void loadLevel(const std::string &levelFileLocation, std::vector<Tile *> &tiles, const LevelMapper &levelMapper, const DebugInfo &debug_info);
    bool killLevel = false;
    void unloadLevel();
};

#endif // LEVEL_HPP
