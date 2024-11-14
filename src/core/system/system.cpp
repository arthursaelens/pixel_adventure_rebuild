#include "core/system/system.hpp"

System::System(const std::string &name) : name(name) {
}

std::string System::get_name() const {
    return name;
}
