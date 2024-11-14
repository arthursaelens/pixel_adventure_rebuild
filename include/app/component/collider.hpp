#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "app/utility/collider_tag.hpp"
#include "core/component/component.hpp"


//core component for collision_system, holds a lot of information about the gameobject it is part of
class Collider : public Component {
  private:
    // ColliderTag tag;
    //   std::string colfile;

  public:
    Collider(GameObject *game_object, ColliderTag tag, bool dynamicBool, unsigned int mask, std::string colfile);
    GameObject *gameObject;
    virtual ~Collider() = default;
    virtual void setColliderTag(ColliderTag tag);
    ColliderTag getColliderTag() const;

    bool isGrounded = false;
    bool toLeft = 0;
    bool isGrabbed = 0;
    bool hit = 0;
    bool isHit = 0;
    bool topHit = 0;
    bool bottomHit = 0;
    int characterLives = 1;
    int enemyLives = 3;
    int respawns = 2;
    bool kill = 0;

    bool finishedLevel = 0;
    /*int enemyLevens = 6; 
    int characterLevens = 2;*/

    //used in debugMode
    virtual void drawBoundingBox() const;

    // given the gameObject position (you can get this with game_object->get_pos()), calc where the bounds are (using bounding box)
    Rectangle calculateBounds() const;
    unsigned int mask;
    ColliderTag tag;

    Vector2 Speed;

    bool isDynamic;

    //offsets and width/height
    Rectangle BoundingBox;
    

    // virtual char LoadCollisionFile(GameObject *game_object);
};

#endif // COLLIDER_HPP
