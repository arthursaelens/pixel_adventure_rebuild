#ifndef BEE_HPP
#define BEE_HPP

#include "app/game_object/character.hpp"
#include "app/game_object/enemy.hpp"

class Bee : public Enemy {
  public:
    Bee(Vector2 location, const DebugInfo &debug_info, GameObject *target);
    virtual void update(float delta_time) override;
    bool killBee = 0;

  private:
    GameObject *target;

    Vector2 displacement = {0, 0};
    Vector2 speed = {100.0f, 0};

    bool inCoolDown;
    float coolDownPeriod = 1.2f;
    float coolDownTimer = 0.0;
    int aantalFaints = 0;
};

#endif
