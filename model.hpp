#ifndef MODEL_H
#define MODEL_H
// local libs
#include "obj.hpp"
// OpenGL libs
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
// C++ libs
#include <vector>

struct ModelProps{
    glm::vec3 position {0, 0, 0};
    glm::vec3 rotation {0, 0, 0};
    glm::vec3 scale {1, 1, 1};
};

class Model
{
    public:
    Model (std::vector<GLfloat> data);
    
    Model (std::vector<GLfloat> data, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    
    Model (Obj object, string, ModelProps props = {});
    
    void render (const GLuint &shaderID); 
    
    private:
    GLuint vao; //vertex array
    GLuint vbo; //vertex buffer
    std::vector<GLfloat> data;
    
    int t_width, t_height,channels;
    unsigned char* textureData;
    GLuint texture;
    
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    
    glm::mat4 modelMatrix;
    size_t polyCount;
    
    void createVertexBuffer (Obj &object);
    void makeModelMatrix ();
};

#endif