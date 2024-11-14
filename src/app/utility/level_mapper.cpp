#include "app/utility/level_mapper.hpp"

#include "toml++/toml.hpp"
#include <iomanip>
#include <iostream>

LevelMapper &LevelMapper::get_instance() {
    static LevelMapper instance;
    return instance;
}

LevelMapper::LevelMapper() {
    try {
        toml::table level_mapping = toml::parse_file("assets/levels/level_mapping.toml");

        for (const auto &[table_key, table] : *level_mapping.as_table()) {
            for (const auto &[name, code] : *table.as_table()) {
                level_map[std::string(name)] = code.as_integer()->get();
                level_map_inverse[code.as_integer()->get()] = std::string(name);
            }
        }
    } catch (const toml::parse_error &err) {
        std::cerr << err << std::endl;
        std::exit(1);
    }

     for (auto [name, code] : level_map) {
         std::cout << name << " = " << std::hex << (int)code << std::endl;
     }

     for (auto [code, name] : level_map_inverse) {
         std::cout << std::hex << (int)code << " = " << name << std::endl;
    }
}

uint8_t LevelMapper::get_code(const std::string &name) const {
    return level_map.at(name);
}

const std::string &LevelMapper::get_name(uint8_t code) const {
    return level_map_inverse.at(code);
}
