#version 410
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 normal;
out vec4 vcolor;
uniform mat4 MVP;
uniform vec3 LightPos;
void main() {

   gl_Position =  MVP * vec4(vp,1.0);
   float invDist = length(vp - LightPos);
   invDist = invDist * invDist;
   invDist = 1/(invDist);
   vcolor =    vec4(invDist,invDist,invDist,1);
   
}
