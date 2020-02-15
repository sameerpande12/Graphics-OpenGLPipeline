#version 410
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 inVertexColor;
layout(location = 3) in vec2 texPos;
out vec4 vcolor;
out vec2 TexCoord;
out vec4 colorMultiply;

uniform mat4 MVP;
uniform mat4 MV;
uniform vec3 LightPos;
void main() {

   gl_Position =  MVP * vec4(vp,1.0);
   vec3 newvp = vec3(MV*vec4(vp,1.0));
   float invDist = length( newvp );//in newvp which is in camera space , camera origin is at (0,0,0)
//    invDist = invDist * invDist;
   invDist = 1/(invDist);
   
   colorMultiply=vec4(invDist,invDist,invDist,1);
   vcolor =    colorMultiply * inVertexColor;
   
    TexCoord = texPos;
   
}
