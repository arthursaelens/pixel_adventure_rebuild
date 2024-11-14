#include "core/component/render/renderer.hpp"

Renderer::Renderer(GameObject *game_object, unsigned int z_index) : Component(game_object), z_index(z_index) {
}

unsigned int Renderer::get_z_index() const {
    return z_index;
}

void Renderer::set_z_index(unsigned int _z_index) {
    z_index = _z_index;
}
