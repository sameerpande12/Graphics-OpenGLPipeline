#include <fstream>
#include<iostream>
#include <cstring>
#include <vector>
// using namespace std;
int main(){
    std::ifstream infile("vertices.csv");
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

    float vertices[vertStride*numVertices];
    int indices[primStride*numPrimLines];

    for(int i=0;i<numVertices;i++){
        for(int j =0;j<vertStride;j++){
            vertices[i*vertStride+j]=stof(lines[i][j]);
            std::cout<<vertices[i*vertStride+j]<<" ";
        }
        std::cout<<'\n';
    }

    for(int i=0;i<numPrimLines;i++){
        for(int j=0;j<primStride;j++){
            indices[i*primStride + j] = stoi(lines[numVertices+i][j]);
            std::cout<<indices[i*primStride+j]<<" ";
            
        }
        std::cout<<'\n';
    }
    
    
    
    
}