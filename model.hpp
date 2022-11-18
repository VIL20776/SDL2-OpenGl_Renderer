#ifndef MODEL_H
#define MODEL_H
// local libs
#include "obj.hpp"
#include <string>
// OpenGL libs
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
// C++ libs
#include <vector>


class Model
{
    struct ModelProps{
        glm::vec3 position {0, 0, 0};
        glm::vec3 rotation {0, 0, 0};
        glm::vec3 scale {1, 1, 1};
    };

    public:
    Model (Obj object, std::string tex_path, ModelProps props = {{},{},{}});
    void loadTexture();
    void render (const GLuint &shaderID); 
    glm::vec3 getPosition ();
    
    private:
    GLuint vao; //vertex array
    GLuint vbo; //vertex buffer
    std::vector<GLfloat> data;
    
    std::string tex_path;
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