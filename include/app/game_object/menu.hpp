#ifndef MENU_HPP
#define MENU_HPP

#include "common.hpp"
#include "core/game_object/game_object.hpp"
#include "app/component/background_renderer.hpp"
#include "app/component/menu_text_renderer.hpp"
#include  <cstdlib>

#include "app/utility/collider_tag.hpp"
#include "app/utility/debug_mode.hpp"
#include "core/input/input_manager.hpp"
#include "app/game_object/level.hpp"

class Menu : public GameObject {
  private:
    //will remove some bgs for visibility of "debugmode button"
    std::string bgFilesList[7] = { "assets/sprites/bg_blue.png",
                                   "assets/sprites/bg_brown.png",
                                   "assets/sprites/bg_gray.png",
                                   "assets/sprites/bg_green.png",
                                   "assets/sprites/bg_pink.png",
                                   "assets/sprites/bg_purple.png",
                                   "assets/sprites/bg_yellow.png" };
    std::string currentBgFile;
    InputManager &im = InputManager::get_instance();
    bool renderEnabled;

  public:
    bool killMenu = false;
    Menu();
    ~Menu();
    int level_to_load = -1;
    virtual void update(float delta_time);
    MenuTextRenderer *mtr;


    // Function to enable or disable rendering
    void setRenderEnabled(bool enabled);
    bool isRenderEnabled() const { return renderEnabled; }


  protected:
    
    BackgroundRenderer *bgr;

    void createRenderers(); // Function to create renderer components
    void deleteRenderers(); // Function to delete renderer components
    
};

#endif //MENU_HPP
