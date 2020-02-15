#version 410
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 inVertexColor;
layout(location = 3) in vec2 texPos;
out vec4 vcolor;
out vec2 TexCoord;

uniform mat4 MVP;
uniform vec3 LightPos;
void main() {

   gl_Position =  MVP * vec4(vp,1.0);
   float invDist = length(vp - LightPos);
   invDist = invDist * invDist;
   invDist = 1/(invDist);
   vcolor =    inVertexColor;

  TexCoord = texPos;
   
}
