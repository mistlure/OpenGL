#pragma once
#include <GL/glew.h>
#include <string>

class Texture {
public:
    Texture(const std::string& path);
    void bind(GLuint unit = 0) const;
    ~Texture();

private:
    GLuint id = 0;
};
