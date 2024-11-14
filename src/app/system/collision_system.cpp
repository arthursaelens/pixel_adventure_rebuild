#include "app/system/collision_system.hpp"
#include "app/utility/collider_tag.hpp"
#include "common.hpp"
#include <iostream>
#include <math.h>
CollisionSystem::CollisionSystem(const std::string &name) : System(name) {
}

void CollisionSystem::update(float delta_time) {

    // Eerst definiëren we de grootte van de cellen en het aantal cellen
    const int CELL_SIZE = 32;
    const int GRID_WIDTH = 1920 / CELL_SIZE;
    const int GRID_HEIGHT = 1080 / CELL_SIZE;

    // We maken een 2D vector om de cellen in op te slaan
    std::vector<std::vector<std::vector<Collider *>>> grid(GRID_WIDTH, std::vector<std::vector<Collider *>>(GRID_HEIGHT));
    auto collisionComponents = Engine::get_instance().get_components<Collider>();
    fruitCount = 0;
    enemyCount = 0;

    // Plaats elke colliderComponent in de juiste cellen van het grid
    for (Collider *collider : collisionComponents) {

        if (collider->tag == ColliderTag::ENEMY) {
            enemyCount++;
        } else if (collider->tag == ColliderTag::PICKUP) {
            fruitCount++;
        }
        Rectangle bounds = collider->calculateBounds();
        // Vector2 objectPos = collider->gameObject->get_transform()->get_pos();
        int left = floor((bounds.x) / CELL_SIZE);
        int right = floor((bounds.x + bounds.width) / CELL_SIZE);
        int top = floor((bounds.y) / CELL_SIZE);
        int bottom = floor((bounds.y + bounds.height) / CELL_SIZE);
        for (int x = left; x <= right; ++x) {
            for (int y = top; y <= bottom; ++y) {
                grid[x][y].push_back(collider);
            }
        }
    }

    // Check if all enemies and pickups are gone
    if (enemyCount == 0 && fruitCount == 0) {
        finishedLevel = 1;
    } else {
        finishedLevel = 0;
    }
    // Controleer op botsingen binnen dezelfde en aangrenzende cellen
    for (Collider *collider : collisionComponents) {
        if (collider->isDynamic) {
            Rectangle bounds = collider->calculateBounds();
            Vector2 positionDynamicObject = collider->gameObject->get_transform()->get_pos();
            int gridX = floor((bounds.x) / CELL_SIZE);
            int gridY = floor((bounds.y) / CELL_SIZE);

            // isGrounded resetten
            collider->isGrounded = 0;

            // Controleer de huidige cel en de aangrenzende cellen
            for (int x = std::max(0, gridX - 1); x <= std::min(GRID_WIDTH - 1, gridX + 1) + 1; ++x) {
                for (int y = std::max(0, gridY - 1); y <= std::min(GRID_HEIGHT - 1, gridY + 1) + 1; ++y) {

                    for (Collider *collider2 : grid[x][y]) {
                        if (collider == collider2 || collider2->tag == 0) {
                            continue;
                        }

                        Rectangle bounds2 = collider2->calculateBounds();
                        Vector2 posObject2 = collider2->gameObject->get_transform()->get_pos();

                        bool collision = CheckCollisionRecs(bounds, bounds2);
                        // debug statements om gegevens te checken
                        /*if (collider->tag == ColliderTag::CHARACTER) {
                            //   std::cout << bounds.y + bounds.height << " player y bounds +height (bottomborder)" << std::endl;

                            // std::cout << bounds.x << " player y positie" << std::endl;
                            std::cout << bounds.x + bounds.width << " rechts1" << std::endl;
                            std::cout << bounds.x << " links1" << std::endl;
                            std::cout << bounds.y << " boven1" << std::endl;
                            std::cout << bounds.y + bounds.height << " onder1" << std::endl;

                            std::cout << bounds2.x << " links2" << std::endl;
                            std::cout << bounds2.x + bounds2.width << " rechts2" << std::endl;
                            std::cout << bounds2.y << " boven2" << std::endl;
                            std::cout << bounds2.y + bounds2.height << "onder2" << std::endl;
                            std::cout << collision << " collision?" << std::endl;
                        }*/

                        if (collision) {

                            // std::cout << " collision! " << collider2->tag << std::endl;
                            if (collider2->tag == TERRAIN) {

                                std::string collisionPlace = checkCollision(bounds, bounds2);

                                // std::cout << " collision! " << collisionPlace << std::endl;
                                //  std::cout << collider2->gameObject->get_internal_id() << std::endl;
                                //  std::cout << collider2->gameObject->get_internal_id() << std::endl;
                                //  std::cout << collider2->gameObject->get_internal_id() << std::endl;
                                if (collisionPlace == "bottom") {
                                    // std::cout << bounds.y << " player y bounds" << std::endl;
                                    // std::cout << positionDynamicObject.y << " player y positie" << std::endl;
                                    // std::cout << bounds.height << " player hoogte" << std::endl;
                                    // std::cout << "!!!!!!!!!!!!!bottom hit" << std::endl;
                                    // std::cout << bounds2.y << " tile y bounds" << std::endl;
                                    //  std::cout << bounds2.y - bounds.height - (bounds.y - positionDynamicObject.y) << " player y positie" << std::endl;
                                    //  std::cout << bounds2.y << " tile y positie" << std::endl;
                                    collider->gameObject->get_transform()->set_pos(positionDynamicObject.x, bounds2.y - bounds.height - (bounds.y - positionDynamicObject.y));
                                    positionDynamicObject.y = bounds2.y - bounds.height - (collider->BoundingBox.y);
                                    bounds.y = positionDynamicObject.y + collider->BoundingBox.y;
                                    collider->isGrounded = 1;
                                }
                                if (collisionPlace == "right") {
                                    // std::cout << "right hit" << std::endl;
                                    collider->gameObject->get_transform()->set_pos(bounds2.x - bounds.width - (bounds.x - positionDynamicObject.x), positionDynamicObject.y);
                                    positionDynamicObject.x = bounds2.x - bounds.width - (collider->BoundingBox.x);
                                    bounds.x = positionDynamicObject.x + collider->BoundingBox.x;
                                    collider->toLeft = 1;
                                }
                                if (collisionPlace == "left") {
                                    // std::cout << "left hit" << std::endl;
                                    collider->gameObject->get_transform()->set_pos(bounds2.x + bounds2.width - (bounds.x - positionDynamicObject.x), positionDynamicObject.y);
                                    positionDynamicObject.x = bounds2.x + bounds2.width - (collider->BoundingBox.x);
                                    bounds.x = positionDynamicObject.x + collider->BoundingBox.x;
                                    collider->toLeft = 0;
                                }
                                if (collisionPlace == "top") {
                                    // std::cout << "top hit" << std::endl;
                                    collider->gameObject->get_transform()->set_pos(positionDynamicObject.x, bounds2.y + bounds2.height - (bounds.y - positionDynamicObject.y));
                                    collider->topHit = 1;
                                    positionDynamicObject.y = bounds2.y + bounds2.height - (collider->BoundingBox.y);
                                    bounds.y = positionDynamicObject.y + collider->BoundingBox.y;
                                }
                            }
                            if (collider2->tag == ColliderTag::PICKUP && collider->tag == ColliderTag::CHARACTER) {
                                // std::cout << "njam njam" << std::endl;
                                collider2->isGrabbed = 1;
                            }
                            if (collider->tag == ColliderTag::CHARACTER && collider2->tag == ColliderTag::ENEMY || collider2->tag == ColliderTag::CHARACTER && collider->tag == ColliderTag::ENEMY) {
                                std::string collisionPlace = checkCollision(bounds, bounds2);
                                if (collider->tag == ColliderTag::CHARACTER) {
                                    if (collisionPlace == "bottom") {
                                        collider2->topHit = 1;
                                        collider->bottomHit = 1;
                                    } else {
                                        collider->isHit = 1;
                                    }
                                } else {
                                    if (collisionPlace == "top") {
                                        collider->topHit = 1;
                                        collider2->bottomHit = 1;
                                    } else {
                                        collider2->isHit = 1;
                                    }
                                }
                            }
                            if (collider->tag == ColliderTag::ENEMY_PROJECTILE) {
                                if (collider->mask & collider2->tag) {
                                    collider->hit = 1;
                                    if (collider2->tag == ColliderTag::CHARACTER) {
                                        collider2->isHit = 1;
                                    }
                                }
                            } else if (collider2->tag == ColliderTag::ENEMY_PROJECTILE) {
                                if (collider2->mask & collider->tag) {
                                    collider2->hit = 1;
                                    if (collider->tag == ColliderTag::CHARACTER) {
                                        collider->isHit = 1;
                                    }
                                }
                            }
                            if (collider->tag == ColliderTag::PLAYER_PROJECTILE) {
                                if (collider->mask & collider2->tag) {
                                    collider->hit = 1;
                                    if (collider2->tag == ColliderTag::ENEMY) {
                                        collider2->isHit = 1;
                                    }
                                }
                            } else if (collider2->tag == ColliderTag::PLAYER_PROJECTILE) {
                                if (collider2->mask & collider->tag) {
                                    collider2->hit = 1;
                                    if (collider->tag == ColliderTag::ENEMY) {
                                        collider->isHit = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            if (collider->tag == ColliderTag::CHARACTER) {
                collider->finishedLevel = finishedLevel;
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------------
// collision system zonder grid
// std::cout << "ColliderSystem update() is called" << std::endl;
/*auto collisionComponents = Engine::get_instance().get_components<Collider>();
for (Collider *collider : collisionComponents) {
    // std::cout << "for a component  update() is called " <<std::endl;
    if (collider->isDynamic) {
        // zou het niet makkelijker zijn om alles binnen een bepaalde afstand van manneke te checken in plaats van een volledig grid te maken?
        Vector2 positionDynamicObject = collider->gameObject->get_transform()->get_pos();
        Rectangle bounds = collider->calculateBounds();
        for (Collider *collider2 : collisionComponents) {
            if (collider == collider2 || collider2->tag == 0) {
                continue;
            }
            if (collider2->tag != ColliderTag::TERRAIN) {
                continue;
            }
            Vector2 posObject2 = collider2->gameObject->get_transform()->get_pos();
            float distance = sqrtf(powf(posObject2.x - positionDynamicObject.x, 2) + powf(posObject2.y - positionDynamicObject.y, 2));
            if (distance > 2 * bounds.height) {
                continue;
            }
            Rectangle bounds2 = collider2->calculateBounds();
            bool collision = CheckCollisionRecs(bounds, bounds2);
            if (collision) {
                // std::cout << "collision!!!" << std::endl;
                //  std::cout << "Collision detected with tag: " << collider2->tag << std::endl;
                if (collider2->tag == TERRAIN) {
                    collisionPlace = checkCollision(bounds, bounds2);
                    std::cout << collider2->gameObject->get_internal_id() << std::endl;
                    std::cout << collider2->gameObject->get_internal_id() << std::endl;
                    std::cout << collider2->gameObject->get_internal_id() << std::endl;
                    if (collisionPlace == "bottom") {
                        std::cout << "bottom hit" << std::endl;
                        collider->gameObject->get_transform()->set_pos(positionDynamicObject.x, bounds2.y - bounds.height - (bounds.y - positionDynamicObject.y) - 1);
                        collider->isGrounded = 1;
                    } else if (collisionPlace == "right") {
                        std::cout << "right hit" << std::endl;
                        collider->gameObject->get_transform()->set_pos(bounds2.x - bounds.width - (bounds.x - positionDynamicObject.x) - 1, positionDynamicObject.y);
                    } else if (collisionPlace == "left") {
                        std::cout << "left hit" << std::endl;
                        collider->gameObject->get_transform()->set_pos(bounds2.x + bounds2.width - (bounds.x - positionDynamicObject.x) + 1, positionDynamicObject.y);
                    } else if (collisionPlace == "top") {
                        std::cout << "top hit" << std::endl;
                        collider->gameObject->get_transform()->set_pos(positionDynamicObject.x, bounds2.y + bounds2.height - (bounds.y - positionDynamicObject.y) + 1);
                    }
                }
                // if (collider2->mask && colliderTag::CHARACTER) {}
            }
        }
        if (collisionPlace != "bottom") {
            collider->isGrounded = 0;
        }
    }
}
}*/

// functie die terug geeft waar de botsing zich precies bevindt
// al de documentatie die erbij staat zijn de verschillende cases die we hebben uitgetekend hoe twee bounding boxes kunnen colliden
std::string CollisionSystem::checkCollision(Rectangle rec1, Rectangle rec2) {
    float rechts1 = (rec1.x + rec1.width);
    float rechts2 = (rec2.x + rec2.width);
    float onder1 = (rec1.y + rec1.height);
    float onder2 = (rec2.y + rec2.height);
    float links1 = rec1.x;
    float links2 = rec2.x;
    float boven1 = rec1.y;
    float boven2 = rec2.y;
    // soorten collisions, cases heb ik getekend zodat ik niet mis
    if (links1 < links2 && links2 < rechts1 && rechts1 < rechts2 && boven1 < boven2 && boven2 < onder2 && onder2 < onder1) // case 1
    {
        // std::cout << "right hit 1" << std::endl;
        return "right";
    }
    if (links1 < links2 && links2 < rechts1 && rechts1 < rechts2 && boven2 < boven1 && boven1 < onder1 && onder1 < onder2) // case 2
    {
        // std::cout << "right hit 2" << std::endl;
        return "right";
    }
    if (links1 <= links2 && links2 <= rechts1 && rechts1 <= rechts2 && boven2 <= boven1 && boven1 <= onder2 && onder2 <= onder1) {
        if (onder2 - boven1 > rechts1 - links2) // case 3
        {
            // std::cout << "right hit 3" << std::endl;
            return "right";
        } else // case 5
        {
            // std::cout << "top hit 5" << std::endl;
            return "top";
        }
    }
    if (links1 <= links2 && links2 <= rechts1 && rechts1 <= rechts2 && boven1 <= boven2 && boven2 <= onder1 && onder1 <= onder2) {
        // std::cout << "komj tot hier? " << std::endl;
        if (onder1 - boven2 > rechts1 - links2) // case 4
        {
            // std::cout << "right hit 4" << std::endl;
            return "right";
        } else // case 6
        {
            // std::cout << "bottom hit 6" << std::endl;
            return "bottom";
        }
    }
    if (links2 < links1 && links1 < rechts2 && rechts2 < rechts1 && boven1 < boven2 && boven2 < onder2 && onder2 < onder1) // case 7
    {
        // std::cout << "left hit 7" << std::endl;
        return "left";
    }
    if (links2 < links1 && links1 < rechts2 && rechts2 < rechts1 && boven2 < boven1 && boven1 < onder1 && onder1 < onder2) // case 8
    {
        // std::cout << "left hit 8" << std::endl;
        return "left";
    }
    if (links2 <= links1 && links1 <= rechts2 && rechts2 <= rechts1 && boven2 <= boven1 && boven1 <= onder2 && onder2 <= onder1) {
        if (onder2 - boven1 > rechts2 - links1) // case 9
        {
            // std::cout << "left hit 9" << std::endl;
            return "left";
        } else // case 11
        {
            // std::cout << "top hit 11" << std::endl;
            return "top";
        }
    }
    if (links2 <= links1 && links1 <= rechts2 && rechts2 <= rechts1 && boven1 <= boven2 && boven2 <= onder1 && onder1 <= onder2) {
        if (onder1 - boven2 > rechts2 - links1) // case 10
        {
            // std::cout << "left hit 10" << std::endl;
            return "left";
        } else // case 12
        {
            // std::cout << "bottom hit 12" << std::endl;
            return "bottom";
        }
    }
    if (boven2 < boven1 && boven1 < onder2 && onder2 < onder1 && links2 < links1 && links1 < rechts1 && rechts1 < rechts2) // case 13
    {
        // std::cout << "top hit 13" << std::endl;
        return "top";
    }
    if (boven2 < boven1 && boven1 < onder2 && onder2 < onder1 && links1 < links2 && links2 < rechts2 && rechts2 < rechts1) // case 14
    {
        // std::cout << "top hit 14" << std::endl;
        return "top";
    }
    if (boven1 < boven2 && boven2 < onder1 && onder1 < onder2 && links2 < links1 && links1 < rechts1 && rechts1 < rechts2) // case 15
    {
        // std::cout << "bottom hit 15" << std::endl;
        return "bottom";
    }
    if (boven1 < boven2 && boven2 < onder1 && onder1 < onder2 && links1 < links2 && links2 < rechts2 && rechts2 < rechts1) // case 16
    {
        // std::cout << "bottom hit 16" << std::endl;
        return "bottom";
    }
    return "niets";
}
