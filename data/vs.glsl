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
uniform vec3 LightPos1;
uniform vec3 LightPos2;
uniform vec3 CameraPos;
uniform float DiffusionCoefficient;
uniform float Shininess;
uniform float SpecularCoefficient;
void main() {

    gl_Position =  MVP * vec4(vp,1.0);

    vec3 transformedLightPos1 = vec3(CamViewMatrix*vec4(LightPos1,1));
    vec3 transformedLightPos2 = vec3(CamViewMatrix*vec4(LightPos2,1));
    vec3 transformedCameraPos = vec3(CamViewMatrix*vec4(CameraPos,1));

    vec3 transformedVp  = vec3(MV* vec4(vp,1));

    vec3 transformedNormal = normalize(vec3(MV * vec4(normal,0)));//since we are rotating the vector


    vec3 l1 = normalize(transformedLightPos1 - transformedVp);
    vec3 l2 = normalize(transformedLightPos2 - transformedVp);
    
    vec3 v = normalize(transformedCameraPos - transformedVp);
    
    vec3 h1 = normalize(v+l1);
    vec3 h2 = normalize(v+l2);

    float s = Shininess;
    float diffCoeff = 0.5* DiffusionCoefficient;
    float specCoeff = SpecularCoefficient;

    float diffColor =  diffCoeff*(  dot(l1,transformedNormal) + max(dot(l2,transformedNormal),0));
    
    float specColor = 0;
    if(dot(h1,transformedNormal)> 0)
        specColor = specCoeff * pow(dot(h1,transformedNormal),s);
    
    if(dot(h2,transformedNormal)> 0)
        specColor = specCoeff * pow(dot(h2,transformedNormal),s); 

    float finalCoeff = diffColor+specColor;
    
    colorMultiply = vec4(finalCoeff,finalCoeff,finalCoeff,1);
    vcolor = colorMultiply*inVertexColor;

    TexCoord = texPos;
   
}
