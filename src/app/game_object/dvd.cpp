#include "app/game_object/dvd.hpp"

Dvd::Dvd() {
    sp = add_component<SpriteRenderer>("assets/sprites/dvd.png");

    sp->set_tint(GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255));

    get_transform()->set_pos(50.0, 50.0);
}

void Dvd::update(float delta_time) {
    Transform2D *t = get_transform();

    bool hit_wall = false;

    if (t->get_pos().y + speed.y * delta_time + sp->get_height() > 1080 || t->get_pos().y + speed.y * delta_time < 0) {
        speed.y *= -1;
        hit_wall = true;
    } else if (t->get_pos().x + speed.x * delta_time + sp->get_width() > 1920 || t->get_pos().x + speed.x * delta_time < 0) {
        speed.x *= -1;
        hit_wall = true;
    }

    if (hit_wall) {
        sp->set_tint(GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255));
    }

    t->set_pos(t->get_pos().x + speed.x * delta_time, t->get_pos().y + speed.y * delta_time);
}
