#ifndef STAR_HPP
#define STAR_HPP

#include "app/game_object/projectile.hpp"
#include "core/input/input_manager.hpp"

class Star : public Projectile {
  public:
    Star(GameObject *gameObject, bool richting);
    virtual void update(float delta_time) override;
    Transform2D *t = get_transform();

  private:
    Vector2 position;
};

#endif
