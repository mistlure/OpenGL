#include "Scene1.h"
#include "Shader.h"
#include "ShaderPairs.h"
#include "SphereData.h"
Scene1::Scene1()
{

	addLight(new PointLight(glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(1.f)));
	addLight(new PointLight(glm::vec3(0.0f, -5.0f, -5.0f), glm::vec3(1.f)));
    float triangle[] = {
        1.0f,  0.0f,  1.0f, 0.0f, 1.0f, 0.0f,
        1.0f,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    };

    Model* triangleModel = new Model(sphere, sphereSize);

	DrawableObject* triangleObject = new DrawableObject(ShaderPairs::Phong, triangleModel, getCamera(), &lights);


    addObject(triangleObject);

	Model* sphereModel = new Model(sphere, sphereSize);
    triangleObject = new DrawableObject(ShaderPairs::Phong, sphereModel, getCamera(), &lights);
    triangleObject->transform->addTransform(new Translate(glm::vec3(0.0f, 1.0f, -2.0f)));

    addObject(triangleObject);


}