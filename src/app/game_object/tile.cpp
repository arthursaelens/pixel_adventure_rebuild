#include "app/game_object/tile.hpp"

#include <iostream>

Tile::Tile(const std::string &spritesheet_path, const std::string &tile_name, float x, float y, bool has_collision, const DebugInfo &debug_info)
    : spritesheet_path(spritesheet_path), tile_name(tile_name), has_collision(has_collision) {

    // posDisplay = add_component<PositionDisplay>();
    // std::cout << tile_name << std::endl;
    tile_renderer = add_component<SpriteSheetRenderer>("assets/sprites/terrain.sht", tile_name);
    tile_renderer->set_z_index(3);
    get_transform()->set_pos(x, y);

    // tileCollider->setColliderTag(ColliderTag::TERRAIN);

    unsigned int tileMask = ColliderTag::CHARACTER | ColliderTag::ENEMY; // basic mask will have to add to this (projectiles etc.)
    if (tile_name == "EMPTY" | tile_name == "BLANK") {
        tileCollider = add_component<Collider>(ColliderTag::NOTHING, false, tileMask, "assets/collision/terrain.col");
    } else {
        tileCollider = add_component<Collider>(ColliderTag::TERRAIN, false, tileMask, "assets/collision/terrain.col");
    }

    if (debug_info.canRenderOnScreenInfo() && !(tile_name == "EMPTY" | tile_name == "BLANK")) {
        bbDisplay = add_component<DisplayBoundingBox>("assets/collision/terrain.col");
    }
}

void Tile::update(float delta_time) {
    if (killTile) {
        self_destruct();
        // std::cout << "deleted a tile" << std::endl;
    }
}
