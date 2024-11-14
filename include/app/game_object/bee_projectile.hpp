#ifndef BEE_PROJECTILE_HPP
#define BEE_PROJECTILE_HPP

#include "app/game_object/projectile.hpp"

class BeeProjectile : public Projectile {
  public:
    BeeProjectile(GameObject *gameObject);
    virtual void update(float delta_time) override;
    Transform2D *t = get_transform();

  private:
    Vector2 position;
};

#endif
