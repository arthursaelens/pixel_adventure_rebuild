#ifndef TEXTURE_LOADER_HPP
#define TEXTURE_LOADER_HPP

#include "common.hpp"
#include "core/utility/utility_functions.hpp"

#include <map>
#include <string>

class TextureLoader {
  public:
    static TextureLoader &get_instance();

    TextureLoader(TextureLoader const &) = delete;
    void operator=(const TextureLoader &) = delete;

    ~TextureLoader();

    Texture2D *load_texture(const std::string &image_path);
    void unload_texture(const std::string &image_path);
    void unload_all_textures();

  private:
    TextureLoader() = default;

    std::map<uint32_t, Texture2D> texture_cache;
};

#endif
