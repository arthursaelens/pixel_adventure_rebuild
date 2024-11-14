#ifndef ANIMATION_NODE_HPP
#define ANIMATION_NODE_HPP

#include <string>
#include <unordered_map>

#include "core/component/component.hpp"

class AnimationNode {
    private:
        std::string name;
        std::unordered_map<std::string, AnimationNode*> transitions; // Transition type -> Next animation node

    public:
        AnimationNode(const std::string& name, const std::string& spriteName);
        std::string spriteName; //initialize same as name

        const std::string& getName() const;

        //could be left out as spriteName is public
        const std::string& getSpriteName() const;

        void addTransition(const std::string& transitionType, AnimationNode* nextNode);
        
        // Method to get the next animation node based on a transition type
        AnimationNode* getNextNode(const std::string& transitionType) const;

        //method  to get map of transitions of 1 node
        const std::unordered_map<std::string, AnimationNode*>& getTransitions() const; 
        
        //use in if statement before getNextNode() to insure we can do this transistion 
        bool hasTransition(const std::string& transition) const;
};

#endif
