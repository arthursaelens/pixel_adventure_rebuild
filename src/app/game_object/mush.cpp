#include "app/game_object/mush.hpp"

#include <fstream>
#include <iostream>

Mush::Mush(Vector2 location, const DebugInfo &debug_info) : Enemy(location, "assets/anim/mush.sap", "assets/sprites/mush.sht", "assets/collision/mush.col", debug_info) {
    sp->set_z_index(3);
}

void Mush::update(float delta_time) {
    if (collider->kill) {
        self_destruct();
    }
    Transform2D *t = get_transform();

    float movement_speed = 100.0f;
    const float gravAccelaration = 1000.0f;
    const float maxVerticalSpeed = 400.0f;

    const float initialJumpSpeed = 300.0f;

    if (collider->isHit == 1) {
        if (animation->getCurrentNode()->hasTransition("HIT")) {
            animation->setCurrentNode(animation->getCurrentNode()->getNextNode("HIT"));
        }
        collider->isHit = 0;
        collider->enemyLives -= 1;

    } else if (collider->topHit) {
        if (animation->getCurrentNode()->hasTransition("HIT")) {
            animation->setCurrentNode(animation->getCurrentNode()->getNextNode("HIT"));
        }
        collider->enemyLives = 0;
        collider->topHit = 0;

        collider->tag = ColliderTag::NOTHING;
    }
    if (collider->enemyLives == 0) {

        collider->tag = ColliderTag::NOTHING;
        collider->enemyLives = -1;
        if (animation->getCurrentNode()->hasTransition("FAINT")) {
            // std::cout << " heeft transition faint" << std::endl;
            animation->setCurrentNode(animation->getCurrentNode()->getNextNode("FAINT"));
            // std::cout << animation->getCurrentNode()->getSpriteName() << std::endl;
            // std::cout << animation->getCurrentNode()->getName() << "naam" << std::endl;
        }

        speed.y -= initialJumpSpeed;
        // std::cout << collider->enemyLives << " aantal levens" << std::endl;
        // std::cout << "speed" << speed.y << "displacement" << displacement.y << "  " << 0.5 * gravAccelaration * delta_time * delta_time << "  " << speed.y * delta_time << std::endl;
        displacement.y = speed.y * delta_time + .5f * gravAccelaration * delta_time * delta_time;
    } else if (collider->enemyLives < 0) {
        aantalFaints += 1;
        if (aantalFaints > 150 || t->get_pos().y > 900) {
            self_destruct();
        }
        speed.y += gravAccelaration * delta_time;
        displacement.y = speed.y * delta_time + .5f * gravAccelaration * delta_time * delta_time;
        // std::cout << "speed" << speed.y << "displacement" << displacement.y << "  " << 0.5 * gravAccelaration * delta_time * delta_time << "  " << speed.y * delta_time << std::endl;
    }

    if (collider->toLeft) {
        displacement.x = -speed.x * delta_time; // Move left
        sp->set_is_flipped(false);
        if (animation->getCurrentNode()->hasTransition("MOVING")) {
            animation->setCurrentNode(animation->getCurrentNode()->getNextNode("MOVING"));
        }
    } else {
        displacement.x = speed.x * delta_time;
        sp->set_is_flipped(true);

        if (animation->getCurrentNode()->hasTransition("MOVING")) {
            animation->setCurrentNode(animation->getCurrentNode()->getNextNode("MOVING"));
        }
    }

    animation->elapsedTime += delta_time;
    sp->updateSprite(animation->getCurrentNode()->getSpriteName());
    t->set_pos(t->get_pos().x + displacement.x, t->get_pos().y + displacement.y);
}
