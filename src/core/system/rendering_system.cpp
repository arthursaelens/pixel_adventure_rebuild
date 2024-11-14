#include "core/system/rendering_system.hpp"
#include "common.hpp"

#include <iostream>

void RenderingSystem::render_frame(int window_width, int window_height) {
    //std::cout << "render_frame is called" << std::endl;
    BeginTextureMode(render_target);
    ClearBackground(BLACK);

    auto cc = Engine::get_instance().get_components<Renderer>();
    std::map<unsigned int, std::vector<Renderer *>> r_order;

    // Loop over render components
    for (auto cc_it = cc.begin(); cc_it != cc.end(); cc_it++) {
        Renderer *r = (*cc_it);

        if (r->get_z_index() > 0) {
            r_order[r->get_z_index()].push_back(r);
        } else {
            r->render();
        }
    }

    for (auto &m : r_order) {
        for (auto r : m.second) {
            r->render();
        }
    }

    DrawFPS(20, 0);
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexturePro(render_target.texture, Rectangle{0.0f, 0.0f, (float)render_target.texture.width, (float)-render_target.texture.height},
                   Rectangle{0.0, 0.0, (float)window_width, (float)window_height},
                   Vector2{0, 0}, 0.0f, WHITE);

    EndDrawing();
}

void RenderingSystem::update(float delta_time) {
    render_frame(GetScreenWidth(), GetScreenHeight());
}
