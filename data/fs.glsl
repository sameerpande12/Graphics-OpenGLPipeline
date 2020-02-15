#version 410
in vec4 vcolor;
in vec2 TexCoord;

out vec4 fcolor;

uniform sampler2D myTexture;


void main() {
   fcolor = texture(myTexture,TexCoord);
   // fcolor = vcolor;
}
