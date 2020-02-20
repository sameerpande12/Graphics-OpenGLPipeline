#include <fstream>
#include <cstring>
#include <vector>
#include "geom.h"
#include "render.h"
#include "shader.h"
#include <iostream>
#include "limits"
#define INF std::numeric_limits<double>::infinity();
#define cout std::cout
#define endl std::endl

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
int Geom::read(const char *filename)
{   
    
    useDrawElements = false;
    if(filename==NULL){    
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        shader = new Shader("data/vs.glsl", "data/fs.glsl");//render nothing 
    }
    else{
        // cout<<"filename="<<filename<<endl;
        std::ifstream infile(filename);
        int numVertices = 0;
        int numPrimLines = 0;
        bool countVertices = true;
        int be,iter;    
        int vertStride;
        int primStride;
        std::vector<std::vector<std::string>> lines;
        std::string imageFileName;
        while(!infile.eof()){
            std::string line;
            infile>>line;
            if(line.length()==0)continue;
            
            
            std::vector<std::string> vals;
            be = 0;iter=0;
            while(iter<line.length()){
                if(line[iter]==','){
                    vals.push_back(line.substr(be,iter-be));
                    be = iter  + 1;
                }
                iter++;
            }
            
            vals.push_back(line.substr(be,iter-be));
            
            if(line.substr(0,2).compare("GL")==0){
                countVertices = false;
                if(vals.size()>=2)
                    imageFileName=vals[1];
                else 
                    imageFileName = "";
                continue;   
            }
            

            lines.push_back(vals);
            if(countVertices)
                numVertices++;
            else 
                numPrimLines++;
            
            if(countVertices)vertStride = vals.size();
            else primStride = vals.size();
        }

        float points[vertStride*numVertices];
        int indices[primStride*numPrimLines];

        for(int i=0;i<numVertices;i++){
            for(int j =0;j<vertStride;j++){
                points[i*vertStride+j]=stof(lines[i][j]);
                
            }
            
        }

        for(int i=0;i<numPrimLines;i++){
            for(int j=0;j<primStride;j++){
                indices[i*primStride + j] = stoi(lines[numVertices+i][j]);
                
            }
        }

        bool hasTex = true;
        if(imageFileName.length()>0){
            std::ifstream checkFile(imageFileName);
            if(checkFile){
                checkFile.close();
            }
            else{
                hasTex = false;
            }
        }
        else{
            hasTex = false;

        }
        hasTex = hasTex && useTexture;
        // cout<<"id = "<<id<<" "<<" Texture"<<hasTex<<"\n";
        
        if(!hasTex){
         
            for(int i = 0;i<numVertices;i++){
                    points[i*vertStride+vertStride - 2]=-1;
                    points[i*vertStride + vertStride -1 ]=-1;
            }   
        }

        if(useDefaultColour){
            for(int i  =0 ;i<numVertices;i++){
                points[i*vertStride+6] = color[0];
                points[i*vertStride+7] = color[1];
                points[i*vertStride+8] = color[2];
                points[i*vertStride+9] = color[3];
            }
        }

        GLuint vbo = 0;
        unsigned int ebo;
        

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glGenBuffers(1, &vbo);
        glGenBuffers(1,&ebo);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertStride*sizeof(float), (void*)(0));        
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertStride*sizeof(float), (void*)(3*sizeof(float)));        
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, vertStride*sizeof(float), (void*)(6*sizeof(float)));        
        glEnableVertexAttribArray(2);
        
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, vertStride*sizeof(float), (void*)(10*sizeof(float)));        
        glEnableVertexAttribArray(3);
        if(hasTex){
                
                // cout<<"id "<<id<<" fname:"<<imageFileName<<"\n";
                // unsigned int tex;
                glGenTextures(1,&tex);
                glBindTexture(GL_TEXTURE_2D,tex);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                // set texture filtering parameters
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                int width;
                int height;
                int numChannels;
                stbi_set_flip_vertically_on_load(true);

                char imFileArr[imageFileName.length()+1];
                strcpy(imFileArr,imageFileName.c_str());
                unsigned char* image = stbi_load(imFileArr,&width,&height,&numChannels,0);
                if(image!=NULL){
                    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,image);
                    glGenerateMipmap(GL_TEXTURE_2D);
                }//https://learnopengl.com/Getting-started/Textures
            
        }
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_DYNAMIC_DRAW);
        shader = new Shader("data/vs.glsl", "data/fs.glsl");
        useDrawElements = true;
        numIndices = numPrimLines*primStride;
    }

   return vao;
}

void printVector(std::string str,glm::vec3 vec){
    cout<<str<<" ";
    cout<<vec[0]<<","<<vec[1]<<","<<vec[2]<<"\n";
}

