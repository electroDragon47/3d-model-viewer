#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;

out vec4 vertexColor;
uniform vec3 scale;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

vec3 lightVector;
vec3 normal;
out float lightIntensity;
vec3 worldPos;

void main()
{
    gl_Position =  projection * view * model *  vec4(aPos *scale, 1.0f);
    worldPos = vec3(model * vec4(aPos * scale, 1.0f));
    lightVector = normalize(lightPos - worldPos); // got the vector
    normal = normalize(mat3(model) * aNormal);
    lightIntensity = max(dot(lightVector, normal), 0);
    vertexColor = vec4(aColor , 1.0f);
}