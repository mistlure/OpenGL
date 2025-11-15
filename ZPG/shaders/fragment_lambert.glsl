#version 330 core
in vec3 fragColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
out vec4 finalColor;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 result = diff * fragColor;
    finalColor = vec4(result, 1.0);
}
