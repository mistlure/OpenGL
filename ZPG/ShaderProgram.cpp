#include "ShaderProgram.h"
#include <iostream>

ShaderProgram::ShaderProgram(Shader& vertex, Shader& fragment, Camera* cam, std::vector<Light*>* lights) : camera(cam), lights(lights)
{   
    id = glCreateProgram();

    vertex.attachShader(id);
    fragment.attachShader(id);
    
    GLint success;

    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (!success)
    {
        GLint logLength;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);
        char* log = new char[logLength];
        glGetProgramInfoLog(id, logLength, nullptr, log);
        std::cerr << "Shader program linking failed:\n" << log << std::endl;
        delete[] log;
    }

    camera->attach(this);
    onNotify(ObservableSubjects::SCamera);
	for (auto light : *lights)
        light->attach(this);
    onNotify(ObservableSubjects::SLight);

}   

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(id);
}

void ShaderProgram::useProgram()
{
    glUseProgram(id);
}

void ShaderProgram::setModelMatrix(const glm::mat4& matrix) const
{
    GLint location = glGetUniformLocation(id, "modelMatrix");
    if (location == -1)
    {
        std::cerr << "Uniform 'modelMatrix' not found!" << std::endl;
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat4& matrix) const
{
    GLint location = glGetUniformLocation(id, name.c_str());
    if (location != -1)
        glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void ShaderProgram::setUniform(const std::string& name, const glm::vec3& vector) const
{
    GLint location = glGetUniformLocation(id, name.c_str());
    if (location != -1)
        glUniform3fv(location, 1, &vector[0]);
}

void ShaderProgram::setUniform(const std::string& name, float value) const
{
    GLint location = glGetUniformLocation(id, name.c_str());
    if (location != -1)
        glUniform1f(location, value);
}

void ShaderProgram::setUniform(const std::string& name, int value) const
{
    GLint location = glGetUniformLocation(id, name.c_str());
    if (location != -1)
        glUniform1i(location, value);
}

void ShaderProgram::onNotify(ObservableSubjects source) {
    useProgram();

    switch (source) {
    case SCamera: {
        setUniform("viewMatrix", camera->getViewMatrix());
        setUniform("projectMatrix", camera->getProjectionMatrix());
        setUniform("viewPos", camera->getPosition());
        break;
    }
    case SLight: {
        const auto& lightList = *lights;

        setUniform("numberOfLights", static_cast<int>(lightList.size()));

        for (size_t i = 0; i < lightList.size(); ++i)
        {
            Light* light = lightList[i];
            std::string prefix = "lights[" + std::to_string(i) + "]";

            // Base light properties
            setUniform(prefix + ".type", static_cast<int>(light->type));
            setUniform(prefix + ".color", light->color);
            setUniform(prefix + ".isOn", light->isOn);

            // PointLight specific
            if (auto* point = dynamic_cast<PointLight*>(light))
            {
                setUniform(prefix + ".position", point->position);
                setUniform(prefix + ".constant", point->constant);
                setUniform(prefix + ".linear", point->linear);
                setUniform(prefix + ".quadratic", point->quadratic);
            }
            else if (auto* point = dynamic_cast<SpotLight*>(light)) {
                setUniform((prefix + ".position").c_str(), point->position);
                setUniform((prefix + ".direction").c_str(), point->direction);
                setUniform((prefix + ".cutOff").c_str(), point->cutOff);
                setUniform((prefix + ".outerCutOff").c_str(), point->outerCutOff);
                setUniform((prefix + ".constant").c_str(), 1.0f);
                setUniform((prefix + ".linear").c_str(), 0.09f);
                setUniform((prefix + ".quadratic").c_str(), 0.032f);
            }
            // TODO: if you add SpotLight or DirectionalLight, extend here
            // if (auto* spot = dynamic_cast<SpotLight*>(light)) { ... }
        }

        break;
    }
    }
}
