#ifndef DVD_H
#define DVD_H

#include "core/component/render/sprite_renderer.hpp"
#include "core/game_object/game_object.hpp"

class Dvd : public GameObject {
  public:
    Dvd();
    virtual void update(float delta_time);

  private:
    Vector2 speed{150.0, 150.0};
    SpriteRenderer *sp;
};

#endif
