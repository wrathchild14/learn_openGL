#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 currentPos;
out vec3 Normal;
out vec3 color;
out vec2 texCoord;

uniform mat4 camMatrix;
uniform mat4 model;

void main()
{
    currentPos = vec3(model * vec4(aPos, 1.0));
    Normal = aNormal;
    color = aColor;
    texCoord = aTex;

    gl_Position = camMatrix * vec4(currentPos, 1.0);
    // gl_Position = vec4(aPos.x * scale, aPos.y * scale, aPos.z * scale, 1.0);
}