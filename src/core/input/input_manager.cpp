#include "core/input/input_manager.hpp"
#include "common.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

InputManager &InputManager::get_instance() {
    static InputManager instance;
    return instance;
}

InputManager::InputManager() {
    std::ifstream input("assets/input/control.inp");
    std::string line;

    getline(input, line);

    std::string cc_name = line.substr(1, line.length() - 1);
    ControlContext cc(cc_name);

    getline(input, line);

    while (!line.empty() && !input.eof()) {
        std::istringstream sprite_line(line);
        std::string key_name;
        unsigned int key_code;

        sprite_line >> key_name;
        sprite_line >> key_code;

        cc.change_key(Utility::to_hash(key_name), key_code);

        getline(input, line);
    }

    auto cc_p = control_contexts.insert({Utility::to_hash(cc_name), std::move(cc)});

    active_context = &(cc_p.first->second);
}

int InputManager::get_pressed_key() const {
    return GetKeyPressed();
}

bool InputManager::is_action_pressed(const std::string &action) const {
    if (active_context == nullptr) {
        return false;
    }

    unsigned int hash = Utility::to_hash(action);
    int key = active_context->get_key_for_action(hash);

    return IsKeyPressed(key);
}

bool InputManager::is_action_down(const std::string &action) const {
    if (active_context == nullptr) {
        return false;
    }

    unsigned int hash = Utility::to_hash(action);
    int key = active_context->get_key_for_action(hash);

    return IsKeyDown(key);
}

void InputManager::switch_control_context(const std::string &control_context) {
    auto it = control_contexts.find(Utility::to_hash(control_context));

    if (it != control_contexts.end()) {
        active_context = &(it->second);
    }
}

KeyChangeStatus InputManager::change_key(uint32_t control_context_hash, std::string action, int new_key) {
    bool is_changed = false;

    if (auto it = control_contexts.find(control_context_hash); it != control_contexts.end()) {
        return it->second.change_key(Utility::to_hash(action), new_key);
    }

    return KeyChangeStatus{false, 0};
}
