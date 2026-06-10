#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 scale;

uniform vec3 lightPos;
uniform vec3 lightColor;

vec3 worldPos;
vec3 lightVector;
vec3 normal;
out float lightIntensity;

void main()
{
    gl_Position = projection * view * model * vec4(aPos * scale, 1.0f);
    worldPos = vec3(model * vec4(aPos * scale, 1.0f));
    lightVector = normalize(lightPos - worldPos); // got the vector
    normal = normalize(mat3(model) * aNormal);
    lightIntensity = max(dot(lightVector, normal), 0);
}