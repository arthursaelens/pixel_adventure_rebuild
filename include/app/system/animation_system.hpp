#ifndef ANIMATION_SYSTEM_HPP
#define ANIMATION_SYSTEM_HPP

#include <vector>
#include "core/system/system.hpp"
#include "app/component/animation.hpp"

class AnimationSystem : public System {
public:
    AnimationSystem(const std::string &name);
    ~AnimationSystem();

    void update(float delta_time) override;

    

private:
    std::vector<Animation*> animationComponents;
};

#endif // ANIMATION_SYSTEM_HPP
