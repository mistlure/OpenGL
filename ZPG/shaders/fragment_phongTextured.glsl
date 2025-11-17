#version 330 core
#define MAX_LIGHTS 4

in vec3 FragPos;
in vec3 Normal;
in vec2 UV;

out vec4 finalColor;

struct Light {
    int type;
    bool isOn;
    vec3 position;
    vec3 direction;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
};

const int LIGHT_TYPE_DIRECTIONAL = 0;
const int LIGHT_TYPE_POINT = 1;
const int LIGHT_TYPE_SPOT = 2;

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;

uniform vec3 viewPos;
uniform sampler2D textureUnitID;

float ra = 0.1;
float rd = 0.7;
float rs = 0.5;
float h  = 32.0;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 objectColor = texture(textureUnitID, UV).rgb;

    vec3 ambient = ra * objectColor;
    vec3 result = ambient;

    for (int i = 0; i < numberOfLights; i++)
    {
        if (!lights[i].isOn) continue;

        vec3 lightColor = lights[i].color;
        vec3 lightDir;
        float attenuation = 1.0;

        if (lights[i].type == LIGHT_TYPE_DIRECTIONAL) {
            lightDir = normalize(-lights[i].direction);
        } else {
            lightDir = normalize(lights[i].position - FragPos);
            float distance = length(lights[i].position - FragPos);
            attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * distance * distance);

            if (lights[i].type == LIGHT_TYPE_SPOT) {
                float theta   = dot(lightDir, normalize(-lights[i].direction));
                float epsilon = lights[i].cutOff - lights[i].outerCutOff;
                float intensity = clamp((theta - lights[i].outerCutOff) / epsilon, 0.0, 1.0);
                attenuation *= intensity;
            }
        }

        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = rd * diff * objectColor * lightColor;

        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), h);
        vec3 specular = rs * spec * lightColor;

        result += attenuation * (diffuse + specular);
    }

    finalColor = vec4(result, 1.0);
}
