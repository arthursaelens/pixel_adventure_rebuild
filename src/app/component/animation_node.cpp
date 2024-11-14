#include "app/component/animation_node.hpp"
#include <iostream>

AnimationNode::AnimationNode(const std::string& name, const std::string& spriteName)
: name(name), spriteName(spriteName) {}

//getters
const std::string& AnimationNode::getName() const {
    return name;
}

const std::string& AnimationNode::getSpriteName() const {
    return spriteName;
}

// Method to add transition
void AnimationNode::addTransition(const std::string& transition, AnimationNode* nextNode) {
    transitions[transition] = nextNode;
}

// Method to get next animation node for a transition
AnimationNode* AnimationNode::getNextNode(const std::string& transition) const {
    auto it = transitions.find(transition);
    if (it != transitions.end()) {
        return it->second;
    }
    
    return nullptr;
}

//needed bcs transitions was private
const std::unordered_map<std::string, AnimationNode*>& AnimationNode::getTransitions() const {
    return transitions;
}

bool AnimationNode::hasTransition(const std::string& transition) const {
    return transitions.find(transition) != transitions.end();
}
