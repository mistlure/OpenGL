#version 330 core

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    bool enabled;
};

uniform SpotLight spotLight;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 viewPos;

const int NUM_LIGHTS = 8;
uniform vec3 lightPositions[NUM_LIGHTS];
uniform vec3 lightAttenuations[NUM_LIGHTS];

uniform vec3 ambientColor;
uniform float ambientStrength;

out vec4 finalColor;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 result = vec3(0.0);

    // Очень слабое ambient-освещение (ночь)
    result += ambientStrength * ambientColor;

    for (int i = 0; i < NUM_LIGHTS; ++i)
    {
        vec3 lightDir = normalize(lightPositions[i] - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);

        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);

        vec3 diffuse = diff * vec3(0.4);
        vec3 specular = spec * vec3(0.05); // слабый specular

        float distance = length(lightPositions[i] - FragPos);
        float attenuation = 1.0 / (
            lightAttenuations[i].x +
            lightAttenuations[i].y * distance +
            lightAttenuations[i].z * distance * distance
        );

        result += attenuation * (diffuse + specular);
    }

    if (spotLight.enabled) {
        vec3 lightDir = normalize(spotLight.position - FragPos);
        float theta = dot(lightDir, normalize(-spotLight.direction));

        float epsilon = spotLight.cutOff - spotLight.outerCutOff;
        float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * vec3(1.0);
        vec3 specular = vec3(0.3);

        result += intensity * (diffuse + specular);
    }

    finalColor = vec4(result, 1.0);
}
