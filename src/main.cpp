#include <iostream>

#include "app/game_object/character.hpp"
#include "app/game_object/dvd.hpp"
#include "app/game_object/game_manager.hpp"
#include "app/game_object/level.hpp"
#include "app/game_object/menu.hpp"
#include "app/game_object/test.hpp"
#include "app/system/animation_system.hpp"
#include "app/system/collision_system.hpp"
#include "common.hpp"
#include "core/engine.hpp"

int main(void) {
    const int windowWidth = 1080;
    const int windowHeight = 720;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowWidth, windowHeight, "Project Programmeren 2024");
    SetWindowMinSize(320, 240);

    SetTargetFPS(240);

    Engine &e = Engine::get_instance();
    AnimationSystem *animation_system = new AnimationSystem("ANIMATION_SYSTEM");
    CollisionSystem *collision_system = new CollisionSystem("COLLISION_SYSTEM");

    e.add_system_after("GAMEOBJECT_SYSTEM", collision_system);
    e.add_system_before("RENDERING_SYSTEM", animation_system);

    // TODO: Dit is een voorbeeld van hoe je een gameobject kan toevoegen aan de engine
    // Dvd is afgeleid van GameObject. De GameObject constructor voegt het gameobject toe aan de engine.
    // Het wordt wel afgeraden om GameObjects hier in main aan te maken, het is beter om via een GameManager of gelijkaardig te werken.

    // DebugInfo *dbi = new DebugInfo();
    // dbi->setDebugMode(DebugMode::NoDebugInfo);

    // TestObject *jaspertje = new TestObject();
    // Character *player = new Character(*dbi);
    // Level *level1 = new Level("assets/levels/level1.toml", *dbi);
    // Level *level2 = new Level("assets/levels/level2.toml", *dbi);
    //  Level *level3 = new Level("assets/levels/level3.toml", *dbi);

    GameManager &gamma = GameManager::get_instance();

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        e.update();
    }

    CloseWindow(); // Close window and OpenGL context

    // delete level2;
    //  delete player;
    //  delete jaspertje;

    return 0;
}
