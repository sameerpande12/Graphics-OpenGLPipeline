#version 410
in vec4 vcolor;
in vec2 TexCoord;

out vec4 fcolor;

uniform sampler2D myTexture;


void main() {
   if (TexCoord[0]<=1 && TexCoord[0]>=0 && TexCoord[1]>=0 && TexCoord[1]<=1)
      fcolor = texture(myTexture,TexCoord);
   else 
      fcolor = vcolor;
}
