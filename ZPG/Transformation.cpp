#include "Transformation.h"

Transformation::Transformation()
    : localTransform(glm::mat4(1.0f)), parent(nullptr) {}

// Sets the local transformation matrix (e.g., rotate, scale, translate).
void Transformation::setLocalTransform(const glm::mat4& transform)
{
    localTransform = transform;
}

// Returns the local transformation matrix.
glm::mat4 Transformation::getLocalTransform() const
{
    return localTransform;
}

// Sets the parent node in the hierarchy
void Transformation::setParent(Transformation* p)
{
    parent = p;
}

// Adds a child node and links it to this node.
void Transformation::addChild(Transformation* child)
{
    children.push_back(child);
    child->setParent(this);
}

// Computes the global transformation by recursively combining with parent transforms.
glm::mat4 Transformation::getGlobalTransform() const
{
    if (parent)
        // If there's a parent, multiply its global transform with this node's local transform.
        return parent->getGlobalTransform() * localTransform;
    else
        // If no parent, return local transform as global.
        return localTransform;
}
