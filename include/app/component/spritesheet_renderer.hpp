#ifndef SPRITESHEET_RENDERER_HPP
#define SPRITESHEET_RENDERER_HPP

#include "app/utility/spritesheet_loader.hpp"
#include "common.hpp"
#include "core/component/render/renderer.hpp"
#include "core/utility/texture_loader.hpp"

#include <string>
#include <unordered_map> //used for mapping

class SpriteSheetRenderer : public Renderer {
  public:
    SpriteSheetRenderer(GameObject *game_object, const std::string &file_location, std::string sprite_name);
    virtual ~SpriteSheetRenderer() = default;
    virtual void updateSprite(std::string updatedSpriteName);

    virtual void render();
    int get_height() const;
    int get_width() const;
    bool get_is_flipped() const;
    void set_is_flipped(bool filipiddy);

  protected:
    std::string png_location;
    SpriteSheetLoader* spriteSheetLoader;
    std::string sprite_name;

  private:
    Texture2D *tex_big;
    bool is_flipped = false;
    Rectangle source_rect;

    //previously spritesheetloader methods
    void load_sprite_sheet(const std::string& file_path);
    SpriteInfo get_sprite_info(const std::string& sprite_name) const;
    std::string get_png_location(const std::string& file_path);

    //also previously attribute of spshloader
    std::unordered_map<std::string, SpriteInfo> sprite_info_map;
};

#endif
