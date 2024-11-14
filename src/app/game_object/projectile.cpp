#include "app/game_object/projectile.hpp"

#include <fstream>
#include <iostream>

Projectile::Projectile(GameObject *gameObject, std::string objectName, ColliderTag tag, std::string filePathSAP, std::string filePathSHT, std::string filePathCOL, std::string filePathPNG, bool richting) {

    // mss extra argument meegeven met projectile in welke richting dat het moet geschoten worden
    toLeft = richting;

    game_object_shooting = gameObject;
    if (filePathSAP != "geen sap") {
        animation = add_component<Animation>(filePathSAP, objectName);

        sp = add_component<SpriteSheetRenderer>(filePathSHT, animation->getStartingNodeProjectile(objectName)->getSpriteName());
        sp->set_z_index(2);
    } else {
        sprite = add_component<SpriteRenderer>(filePathPNG);
        sprite->set_z_index(2);
    }

    unsigned int projectileMask;
    if (tag == ColliderTag::ENEMY_PROJECTILE) {
        projectileMask = ColliderTag::TERRAIN | ColliderTag::CHARACTER;
    } else {
        projectileMask = ColliderTag::TERRAIN | ColliderTag::ENEMY;
    }
    collider = add_component<Collider>(tag, true, projectileMask, filePathCOL);
    collider->setColliderTag(tag);
}

Projectile::~Projectile() {
}

void Projectile::update(float delta_time) {
}
