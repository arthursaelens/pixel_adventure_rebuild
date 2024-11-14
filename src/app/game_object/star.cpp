#include "app/game_object/star.hpp"

#include <fstream>
#include <iostream>

Star::Star(GameObject *gameObject, bool richting) : Projectile(gameObject, "star", ColliderTag::PLAYER_PROJECTILE, "assets/anim/star.sap", "assets/sprites/star.sht", "assets/collision/star.col", "geen png", richting) {

    t->set_pos(gameObject->get_transform()->get_pos().x + 23, gameObject->get_transform()->get_pos().y + 32); // cijfers berekent uit colfile helft van x+width en helft van y+height
}

void Star::update(float delta_time) {
    Vector2 displacement = {0.0f, 0.0f};
    float movement_speed = 500.0;

    const float gravAccelaration = 500.0f;

    displacement.y = gravAccelaration * delta_time * delta_time + .5f * gravAccelaration * delta_time * delta_time;

    if (toLeft) {
        displacement.x = -movement_speed * delta_time; // Move left
        if (animation->getCurrentNode()->hasTransition("MOVING")) {
            animation->setCurrentNode(animation->getCurrentNode()->getNextNode("MOVING"));
        }
    } else {
        displacement.x = movement_speed * delta_time;

        if (animation->getCurrentNode()->hasTransition("MOVING")) {
            animation->setCurrentNode(animation->getCurrentNode()->getNextNode("MOVING"));
        }
    }

    animation->elapsedTime += delta_time;
    sp->updateSprite(animation->getCurrentNode()->getSpriteName());
    t->set_pos(t->get_pos().x + displacement.x, t->get_pos().y + displacement.y);
    if (collider->hit) {
        self_destruct();
    }
}
