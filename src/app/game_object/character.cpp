#include "app/game_object/character.hpp"

#include <fstream>
#include <iostream>

Character::Character(const DebugInfo &debug_info) {
    get_transform()->set_pos(960 - 32, 540 - 32);
    characterPosition = get_transform()->get_pos();

    animation = add_component<Animation>("assets/anim/frog.sap", "character");

    sp = add_component<SpriteSheetRenderer>("assets/sprites/frog.sht", animation->getStartingNode()->getSpriteName());
    sp->set_z_index(3);

    // collider->setColliderTag(ColliderTag::CHARACTER);

    unsigned int playerMask = ColliderTag::TERRAIN | ColliderTag::ENEMY | ColliderTag::PICKUP; // very basic, will add later when necessaazyrr

    collider = add_component<Collider>(ColliderTag::CHARACTER, true, playerMask, "assets/collision/frog.col");

    if (debug_info.canRenderOnScreenInfo()) {
        posDisplay = add_component<PositionDisplay>();
        bbDisplay = add_component<DisplayBoundingBox>("assets/collision/frog.col");
        posDisplay->set_z_index(3);
        bbDisplay->set_z_index(3);
        speedDisplay = add_component<SpeedDisplay>();
        speedDisplay->set_z_index(3);
        // later add more (rendering) components related to debugging
    }

    drawText = add_component<TextRenderer>(collider);

    jumpPressedTime = 0.0f;
}

/*void Character::update(float delta_time) {
    Transform2D *t = get_transform();
    InputManager &i = InputManager::get_instance();

    speed.x = 0;
    speed.y = 0;
    if (i.is_action_down("RIGHT")) {
        speed.x += 300;
    }

    if (i.is_action_down("LEFT")) {
        speed.x -= 300;
    }

    if (i.is_action_down("JUMP")) {

        speed.y = -300;
    }

    if (i.is_action_down("DOWN")) {

        speed.y = 300;
    }

    t->set_pos(t->get_pos().x + speed.x * delta_time, t->get_pos().y + speed.y * delta_time);
}*/

// calculate appropriate accelaration: big if movement oposes direction of current speed
float calcAccelaration(float currSpeed, float maxSpeedwithDirection, float maxAcceleration) {
    float difference = abs(maxSpeedwithDirection - currSpeed);
    // linear function acc is maxAcc when diff is 500
    float acc = (0.0014 * difference + 0.3) * maxAcceleration;
    if (abs(acc) > abs(maxAcceleration)) {
        acc = maxAcceleration;
    }
    return acc;
}

