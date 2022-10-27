#ifndef RENDERER_H
#define RENDERER_H
//OpenGL libs
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
//C++ libs
#include <vector>

// local libs
#include "model.hpp"

class Renderer
{
    public:
    Renderer (int width, int height);
    
    void update ();
    
    int loadShaders (const char *vertex_shader_path, const char *fragment_shader_path);
    
    void addModel (Model obj);
    
    void render ();
    
    private:
    GLint width, height;
    GLuint activeShader;
    std::vector<Model> scene;
    glm::vec3 camPosition;
    glm::vec3 camRotation;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    
    void makeViewMatrix ();
};

#endif
