#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "common.hpp"
#include "core/game_object/game_object.hpp"

#include <string>

class GameObject;

class Component {
  public:
    Component(GameObject *game_object);
    virtual ~Component() = default;

  protected:
    GameObject *game_object;
};

class Transform2D : public Component {
  public:
    Transform2D(GameObject *game_object);
    virtual ~Transform2D() = default;

    Vector2 get_pos() const;
    void set_pos(float x, float y);

  private:
    Vector2 pos{0.0, 0.0};
};

#endif
