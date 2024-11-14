#include "app/system/animation_system.hpp"
#include "common.hpp"

#include <iostream>

AnimationSystem::AnimationSystem(const std::string &name) : System(name) {
    // std::cout <<"AnimationSystem object: " << name << " is created" << std::endl;
}

AnimationSystem::~AnimationSystem() {}

void AnimationSystem::update(float delta_time) {

    // std::cout << "AnimationSystem Update is called" << std::endl;
    auto animationComponents = Engine::get_instance().get_components<Animation>();
    for (auto animation : animationComponents) {

        animation->update(delta_time);
    }
}
