#ifndef POSITION_DISPLAY_H
#define POSITION_DISPLAY_H

#include "common.hpp"
#include "core/component/render/renderer.hpp"

#include <string>

class PositionDisplay : public Renderer {
public:
    PositionDisplay(GameObject* game_object);
    void render();
};

#endif // POSITION_DISPLAY_H
