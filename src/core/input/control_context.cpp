#include "core/input/control_context.hpp"
#include "common.hpp"

ControlContext::ControlContext(const std::string &name) : name(name) {
}

int ControlContext::get_key_for_action(unsigned int hash) const {
    return input_to_key.at(hash);
}

bool ControlContext::subscribe_to_key(INPUT_PRESS_TYPE press_type, uint64_t internal_id, std::function<void(int action)> cb) {
    return false;
}

bool ControlContext::unsubscribe_to_key(INPUT_PRESS_TYPE press_type, uint64_t internal_id, std::function<void(int action)> cb) {
    return false;
}

KeyChangeStatus ControlContext::change_key(uint32_t key_hash, int new_key) {
    input_to_key[key_hash] = new_key;
    return KeyChangeStatus();
}
