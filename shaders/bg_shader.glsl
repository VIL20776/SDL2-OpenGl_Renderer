#version 450 core
out vec4 fragColor;

in vec2 uvs;
in vec3 norms;
in vec3 pos;

uniform vec3 pointLight;
uniform vec3 forward;

uniform sampler2D tex;

void main()
{
    float intensity = dot(norms, normalize(pointLight - pos));
    float pColor = 1 - dot(norms, forward);

    fragColor = texture(tex, uvs) * intensity;
    if (pColor < 0.5)
        fragColor.b += pColor;
    fragColor.r += pColor;

    if (fragColor.b > 1) fragColor.b = 1;
    if (fragColor.r > 1) fragColor.r = 1;
}