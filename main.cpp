#include "scene.hpp"
#include <cmath>
#include <memory>
#include <vector>
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_timer.h>

#include <cstdio>

#include "shader.hpp"
#include "renderer.hpp"
#include "controller.hpp"
#include "obj.hpp"

int main ()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return -1;
    }
    
    // OpenGL compatibility
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    
    const int width = 512;
    const int height = 512;
    
    // Creating SDL window
    SDL_Window* window = SDL_CreateWindow("OpenGl-SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    
    // Initialize GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::fprintf(stderr, "Failed to initialize GLEW.");
        return -1;
    }
    
    // Initialize renderer
    Renderer rend (width, height);  
    
    // Create Shaders 
    GLuint baseShader = ShaderFactory::createShader(
        "shaders/vertex_shader.glsl",
        "shaders/fragment_shader.glsl");
    GLuint toonShader = ShaderFactory::createShader(
        "shaders/vertex_shader.glsl",
        "shaders/toon_shader.glsl");
    GLuint glowShader = ShaderFactory::createShader(
        "shaders/vertex_shader.glsl",
        "shaders/glow_shader.glsl");
        
    std::shared_ptr<Scene> scene (new Scene {});
    scene->addShader(baseShader);
    scene->addShader(toonShader);
    scene->addShader(glowShader);
    
    scene->useShader(0);

    Model fox (
        Obj ("data/obj/fox.obj"),
        {
            {0 ,0, -10},        //Position
            {0, 45, 0},          //Rotation
            {0.05, 0.05, 0.05}  //Scale
        } );
        
    fox.loadTexture("data/obj/texture.png");
        
    scene->addModel(fox, true);
    
    Controller ctrl {scene};
    
    unsigned int oldTime = SDL_GetTicks(), newTime = 0;
    double deltaTime = 0;

    bool running = true;
    while (running) {
        // Delta time
        newTime = SDL_GetTicks();
        deltaTime = float(newTime - oldTime) * 0.001f;
        //Events
        if (ctrl.handleEvents(deltaTime) == STOP)
            running = false;
        //update frame
        SDL_GL_SetSwapInterval(1);
        
        /* Render */
        rend.update(scene);
        rend.render();
        
        SDL_GL_SwapWindow(window);

        oldTime = newTime;
    }    
    
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}        