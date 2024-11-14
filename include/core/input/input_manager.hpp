#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "common.hpp"
#include "core/input/control_context.hpp"
#include "core/utility/utility_functions.hpp"

#include <functional>
#include <map>
#include <string>
#include <vector>

class InputManager {
  public:
    static InputManager &get_instance();
    InputManager(InputManager const &) = delete;
    void operator=(InputManager const &) = delete;

    int get_pressed_key() const;

    bool is_action_pressed(const std::string &action) const;
    bool is_action_down(const std::string &action) const;
    void switch_control_context(const std::string &control_context);

    KeyChangeStatus change_key(uint32_t control_context_hash, std::string action, int new_key);

  private:
    InputManager();

    ControlContext *active_context;
    std::map<unsigned int, ControlContext> control_contexts;
};

#endif
