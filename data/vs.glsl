#version 410
layout(location = 0) in vec3 vp;
out vec4 vcolor;
uniform mat4 MVP;
void main() {
   gl_Position =  MVP * vec4(vp,1.0);
   if(gl_VertexID == 0)
      vcolor = vec4(0.5, 0.0, 0.5, 1.0);
   if(gl_VertexID == 1)
      vcolor = vec4(0.0, 0.5, 0.5, 1.0);
   if(gl_VertexID == 2)
      vcolor = vec4(0.5, 0.5, 0.0, 1.0);
}
