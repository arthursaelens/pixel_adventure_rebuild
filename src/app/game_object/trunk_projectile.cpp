#include "app/game_object/trunk_projectile.hpp"

#include <fstream>
#include <iostream>

TrunkProjectile::TrunkProjectile(GameObject *gameObject, bool richting) : Projectile(gameObject, "trunkProjectile", ColliderTag::ENEMY_PROJECTILE, "geen sap", "geen sht", "assets/collision/trunk_projectile.col", "assets/sprites/trunk_projectile.png", richting) {

    t->set_pos(gameObject->get_transform()->get_pos().x + 42, gameObject->get_transform()->get_pos().y + 32); // cijfers berekent uit colfile
}

void TrunkProjectile::update(float delta_time) {
    Vector2 displacement = {0.0f, 0.0f};
    float movement_speed = 500.0;

    const float gravAccelaration = 500.0f;

    displacement.y = gravAccelaration * delta_time * delta_time + .5f * gravAccelaration * delta_time * delta_time;

    if (toLeft) {
        displacement.x = -movement_speed * delta_time; // Move left
        // geen animatie
    } else {
        displacement.x = movement_speed * delta_time;
        // geen animatie
    }
    t->set_pos(t->get_pos().x + displacement.x, t->get_pos().y + displacement.y);
    if (collider->hit) {
        self_destruct();
    }
}
