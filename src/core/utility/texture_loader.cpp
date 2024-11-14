#include "core/utility/texture_loader.hpp"
#include "common.hpp"

#include <iostream>

TextureLoader &TextureLoader::get_instance() {
    static TextureLoader instance;
    return instance;
}

TextureLoader::~TextureLoader() {
    unload_all_textures();
}

Texture2D *TextureLoader::load_texture(const std::string &image_path) {
    uint32_t img_hash = Utility::to_hash(image_path);

    if (auto it = texture_cache.find(img_hash); it == texture_cache.end()) {
        Image img = LoadImage(image_path.c_str());
        texture_cache[img_hash] = LoadTextureFromImage(img);
        UnloadImage(img);
    }

    return &texture_cache[img_hash];
}

void TextureLoader::unload_texture(const std::string &image_path) {
    uint32_t img_hash = Utility::to_hash(image_path);

    if (auto it = texture_cache.find(img_hash); it != texture_cache.end()) {
        UnloadTexture(it->second);
        texture_cache.erase(img_hash);
    }
}

void TextureLoader::unload_all_textures() {
    for (const auto &[id, e] : texture_cache) {
        UnloadTexture(e);
    }

    texture_cache.clear();
}
