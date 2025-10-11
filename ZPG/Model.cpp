#include "Model.h"

Model::Model(float* data, size_t size)
{
    // Generate VAO to store vertex attribute configuration
    glGenVertexArrays(1, &vao);
	// Generate VBO to store vertex data in GPU memory
    glGenBuffers(1, &vbo);



    // Bind the VAO
    // This stores the vertex attribute configuration
    glBindVertexArray(vao);
	// Bind the VBO
    // This holds the actual vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Upload the vertex data to the GPU
    // 'size' is the total byte size, 'data' is the pointer to the vertex array
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);



    // Enable vertex attribute at location 0
    // This is typically used for vertex positions (vec3)
    glEnableVertexAttribArray(0);

    // Define how attribute 0 is laid out in the buffer
    // It reads 3 floats starting at offset 0, with a stride of 6 floats per vertex
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);



    // Enable vertex attribute at location 1
    // This is typically used for normals or colors (vec3)
    glEnableVertexAttribArray(1);
    // Define how attribute 1 is laid out in the buffer
    // It reads 3 floats starting at offset 3 * sizeof(float), same stride
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));

    vertexCount = size / (6 * sizeof(float));
}

Model::~Model()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

void Model::bind()
{
    glBindVertexArray(vao);
}

void Model::draw()
{
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}