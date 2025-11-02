// DrawableObject connects a Model and a ShaderProgram.
// 
// It represents a visual object in your scene that knows how to draw itself ->
// -> using the assigned shader and geometry.
// 
// This class does not own the model or shader — it simply uses them.

#pragma once
#include "ShaderProgram.h"
#include "Model.h"
#include "Transformation.h"
#include "Transform.h"

class DrawableObject
{
public:
    DrawableObject(ShaderProgram* shader, Model* model);
    void draw();

    //Transformation* transform = nullptr;
    Transform* transform = nullptr;

private:
    ShaderProgram* shader;
    Model* model;
};
