#ifndef COLLISION_SYSTEM_HPP
#define COLLISION_SYSTEM_HPP

#include "app/component/collider.hpp"
#include "common.hpp"
#include "core/system/system.hpp"
#include <vector>

class CollisionSystem : public System {
  public:
    CollisionSystem(const std::string &name);
    virtual ~CollisionSystem() = default;
    // functie die checked langs welke kant er collision is

    int deadEnemies = 0;

    void update(float delta_time) override;

    virtual std::string checkCollision(Rectangle bounds1, Rectangle bounds2);

  private:
    int fruitCount = 0;
    int enemyCount = 0;
    bool finishedLevel = 0;
};

#endif // COLLISION_SYSTEM_HPP
