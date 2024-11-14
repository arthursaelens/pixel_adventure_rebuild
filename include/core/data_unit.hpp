#ifndef DATA_UNIT_HPP
#define DATA_UNIT_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "core/component/component.hpp"

#include <iostream>
#include <map>
#include <vector>

class Component;

class DataUnit {
  public:
    DataUnit(std::map<size_t, std::map<uint64_t, Component *>> &components) : components(components){};

    template <class T>
    class ComponentCollection {

        class iterator : public std::iterator<
                             std::input_iterator_tag, // iterator_category
                             T *,                     // value_type
                             long,                    // difference_type
                             T **,                    // pointer
                             T *&                     // reference
                             > {
          public:
            explicit iterator(ComponentCollection &parent_cc, bool is_end = false) : parent_cc(parent_cc) {
                n = 0;
                size_t total_size = 0;
                for (auto x : parent_cc.parent_data_unit.component_ids) {
                    size_t s = parent_cc.parent_data_unit.components[x].size();
                    total_size += s;
                    borders.push_back(s);
                }
                if (is_end) {
                    n = total_size;
                }
            }
            iterator &operator++() {
                n++;
                return *this;
            }
            iterator operator++(int) {
                iterator retval = *this;
                ++(*this);
                return retval;
            }
            bool operator==(iterator other) const { return n == other.n; }
            bool operator!=(iterator other) const {
                return !(*this == other);
                ;
            }
            T *operator*() {
                int current_c = 0;
                int jump_size = n;
                int total_border = borders[current_c];
                while (n >= total_border && current_c < borders.size()) {
                    jump_size -= borders[current_c];
                    current_c++;
                    total_border += borders[current_c];
                }
                if (current_c >= borders.size()) {
                    return nullptr;
                }
                if (last_c != current_c) {
                    last_c = current_c;
                    ccc = parent_cc.parent_data_unit.components[parent_cc.parent_data_unit.component_ids[current_c]].begin();

                } else {
                    if (jump_size - prev_jump > 0)
                        ccc++;
                }

                prev_jump = jump_size;

                return (T *)(ccc->second);
            }

          private:
            uint64_t n;
            ComponentCollection &parent_cc;
            std::vector<size_t> borders;
            std::map<uint64_t, Component *>::iterator ccc;
            std::map<uint32_t, bool> is_set;
            int last_c = -1;
            int prev_jump = 0;
        };

      public:
        ComponentCollection(DataUnit &parent_data_unit) : parent_data_unit(parent_data_unit){};
        iterator begin() { return iterator(*this); }
        iterator end() { return iterator(*this, true); }

      private:
        DataUnit &parent_data_unit;
    };

    template <class T>
    ComponentCollection<T> get_components() {
        return ComponentCollection<T>(*this);
    }

    template <class T>
    void update() {
        component_ids.clear();
        for (auto m : components) {
            if (m.second.size() > 0) {
                Component *c = m.second.begin()->second;
                if (dynamic_cast<T *>(c) != nullptr) {

                    component_ids.push_back(m.first);
                }
            }
        }
        m_is_updated = true;
        m_needs_update = false;
    }
    bool is_updated() {
        return m_is_updated;
    }
    bool get_needs_update() {
        return m_needs_update;
    }
    void set_needs_update(bool needs_update) {
        m_is_updated = !needs_update;
        m_needs_update = needs_update;
    }

  private:
    bool m_is_updated = false;
    bool m_needs_update = false;
    std::map<size_t, std::map<uint64_t, Component *>> &components;
    std::vector<size_t> component_ids;
};

#pragma GCC diagnostic pop

#endif
