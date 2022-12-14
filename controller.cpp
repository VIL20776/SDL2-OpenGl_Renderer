#include "controller.hpp"
#include "scene.hpp"
#include <SDL2/SDL_keycode.h>
#include <glm/fwd.hpp>
#include <memory>

Controller::Controller (std::shared_ptr<Scene> &scene)
{
    this->scene = scene;
    
}

int Controller::handleEvents(float deltaTime)
{
        // Handle events
        this->deltaTime = deltaTime;
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    return 1;
                case SDL_KEYUP:
                    //ESC - Quit
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        return 1;
                    break;
                case SDL_KEYDOWN:
                {
                    SDL_Keycode key = event.key.keysym.sym;
                    keyDownEvent(key);
                    break;
                }
            }
        }
    return 0;
}

void Controller::keyDownEvent (SDL_Keycode key)
{
    if (key == SDLK_w)
    {
        glm::vec3 prevPos = scene->shareCamera()->getPosition();
        scene->shareCamera()->setPosition({prevPos.x, prevPos.y + 5*deltaTime, prevPos.z });
    }    
    if (key == SDLK_s)
    {
        glm::vec3 prevPos = scene->shareCamera()->getPosition();
        scene->shareCamera()->setPosition({prevPos.x, prevPos.y - 5*deltaTime, prevPos.z });
    }    
    if (key == SDLK_q)
    {
        glm::vec3 prevPos = scene->shareCamera()->getPosition();
        scene->shareCamera()->setPosition({prevPos.x, prevPos.y, prevPos.z + 5*deltaTime});
    }    
    if (key == SDLK_e)
    {
        glm::vec3 prevPos = scene->shareCamera()->getPosition();
        scene->shareCamera()->setPosition({prevPos.x, prevPos.y, prevPos.z - 5*deltaTime});
    }
    if (key == SDLK_a)
    {
        float prevAngle = scene->shareCamera()->getAngle();
        scene->shareCamera()->setPosition(prevAngle + 30*deltaTime);
    }
    if (key == SDLK_d)
    {
        float prevAngle = scene->shareCamera()->getAngle();
        scene->shareCamera()->setPosition(prevAngle - 30*deltaTime);
    }
    if (key == SDLK_r)
        scene->nextModel();

    if (key == SDLK_f)
        scene->prevModel();

    if (key == SDLK_1)
        scene->useShader(0);

    if (key == SDLK_2)
        scene->useShader(1);
    
    if (key == SDLK_3) 
        scene->useShader(2);
    
    if (key == SDLK_4)
        scene->useShader(3);
        
    if (key == SDLK_5)
        scene->useShader(4);
}
