#ifndef COLLIDER_TAG_HPP
#define COLLIDER_TAG_HPP

enum ColliderTag {
    NOTHING = 0,
    TERRAIN = 1,
    CHARACTER = 2,
    ENEMY = 4,
    PICKUP = 8,
    PLAYER_PROJECTILE = 16,
    ENEMY_PROJECTILE = 32,
    TRAP = 64,
    MOVING_PLATFORM = 128
};

#endif
