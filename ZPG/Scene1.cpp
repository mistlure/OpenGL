#include "Scene1.h"
#include "Shader.h"
Scene1::Scene1()
{
    Shader vertexShader(GL_VERTEX_SHADER, "shaders/vertex.glsl");
    Shader fragmentShader(GL_FRAGMENT_SHADER, "shaders/fragment_phong.glsl");

    auto shaderProgram = new ShaderProgram(vertexShader, fragmentShader);
    shaderProgram->useProgram();
    
    getCamera()->attach(shaderProgram);

    light->attach(shaderProgram);
    shaderProgram->setUniform("lightPos", light->getPosition());

    float triangle[] = {
        // pos             // normal
        -0.3f, -0.3f, 0.0f,  0.0f, 0.0f, 1.0f,
         0.3f, -0.3f, -0.5f, 0.0f, 0.0f, 1.0f,
         0.0f,  0.3f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    Model* triangleModel = new Model(triangle, sizeof(triangle));


    addObject(new DrawableObject(shaderProgram, triangleModel)); // Placeholder object for scene 0


}