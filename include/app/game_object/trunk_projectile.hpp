#ifndef TRUNK_PROJECTILE_HPP
#define TRUNK_PROJECTILE_HPP

#include "app/game_object/projectile.hpp"

class TrunkProjectile : public Projectile {
  public:
    TrunkProjectile(GameObject *gameObject, bool richting);
    virtual void update(float delta_time) override;
    Transform2D *t = get_transform();

  private:
    Vector2 position;
};

#endif
