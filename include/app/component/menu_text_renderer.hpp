#ifndef MENU_TEXT_RENDERER_HPP
#define MENU_TEXT_RENDERER_HPP

#include "common.hpp"
#include "core/component/render/renderer.hpp"


class MenuTextRenderer: public Renderer {
    private:
        Vector2 position;
        const char* text;
        

    public:
        MenuTextRenderer(GameObject *game_object);
        virtual void render() override;
        int level_index = 0;
        int number_of_levels = 3;

        //bools for Debug "Button"
        bool selectingDebugMode = 0;
        bool debugMode = 0;
       
};

#endif //mmmenetectrendefrrrr
