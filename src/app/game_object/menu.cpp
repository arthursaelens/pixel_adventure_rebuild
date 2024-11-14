#include "app/game_object/menu.hpp"

#include <fstream>
#include <iostream>
#include <time.h>

Menu::Menu() {
    srand((unsigned int)time(NULL));
    int randInt = rand();
    std::cout << "random int: " << randInt << std::endl;
    currentBgFile = bgFilesList[randInt % 7];
    Rectangle recFullScreen = {0, 0, 1920, 1600};
    bgr = add_component<BackgroundRenderer>(currentBgFile, recFullScreen);
    mtr = add_component<MenuTextRenderer>();

    /*
    // Define positions for the level texts
    Vector2 level1Pos = {480 - 160, 500};
    Vector2 level2Pos = {2 * 480 - 160, 500};
    Vector2 level3Pos = {3 * 480 - 160, 500};

    // Add level text renderers
    level1TextRenderer = add_component<MenuTextRenderer>(level1Pos, "Level 1", true); // Level 1 is initially selected
    level2TextRenderer = add_component<MenuTextRenderer>(level2Pos, "Level 2", false);
    level3TextRenderer = add_component<MenuTextRenderer>(level3Pos, "Level 3", false);
    */
}

// het enablen en disablen van renderer componenten wordt niet langer gebruikt
void Menu::setRenderEnabled(bool enabled) {
    if (enabled && !renderEnabled) {
        createRenderers(); // Create renderer components if rendering is enabled
    } else if (!enabled && renderEnabled) {
        deleteRenderers(); // Delete renderer components if rendering is disabled
    }
    renderEnabled = enabled;
}

void Menu::createRenderers() {
    Rectangle recFullScreen = {0, 0, 1920, 1080};
    bgr = add_component<BackgroundRenderer>(currentBgFile, recFullScreen);
    mtr = add_component<MenuTextRenderer>();
}

// deleten van componenten op deze manier is gevaarlijk (gebruiken we niet)
void Menu::deleteRenderers() {
    delete bgr;
    delete mtr;
    bgr = nullptr;
    mtr = nullptr;
}

Menu::~Menu() {
}

void Menu::update(float delta_time) {
    if (killMenu) {
        self_destruct();
    }
    /*
    std::cout << "are we seleting debug mode?: " << mtr->selectingDebugMode << std::endl;
    std::cout << "bebugmode on?: " << mtr->debugMode << std::endl;
    std::cout << "level " << mtr->level_index << std::endl;
    */

    if (renderEnabled) {
        if (!mtr->selectingDebugMode) {
            if (im.is_action_pressed("DOWN")) {
                mtr->selectingDebugMode = true;
            }
            if (im.is_action_pressed("LEFT")) {
                if (mtr->level_index == 0) {
                    mtr->level_index = 2;
                } else {
                    mtr->level_index = (mtr->level_index - 1);
                }
            }
            if (im.is_action_pressed("RIGHT")) {
                mtr->level_index = (mtr->level_index + 1) % mtr->number_of_levels;
            }
            if (im.is_action_pressed("ENTER")) {
                level_to_load = mtr->level_index;
            }
        } else {
            if (im.is_action_pressed("ENTER")){
                //std::cout << "switched mode from" << mtr->debugMode << "to" << ! << std::endl;
                mtr->debugMode = !mtr->debugMode;
            }
            if (im.is_action_pressed("JUMP")) {
                mtr->selectingDebugMode = false;
            }
        }
    }
}
