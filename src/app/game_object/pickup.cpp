#include "app/game_object/pickup.hpp"

#include <fstream>
#include <iostream>

Pickup::Pickup(Vector2 location, std::string fruitName, const DebugInfo &debug_info) {

    position = location;
    get_transform()->set_pos(location.x, location.y);

    // which fruit?
    // std::cout << "BOE!" << std::endl;
    // std::cout << "sprite name: " << animation->getStartingNode()->getSpriteName() << std::endl;

    this->fruitName = fruitName;
    animation = add_component<Animation>("assets/anim/fruit.sap", "pickup");
    sp = add_component<SpriteSheetRenderer>("assets/sprites/fruit.sht", animation->getStartingNode()->getSpriteName() + "_" + fruitName);
    // animation->printAnimationGraph();
    sp->set_z_index(2);

    unsigned int pickupMask = ColliderTag::CHARACTER;
    collider = add_component<Collider>(ColliderTag::PICKUP, false, pickupMask, "assets/collision/fruit.col");
    collider->setColliderTag(ColliderTag::PICKUP);
}

Pickup::~Pickup() {}

void Pickup::update(float delta_time) {
    if (collider->kill) {
        self_destruct();
    }

    // Transform2D *t = get_transform();
    //  print statements for debugging fruit animation
    /*
    if (position.x == 586 && inPickupAnimation && id < 10) {
            std::cout << "fruit at : " << position.x << " ,picked up? : " << collider->isGrabbed << std::endl;
            std::cout << animation->getCurrentNode()->getName() <<std::endl;

    }
    */

    if (collider->isGrabbed /*&& !inPickupAnimation*/) {

        if (animation->getCurrentNode()->hasTransition("PICKUP")) {
            inPickupAnimation = true;
            animation->setCurrentNode(animation->getCurrentNode()->getNextNode("PICKUP"));
        }
    }

    // if the animation is completed self destruct
    if (animation->getCurrentNode()->getName().find("PICKUP_5") != std::string::npos) {
        self_destruct();
    }

    // update the spritesheet renderer,
    //(spritesheetrenderer needs to know name of fruit when its in idle)

    // the following if statement checks if PICKUP is a substring of the current node sprite name
    if (animation->getCurrentNode()->getSpriteName().find("PICKUP") != std::string::npos) {
        sp->updateSprite(animation->getCurrentNode()->getSpriteName());
    } else {
        sp->updateSprite(animation->getCurrentNode()->getSpriteName() + "_" + fruitName);
    }

    /*if (collider->isGrabbed) {
        std::cout << animation->getCurrentNode()->getName() << std::endl;
        if (animation->getCurrentNode()->hasTransition("PICKUP")) {
            animation->setCurrentNode(animation->getCurrentNode()->getNextNode("PICKUP"));
        }
        pickupAnimations += 1;
        if (pickupAnimations > 5) {
            self_destruct();
        }
        sp->updateSprite(animation->getCurrentNode()->getSpriteName());
    } else {
        sp->updateSprite(animation->getCurrentNode()->getSpriteName() + "_" + fruitName);
    }*/
}
