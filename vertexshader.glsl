#version 130

uniform mat4 Matrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

in vec3 in_position;
in vec2 texcoord;
in vec4 in_color;

out vec4 pass_color;
out vec3 Color;
out vec2 Texcoord;

void main(){
  gl_Position=Matrix*viewMatrix*modelMatrix*vec4(in_position,1.0); 
  pass_color=in_color;
  Texcoord = texcoord;
}
