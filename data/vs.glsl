#version 410
layout(location = 0) in vec3 vp;
out vec4 vcolor;
uniform mat4 MVP;
void main() {

   gl_Position =  MVP * vec4(vp,1.0);
   if( gl_VertexID == 0)
      vcolor = vec4(0,0,1,1);
   else if( ((gl_VertexID-1)/100)%3 == 0)
      vcolor = vec4(1, 0, 0, 1.0);
   else if(((gl_VertexID-1)/100)%3 == 1)
      vcolor = vec4(0, 1, 0, 1.0);
   else if(((gl_VertexID-1)/100)%3 == 2)
      vcolor = vec4(0, 0, 1.0, 1.0);
}
