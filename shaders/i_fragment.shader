#version 330 core

out vec4 FragColor;

in float lightIntensity;
in vec2 uv;
float ambient = 0.2f;
uniform sampler2D diffuseTexture;
vec4 vertexColor;


void main()
{
  vec4 texColor = texture(diffuseTexture, uv);
  FragColor = vec4(texColor.rgb * (ambient + lightIntensity),texColor.a);
}