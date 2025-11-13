#include "ShaderProgram.h"
#include <iostream>

ShaderProgram::ShaderProgram(Shader& vertex, Shader& fragment)
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

void ShaderProgram::onNotify(ObservableSubjects source, const void* subject) {
    useProgram();
    switch (source) {
    case SCamera: {
        const Camera* cam = static_cast<const Camera*>(subject);
        setUniform("viewMatrix", cam->getViewMatrix());
        setUniform("projectMatrix", cam->getProjectionMatrix());
        setUniform("viewPos", cam->getPosition());
        break;
    }
    case SLight: {
        const Light* light = static_cast<const Light*>(subject);
        setUniform("lightPos", light->getPosition());
        //std::cout << "Light updated: " << light->getPosition().y << std::endl;
        break;
    }
    default:
        break;
    }
}
