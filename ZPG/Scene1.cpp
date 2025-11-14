#include "Scene1.h"
#include "Shader.h"
#include "ShaderPairs.h"

Scene1::Scene1()
{

	addLight(new Light(glm::vec3(0.0f, 5.0f, 5.0f)));
    float triangle[] = {
        1.0f,  0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
        1.0f,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };

    Model* triangleModel = new Model(triangle, sizeof(triangle));

	DrawableObject* triangleObject = new DrawableObject(ShaderPairs::Phong, triangleModel, getCamera(), &lights);


    addObject(triangleObject);

    triangleObject = new DrawableObject(ShaderPairs::Phong, triangleModel, getCamera(), &lights);
    triangleObject->transform->addTransform(new Translate(glm::vec3(0.0f, 1.0f, -2.0f)));

    addObject(triangleObject);


}