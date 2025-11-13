#include "Scene1.h"
#include "Shader.h"
#include "ShaderPairs.h"

Scene1::Scene1()
{

    float triangle[] = {
        // pos             // normal
        -0.3f, -0.3f, 0.0f,  0.0f, 0.0f, 1.0f,
         0.3f, -0.3f, -0.5f, 0.0f, 0.0f, 1.0f,
         0.0f,  0.3f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    Model* triangleModel = new Model(triangle, sizeof(triangle));

	DrawableObject* triangleObject = new DrawableObject(ShaderPairs::Phong, triangleModel, getCamera(), light);
	triangleObject->transform->addTransform(new Translate(glm::vec3(0.0f, 0.0f, -1.0f)));

    addObject(triangleObject);


}