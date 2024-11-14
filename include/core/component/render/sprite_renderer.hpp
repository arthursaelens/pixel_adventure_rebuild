#ifndef SPRITE_RENDERER_HPP
#define SPRITE_RENDERER_HPP

#include "common.hpp"
#include "core/component/render/renderer.hpp"
#include "core/utility/texture_loader.hpp"

#include <string>

class SpriteRenderer : public Renderer {
  public:
    SpriteRenderer(GameObject *game_object, const std::string &file_location); // Load from cache if possible
    virtual ~SpriteRenderer() = default;

    virtual void render();
    int get_height() const;
    int get_width() const;
    bool get_is_flipped() const;
    void set_is_flipped(bool is_flipped);
    void set_tint(unsigned char r, unsigned char g, unsigned char b);

  protected:
    Texture2D *tex;
    Color tint{255, 255, 255, 255};
    bool is_flipped = false;
};

#endif
