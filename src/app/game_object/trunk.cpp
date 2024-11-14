#include "app/game_object/trunk.hpp"

#include <fstream>
#include <iostream>

Trunk::Trunk(Vector2 location, const DebugInfo &debug_info, GameObject *target) : Enemy(location, "assets/anim/trunk.sap", "assets/sprites/trunk.sht", "assets/collision/trunk.col", debug_info) {
    this->target = target;
}

void Trunk::update(float delta_time) {
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
        if (aantalFaints > 150 || t->get_pos().y > 1000) {
            self_destruct();
        }
        speed.y += gravAccelaration * delta_time;
        displacement.y = speed.y * delta_time + .5f * gravAccelaration * delta_time * delta_time;
        // std::cout << "speed" << speed.y << "displacement" << displacement.y << "  " << 0.5 * gravAccelaration * delta_time * delta_time << "  " << speed.y * delta_time << std::endl;
    }

    if (collider->toLeft) {
        displacement.x = -movement_speed * delta_time; // Move left
        sp->set_is_flipped(false);
        if (animation->getCurrentNode()->hasTransition("MOVING")) {
            animation->setCurrentNode(animation->getCurrentNode()->getNextNode("MOVING"));
        }
        // nog geen idee hoe we player in front of us gaan checken, heb beetje opgezocht we zouden het met raycasting moeten doen
        // maar dan moeten we ook checken dat hij maar max om de 3 seconden kan schieten
        /*if (player in front of us) {

            TrunkProjectile *projectile = new TrunkProjectile(this, 1);
        }*/
    } else {
        displacement.x = movement_speed * delta_time;
        sp->set_is_flipped(true);

        if (animation->getCurrentNode()->hasTransition("MOVING")) {
            animation->setCurrentNode(animation->getCurrentNode()->getNextNode("MOVING"));
        }
        /*if (player in front of us) {

            TrunkProjectile *projectile = new TrunkProjectile(this, 0);
        }*/
    }

    float pi = 3.14159265359;
    float isUnderThreshold = 30.0f;

    // raycasting onder ons

    if (abs(t->get_pos().y - target->get_transform()->get_pos().y) < isUnderThreshold && !inCoolDown && t->get_pos().x - target->get_transform()->get_pos().x < 0 && !collider->toLeft && collider->enemyLives > 0) {

        TrunkProjectile *projectile = new TrunkProjectile(this, 0);
        inCoolDown = 1;
    } else if (abs(t->get_pos().y - target->get_transform()->get_pos().y) < isUnderThreshold && !inCoolDown && t->get_pos().x - target->get_transform()->get_pos().x > 0 && collider->toLeft && collider->enemyLives > 0) {
        TrunkProjectile *projectile = new TrunkProjectile(this, 1);

        inCoolDown = 1;
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
