#version 450 core
out vec4 fragColor;

in vec2 uvs;
in vec3 norms;
in vec3 pos;

uniform vec3 pointLight;
uniform sampler2D tex;

void main()
{
    float intensity = dot(norms, normalize(pointLight - pos));

    if (intensity < 0.25)
        intensity = 0.2;
    else if (intensity < 0.5)
        intensity = 0.4;
    else if (intensity < 0.75)
        intensity = 0.7;
    else if (intensity < 0.95)
        intensity = 0.9;
    else 
        intensity = 1;

    fragColor = texture(tex, uvs) * intensity;
}