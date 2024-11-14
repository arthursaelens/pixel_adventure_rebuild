#include "app/component/collider.hpp"

#include <fstream>
#include <iostream>
#include <raylib.h>
#include <rshapes.c>
#include <stdio.h>

/*char Collider::LoadCollisionFile(GameObject *game_object) {
    //
    char bestand = *game_object->colfile;
    return bestand;
}*/

Collider::Collider(GameObject *game_object, ColliderTag tag, bool dynamicBool, unsigned int obj_mask, std::string colfile) : Component(game_object) {

    setColliderTag(tag);
    mask = obj_mask;
    isDynamic = dynamicBool;
    gameObject = game_object;

    // bounding box maken van ons gameobject
    std::ifstream infile(colfile);
    if (!infile.is_open()) {
        std::cout << "colfile opent niet" << std::endl;
    }
    infile >> BoundingBox.x >> BoundingBox.y >> BoundingBox.width >> BoundingBox.height;
    infile.close();
}

void Collider::setColliderTag(ColliderTag tag) {
    this->tag = tag;
}

ColliderTag Collider::getColliderTag() const {
    return tag;
}


void Collider::drawBoundingBox() const {
    // Transform2D* transform = game_object->get_transform();

    Rectangle bounds = calculateBounds();

    DrawRectangleLinesEx(bounds, 3, GREEN);
}


Rectangle Collider::calculateBounds() const {
    Transform2D *transform = game_object->get_transform();

    float x = transform->get_pos().x + BoundingBox.x;
    float y = transform->get_pos().y + BoundingBox.y;

    return {x, y, BoundingBox.width, BoundingBox.height};
}
