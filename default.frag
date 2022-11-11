#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 Normal;
in vec3 currentPos;

uniform sampler2D tex0;
uniform sampler2D tex1;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight() 
{
    vec3 lightVec = lightPos - currentPos;
    // float dist = length(lightVec);
    // float a = 3.0;
    // float b = 0.7;
    // float inten = 1.0 / (a * dist + b * dist + 1.0);

    float ambient = 0.2;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightVec);

    // Diffused lighting, can be negative - using max() 
    float diffuse = max(dot(normal, lightDirection), 0.0);

    float specularIntensity = 0.5; // Maximum intesity
    vec3 viewDirection = normalize(camPos - currentPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 16);
    float specular = specularAmount * specularIntensity;

    return (texture(tex0, texCoord) * (diffuse + ambient) + texture(tex1, texCoord).r * specular) * lightColor;

    // return (texture(tex0, texCoord) * lightColor * (diffuse + ambient) + texture(tex1, texCoord).r * specular);
}

void main()
{
    FragColor = pointLight();
}