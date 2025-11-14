// ShaderProgram links multiple shaders into a complete GPU program.
// 
// It handles linking, validation, and activation of the program.

#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Observer.h"
#include "Camera.h"
#include "Light.h"

#include <vector>
#include <string>

class ShaderProgram : public Observer
{
public:
    ShaderProgram(Shader& vertex, Shader& fragment, Camera* camera, std::vector<Light*>* lights);
    ~ShaderProgram();

    void useProgram();
    
    void setModelMatrix(const glm::mat4& matrix) const;

    void setUniform(const std::string& name, const glm::mat4& matrix) const;
    void setUniform(const std::string& name, const glm::vec3& vector) const;
    void setUniform(const std::string& name, float value) const;
    void setUniform(const std::string& name, int value) const;

    void onNotify(ObservableSubjects source) override;


private:
    GLuint id;
	Camera* camera = nullptr;
	std::vector<Light*>* lights= nullptr;
};
