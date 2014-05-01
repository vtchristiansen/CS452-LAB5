#version 130

in vec3 Color;
in vec2 Texcoord;

out vec4 out_color;

uniform sampler2D mytex;

void main(){
  out_color=texture(mytex,Texcoord) * vec4(Color, 1.0);
}
