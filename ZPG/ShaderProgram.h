// ShaderProgram links multiple shaders into a complete GPU program.
// 
// It handles linking, validation, and activation of the program.

#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "CameraObserver.h"
#include "ILightObserver.h"

#include <vector>
#include <string>

class ShaderProgram : public ICameraObserver, public ILightObserver
{
public:
    ShaderProgram(const Shader& vertex, const Shader& fragment);
    ~ShaderProgram();

    void use() const;

    void setModelMatrix(const glm::mat4& matrix) const;

    void setUniform(const std::string& name, const glm::mat4& matrix) const;
    void setUniform(const std::string& name, const glm::vec3& vector) const;
    void setUniform(const std::string& name, float value) const;
    void setUniform(const std::string& name, int value) const;
    
    void onCameraUpdated(const glm::mat4& viewMatrix) override;
    void onLightUpdated(const glm::vec3& position) override;

    void setLightPosition(const glm::vec3& position);
    void setLightPositions(const std::vector<glm::vec3>& positions);

    void setLightAttenuations(const std::vector<glm::vec3>& values);
private:
    GLuint id;
};