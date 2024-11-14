#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "common.hpp"
#include "core/data_unit.hpp"
#include "core/game_object/game_object.hpp"
#include "core/system/system.hpp"

#include <list>
#include <map>

class Component;
class System;

class Engine {
  public:
    static Engine &get_instance();
    Engine(Engine const &) = delete;
    void operator=(const Engine &) = delete;

    ~Engine();

    void update();
    void clean_up_deferred();
    uint64_t add_gameobject(GameObject *e);
    void delete_gameobject(GameObject *e);
    void delete_gameobject_deferred(GameObject *e);

    void add_component(uint64_t gameobject_id, size_t c_type, Component *c) {
        if (components.find(c_type) == components.end()) {
            for (auto &d : d_units) {
                d.second.set_needs_update(true);
            }
        }
        components[c_type][gameobject_id] = c;
    };

    template <class T>
    DataUnit::ComponentCollection<T> get_components() {
        if (auto it = d_units.find(typeid(T).hash_code()); it == d_units.end()) {
            d_units.insert({typeid(T).hash_code(), DataUnit(components)});
        }

        if (!d_units.at(typeid(T).hash_code()).is_updated()) {
            d_units.at(typeid(T).hash_code()).update<T>();
        }

        return d_units.at(typeid(T).hash_code()).get_components<T>();
    };

    bool add_system_before(const std::string &other_system_name, System *s);
    bool add_system_after(const std::string &other_system_name, System *s);

    System *get_system(const std::string &system_name) const;

  private:
    Engine();

    std::list<System *> system_pipeline;
    uint64_t gameobject_counter = 0;
    std::map<uint64_t, GameObject *> gameobjects;
    std::map<size_t, std::map<uint64_t, Component *>> components;
    std::map<size_t, DataUnit> d_units;
    std::vector<GameObject *> gameobjects_to_delete;
};

#endif
