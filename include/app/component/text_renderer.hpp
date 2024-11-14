#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include "app/component/collider.hpp"
#include "app/utility/spritesheet_loader.hpp"
#include "common.hpp"
#include "core/component/render/renderer.hpp"
#include "core/utility/texture_loader.hpp"

class TextRenderer : public Renderer {

  public:
    TextRenderer(GameObject *game_object, Collider *collider);
    virtual ~TextRenderer() = default;

    virtual void render();

  protected:
    Collider *collider;
};

#endif
