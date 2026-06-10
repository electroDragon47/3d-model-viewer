#version 330 core

out vec4 FragColor;

in float lightIntensity;
float ambient = 0.2f;

vec4 vertexColor;

void main()
{
  vertexColor = vec4 (1.0f, 1.0f ,1.0f, 1.0f);
  FragColor = vec4(vertexColor.rgb * (ambient + lightIntensity), 1.0f);
  // FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}