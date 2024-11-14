#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "common.hpp"
#include "core/component/component.hpp"

#include <map>
#include <typeinfo>
#include <vector>

class Component;
class Transform2D;

class GameObject {
  public:
    GameObject();
    virtual ~GameObject();
    virtual void update(float delta_time) = 0;
    uint64_t get_internal_id() const;

    template <class T, class... Args>
    T *add_component(Args &&...args) {
        T *c = new T(this, args...);
        std::size_t c_type = typeid(T).hash_code();
        components[c_type] = c;
        register_component_to_engine(c_type, c);
        return c;
    };

    template <class T>
    T *get_component() const {
        T *c = nullptr;
        if (auto it = components.find(typeid(T).hash_code()); it != components.end()) {
            c = it->second;
        }
        return c;
    };

    std::map<std::size_t, Component *> get_components() const;
    Transform2D *get_transform() const;

    bool get_is_deleted() const { return is_deleted; }

  private:
    uint64_t internal_id;
    std::map<std::size_t, Component *> components;
    void register_component_to_engine(std::size_t c_type, Component *c);

  protected:
    bool is_deleted = false;
    Transform2D *transform;
    void self_destruct();
};

#endif
