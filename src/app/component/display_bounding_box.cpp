#include "app/component/display_bounding_box.hpp"
#include <fstream>
#include <iostream>

DisplayBoundingBox::DisplayBoundingBox(GameObject *game_object, std::string colfile) : Renderer(game_object) {
    set_z_index(10);

    // bounding box maken van ons gameobject
    std::ifstream infile(colfile);
    if (!infile.is_open()) {
        std::cout << "colfile opent niet" << std::endl;
    }
    infile >> BoundingBox.x >> BoundingBox.y >> BoundingBox.width >> BoundingBox.height;
    infile.close();
}

void DisplayBoundingBox::render() {
    Rectangle bounds = calculateBounds();

    DrawRectangleLinesEx(bounds, 3, GREEN);
}

Rectangle DisplayBoundingBox::calculateBounds() const {
    Transform2D *transform = game_object->get_transform();

    float x = transform->get_pos().x + BoundingBox.x;
    float y = transform->get_pos().y + BoundingBox.y;

    return {x, y, BoundingBox.width, BoundingBox.height};
}


