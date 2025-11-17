#include "ShaderPairs.h"

const char* ShaderPairs::Phong[2] = 
{
    "shaders/vertex.glsl", "shaders/fragment_phong.glsl"
};

const char* ShaderPairs::PhongTextured[2] =
{
    "shaders/vertexTextured.glsl",
    "shaders/fragment_phongTextured.glsl"
};