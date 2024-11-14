#include "app/component/background_renderer.hpp"

#include <fstream>
#include <iostream>

BackgroundRenderer::BackgroundRenderer(GameObject *game_object, std::string &pngFileLocation, Rectangle rec) : Renderer(game_object) {
    texture = TextureLoader::get_instance().load_texture(pngFileLocation);
    this->rec = rec;
}

//render called from rendering_system, has movement (see while loops)
void BackgroundRenderer::render() {

    Color color = {33, 31, 48, 255};
    ClearBackground(color);
    offset -= 0.5;
    Rectangle source = (Rectangle){0, offset, 128, 128};
    Vector2 origin = {0, 0};
    float r = 0;

    float maxWidth = rec.width + rec.x;
    float maxHeight = rec.y + rec.height;
    float x = rec.x;

    while (x < maxWidth) {

        float y = rec.y;

        while (y < maxHeight) {
            
            // Calculate the remaining width and height to cover
            float restWidth = fmin(128, maxWidth - x);
            float restHeight = fmin(128, maxHeight - y);

            Rectangle source = {0, offset, restWidth, restHeight};
            Rectangle destination = {x, y, restWidth, restHeight};

            DrawTexturePro(*texture, source, destination, origin, r, Color{tint});

            y += restHeight;

            //old implementation for moving backgroung
            /*
            if (!(x + 128 > maxWidth || y + 128 > maxHeigth && !(x == maxWidth || y == maxHeigth))) {
                Rectangle destination = (Rectangle){x, y, 128, 128};
                DrawTexturePro(*texture, source, destination, origin, r, Color{tint});
            } else {
                float restbreedte = maxWidth - x;
                float resthoogte = maxHeigth - y;
                if (resthoogte >= 128) {
                    resthoogte = 128;
                    float x1 = x;
                    Rectangle source = {0, 0, restbreedte, resthoogte};
                    Rectangle destination = {x1, y, restbreedte, resthoogte};
                    DrawTexturePro(*texture, source, destination, origin, r, Color{tint});
                }
                if (restbreedte >= 128) {
                    restbreedte = 128;
                    float y1 = y;
                    Rectangle source = {0, 0, restbreedte, resthoogte};
                    Rectangle destination = {x, y1, restbreedte, resthoogte};
                    DrawTexturePro(*texture, source, destination, origin, r, Color{tint});
                }
            }
            */

            //y += 128;
        }
        x += 128;
    }
}
