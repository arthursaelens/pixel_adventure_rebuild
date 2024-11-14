#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "core/component/render/sprite_renderer.hpp"
#include "core/game_object/game_object.hpp"
#include "core/input/input_manager.hpp"

#include "app/component/animation.hpp"
#include "app/component/collider.hpp"
#include "app/component/display_bounding_box.hpp"
#include "app/component/position_display.hpp"
#include "app/component/spritesheet_renderer.hpp"
#include "app/utility/collider_tag.hpp"
#include "app/utility/debug_mode.hpp"

class Projectile : public GameObject {

  public:
    Projectile(GameObject *gameObject, std::string objectName, ColliderTag tag, std::string filePathSAP, std::string filePathSHT, std::string filePathCOL, std::string filePathPNG, bool richting);
    virtual ~Projectile();
    virtual void update(float delta_time);
    bool toLeft;
    GameObject *game_object_shooting;

  protected:
    InputManager &inputManager = InputManager::get_instance();
    Animation *animation;
    SpriteSheetRenderer *sp;
    SpriteRenderer *sprite;
    Collider *collider;

    DisplayBoundingBox *bbDisplay;
};

#endif
