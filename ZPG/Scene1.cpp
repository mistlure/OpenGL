#include "Scene1.h"
#include "Shader.h"
#include "ShaderPairs.h"
#include "SphereData.h"
Scene1::Scene1()
{

	// SpotLight 1: looking forward and slightly down
	addLight(new SpotLight(
		glm::vec3(0.0f, 0.0f, 0.0f),                 // position at origin
		glm::normalize(glm::vec3(0.0f, -1.0f, -1.0f)), // direction normalized
		glm::vec3(1.0f, 1.0f, 1.0f)                  // purple color
	));

	// SpotLight 2: looking left and slightly down
	addLight(new SpotLight(
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::normalize(glm::vec3(-1.0f, -1.0f, 0.0f)),
		glm::vec3(1.0f, 1.0f, 1.0f)
	));

	// SpotLight 3: looking backward and slightly down
	addLight(new SpotLight(
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::normalize(glm::vec3(0.0f, -1.0f, 1.0f)),
		glm::vec3(1.0f, 1.0f, 1.0f)
	));

	//addLight(new PointLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.f)));

	// Create a single sphere model
	Model* sphereModel = new Model(sphere, sphereSize);

	// First sphere
	DrawableObject* sphere1 = new DrawableObject(ShaderPairs::Phong, sphereModel, getCamera(), &lights);
	sphere1->transform->addTransform(new Translate(glm::vec3(-2.0f, -0.0f, 0.0f)));
	addObject(sphere1);

	// Second sphere
	DrawableObject* sphere2 = new DrawableObject(ShaderPairs::Phong, sphereModel, getCamera(), &lights);
	sphere2->transform->addTransform(new Translate(glm::vec3(0.0f, -2.0f, 0.0f)));
	addObject(sphere2);

	// Third sphere
	DrawableObject* sphere3 = new DrawableObject(ShaderPairs::Phong, sphereModel, getCamera(), &lights);
	sphere3->transform->addTransform(new Translate(glm::vec3(0.0f, 2.0f, 0.0f)));
	addObject(sphere3);

	// Fourth sphere
	DrawableObject* sphere4 = new DrawableObject(ShaderPairs::Phong, sphereModel, getCamera(), &lights);
	sphere4->transform->addTransform(new Translate(glm::vec3(2.0f, 0.0f, 0.0f)));
	addObject(sphere4);


}