#include <stdio.h>
#include "iostream"
#include <cmath>
#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;
int main(int argc, char**argv){//produces an xy plane
    unordered_map<int,std::vector<float>> points;
    float len = 1.0;
    int numPoints = 25;//including both the poles
    int id = 0;

    ofstream outputfile;
    outputfile.open("xyPlaneVertices.csv");
    
    std::vector<std::vector<int>>triangles;
    for(int i = 0;i<numPoints;i++){
        for(int j = 0;j<numPoints;j++){
            float x = -len/2 + ((float)i/(float)(numPoints-1)) * len ;
            float y = -len/2 + ((float)j/(float)(numPoints-1)) * len ;
            float z = 0;
            float texX = (x+len/2)/len;
            float texY = (y + len/2)/len;
            // float color[] = {0.984,0.851,0.329,1};
            float color[] = {1,1,1,0.5};
            float normal[] = {0,0,1};
            points[id] = std::vector<float>{x,y,z,normal[0],normal[1],normal[2],color[0],color[1],color[2],color[3],texX,texY};

            for(int iter = 0;iter<points[id].size();iter++){
                outputfile<<points[id][iter];
                if(iter==points[id].size()-1)outputfile<<'\n';
                else outputfile<<",";
            }

            if(i!=numPoints-1 && j!= numPoints - 1){
                std::vector<int> tri1;
                tri1.push_back(id);
                tri1.push_back(id+numPoints);
                tri1.push_back(id + numPoints + 1);

                triangles.push_back(tri1);

                std::vector<int> tri2;

                
                tri2.push_back(id);
                tri2.push_back(id+numPoints+1);
                tri2.push_back(id + 1);
                triangles.push_back(tri2);
            }
            id++;
        }
        
    }
    outputfile<<"GL_TRIANGLES,data/snowtex.jpg\n";
    for(int i = 0;i<triangles.size();i++){
        for(int j = 0;j<triangles[i].size();j++){
            outputfile<<triangles[i][j];
            if(j!=triangles[i].size()-1)outputfile<<',';
            else outputfile<<'\n';
        }
    }

}