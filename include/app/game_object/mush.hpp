#ifndef MUSH_HPP
#define MUSH_HPP

#include "app/game_object/enemy.hpp"

class Mush : public Enemy {
  public:
    Mush(Vector2 location, const DebugInfo &debug_info);
    virtual void update(float delta_time) override;
    bool killMush = 0;

  private:
    int aantalFaints = 0;
    bool inCoolDown;
    float coolDownPeriod = 0.6;
    float coolDownTimer = 0.0;
    Vector2 displacement = {0, 0};
    Vector2 speed = {100.0f, 0};
};

#endif
