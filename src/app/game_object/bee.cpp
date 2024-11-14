#include "app/game_object/bee.hpp"
#include <math.h>

#include <fstream>
#include <iostream>

Bee::Bee(Vector2 location, const DebugInfo &debug_info, GameObject *target) : Enemy(location, "assets/anim/bee.sap", "assets/sprites/bee.sht", "assets/collision/bee.col", debug_info) {
    this->target = target;
}

void Bee::update(float delta_time) {
    if (collider->kill) {
        self_destruct();
    }
    Transform2D *t = get_transform();
    Vector2 displacement = {0.0f, 0.0f};
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
        // std::cout << lives << " aantal levens" << std::endl;
        // std::cout << "speed" << speed.y << "displacement" << displacement.y << "  " << 0.5 * gravAccelaration * delta_time * delta_time << "  " << speed.y * delta_time << std::endl;
        displacement.y = speed.y * delta_time + .5f * gravAccelaration * delta_time * delta_time;
    } else if (collider->enemyLives < 0) {
        aantalFaints += 1;
        if (aantalFaints > 100 || t->get_pos().y > 1000) {
            self_destruct();
        }
        
        speed.y += gravAccelaration * delta_time;
        displacement.y = speed.y * delta_time + .5f * gravAccelaration * delta_time * delta_time;
        // std::cout << "speed" << speed.y << "displacement" << displacement.y << "  " << 0.5 * gravAccelaration * delta_time * delta_time << "  " << speed.y * delta_time << std::endl;
    }

    if (animation->getCurrentNode()->hasTransition("MOVING")) {
        animation->setCurrentNode(animation->getCurrentNode()->getNextNode("MOVING"));
    }

    // use atan normalized between 0.5 and 1 to have bee shoot earlier
    //(bigger range for when character is counted as "under" the bee) when character is moving at high speeds
    float pi = 3.14159265359;
    float isUnderThreshold = 150.0f;

    // raycasting onder ons
    if (abs(t->get_pos().x - target->get_transform()->get_pos().x) < isUnderThreshold && !inCoolDown && collider->enemyLives > 0) {

        inCoolDown = 1;
        BeeProjectile *projectile = new BeeProjectile(this);
    }

    animation->elapsedTime += delta_time;
    sp->updateSprite(animation->getCurrentNode()->getSpriteName());
    t->set_pos(t->get_pos().x + displacement.x, t->get_pos().y + displacement.y);

    if (inCoolDown) {
        coolDownTimer += delta_time;
    }
    if (coolDownTimer >= coolDownPeriod) {
        inCoolDown = 0;
        coolDownTimer = 0.0f;
    }
}
