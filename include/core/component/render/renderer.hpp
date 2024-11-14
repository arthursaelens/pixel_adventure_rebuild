#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "core/component/component.hpp"

class Renderer : public Component {
  public:
    Renderer(GameObject *game_object, unsigned int z_index = 0);
    virtual ~Renderer() = default;

    virtual void render() = 0;
    unsigned int get_z_index() const;
    void set_z_index(unsigned int z_index);

  private:
    unsigned int z_index = 0;
};

#endif