float Geom::getIntersectionTValue(glm::vec3 rayOrigin, glm::vec3 rayDir){
    if(isSphere){

            double tmin = INF;
            double a,b,c;
            // if(id==7)printVector("Centre of Sphere ", featureVec);
            glm::vec3 centreToRayOrg = rayOrigin - featureVec;
            a = glm::dot(rayDir,rayDir);
            b = 2* glm::dot(rayDir,centreToRayOrg);
            c = glm::dot(centreToRayOrg,centreToRayOrg) - featureValue*featureValue;

            double discriminant = b*b - 4*a*c;
            // if(id==7)cout<<discriminant<<"\n";
            int numRoots = 0;
            if(discriminant < 0){
                
                return (float)tmin;
            }
            numRoots= numRoots + 2 ;

            std::vector<double> roots;
            double root1 = (-b + sqrt(discriminant))/(2*a);
            double root2 = (-b - sqrt(discriminant))/(2*a);

            roots.push_back(root1);
            roots.push_back(root2);

            for(int i =0 ;i<numRoots;i++){
                if(roots[i]>=0 && roots[i]<=tmin){
                    tmin = roots[i];
                }
            }
            
            return (float)tmin;
    }
    else{
        double tmin = INF;
        if( glm::dot(featureVec,rayDir)==0)return (float)tmin;

        double tempTvalue = ( featureValue - glm::dot(featureVec,rayOrigin))/(glm::dot(featureVec,rayDir));

        // cout<<"tempTvalue=="<<tempTvalue<<"\n";
        if(tempTvalue>=0 && tempTvalue < tmin){

            glm::vec3 location = rayOrigin + (float)tempTvalue * rayDir;
            // printVector("location ",location);
            // printVector("minBound",minBounds);
            // printVector("maxBound",maxBounds);
            if( location[0] >= minBounds[0]-delta && location[1]>=minBounds[1] -delta && location[2] >= minBounds[2]-delta 
            &&  location[0] <= maxBounds[0]+delta && location[1]<=maxBounds[1] +delta && location[2] <= maxBounds[2]+delta){
                
                
                tmin = tempTvalue;
            }
        }

        // cout<<"tmin=="<<tmin<<"\n\n";
        
            return (float)tmin;   
    }
};
int Geom::render(Renderer *renderer, glm::mat4 rendermat, glm::mat4 viewrendermat,bool renderMirror,bool reflectScene) const//view render mat is same as render mat except projection matrix is not applied
{
    if(numIndices<=0 )return glGetError();
    
    // if(renderMirror && id==renderer->getFloorID())return glGetError();
    // cout<<"Render Mirror = "<<renderMirror<<" reflectScene "<<reflectScene<<"\n";

    if(renderMirror && id!=renderer->getFloorID())return glGetError();
    if(!renderMirror && id==renderer->getFloorID())return glGetError();

    if(reflectScene){
        glm::mat4 viewMatrix = renderer->camera.viewmatrix();
        glm::mat4 projmat = rendermat * glm::inverse(viewrendermat);
        glm::mat4 objectMatrix = glm::inverse(viewMatrix) * viewrendermat;
        objectMatrix = glm::scale(glm::mat4(1.0f),glm::vec3(1,1,-1))*objectMatrix ;//reflection about z =  0
    
        viewrendermat = viewMatrix * objectMatrix;
        rendermat = projmat * viewrendermat;
    }

    //  if(id==renderer->getFloorID()){ 
    if(renderMirror){   
        // cout<<"HI\n"; 
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
     }
    
    renderer->useShader(shader);
    glm::vec3 cameraPos = renderer->camera.getPosition();
    shader->setXform((const GLfloat*)glm::value_ptr(rendermat));
    shader->setMVmatrix((const GLfloat*)glm::value_ptr(viewrendermat));
    shader->setViewMatrix((const GLfloat*)glm::value_ptr(renderer->camera.viewmatrix()));
    shader->setLightPos1((const GLfloat*)glm::value_ptr(cameraPos));
    shader->setLightPos2((const GLfloat*)glm::value_ptr(topLight));
    shader->setLightIntensity1((const GLfloat*)glm::value_ptr(lightIntensity1));
    shader->setLightIntensity2((const GLfloat*)glm::value_ptr(lightIntensity2));
    shader->setCameraPos((const GLfloat*)glm::value_ptr(cameraPos));
    
    shader->setDiffusion((GLfloat)diffuseness);
    shader->setShininess((GLfloat)shininess);
    shader->setSpecularCeoff((GLfloat)specularCoefficient);
   
   
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D,tex);
   
    if(numIndices>0 && useDrawElements)
    {    
        glDrawElements(GL_TRIANGLES,numIndices,GL_UNSIGNED_INT,0);
    }
    else    
        glDrawArrays(GL_TRIANGLES, 0, 0);

    // if(id==renderer->getFloorID()){
    if(renderMirror){
        glDisable(GL_BLEND);
    }
    return glGetError();
}
