#include "core/engine.hpp"
#include "common.hpp"
#include "core/system/game_object_system.hpp"
#include "core/system/rendering_system.hpp"
#include   "app/system/animation_system.hpp"

#include <iostream>

Engine &Engine::get_instance() {
    static Engine instance;
    return instance;
}

Engine::~Engine() {
    for (const auto &[id, e] : gameobjects) {
        delete e;
    }

    gameobjects.clear();

    clean_up_deferred();

    for (auto s : system_pipeline) {
        delete s;
    }
}

bool Engine::add_system_before(const std::string &other_system_name, System *s) {
    auto n = system_pipeline.begin();
    while (n != system_pipeline.end() && *n != nullptr) {
        if (other_system_name == (*n)->get_name()) {
            system_pipeline.insert(n, s);
            return true;
        }
        n++;
    }
    system_pipeline.push_front(s);
    return false;
}

bool Engine::add_system_after(const std::string &other_system_name, System *s) {
    bool insert_at_start = true;
    auto n = system_pipeline.begin();
    while (n != system_pipeline.end() && *n != nullptr) {
        insert_at_start = false;
        if (other_system_name == (*n)->get_name()) {
            system_pipeline.insert(++n, s);
            return true;
        }
        n++;
    }
    if (insert_at_start)
        system_pipeline.push_front(s);
    else
        system_pipeline.push_back(s);
    return false;
}

Engine::Engine() {
    GameObjectSystem *game_object_system = new GameObjectSystem("GAMEOBJECT_SYSTEM", gameobjects);
    RenderingSystem *rendering_system = new RenderingSystem("RENDERING_SYSTEM", 1920, 1080);

    add_system_after("PHYSICS_SYSTEM", game_object_system);
    add_system_after("COLLIDER_SYSTEM", rendering_system);
}

void Engine::update() {
    float delta_time = GetFrameTime();

    // loop over all systems in pipeline
    auto s = system_pipeline.begin();
    while (s != system_pipeline.end() && *s != nullptr) {
        (*s)->update(delta_time);
        s++; // get next system in pipeline
    }
}

void Engine::clean_up_deferred() {
    for (auto e : gameobjects_to_delete) {
        delete e;
    }

    gameobjects_to_delete.clear();
}

uint64_t Engine::add_gameobject(GameObject *e) {
    uint64_t internal_id = gameobject_counter++;
    gameobjects[internal_id] = e;
    return internal_id;
}

void Engine::delete_gameobject(GameObject *e) {
    for (const auto &[id, c] : e->get_components()) {
        components[id].erase(e->get_internal_id());
        if (components[id].empty()) {
            components.erase(id);
        }
    }
    gameobjects[e->get_internal_id()] = nullptr;
}

void Engine::delete_gameobject_deferred(GameObject *e) {
    gameobjects_to_delete.push_back(e);
    gameobjects[e->get_internal_id()] = nullptr;
}
System *Engine::get_system(const std::string &system_name) const {
    // loop over all systems in pipeline
    auto s = system_pipeline.begin();
    while (s != system_pipeline.end() && *s != nullptr) {
        if ((*s)->get_name() == system_name) {
            return *s;
        }
        s++;
    }
    return nullptr;
}
