#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "core/engine.hpp"

#include <map>
#include <string>
#include <typeinfo>
#include <vector>

class System {
  public:
    System(const std::string &name);
    virtual ~System() = default;
    virtual void update(float delta_time) = 0;
    std::string get_name() const;

  private:
    std::string name;
};

#endif
