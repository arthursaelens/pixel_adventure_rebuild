#include "app/component/spritesheet_renderer.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
// use for file parsing

SpriteSheetRenderer::SpriteSheetRenderer(GameObject *game_object, const std::string &file_location, const std::string sprite_name)
    : Renderer(game_object) {

    
    this->sprite_name = sprite_name;
    if (sprite_name != "background") {

        load_sprite_sheet(file_location);
        png_location = get_png_location(file_location);

        tex_big = TextureLoader::get_instance().load_texture(png_location);
    } else {
        png_location = file_location;
        tex_big = TextureLoader::get_instance().load_texture(png_location);
    }

    // test_textur = TextureLoader::get_instance().load_texture("assets/sprites/terrain.png");

    // was to compare character info to tile info
    /*
    if (sprite_name.find("IDLE") != std::string::npos)
    {
        std::cout << "Initializing SpriteSheetRenderer" << std::endl;
        std::cout << "GameObject: " << game_object << std::endl;
        std::cout << "File Location: " << file_location << std::endl;
        std::cout << "Sprite Name: " << sprite_name << std::endl;
        std::cout << "PNG Location: " << png_location << std::endl;
        std::cout << "right PNG Location for terrain: assets/sprites/terrain.png" << std::endl;
        std::cout << "Big Texture Loaded: " << tex_big << std::endl;
    }
    */
}

void SpriteSheetRenderer::load_sprite_sheet(const std::string &file_path) {
    std::ifstream file(file_path);
    std::string line;

    while (std::getline(file, line)) { // terminates at end of file
        std::istringstream iss(line);
        std::string sprite_name;
        int x, y, width, height;

        if (!(iss >> sprite_name >> x >> y >> width >> height)) {
            // Error handling: Failed to parse line so skip to the next one
            continue;
        }

        sprite_info_map[sprite_name] = {x, y, width, height, true}; // add to the mapping: sprite_name -> SpriteInfo (is a struct)
    }
}


SpriteInfo SpriteSheetRenderer::get_sprite_info(const std::string &sprite_name) const {
    if (sprite_name == "background") {
        return {32,32,32,32 ,true};
    }
    auto it = sprite_info_map.find(sprite_name);

    /*
    it wijst nu naar juist key val paar,
    als key niet in mapping dan wijst
    it naar end of mapping
    */

    if (it != sprite_info_map.end()) {
        return it->second;
    }
    // std::cout << "Sprite name '" << sprite_name << "' not found" << std::endl;
    //  Handle sprite not found
    return {0, 0, 0, 0, false}; // Default sprite info
}


std::string SpriteSheetRenderer::get_png_location(const std::string &file_path) {
    std::ifstream file(file_path);

    std::string png_location;
    std::getline(file, png_location); // Read the first line
    png_location = png_location.substr(png_location.find(' ') + 1);

    //std::cout << png_location << std::endl;

    file.close();

    return png_location;
}


void SpriteSheetRenderer::updateSprite(std::string updatedSpriteName) {
    sprite_name = updatedSpriteName;
}

/*
bool containsAnimation(const std::string& str) {
    // Substrings to check for
    std::vector<std::string> substrings = {"IDLE", "RUN", "FALL", "FAINT"};

    // Check if any of the substrings is found in the input string
    for (const std::string& substr : substrings) {
        if (str.find(substr) != std::string::npos) {
            return true; // Found at least one substring
        }
    }

    return false; // None of the substrings found
}
*/

void SpriteSheetRenderer::set_is_flipped(bool filipiddy) {
    is_flipped = filipiddy;
}

bool SpriteSheetRenderer::get_is_flipped() const {
    return is_flipped;
}

void SpriteSheetRenderer::render() {
    // std::cout << sprite_name << std::endl;
    SpriteInfo sprite_info = get_sprite_info(sprite_name);

    if (sprite_info.valid) {
        /*
        if (sprite_name.find("IDLE") != std::string::npos || print_index < 3){
        std::cout << "Sprite Info: " << sprite_name<< " - x: " << static_cast<float>(sprite_info.x) << ", y: " << static_cast<float>(sprite_info.y)
        << ", width: " << static_cast<float>(sprite_info.width) << ", height: " << static_cast<float>(sprite_info.height) << std::endl;
        }
        print_index++;

        */
        // Print sprite info for testing

        source_rect = {static_cast<float>(sprite_info.x), static_cast<float>(sprite_info.y), static_cast<float>(sprite_info.width), static_cast<float>(sprite_info.height)};
        auto v = game_object->get_transform()->get_pos();

        // DrawTexture(*tex_big, v.x, v.y, WHITE);
        // Rectangle source_dup = {source_rect.x+500, source_rect.y, source_rect.width, source_rect.height};

        Rectangle flippedRect = source_rect;
        if (is_flipped) {
            flippedRect.width *= -1;
        }

        // normally this is the only Draw function we need
        DrawTextureRec(*tex_big, flippedRect, v, WHITE);

        // because something goes wrong for loading the level png into tex_big, use a "hard_coded" texture
        /*
        if (!containsAnimation(sprite_name)) {

            DrawTextureRec(*test_textur ,source_rect , v, WHITE);

        }
        */

        // some tests, seeing if every object gets rendering and if the location in the png file is correct
        // DrawRectangle(round(v.x), round(v.y), 10, 10, RED);
        // DrawRectangleLinesEx(source_rect, 2, GREEN);     // Draw rectangle outline with extended parameters
    }
}
