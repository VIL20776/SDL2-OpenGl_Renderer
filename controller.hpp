#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "scene.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

class SceneController
{
    public:
    SceneController (Scene scene);
    void HandleEvents (SDL_Event event);

    private:
    Scene scene;

    void KeyUpEvent (SDL_KeyCode key);
    void KeyDownEvent (SDL_KeyCode key);
};

#endif