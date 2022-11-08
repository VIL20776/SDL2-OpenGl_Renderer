#ifndef SCENE_H
#define SCENE_H

#include "shader.hpp"
#include "model.hpp"
#include "camera.hpp"

#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include <vector>
#include <memory>

class Scene
{
    public:
    Scene ();
    std::shared_ptr<Camera> shareCamera();
    void addModel (Model model, bool target = false);
    void addShader (GLuint shader);
    void useShader (int i);
    std::vector<Model> getSceneModels ();
    GLuint getActiveShader ();

    private:
    std::vector<Model> models;
    std::vector<GLuint> shaders;
    std::shared_ptr<Camera> camera;
    GLuint activeShader;
};

#endif