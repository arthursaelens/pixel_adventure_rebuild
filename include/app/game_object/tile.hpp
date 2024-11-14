#ifndef TILE_HPP
#define TILE_HPP

#include "app/component/collider.hpp"
#include "app/component/position_display.hpp"
#include "app/component/spritesheet_renderer.hpp"
#include "app/utility/collider_tag.hpp"
#include "core/component/render/sprite_renderer.hpp"
#include "core/game_object/game_object.hpp"
#include "app/utility/debug_mode.hpp"
#include "app/component/display_bounding_box.hpp"

class Tile : public GameObject {
  public:
    Tile(const std::string &spritesheet_path, const std::string &tile_name, float x, float y, bool has_collision, const DebugInfo& debug_info);
    virtual void update(float delta_time);
    //unsigned int tileMask;
    bool killTile = false;
    
  private:
    // PositionDisplay *posDisplay;
    SpriteSheetRenderer *tile_renderer;

    std::string spritesheet_path;
    std::string tile_name;
    bool has_collision;

    Collider *tileCollider;

    DisplayBoundingBox *bbDisplay; 
};

#endif // TILE_HPP
