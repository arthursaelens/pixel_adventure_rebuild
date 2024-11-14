#ifndef DISPLAY_BOUNDING_BOX_H
#define DISPLAY_BOUNDING_BOX_H

#include "common.hpp"
#include "core/component/render/renderer.hpp"

#include <string>

//renders a green square for gameobjects' bounding boxes
class DisplayBoundingBox : public Renderer {
public:
    DisplayBoundingBox(GameObject* game_object, std::string colfile);
    void render();
private:
    //some code duplication from collider
    Rectangle calculateBounds() const;

    Rectangle BoundingBox;
};

#endif // DISPLAY_BOUNDING_BOX_H
