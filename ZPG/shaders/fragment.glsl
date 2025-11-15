#version 330 core
in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 finalColor;

void main () {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

    vec3 ambient = vec3(0.1);
    vec3 diffuse = diff * vec3(0.5);
    vec3 specular = spec * vec3(1.0);

    vec3 result = ambient + diffuse + specular;
    finalColor = vec4(result, 1.0);
}
