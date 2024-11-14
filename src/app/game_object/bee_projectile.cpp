#include "app/game_object/bee_projectile.hpp"

#include <fstream>
#include <iostream>

BeeProjectile::BeeProjectile(GameObject *gameObject) : Projectile(gameObject, "beeProjectile", ColliderTag::ENEMY_PROJECTILE, "geen sap", "geen sht", "assets/collision/bee_projectile.col", "assets/sprites/bee_projectile.png", 1) {

    t->set_pos(gameObject->get_transform()->get_pos().x + 19, gameObject->get_transform()->get_pos().y + 65); // cijfers berekent uit colfile
}

void BeeProjectile::update(float delta_time) {
    Vector2 displacement = {0.0f, 0.0f};
    float movement_speed = 500.0;

    const float gravAccelaration = 200.0f;

    displacement.y = gravAccelaration * delta_time + .5f * gravAccelaration * delta_time * delta_time;
    // geen animatie

    t->set_pos(t->get_pos().x + displacement.x, t->get_pos().y + displacement.y);
    if (collider->hit) {
        self_destruct();
    }
}
