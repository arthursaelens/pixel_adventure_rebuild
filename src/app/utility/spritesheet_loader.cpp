#include "app/utility/spritesheet_loader.hpp"

#include <fstream>
#include <sstream>
// use for file parsing
#include <iostream>


SpriteSheetLoader::SpriteSheetLoader() {}

void SpriteSheetLoader::load_sprite_sheet(const std::string &file_path) {
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

SpriteInfo SpriteSheetLoader::get_sprite_info(const std::string &sprite_name) const {
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

std::string SpriteSheetLoader::get_png_location(const std::string &file_path) {
    std::ifstream file(file_path);

    std::string png_location;
    std::getline(file, png_location); // Read the first line
    png_location = png_location.substr(png_location.find(' ') + 1);

    //std::cout << png_location << std::endl;

    file.close();

    return png_location;
}
