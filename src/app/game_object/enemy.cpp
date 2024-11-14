#include "app/game_object/enemy.hpp"

#include <fstream>
#include <iostream>

Enemy::Enemy(Vector2 position, std::string filePathSAP, std::string filePathSHT, std::string filePathCOL, const DebugInfo &debug_info) {

    get_transform()->set_pos(position.x, position.y);

    animation = add_component<Animation>(filePathSAP, "enemy");
    sp = add_component<SpriteSheetRenderer>(filePathSHT, animation->getStartingNode()->getSpriteName());
    sp->set_z_index(3);

    unsigned int enemyMask = ColliderTag::TERRAIN | ColliderTag::CHARACTER;
    collider = add_component<Collider>(ColliderTag::ENEMY, true, enemyMask, filePathCOL);
    collider->setColliderTag(ColliderTag::ENEMY);

    // enemyMask = ColliderTag::TERRAIN | ColliderTag::CHARACTER;

    if (debug_info.canRenderOnScreenInfo()) {
        if (filePathCOL == "assets/collision/mush.col") {
            bbDisplay = add_component<DisplayBoundingBox>("assets/collision/mush.col");
        }
        if (filePathCOL == "assets/collision/bee.col") {
            bbDisplay = add_component<DisplayBoundingBox>("assets/collision/bee.col");
        }
        if (filePathCOL == "assets/collision/trunk.col") {
            bbDisplay = add_component<DisplayBoundingBox>("assets/collision/trunk.col");
        }
        // later add more (rendering) components related to debugging
    }
}

Enemy::~Enemy() {}

void Enemy::update(float delta_time) {
}
