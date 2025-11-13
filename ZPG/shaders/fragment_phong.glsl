#version 330 core

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;      // light position
uniform vec3 viewPos;       // camera position

out vec4 finalColor;

void main()
{
    vec3 objectColor = vec3(0.385, 0.647, 0.812);
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    vec3 result = (diff + spec) * objectColor;
    finalColor = vec4(result, 1.0);
}
