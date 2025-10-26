#include "ShaderProgram.h"
#include <iostream>

// Constructor that links vertex and fragment shaders into a shader program
ShaderProgram::ShaderProgram(const Shader& vertex, const Shader& fragment)
{   
    // Create a new shader program object
    id = glCreateProgram();



    // Attach the compiled vertex&fragment shaders to the program
    // Safe access to internal shader ID
    glAttachShader(id, vertex.id);
    glAttachShader(id, fragment.id);
    // Combine vertex + fragment into one executable
    glLinkProgram(id);



    // Check if the linking was successful
    GLint success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);



	// Failure test
    if (!success)
    {
        GLint logLength;
        // Get the length of the error log
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);
        // Allocate memory for the log
        char* log = new char[logLength];
        // Retrieve the log content
        glGetProgramInfoLog(id, logLength, nullptr, log);
        // Print the error log
        std::cerr << "Shader program linking failed:\n" << log << std::endl;
        // Free the allocated memory
        delete[] log;
    }
}   

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(id);
}

void ShaderProgram::use()
{
    glUseProgram(id);
}



// Bridge between C++ and GLSL that passes transformation data.
// It's universal and will be used for every object.
void ShaderProgram::setModelMatrix(const glm::mat4& matrix)
{
	// Get the location of the "modelMatrix".
    GLint location = glGetUniformLocation(id, "modelMatrix");
	// Location -1 means that the uniform variable was not found or is not used in the shader.
    if (location == -1)
    {
        std::cerr << "Uniform 'modelMatrix' not found!" << std::endl;
        return;
    }
	// Upload the 4x4 matrix to the GPU.
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}



// Passes a 4x4 matrix to a uniform variable in the shader.
// Use for transformations like model, view, projection.
void ShaderProgram::setUniform(const std::string& name, const glm::mat4& matrix)
{
    GLint location = glGetUniformLocation(id, name.c_str());
    if (location != -1)
        glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

// Passes a vec3 to a uniform variable in the shader.
// Use for colors, light directions, positions.
void ShaderProgram::setUniform(const std::string& name, const glm::vec3& vector)
{
    GLint location = glGetUniformLocation(id, name.c_str());
    if (location != -1)
        glUniform3fv(location, 1, &vector[0]);
}

// Passes a float value to a uniform variable in the shader.
// Use for time, animation speed, transparency, etc.
void ShaderProgram::setUniform(const std::string& name, float value)
{
    GLint location = glGetUniformLocation(id, name.c_str());
    if (location != -1)
        glUniform1f(location, value);
}

// Passes an integer value to a uniform variable in the shader.
// Use for mode switching, flags, texture indices.
void ShaderProgram::setUniform(const std::string& name, int value)
{
    GLint location = glGetUniformLocation(id, name.c_str());
    if (location != -1)
        glUniform1i(location, value);
}


// Implementation of the ICameraObserver interface method.
void ShaderProgram::onCameraUpdated(const glm::mat4& viewMatrix)
{
    setUniform("viewMatrix", viewMatrix);
}
void ShaderProgram::onLightUpdated(const glm::vec3& position) {
    setUniform("lightPos", position);
}


void ShaderProgram::setLightPosition(const glm::vec3& position)
{
	setUniform("lightPos", position); //uniform name in shader.
}
void ShaderProgram::setLightPositions(const std::vector<glm::vec3>& positions) {
    GLint location = glGetUniformLocation(id, "lightPositions");
    if (location == -1) {
        std::cerr << "Uniform 'lightPositions' not found!" << std::endl;
        return;
    }
    glUniform3fv(location, static_cast<GLsizei>(positions.size()), &positions[0][0]);
}

// Sets an array of light attenuation values in the shader.
void ShaderProgram::setLightAttenuations(const std::vector<glm::vec3>& values) {
    GLint location = glGetUniformLocation(id, "lightAttenuations");
    if (location == -1) {
        std::cerr << "Uniform 'lightAttenuations' not found!" << std::endl;
        return;
    }
    glUniform3fv(location, static_cast<GLsizei>(values.size()), &values[0][0]);
}
