// DrawableObject connects a Model and a ShaderProgram.
// 
// It represents a visual object in your scene that knows how to draw itself ->
// -> using the assigned shader and geometry.
// 
// This class does not own the model or shader — it simply uses them.

#pragma once
#include "ShaderProgram.h"
#include "Model.h"
#include "Transform.h"
#include "Light.h"
#include "Texture.h"
class DrawableObject
{
public:
    DrawableObject(const char* ShaderPair[2], Model* model, Camera* camera, std::vector<Light*>* lights);
    void draw();

    Texture* texture = nullptr;
    bool useTexture = false;

    Transform* transform = new Transform();

private:
    ShaderProgram* shaderProgram;
    Model* model;
};
