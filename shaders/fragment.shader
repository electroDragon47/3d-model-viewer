#version 330 core

in vec4 vertexColor;
out vec4 FragColor;

in float lightIntensity;
float ambient = 0.2f;

void main()
{
  FragColor = vec4(vertexColor.rgb * (ambient + lightIntensity), 1.0f);
}