void Character::update(float delta_time) {

    if (killPlayer) {
        self_destruct();
    }

    if (collider->isHit == 1) {
        collider->isHit = 0;
        collider->characterLives -= 1;
    }
    if (collider->characterLives <= 0) {

        if (animation->getCurrentNode()->hasTransition("FAINT")) {
            // std::cout << " heeft transition faint" << std::endl;
            animation->setCurrentNode(animation->getCurrentNode()->getNextNode("FAINT"));
            // std::cout << animation->getCurrentNode()->getSpriteName() << std::endl;
            // std::cout << animation->getCurrentNode()->getName() << "naam" << std::endl;
        }

        aantalFaints += 1;

        if (aantalFaints == 20) {
            inCoolDown = 1;
            coolDownTimer = 0.0f;
            sp->set_z_index(0);

            //  self_destruct();
        }
    }

    // player respawned en alles word gereset
    if (collider->characterLives <= 0 && sp->get_z_index() == 0 && !inCoolDown && collider->respawns != 0) {
        collider->characterLives = 1;
        collider->respawns -= 1;
        animation->setCurrentNode(animation->getStartingNode());
        sp->set_z_index(3);
        aantalFaints = 0;
        get_transform()->set_pos(startPosition.x, startPosition.y);
    }

    if (inCoolDown) {
        coolDownTimer += delta_time;
    }
    if (coolDownTimer >= coolDownPeriod) {
        inCoolDown = 0;
    }

    Transform2D *t = get_transform();

    Vector2 displacement = {0.0f, 0.0f};
    const float movement_speed = 400.0f; // ??property of the character later

    // Define constants for acceleration, deceleration
    const float maxAcceleration = 3500.0f; // pix per second^2

    const float gravAccelaration = 1000.0f;
    const float maxVerticalSpeed = 400.0f;

    const float initialJumpSpeed = 300.0f;
    const float maxJumpTime = 0.2f; // Maximum time the jump button can be held for full jump height

    // input

    if (inputManager.is_action_pressed("ENTER") && collider->characterLives > 0) {

        Star *star = new Star(this, toLeft);
    }
    // std::cout << animation->getCurrentNode()->getName() << " node naam" << std::endl;

    if (hasDoubleJumped && animation->getCurrentNode()->hasTransition("ROLL")) {

        animation->setCurrentNode(animation->getCurrentNode()->getNextNode("ROLL"));

    } else if (inputManager.is_action_down("LEFT") && collider->characterLives > 0) {

        float acceleration = calcAccelaration(speed.x, -movement_speed, maxAcceleration);
        // std::cout << "to left:" << acceleration << std::endl;

        // Apply acceleration to the left
        speed.x -= acceleration * delta_time;
        if (speed.x < -movement_speed) {

            // std::cout << "clamped" << std::endl;
            speed.x = -movement_speed; // Clamp speed to maximum
        }

        displacement.x = speed.x * delta_time; // Move left

        sp->set_is_flipped(true);
        toLeft = 1;

        if (animation->getCurrentNode()->hasTransition("MOVING")) {
            animation->setCurrentNode(animation->getCurrentNode()->getNextNode("MOVING"));
        }

        // sp->set_is_flipped(true);
    } else if (inputManager.is_action_down("RIGHT") && collider->characterLives > 0) {

        float acceleration = calcAccelaration(speed.x, movement_speed, maxAcceleration);
        // std::cout << "to right:" << acceleration << std::endl;

        // Apply acceleration to the right
        speed.x += acceleration * delta_time;

        if (speed.x > movement_speed) {
            // std::cout << "clamped" << std::endl;
            speed.x = movement_speed; // Clamp speed to maximum
        }

        displacement.x = speed.x * delta_time; // Move right

        sp->set_is_flipped(false);
        toLeft = 0;
        if (animation->getCurrentNode()->hasTransition("MOVING")) {
            animation->setCurrentNode(animation->getCurrentNode()->getNextNode("MOVING"));
        }

    } else {
        // calculate decelaration in similar way to accelaration
        float decel = calcAccelaration(speed.x, 0, maxAcceleration);

        // decelarate when no input, get right direction
        if (speed.x > 0) {
            speed.x -= decel * delta_time;
            if (speed.x < 0) {
                speed.x = 0; // Stop decelerating when speed reaches 0
            }
        } else if (speed.x < 0) {
            speed.x += decel * delta_time;
            if (speed.x > 0) {
                speed.x = 0; // Stop decelerating when speed reaches 0
            }
        }
        displacement.x = speed.x * delta_time;

        if (animation->getCurrentNode()->hasTransition("IDLE") && !hasDoubleJumped) {
            animation->setCurrentNode(animation->getCurrentNode()->getNextNode("IDLE"));
        }
    }

    // std::cout << doubleJump << " dubblejump " << hasDoubleJumped << "hasdoublejumped" << collider->isGrounded << " grounded" << std::endl;
    if (inputManager.is_action_pressed("JUMP") && doubleJump == 1 && collider->characterLives > 0) {
        // Start jumping
        collider->isGrounded = 0;
        jumpPressedTime = 0.0f;
        speed.y -= initialJumpSpeed;
        doubleJump = 0;
        hasDoubleJumped = 1;
    } else if (inputManager.is_action_pressed("JUMP") && hasDoubleJumped == 0 && abs(speed.y) > 50 && collider->characterLives > 0) {
        // Start jumping
        collider->isGrounded = 0;
        jumpPressedTime = 0.0f;
        speed.y -= initialJumpSpeed;
        doubleJump = 0;
        hasDoubleJumped = 1;
    } else if (inputManager.is_action_pressed("JUMP") && abs(speed.y) < 20 && collider->characterLives > 0) {
        // Start jumping
        collider->isGrounded = 0;
        doubleJump = 1;
        jumpPressedTime = 0.0f;
        speed.y -= initialJumpSpeed;

    } else if (inputManager.is_action_down("JUMP") && jumpPressedTime < maxJumpTime && collider->characterLives > 0) {
        collider->isGrounded = 0;
        // Continue jumping (variable jump height)
        speed.y -= (initialJumpSpeed * (1.0f - jumpPressedTime / maxJumpTime) * 0.5) * delta_time * 15;
        jumpPressedTime += delta_time;
    } else {
        jumpPressedTime = maxJumpTime;
    }

    if (collider->isGrounded) {
        speed.y = 0;
        doubleJump = 0;
        hasDoubleJumped = 0;
    } else {
        if (speed.y < maxVerticalSpeed) {
            speed.y += gravAccelaration * delta_time;
        }
        if (speed.y > 80.0f && animation->getCurrentNode()->hasTransition("FALL") && !hasDoubleJumped) {
            animation->setCurrentNode(animation->getCurrentNode()->getNextNode("FALL"));
        }

        displacement.y = speed.y * delta_time + .5f * gravAccelaration * delta_time * delta_time;
    }

    if (collider->topHit) {
        speed.y *= -0.3; // als hij vanboven hit bots hij terug ipv plakken
        collider->topHit = 0;
    } else if (collider->bottomHit) {
        speed.y *= -0.5;
        collider->bottomHit = 0;
    }

    // std::cout << "spriteName (currentnode->spritename): " << animation->getCurrentNode()->getSpriteName() << std::endl;

    if (speedDisplay != nullptr) {
        speedDisplay->displaySpeed.x = speed.x;
        speedDisplay->displaySpeed.y = speed.y;
    }

    sp->updateSprite(animation->getCurrentNode()->getSpriteName());
    if (!freezed) {
        t->set_pos(t->get_pos().x + displacement.x, t->get_pos().y + displacement.y);
    }
    characterPosition = t->get_pos();
}

/*
void Character::set_AnimationNode(const std::string& animationNode) {
        currentPrimitiveAnimationNode = animationNode;
    }

std::string Character::get_AnimationNode() {
    return currentPrimitiveAnimationNode;
}

void Character::update(float delta_time) {
    Transform2D *t = get_transform();
    t->set_pos(t->get_pos().x, t->get_pos().y);

}
*/

Character::~Character() {
    // Destructor implementation later
}
