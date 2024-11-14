#ifndef TRUNK_HPP
#define TRUNK_HPP

#include "app/game_object/enemy.hpp"

class Trunk : public Enemy {
  public:
    Trunk(Vector2 location, const DebugInfo &debug_info, GameObject *target);
    virtual void update(float delta_time) override;
    bool killTrunk = 0;

  private:
    GameObject *target;
    bool inCoolDown;
    float coolDownPeriod = 0.6;
    float coolDownTimer = 0.0;
    int aantalFaints = 0;
    Vector2 speed = {100.0f, 0};
    Vector2 displacement = {0, 0};
};

#endif
