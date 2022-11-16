#include "scene.hpp"
#include "model.hpp"
#include <glm/fwd.hpp>
#include <cmath>
#include <memory>
#include <vector>

Scene::Scene()
{
    models = {};
    shaders = {};
    camera = std::make_shared<Camera>(
        glm::vec3(0,0,0),
        glm::vec3(0,0,0)
    );
    activeShader = nullptr;
    activeModel = nullptr;
    modelIndex = 0;
}

std::shared_ptr<Camera> Scene::shareCamera()
{
    return camera;
}

void Scene::addModel(Model model, bool target)
{
    models.push_back(model);
    if (target) {
        camera->setTarget(model.getPosition());
    }
}

void Scene::nextModel()
{
    modelIndex = std::abs(modelIndex + 1) % models.size();
    activeModel = &models.at(modelIndex);
}

void Scene::prevModel()
{
    modelIndex = std::abs(modelIndex - 1) % models.size();
    activeModel = &models.at(modelIndex);
    camera->setTarget(activeModel->getPosition());
}

void Scene::addShader(GLuint shader)
{
    shaders.push_back(shader);
}

void Scene::useShader(int i)
{
    activeShader = &shaders.at(i);
}

std::vector<Model> Scene::getSceneModels() { return models;}

GLuint Scene::getActiveShader() { return *activeShader;}

Model Scene::getActiveModel() {
    if (activeModel == nullptr)
        activeModel = &models.at(0);
    return *activeModel;
}