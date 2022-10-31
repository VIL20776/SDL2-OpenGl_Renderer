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
    
    void addModel (Model obj, bool focus = false);

    void setCamPosition (float x, float y, float z);

    std::vector<float> getCamPosition ();
    
    void render ();
    
    private:
    GLint width, height;
    GLuint activeShader;
    
    std::vector<Model> scene;

    glm::vec3 camPosition;
    glm::vec3 camRotation;
    glm::mat4 viewMatrix;

    glm::vec3 pointLight;

    glm::vec3 target;
    glm::vec3 angle;
    float camDistance;

    glm::mat4 projectionMatrix;
    
    void makeViewMatrix ();
};

#endif
