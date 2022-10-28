#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_video.h>

#include <cstdio>

#include "renderer.hpp"
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
    rend.loadShaders("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl");
    
    rend.addModel( 
        Model( Obj ("data/obj/fox.obj"),
        "data/obj/texture.png",
        {
            {0 ,0, -10},        //Position
            {0, 45, 0},          //Rotation
            {0.05, 0.05, 0.05}  //Scale
        } )
    );
    
    bool running = true;
    while (running) {
        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYUP:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                        break;
                    } 
                    break;
            }
        }
        //update frame
        SDL_GL_SetSwapInterval(1);
        
        /* Render */
        rend.update();
        rend.render();
        
        SDL_GL_SwapWindow(window);
    }    
    
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}        