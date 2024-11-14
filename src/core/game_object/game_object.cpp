#include "core/game_object/game_object.hpp"
#include "common.hpp"
#include "core/engine.hpp"

#include <iostream>

GameObject::GameObject() {
    internal_id = Engine::get_instance().add_gameobject(this);
    transform = add_component<Transform2D>();
}

GameObject::~GameObject() {
    for (const auto &[id, c] : components) {
        delete c;
    }

    Engine::get_instance().delete_gameobject(this);
}

uint64_t GameObject::get_internal_id() const {
    return internal_id;
}

std::map<size_t, Component *> GameObject::get_components() const {
    return components;
}

Transform2D *GameObject::get_transform() const {
    return transform;
}

void GameObject::register_component_to_engine(size_t c_type, Component *c) {
    Engine::get_instance().add_component(internal_id, c_type, c);
}

void GameObject::self_destruct() {
    if (!is_deleted) {
        Engine::get_instance().delete_gameobject_deferred(this);
        is_deleted = true;
    }
}
