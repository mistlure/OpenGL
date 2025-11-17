#version 330 core
layout(location = 0) in vec3 vp;      // vertex position
layout(location = 1) in vec3 normal;  // vertex normal
layout(location = 2) in vec2 texCoord; // uv coords

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectMatrix;

out vec3 FragPos;
out vec3 Normal;
out vec2 UV;

void main() {
    vec4 worldPos = modelMatrix * vec4(vp, 1.0);
    FragPos = vec3(worldPos);
    Normal = mat3(transpose(inverse(modelMatrix))) * normal;
    UV = texCoord;

    gl_Position = projectMatrix * viewMatrix * worldPos;
}
