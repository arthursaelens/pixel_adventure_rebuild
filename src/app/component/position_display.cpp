#include "app/component/position_display.hpp"
#include "raylib.h" // Probably unnecessary

// constructor for PositionDisplay
PositionDisplay::PositionDisplay(GameObject *game_object) : Renderer(game_object) {}

void PositionDisplay::render() {
    auto position = game_object->get_transform()->get_pos();
    DrawText(TextFormat("X: %.2f", position.x), position.x + 64, position.y + 30, 25, WHITE);
    DrawText(TextFormat("Y: %.2f", position.y), position.x + 64, position.y + 60, 25, WHITE);
    DrawText(TextFormat("GameObject ID: %d", game_object->get_internal_id()), position.x + 64, position.y, 25, WHITE);
}
