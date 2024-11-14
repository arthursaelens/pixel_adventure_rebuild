#include "app/component/text_renderer.hpp"

#include <fstream>
#include <iostream>

TextRenderer::TextRenderer(GameObject *game_object, Collider *collider) : Renderer(game_object) {
    this->collider = collider;
    set_z_index(3);
}

void TextRenderer::render() {
    if (collider->finishedLevel) {
        DrawText("Level completed!", 645, 460, 80, WHITE);
    }
    if (collider->characterLives <= 0) {
        if (collider->respawns == 2) {

            DrawText("Respawning... 2 lives left", 560, 460, 70, WHITE);

        } else if (collider->respawns == 1) {

            DrawText("Respawning... 1 live left", 580, 460, 70, WHITE);

        } else if (collider->respawns == 0) {
            DrawText("Game over", 720, 450, 100, WHITE);
        }
    }
}
