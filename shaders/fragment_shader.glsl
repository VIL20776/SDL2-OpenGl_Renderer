#version 450 core
out vec4 fragColor;

in vec2 uvs;
uniform sampler2D tex;

void main()
{
    fragColor = texture(tex, uvs);
}