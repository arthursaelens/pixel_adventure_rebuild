#ifndef PICK_UP_HPP
#define PICK_UP_HPP

#include "core/component/render/sprite_renderer.hpp"
#include "core/game_object/game_object.hpp"
#include "core/input/input_manager.hpp"

#include "app/component/animation.hpp"
#include "app/component/collider.hpp"
#include "app/component/position_display.hpp"
#include "app/component/spritesheet_renderer.hpp"
#include "app/utility/collider_tag.hpp"
#include "app/utility/debug_mode.hpp"

class Pickup : public GameObject {

  public:
    Pickup(Vector2 location, std::string fruitName, const DebugInfo &debug_info);
    virtual ~Pickup();
    virtual void update(float delta_time);

    // bool killPickup = 0;

  protected:
    bool inPickupAnimation;
    std::string fruitName;
    Animation *animation;
    SpriteSheetRenderer *sp;
    Collider *collider;
    Vector2 position;
};

#endif
