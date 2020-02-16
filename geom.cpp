#include <fstream>
#include <cstring>
#include <vector>
#include "geom.h"
#include "render.h"
#include "shader.h"
#include <iostream>
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
        if(!hasTex){
            for(int i = 0;i<numVertices;i++){
                    points[i*vertStride+vertStride - 2]=-1;
                    points[i*vertStride + vertStride -1 ]=-1;
            }   
        }

        GLuint vbo = 0;
        unsigned int ebo;
        

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glGenBuffers(1, &vbo);
        glGenBuffers(1,&ebo);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

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
        glDepthFunc(GL_LEQUAL);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
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
int Geom::render(Renderer *renderer, glm::mat4 rendermat, glm::mat4 viewrendermat) const//view render mat is same as render mat except projection matrix is not applied
{
    if(numIndices<=0 )return glGetError();
    // cout<<id<<"\n";
    renderer->useShader(shader);
    glm::vec3 cameraPos = renderer->camera.getPosition();
    // printVector("cameraPos",cameraPos);

    shader->setXform((const GLfloat*)glm::value_ptr(rendermat));
    shader->setMVmatrix((const GLfloat*)glm::value_ptr(viewrendermat));
    // shader->setMVinvmatrix((const GLfloat*)glm::value_ptr((viewrendermat)));
    shader->setViewMatrix((const GLfloat*)glm::value_ptr(renderer->camera.viewmatrix()));
    shader->setLightPos((const GLfloat*)glm::value_ptr(cameraPos));
    shader->setCameraPos((const GLfloat*)glm::value_ptr(cameraPos));
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D,tex);
    // cout<<id<<" "<<vao<<"\n";
    if(numIndices>0 && useDrawElements)
    {    
        glDrawElements(GL_TRIANGLES,numIndices,GL_UNSIGNED_INT,0);
    }
    else    
        glDrawArrays(GL_TRIANGLES, 0, 0);
    
    return glGetError();
}
