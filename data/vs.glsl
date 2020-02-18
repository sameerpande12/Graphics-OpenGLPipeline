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

uniform mat4 CamViewMatrix;
uniform vec3 LightPos;
uniform vec3 CameraPos;
uniform float DiffusionCoefficient;
uniform float Shininess;
void main() {

    gl_Position =  MVP * vec4(vp,1.0);

    vec3 transformedLightPos = vec3(CamViewMatrix*vec4(LightPos,1));
    vec3 transformedCameraPos = vec3(CamViewMatrix*vec4(CameraPos,1));

    transformedLightPos = vec3(0,0,0);
    transformedCameraPos = vec3(0,0,0);

    vec3 transformedVp  = vec3(MV* vec4(vp,1));

    vec3 transformedNormal = normalize(vec3(MV * vec4(normal,0)));//since we are rotating the vector


    vec3 l = normalize(transformedLightPos - transformedVp);
    vec3 v = normalize(transformedCameraPos - transformedVp);
    vec3 h = normalize(v+l);

    float s = 0.5;
    float diffCoeff = DiffusionCoefficient;
    float specCoeff = Shininess;

    float diffColor = diffCoeff*dot(l,transformedNormal);
    
    float specColor = specCoeff * pow(dot(h,transformedNormal),s);
    if(dot(h,normal)<0)specColor = 0; 

    float finalCoeff = diffColor+specColor;
    
    colorMultiply = vec4(finalCoeff,finalCoeff,finalCoeff,1);
    vcolor = colorMultiply*inVertexColor;
    // vcolor = inVertexColor;
    // if(transformedVp[0]<0.1)
        // vcolor = vec4(1,0,1,1);
    TexCoord = texPos;
   
}
