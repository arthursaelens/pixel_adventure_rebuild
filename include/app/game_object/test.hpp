#ifndef TEST_OBJECT_H
#define TEST_OBJECT_H
/* 
header guards: conditional compilation directives 
that help to avoid errors that arise when the same function 
or variable is defined more than once by the mistake 
of a programmer

hier misschien onnodig
*/

#include "core/component/render/sprite_renderer.hpp"
#include "core/game_object/game_object.hpp"
#include "app/component/position_display.hpp"

class TestObject : public GameObject {
    public:
        TestObject();
        virtual void update(float delta_time);

    private:
        SpriteRenderer *sp;
        PositionDisplay *posDisplay;
        Vector2 speed{0,0};
};

#endif //endif voor TEST_OBJECT_H
