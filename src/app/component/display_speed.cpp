#include "app/component/display_speed.hpp"

SpeedDisplay::SpeedDisplay(GameObject *game_object) : Renderer(game_object) {
    arrowScalingFactor = 0.2;
}

void SpeedDisplay::render() {
    Vector2 offs = {32, 42}; 
    Vector2 startPos = game_object->get_transform()->get_pos();

    startPos.x += offs.x;
    startPos.y += offs.y;

    // Calculate the end point of the arrow
    Vector2 arrowEnd = {
        startPos.x + displaySpeed.x * arrowScalingFactor,
        startPos.y + displaySpeed.y * arrowScalingFactor};

    // Draw the arrow (line from position to arrowEnd)
    DrawLineEx(startPos, arrowEnd, 8, RED);
}
