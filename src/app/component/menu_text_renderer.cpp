#include "app/component/menu_text_renderer.hpp"

MenuTextRenderer::MenuTextRenderer(GameObject *game_object) : Renderer(game_object) {}

void MenuTextRenderer::render() {
    float equal_spacing = 1920 / (number_of_levels + 1);
    int offset = 160;

    if (selectingDebugMode) {
        DrawText("Level 1", equal_spacing - offset, 500, 64, GRAY);
        DrawText("Level 2", 2 * equal_spacing - offset, 500, 64, GRAY);
        DrawText("Level 3", 3 * equal_spacing - offset, 500, 64, GRAY);
        if (debugMode) {
            DrawText("Turn Off Debugging Mode", 1920 / 2 - offset * 2.35, 700, 52, DARKGREEN);
            Rectangle rect = {1920 / 2 - offset * 2.35 - 17, 700 - 30, 717, 110};
            DrawRectangleLinesEx(rect, 6, DARKGREEN);
        }
        if (!debugMode) {
            DrawText("Turn On Debugging Mode", 1920 / 2 - offset * 2.35
            , 700, 52, WHITE);
        }
    }

    if (!selectingDebugMode) {
        if (debugMode) {
            DrawText("Turn Off Debugging Mode", 1920 / 2 - offset * 2.2 + 30 , 710, 42, DARKGREEN);
            Rectangle rect = {1920 / 2 - offset * 2.3 + 30 , 700 - 10, 590, 75};
            DrawRectangleLinesEx(rect, 6, DARKGREEN);

            if (level_index == 0) {
                DrawText("Level 1", equal_spacing - offset, 485, 86, WHITE);
                DrawText("Level 2", 2 * equal_spacing - offset, 500, 64, GRAY);
                DrawText("Level 3", 3 * equal_spacing - offset, 500, 64, GRAY);
            }
            if (level_index == 1) {
                DrawText("Level 1", equal_spacing - offset, 500, 64, GRAY);
                DrawText("Level 2", 2 * equal_spacing - offset, 485, 86, WHITE);
                DrawText("Level 3", 3 * equal_spacing - offset, 500, 64, GRAY);
            }
            if (level_index == 2) {
                DrawText("Level 1", equal_spacing - offset, 500, 64, GRAY);
                DrawText("Level 2", 2 * equal_spacing - offset, 500, 64, GRAY);
                DrawText("Level 3", 3 * equal_spacing - offset, 485, 86, WHITE);
            }
        } else {
            DrawText("Turn On Debugging Mode", 1920 / 2 - offset * 2.2 + 30, 710, 42, GRAY);

            if (level_index == 0) {
                DrawText("Level 1", equal_spacing - offset, 485, 86, WHITE);
                DrawText("Level 2", 2 * equal_spacing - offset, 500, 64, GRAY);
                DrawText("Level 3", 3 * equal_spacing - offset, 500, 64, GRAY);
            }
            if (level_index == 1) {
                DrawText("Level 1", equal_spacing - offset, 500, 64, GRAY);
                DrawText("Level 2", 2 * equal_spacing - offset, 485, 86, WHITE);
                DrawText("Level 3", 3 * equal_spacing - offset, 500, 64, GRAY);
            }
            if (level_index == 2) {
                DrawText("Level 1", equal_spacing - offset, 500, 64, GRAY);
                DrawText("Level 2", 2 * equal_spacing - offset, 500, 64, GRAY);
                DrawText("Level 3", 3 * equal_spacing - offset, 485, 86, WHITE);
            }
        }
    }
}
