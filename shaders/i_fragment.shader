#version 330 core

in vec4 vertexColor;
out vec4 FragColor;

in float lightIntensity;
float ambient = 0.2f;
vec3 white = vec3(1.0f, 0.0f, 0.0f);

void main()
{
  FragColor = vec4(white * (ambient + lightIntensity), 1.0f);
//   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}