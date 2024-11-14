#include "app/game_object/test.hpp"
#include "app/component/position_display.hpp"

TestObject::TestObject() {
    sp = add_component<SpriteRenderer>("assets/sprites/jasper??.png");

    get_transform()->set_pos(960 - sp->get_width()/2, 540 - sp->get_height()/2);

    posDisplay = add_component<PositionDisplay>();
}

void TestObject::update(float delta_time) {
    Transform2D *t = get_transform();

    //define g = 9.81 m/s^2 and guess at a good conversion ... 5
    //UPDATE: nvm just guess a nice number for pixels/??^2 (unit of time for delta_time??)
    //UPDATE2: unit of delta_time is probably seconds
    const float gravAccelaration = 150;

    //update speed 
    speed.y += gravAccelaration*delta_time;


    //calculate displacement (y = y0 + v * dt + .5 * a * dt^2)
    float displacement = speed.y * delta_time + .5f * gravAccelaration * delta_time * delta_time;

    if (t->get_pos().y + displacement + sp->get_height() > 1080) {
        speed.y *= -0.95; //energy lost in bounce = 0.05
    }

    //lock position and speed when necessary
    //REMARK: werkt nog niet als gewenst, schijnbaar willekeurige botsingen waar deze voorwaarde voldaan is 
    //(zou kunnen counter hebben voor x aantal frames in onderste paar pixels te zitten)
    if (t->get_pos().y > 1075 - sp->get_height() && abs(speed.y) < 20) {
        speed.y = 0;
        t->set_pos(t->get_pos().x, 1080 - sp->get_height());
    }

    //update posisitione 
    t->set_pos(t->get_pos().x, t->get_pos().y + displacement);


}
