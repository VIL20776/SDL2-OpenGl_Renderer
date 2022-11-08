#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "scene.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <memory>

const int STOP = 1;

class Controller
{
    public:
    Controller (std::shared_ptr<Scene> &scene);
    int handleEvents (float deltaTime);

    private:
    std::shared_ptr<Scene> scene;
    float deltaTime;

    void keyUpEvent (SDL_Keycode key);
    void keyDownEvent (SDL_Keycode key);
};

#endif