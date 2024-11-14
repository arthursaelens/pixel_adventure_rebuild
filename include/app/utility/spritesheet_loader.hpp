//we no longer use this class, component added to component does not get deleted properly
//SpriteInfo is still in use
#ifndef SPRITE_SHEET_LOADER_HPP
#define SPRITE_SHEET_LOADER_HPP

#include <string> //used for sprite_name
#include <unordered_map> //used for mapping

struct SpriteInfo {
    
    int x, y, width, height;
    bool valid;
    
};

class SpriteSheetLoader {
public:
    
    SpriteSheetLoader();
    
    void load_sprite_sheet(const std::string& file_path);
    SpriteInfo get_sprite_info(const std::string& sprite_name) const;
    std::string get_png_location(const std::string& file_path);

private:
    std::unordered_map<std::string, SpriteInfo> sprite_info_map;
    //efficiente manier om key/Value paren bij te houden, zie als beejte als dictionary 
    
    
    
};

#endif // SPRITE_SHEET_LOADER_HPP
