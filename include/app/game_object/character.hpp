#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "core/component/render/sprite_renderer.hpp"
#include "core/game_object/game_object.hpp"
#include "core/input/input_manager.hpp"

#include "app/component/animation.hpp"
#include "app/component/collider.hpp"
#include "app/component/display_bounding_box.hpp"
#include "app/component/position_display.hpp"
#include "app/component/spritesheet_renderer.hpp"
#include "app/component/text_renderer.hpp"
#include "app/game_object/star.hpp"
#include "app/utility/collider_tag.hpp"
#include "app/utility/debug_mode.hpp"
#include "app/component/display_speed.hpp"

class Character : public GameObject {

  public:
    Character(const DebugInfo &debug_info);
    virtual ~Character();
    virtual void update(float delta_time);

    bool killPlayer = 0;

    Vector2 characterPosition;
    Vector2 startPosition;
    Vector2 speed{0, 0};
    /*
    virtual void set_AnimationNode(const std::string& animationNode);
    std::string get_AnimationNode();
    */
    // unsigned int playerMask;

    Collider *collider;

    bool freezed = 0;

  private:
    float jumpPressedTime;

    InputManager &inputManager = InputManager::get_instance();
    Animation *animation;
    bool toLeft = 0;
    int aantalFaints = 0;
    bool doubleJump = 0;
    bool hasDoubleJumped = 0;

    SpriteSheetRenderer *sp;
    TextRenderer *drawText;
    // std::string currentPrimitiveAnimationNode;

    PositionDisplay *posDisplay;
    DisplayBoundingBox *bbDisplay;
    SpeedDisplay *speedDisplay = nullptr;

    bool inCoolDown;
    float coolDownPeriod = 2.5f;
    float coolDownTimer = 0.0f;
};

#endif // CHARACTER_HPP
