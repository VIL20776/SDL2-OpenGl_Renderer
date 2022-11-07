#ifndef SHADERS_H
#define SHADERS_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

// Factory Shader
class ShaderFactory
{
    public:
    static void createShader (const char *vertex_shader_path, const char *fragment_shader_path);
};

#endif