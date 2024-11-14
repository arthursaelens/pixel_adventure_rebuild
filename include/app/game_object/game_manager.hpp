#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "common.hpp"
#include "core/input/input_manager.hpp"
#include "app/game_object/menu.hpp"
#include "app/game_object/level.hpp"
#include "app/utility/debug_mode.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class GameManager : public GameObject {
    public:
        static GameManager &get_instance();

        GameManager(GameManager const &) = delete;
        void operator=(GameManager const &) = delete;
        
        Menu* menuutje;
        Level* current_level = nullptr;
        int current_level_index = -1;
        DebugInfo* dbi;
        bool inMenu;

    private:
        GameManager();

        void goToMenu();
        void load_menu();
        void unload_menu();
        Level *start_level(int level_id);
        

        void update(float delta_time);

        bool timerForMenu = 0;
        float timer = 0.0f;
};

#endif //gameee_manaager_happp
