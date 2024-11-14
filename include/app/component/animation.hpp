#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "animation_node.hpp"
#include "common.hpp"
#include <string>
#include <unordered_map>
#include <vector>


//animation component for every gameobject with a .sap file
class Animation : public Component {
  private:

    std::unordered_map<std::string, AnimationNode *> nodes;
    AnimationNode *currentNode;

  public:
    //handles TIME transitions, called from animation_system
    void update(float delta_time);

    //third argument used for projectile star
    Animation(GameObject *game_object, const std::string &filePath, std::string object);
    ~Animation();
    float elapsedTime = 0.00;


    AnimationNode *getStartingNode() const;
    AnimationNode *getStartingNodeProjectile(std::string object) const;
    AnimationNode *getCurrentNode();
    void setCurrentNode(AnimationNode *updatedNode);

    //prints animation nodes and their transitions with next nodes
    void printAnimationGraph() const;

  private:

    //constructs the animation graph
    void parseSAPFile(const std::string &filePath);
};

#endif // ANIMATION_HPP
