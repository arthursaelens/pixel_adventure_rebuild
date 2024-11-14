#ifndef BACKGROUND_RENDERER_HPP
#define BACKGROUND_RENDERER_HPP

#include "app/utility/spritesheet_loader.hpp"
#include "common.hpp"
#include "core/component/render/renderer.hpp"
#include "core/utility/texture_loader.hpp"

//renderer component added to levels and menu for moving background
class BackgroundRenderer : public Renderer {

  public:
    BackgroundRenderer(GameObject *game_object, std::string &pngFileLocation, Rectangle rec);
    virtual ~BackgroundRenderer() = default;

    virtual void render();
    void setTint(unsigned char red, unsigned char green, unsigned char bleu);

  protected:
    Rectangle rec;
    Color tint{255, 255, 255, 255};
    Texture2D *texture;
    float offset = 0;
};

#endif
