#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

in vec3 Normal;
in vec3 currentPos;

uniform sampler2D tex0;

uniform vec4 lightColor;
uniform vec3 lightPos;

void main()
{
    float ambientValue = 0.1;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - currentPos);

    // Diffused lighting, can be negative - using max() 
    float diffuse = max(dot(normal, lightDirection), 0.0);

    FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambientValue);
};