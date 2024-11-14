#include "app/game_object/level.hpp"

#include "toml++/toml.hpp"
#include <iostream>
#include <vector>

Level::Level(const std::string &levelFileLocation, const DebugInfo &debug_info) : lm(LevelMapper::get_instance()) {
    startPoint = Vector2{0.0f, 0.0f};
    loadLevel(levelFileLocation, tiles, lm, debug_info);

    // Extract the substring representing the level number
    std::string levelStr = levelFileLocation.substr(19, 1);
    std::cout << levelStr << std::endl;

    // Convert the level number string to an integer
    levelId = std::stoi(levelStr) - 1;
    std::cout << levelId << std::endl;

    // std::cout << "level object made" << std::endl;
}

void Level::loadLevel(const std::string &levelFileLocation, std::vector<Tile *> &tiles, const LevelMapper &levelMapper, const DebugInfo &debug_info) {
    try {
        // Parse the level file
        toml::table level_data = toml::parse_file(levelFileLocation);

        // Get the level data
        auto data = level_data.at("data").as_array();

        // Get the start point
        auto start_point = level_data.at("start_point").as_array();
        startPoint.x = start_point->get(0)->as_integer()->get() * 32.0f;
        startPoint.y = start_point->get(1)->as_integer()->get() * 32.0f;

        // get background
        std::optional<std::string> background = level_data["background"].value<std::string>();
        std::string backgroundFile = background.value_or("assets/sprites/bg_blue.png");

        // Get the tile size
        constexpr int tile_size = 32; // 32x32 pixel tiles
        size_t num_rows = data->size();

        Rectangle backgroundRectangle = {startPoint.x + 32, startPoint.y + 16, (float)(data->at(0).as_array()->size() * 31), (float)(num_rows * 31)};
        bgr = add_component<BackgroundRenderer>(backgroundFile, backgroundRectangle);
        bgr->set_z_index(1);

        /*
        size_t num_cols = data->front().as_array()->size();
        std::cout << "level rows: " << num_rows << std::endl;

        float level_center_x = (1920 - num_cols*tile_size) / 2.0f;
        float level_center_y = (1080 - num_rows*tile_size) / 2.0f;
        */

        player = new Character(debug_info);

        //  Iterate over the level data array
        for (std::size_t row_i = 0; row_i < num_rows; ++row_i) {
            auto row = data->at(row_i).as_array();
            for (std::size_t x = 0; x < row->size(); ++x) {

                // std::cout << "posi " << row_i << " " << x << std::endl;
                //  Get the tile code from the level data
                uint8_t object_code = row->at(x).as_integer()->get();

                // Calculate the position of the tile
                float tile_x = start_point->at(0).as_integer()->get() + x * tile_size;
                float tile_y = start_point->at(1).as_integer()->get() + row_i * tile_size;
                // std::cout << "act_posi " << tile_x << " " << tile_y << std::endl;

                // fix position so level is at the middle of screen
                tile_x += startPoint.x;
                tile_y += startPoint.y;

                if (object_code == 176) {
                    Vector2 positionee;
                    positionee.x = tile_x;
                    positionee.y = tile_y;
                    player->startPosition.x = positionee.x;
                    player->startPosition.y = positionee.y;
                    // player = new Character(debug_info);
                    player->get_transform()->set_pos(positionee.x, positionee.y);
                }

                if (object_code == 177) {
                    Vector2 positionee;
                    positionee.x = tile_x;
                    positionee.y = tile_y;
                    mushy = new Mush(positionee, debug_info);
                }
                if (object_code == 178) {
                    Vector2 positionee;
                    positionee.x = tile_x;
                    positionee.y = tile_y;
                    trunky = new Trunk(positionee, debug_info, player);
                }
                if (object_code == 179) {
                    Vector2 positionee;
                    positionee.x = tile_x;
                    positionee.y = tile_y;
                    beee = new Bee(positionee, debug_info, player);
                }

                if (object_code >= 0x00 && object_code <= 0x51) // tiles
                {

                    // Convert the tile code to its corresponding name
                    std::string tile_name = levelMapper.get_name(object_code);
                    // std::cout << tile_name << std::endl;

                    // Create a new tile and add it to the tiles vector
                    Tile *tile = new Tile("assets/sprites/terrain.sht", tile_name, tile_x, tile_y, false, debug_info);
                    tiles.push_back(tile);
                }
                if (object_code >= 0x70 && object_code <= 0x78) // traps
                {
                    std::string trap_name = levelMapper.get_name(object_code);
                }
                if (object_code >= 0x80 && object_code <= 0x88) // platforms
                {

                    std::string platform_name = levelMapper.get_name(object_code);
                }
                if (object_code >= 0xc0 && object_code <= 0xc7) // pickups
                {
                    std::string pickup_name = levelMapper.get_name(object_code);
                    // std::cout << pickup_name << std::endl;
                    Pickup *pickup = new Pickup({tile_x, tile_y}, pickup_name, debug_info);

                    pickups.push_back(pickup);
                }
            }
        }
    } catch (const toml::parse_error &err) {
        std::cerr << err << std::endl;
    }
}

void Level::unloadLevel() {

    for (auto tile : tiles) {
        tile->killTile = true;
    }
    tiles.clear();

    auto comps = Engine::get_instance().get_components<Collider>();

    for (Collider *collider : comps) {
        if (collider->tag == ColliderTag::ENEMY) {
            collider->kill = 1;
            //std::cout << "enemy deze wordt verwijdert" << std::endl;
        }
        if (collider->tag == ColliderTag::PICKUP) {
            collider->kill = 1;
            //std::cout << "pickup deze wordt verwijdert" << std::endl;
        }
        if (collider->tag == ColliderTag::ENEMY_PROJECTILE || collider->tag == ColliderTag::PLAYER_PROJECTILE) {
            //std::cout << "projectiel deze wordt verwijdert" << std::endl;
            collider->hit = 1;
        }
    }

    /*
    if (levelId == 0) {
        if (!mushy->get_is_deleted()) {
            mushy->killMush = true;
            std::cout << "deleting mush" << std::endl;
        }
    }

    if (levelId == 1) {
        trunky->killTrunk = true;
        std::cout << "deleting trunk" << std::endl;
    }

    if (levelId == 2) {
        beee->killBee = true;
        std::cout << "deleting bee" << std::endl;
        std::cout << "deleting trunk" << std::endl;
    }

    for (auto pickup : pickups) {
        std::cout << "we check a pickup" << std::endl;
        if (pickup) {
            pickup->killPickup = true;
            std::cout << "pickup position " << pickup->get_transform()->get_pos().x << std::endl;
        } else {
            std::cout << "pickup was deleted" << std::endl;
        }
    }
    std::cout << "where do we go wrong" << std::endl;
    pickups.clear();
    */

    // std::cout << "we do get here?" << std::endl;
    player->killPlayer = true;
    // player->freezed = true;
    // std::cout << "we deleted everythingg" << std::endl;
}

void Level::update(float delta_time) {
    if (killLevel) {
        unloadLevel();
        self_destruct();
    }
}
