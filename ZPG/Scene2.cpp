#include "Scene2.h"
#include "Shader.h"
#include "ShaderPairs.h"
#include "Scale.h"
#include "Translate.h"

#include "TreeData.h"
#include "BushData.h"


Scene2::Scene2()
{	
    addLight(new PointLight(
        glm::vec3(0.0f, 10.0f, 0.0f),
        glm::vec3(3.0f, 3.0f, 3.0f)
    ));

    const float plain[] = {
        // x, y, z,      nx, ny, nz,      u,   v
         1.0f, 0.0f,  1.0f,   0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
         1.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f,   10.0f, 0.0f,
        -1.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f,   10.0f, 10.0f,

        -1.0f, 0.0f,  1.0f,   0.0f, 1.0f, 0.0f,   0.0f,  10.0f,
         1.0f, 0.0f,  1.0f,   0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -1.0f, 0.0f, -1.0f,   0.0f, 1.0f, 0.0f,   10.0f, 10.0f
    };

    Model* platformModel = new Model((float*)plain, sizeof(plain), true);
    DrawableObject* platform = new DrawableObject(ShaderPairs::PhongTextured, platformModel, getCamera(), getLights());
    platform->texture = new Texture("assets/grass.png");
    platform->useTexture = true;

    Transform* platformTransform = new Transform();
    platformTransform->addTransform(new Scale(glm::vec3(10.0f, 1.0f, 10.0f)));
    platform->transform = platformTransform;

    addObject(platform);

    ///



    Model* shrekModel = new Model("shrek.obj");
    DrawableObject* shrek = new DrawableObject(ShaderPairs::PhongTextured, shrekModel, getCamera(), getLights());
    shrek->texture = new Texture("assets/shrek.png");
    shrek->useTexture = true;

    Transform* shrekTransform = new Transform();
    shrekTransform->addTransform(new Translate(glm::vec3(-3.0f, 0.0f, 0.0f)));
    shrekTransform->addTransform(new Scale(glm::vec3(1.0f, 1.0f, 1.0f)));
    shrek->transform = shrekTransform;
    addObject(shrek);



    Model* fionaModel = new Model("fiona.obj");
    DrawableObject* fiona = new DrawableObject(ShaderPairs::PhongTextured, fionaModel, getCamera(), getLights());
    fiona->texture = new Texture("assets/fiona.png");
    fiona->useTexture = true;

    Transform* fionaTransform = new Transform();
    fionaTransform->addTransform(new Translate(glm::vec3(3.0f, 0.0f, 0.0f)));
    fionaTransform->addTransform(new Scale(glm::vec3(1.0f, 1.0f, 1.0f)));
    fiona->transform = fionaTransform;
    addObject(fiona);



    Model* toiletModel = new Model("toiled.obj");
    DrawableObject* toilet = new DrawableObject(ShaderPairs::PhongTextured, toiletModel, getCamera(), getLights());
    toilet->texture = new Texture("assets/toiled.jpg");
    toilet->useTexture = true;

    Transform* toiletTransform = new Transform();
    toiletTransform->addTransform(new Translate(glm::vec3(0.0f, 0.0f, 0.0f)));
    toiletTransform->addTransform(new Scale(glm::vec3(1.0f, 1.0f, 1.0f)));
    toilet->transform = toiletTransform;
    addObject(toilet);
}