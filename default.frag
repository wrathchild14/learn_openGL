#version 330 core

out vec4 FragColor;

in vec3 currentPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight()
{
    vec3 lightVec = lightPos - currentPos;
    float dist = length(lightVec);
    // todo: constants for the point light (use uniform later on)
    float a = 3.0;
    float b = 0.7;
    float intensity = 1.0 / (a * dist + b * dist + 1.0);

    float ambient = 0.2;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightVec);

    // Diffused lighting, can be negative - using max() 
    float diffuse = max(dot(normal, lightDirection), 0.0);

    float specularIntensity = 0.5;// Maximum intesity
    vec3 viewDirection = normalize(camPos - currentPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 16);
    float specular = specularAmount * specularIntensity;

    return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;

    // return (texture(tex0, texCoord) * lightColor * (diffuse + ambient) + texture(tex1, texCoord).r * specular);
}

vec4 directionalLight()
{
    float ambient = 0.2;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(vec3(1.0, 1.0, 0.0));

    float diffuse = max(dot(normal, lightDirection), 0.0);

    float specularIntensity = 0.5;// Maximum intesity
    vec3 viewDirection = normalize(camPos - currentPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 16);
    float specular = specularAmount * specularIntensity;

    return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;

    // return (texture(tex0, texCoord) * lightColor * (diffuse + ambient) + texture(tex1, texCoord).r * specular);
}

vec4 spotLight()
{
    // to cones to have a nice gradient
    float outerCone = 0.5;
    float innerCone = 0.95;

    float ambient = 0.2;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - currentPos);

    float diffuse = max(dot(normal, lightDirection), 0.0);

    float specularIntensity = 0.5;// Maximum intesity
    vec3 viewDirection = normalize(camPos - currentPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0), 16);
    float specular = specularAmount * specularIntensity;

    float angle = dot(vec3(0.0, -1.0, 0.0), -lightDirection);
    float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0, 1.0);

    return (texture(diffuse0, texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;

    // return (texture(tex0, texCoord) * lightColor * (diffuse + ambient) + texture(tex1, texCoord).r * specular);
}

void main()
{
    //    FragColor = pointLight();
    //    FragColor = directionalLight();
    FragColor = spotLight();
}