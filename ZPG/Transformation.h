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

    void setLocalTransform(const glm::mat4& transform);   // задаёт локальную матрицу
    glm::mat4 getLocalTransform() const;                  // возвращает локальную матрицу

    void setParent(Transformation* parent);               // устанавливает родителя
    void addChild(Transformation* child);                 // добавляет дочерний узел

    glm::mat4 getGlobalTransform() const;                 // возвращает итоговую матрицу с учётом родителей

private:
    glm::mat4 localTransform;
    Transformation* parent;
    std::vector<Transformation*> children;
};
