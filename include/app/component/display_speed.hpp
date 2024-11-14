#ifndef SPEED_DISPLAY_H
#define SPEED_DISPLAY_H

#include "common.hpp"
#include "core/component/render/renderer.hpp"

#include <string>

class SpeedDisplay : public Renderer {
  private:
    float arrowScalingFactor;
  public:
    SpeedDisplay(GameObject *game_object);
    void render();
    Vector2 displaySpeed = { 0, 0 };
};

#endif // SPEED_DISPLAY_H
