#ifndef CONTROL_CONTEXT_HPP
#define CONTROL_CONTEXT_HPP

#include "common.hpp"

#include <functional>
#include <map>
#include <string>

enum INPUT_PRESS_TYPE {
    PRESS,
    DOWN,
    RELEASED
};

struct KeyChangeStatus {
    bool ok;
    uint32_t existing_action;
};

class ControlContext {
  public:
    ControlContext(const std::string &name);

    int get_key_for_action(unsigned int hash) const;
    bool subscribe_to_key(INPUT_PRESS_TYPE press_type, uint64_t internal_id, std::function<void(int action)> cb);
    bool unsubscribe_to_key(INPUT_PRESS_TYPE press_type, uint64_t internal_id, std::function<void(int action)> cb);
    KeyChangeStatus change_key(uint32_t key_hash, int new_key);

  private:
    std::string name;

    // <action_hash, actual_key>
    std::map<uint32_t, int> input_to_key;

    // <action_hash, <internal_id, cb>>
    std::map<uint32_t, std::map<uint64_t, std::function<void(int action)>>> is_pressed_cb;
    std::map<uint32_t, std::map<uint64_t, std::function<void(int action)>>> is_down_cb;
    std::map<uint32_t, std::map<uint64_t, std::function<void(int action)>>> is_released_cb;
};

#endif
