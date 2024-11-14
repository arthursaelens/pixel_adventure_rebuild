#include "core/system/game_object_system.hpp"

GameObjectSystem::GameObjectSystem(const std::string &name, std::map<uint64_t, GameObject *> &gameobjects) : System(name), gameobjects(gameobjects) {
}

void GameObjectSystem::update(float delta_time) {
    std::vector<unsigned int> to_delete;

    for (const auto &[id, e] : gameobjects) {
        if (e) {
            e->update(delta_time);
        } else {
            // Cleanup step
            to_delete.push_back(id);
        }
    }

    for (auto id : to_delete) {
        gameobjects.erase(id);
    }

    Engine::get_instance().clean_up_deferred();
}
