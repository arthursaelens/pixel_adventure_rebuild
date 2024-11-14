#ifndef RENDERING_SYSTEM_HPP
#define RENDERING_SYSTEM_HPP

#include "common.hpp"
#include "core/component/render/sprite_renderer.hpp"
#include "core/system/system.hpp"

#include <map>
#include <vector>

class RenderingSystem : public System {
  public:
    RenderingSystem(const std::string &name, int frame_width, int frame_height) : System(name) {
        render_target = LoadRenderTexture(frame_width, frame_height);
        SetTextureFilter(render_target.texture, TEXTURE_FILTER_BILINEAR); // Texture scale filter to use
        std::cout << " RenderingSystem object is made " << std::endl;
    }

    void update(float delta_time);

  private:
    RenderTexture2D render_target;
    void render_frame(int window_width, int window_height);
};

#endif
