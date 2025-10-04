// Represents a node in a transformation hierarchy.
// 
// It stores a local transformation matrix and supports composition via parent-child.
// 
// This allows Composite pattern.

#pragma once
#include <glm/glm.hpp>
#include <vector>

class Transformation {
public:
    Transformation();

    void setLocalTransform(const glm::mat4& transform);   
    glm::mat4 getLocalTransform() const;                  

    void setParent(Transformation* parent);               
    void addChild(Transformation* child);                 

    glm::mat4 getGlobalTransform() const;                 

private:
    glm::mat4 localTransform;
    Transformation* parent;
    std::vector<Transformation*> children;
};
