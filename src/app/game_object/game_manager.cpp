#include "app/game_object/game_manager.hpp"

GameManager &GameManager::get_instance() {
    static GameManager instance;
    return instance;
}

GameManager::GameManager() {
    dbi = new DebugInfo();
    dbi->setDebugMode(DebugMode::NoDebugInfo);

    inMenu = 1;

    load_menu();
}

void GameManager::load_menu() {
    menuutje = new Menu();
}

void GameManager::unload_menu() {
    menuutje->killMenu = true;
    menuutje = nullptr;
}

Level *GameManager::start_level(int level_index) {
    
    std::string filepath = "assets/levels/level" + std::to_string(level_index + 1) + ".toml";
    if (menuutje->mtr->debugMode) {
        dbi->setDebugMode(DebugMode::AllDebugInfo);
    } else (dbi->setDebugMode(DebugMode::NoDebugInfo));
    return new Level(filepath, *dbi);

}

void GameManager::goToMenu() {

    if (current_level != nullptr) {
        current_level->killLevel = true;
        current_level = nullptr;
    }
    load_menu();
    
    inMenu = true;
}




void GameManager::update(float delta_time) {
    
    //std::cout<< timerForMenu << std::endl;

    if (timerForMenu) {
        timer += delta_time;
        //std::cout << timer << std::endl;
    }

    if (timer >= 3) {
        timer = 0.0f;
        goToMenu();
        timerForMenu = 0;
    }

    if (menuutje != nullptr) {
        if (menuutje->level_to_load >= 0 && inMenu) {
            // Transition from menu to game level
            inMenu = false;
            current_level_index = menuutje->level_to_load;
            current_level = start_level(menuutje->level_to_load);
        }
    }

    if (menuutje != nullptr && !inMenu) {
        unload_menu();
    }

    if (menuutje == nullptr && !inMenu && current_level != nullptr) {
    
        if (current_level->player->collider->finishedLevel || (current_level->player->collider->respawns == 0 && current_level->player->collider->characterLives<=0)) {
            //std::cout << "level is finished:" << current_level->player->collider->finishedLevel << std::endl;
            timerForMenu = true;
        }

    }

}
