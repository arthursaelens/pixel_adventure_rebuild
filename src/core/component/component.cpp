#include "core/component/component.hpp"
#include "core/game_object/game_object.hpp"

Component::Component(GameObject *game_object) : game_object(game_object) {
}

Transform2D::Transform2D(GameObject *game_object) : Component(game_object) {
}

Vector2 Transform2D::get_pos() const {
    return pos;
}

void Transform2D::set_pos(float x, float y) {
    pos.x = x;
    pos.y = y;
}
