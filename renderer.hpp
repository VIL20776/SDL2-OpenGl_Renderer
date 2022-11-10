#ifndef RENDERER_H
#define RENDERER_H
//OpenGL libs
#include <memory>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>
//C++ libs
#include <vector>
#include <ctime>

// local libs
#include "scene.hpp"
#include "model.hpp"

class Renderer
{
    public:
    Renderer (std::shared_ptr<Scene> scene, int width, int height);
    void update ();
    void render ();
    
    private:
    GLint width, height;
    std::shared_ptr<Scene> scene;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    
    std::vector<Model> models;
    GLuint activeShader;
    
    glm::vec3 pointLight;
    std::clock_t startupTime;
    
};

#endif
