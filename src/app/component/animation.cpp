#include "app/component/animation.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

Animation::Animation(GameObject *game_object, const std::string &filePath, std::string object) : Component(game_object) {
    if (filePath == "assets/anim/star.sap") {

        parseSAPFile(filePath);
        currentNode = getStartingNodeProjectile(object);

    } else {
        parseSAPFile(filePath);
        currentNode = getStartingNode();
    }
}

Animation::~Animation() {
    // Free memory allocated for animation nodes
    for (auto &pair : nodes) {
        delete pair.second;
    }
}

AnimationNode *Animation::getStartingNode() const {
    return nodes.at("IDLE_0");
}

AnimationNode *Animation::getStartingNodeProjectile(std::string object) const {
    if (object == "star") {
        return nodes.at("STAR_0");
    }
    return nodes.at("STAR_0");
}

AnimationNode *Animation::getCurrentNode() {
    return currentNode;
}

void Animation::setCurrentNode(AnimationNode *updatedNode) {
    currentNode = updatedNode;
}

void Animation::update(float delta_time) {
    elapsedTime += delta_time;

    if (elapsedTime >= 0.1f) {

        setCurrentNode(getCurrentNode()->getNextNode("TIME"));

        elapsedTime = 0.0f;
    }
}

void Animation::parseSAPFile(const std::string &filePath) {

    // open file
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "oeps, SAPfile niet open" << std::endl;
        return;
    }

    // initializatioon for line and section variables
    std::string line;
    std::string section;

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        if (line == "open nodes") {
            section = "nodes";
            continue;
        } else if (line == "open transitions") {
            section = "transitions";
            continue;
        } else if (line == "close list") {
            section = "";
            continue;
        }

        if (section == "nodes") {

            // Parse animation nodes using sstream:
            // iss is input string stream
            std::istringstream iss(line);
            std::string nodeName, spriteName;
            iss >> nodeName >> spriteName;

            // create a new pair in the map: nodeName -> Node
            // first check if there is a different spriteName
            if (spriteName.empty()) {
                spriteName = nodeName;
            }
            nodes[nodeName] = new AnimationNode(nodeName, spriteName);

        } else if (section == "transitions") {
            // Parse transitions between animation nodes
            std::istringstream iss(line);
            std::string currentNode, nextNode, transitionType;
            iss >> currentNode >> nextNode >> transitionType;

            //if current node and next node exist in the nodes
            //add the transition linking them
            if (nodes.find(currentNode) != nodes.end() && nodes.find(nextNode) != nodes.end()) {
                nodes[currentNode]->addTransition(transitionType, nodes[nextNode]);
            }
        }
    }

    file.close();
}

void Animation::printAnimationGraph() const {
    std::cout << "Animation Graph:" << std::endl;
    for (const auto &pair : nodes) {
        const AnimationNode *node = pair.second;
        std::cout << "Node: " << node->getName() << " Sprite: " << node->getSpriteName() << std::endl;
        for (const auto &transition : node->getTransitions()) {
            std::cout << "   Transition: " << transition.first << " Next Node: " << transition.second->getName() << std::endl;
        }
    }
}
