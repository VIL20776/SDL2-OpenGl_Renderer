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

    fragColor = texture(tex, uvs) * intensity;
    
    fragColor.b = (fragColor.b <= 0.5) ? 0.3: 1;
    fragColor.g = (fragColor.g <= 0.5) ? 0.3: 1;
    fragColor.r = (fragColor.r <= 0.5) ? 0.3: 1;   
}