#include <fstream>
#include <cstring>
#include <vector>
#include "geom.h"
#include "render.h"
#include "shader.h"

int Geom::read(const char *filename)
{
    useDrawElements = false;
    if(filename==NULL){    
        float points[] = {
        1.f,  0.0f,  0.0f,
        -1.f,  0.0f,  0.0f,
        0.0f,  1.0f,  0.0f,

        1.f,  -0.5f,  0.0f,
        -1.f,  -0.5f,  0.0f,
        0.0f,  -1.2f, 0.0f
        };

        GLuint vbo = 0;

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glBindVertexArray(vao);

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);


        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        
        
        shader = new Shader("data/vs.glsl", "data/fs.glsl"); 
    }
    else{
        std::ifstream infile(filename);
        int numVertices = 0;
        int numPrimLines = 0;
        bool countVertices = true;
        int be,iter;    
        int vertStride;
        int primStride;
        std::vector<std::vector<std::string>> lines;
        while(!infile.eof()){
            std::string line;
            infile>>line;
            if(line.length()==0)continue;
            if(line.substr(0,2).compare("GL")==0){
                countVertices = false;   
                continue;   
            }
            if(countVertices)
                numVertices++;
            else 
                numPrimLines++;
            
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
            lines.push_back(vals);
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
        
        GLuint vbo = 0;
        unsigned int ebo;
        

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        
        glGenBuffers(1, &vbo);
        glGenBuffers(1,&ebo);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, vertStride, GL_FLOAT, GL_FALSE, 0, NULL);        
        glEnableVertexAttribArray(0);


        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);
        shader = new Shader("data/vs.glsl", "data/fs.glsl");
        useDrawElements = true;
        
    }

   return vao;
}

int Geom::render(Renderer *renderer, glm::mat4 rendermat) const
{
    renderer->useShader(shader);
    shader->setXform((const GLfloat*)glm::value_ptr(rendermat));
    glBindVertexArray(vao);
    if(numIndices>0 && useDrawElements)
        glDrawElements(GL_TRIANGLES,numIndices,GL_UNSIGNED_INT,0);
    else    
        glDrawArrays(GL_TRIANGLES, 0, 6);
    
    return glGetError();
}
