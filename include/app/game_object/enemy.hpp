#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "core/component/render/sprite_renderer.hpp"
#include "core/game_object/game_object.hpp"
#include "core/input/input_manager.hpp"

#include "app/component/animation.hpp"
#include "app/component/collider.hpp"
#include "app/component/display_bounding_box.hpp"
#include "app/component/position_display.hpp"
#include "app/component/spritesheet_renderer.hpp"
#include "app/game_object/bee_projectile.hpp"
#include "app/game_object/character.hpp"
#include "app/game_object/projectile.hpp"
#include "app/game_object/trunk_projectile.hpp"
#include "app/utility/collider_tag.hpp"
#include "app/utility/debug_mode.hpp"

class Enemy : public GameObject {

  public:
    Enemy(Vector2 position, std::string filePathSAP, std::string filePathSHT, std::string filePathCOL, const DebugInfo &debug_info);
    virtual ~Enemy();
    virtual void update(float delta_time);

  protected:
    Animation *animation;
    SpriteSheetRenderer *sp;
    Collider *collider;

    DisplayBoundingBox *bbDisplay;
};

#endif
