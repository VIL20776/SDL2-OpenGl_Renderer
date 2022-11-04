#version 450 core
out vec4 fragColor;

in vec2 uvs;
in vec3 norms;
in vec3 pos;

uniform vec3 pointLight;
uniform float time;
uniform sampler2D tex;

void main()
{
    float intensity = dot(norms, normalize(pointLight - pos));

    intensity = intensity + sin(time * 0.3);

    if (intensity < 0)
        intensity = 0;
    else if (intensity > 1)
        intensity = 1;

    fragColor = texture(tex, uvs) * intensity;
}