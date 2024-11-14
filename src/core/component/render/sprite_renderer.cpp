#include "core/component/render/sprite_renderer.hpp"

#include <iostream>

SpriteRenderer::SpriteRenderer(GameObject *game_object, const std::string &file_location) : Renderer(game_object) {
    tex = TextureLoader::get_instance().load_texture(file_location);
}

void SpriteRenderer::render() {
    auto v = game_object->get_transform()->get_pos();
    DrawTexture(*tex, v.x, v.y, Color{tint});
}

int SpriteRenderer::get_height() const {
    return tex->height;
}

int SpriteRenderer::get_width() const {
    return tex->width;
}

bool SpriteRenderer::get_is_flipped() const {
    return is_flipped;
}

void SpriteRenderer::set_is_flipped(bool _is_flipped) {
    is_flipped = _is_flipped;
}

void SpriteRenderer::set_tint(unsigned char r, unsigned char g, unsigned char b) {
    tint = Color{r, g, b, 255};
}
