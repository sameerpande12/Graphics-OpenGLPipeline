#include <stdio.h>
#include "iostream"
#include <cmath>
#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;
int main(int argc, char**argv){
    unordered_map<int,std::vector<float>> points;
    float R = 1.0;
    float theta = 0.0;
    //theta is the angle in the x-y plane with x angle
    float phi = 0.0;//phi is the angle with xy plane
    
    int numLatitudes = 150;//including both the poles
    int numLongitudes = 150;
    int id = 0;

    ofstream outputfile;
    outputfile.open("vertices.csv");
    
    // points[id]= std::vector<float> {0,0,-R};
    points[id]= std::vector<float> {0,0,-R,0,0};
    id++;

    for(int i = 1; i<=numLatitudes-2;i++){
        phi = M_PI_2 * (   2* ((float)(i)/(float)(numLatitudes-1)) - 1);
        for(int j = 0;j<numLongitudes;j++){
            theta = M_PI * (   2* ((float)(j)/(float)(numLongitudes)) - 1);
            float x = R * cos(phi) * cos(theta);
            float y = R * cos(phi) * sin(theta);
            float z = R * sin(phi);
            std::vector<float> temp;
            temp.push_back(x);temp.push_back(y);temp.push_back(z);

            float texX = 0.5*(theta/(M_PI)+1);
            float texY = phi/M_PI + 0.5;
            
            temp.push_back(texX);
            temp.push_back(texY);

            points[id]=temp;
            id++;
        } 
    }

    // points[id]= std::vector<float> {0,0,R};
    points[id]= std::vector<float> {0,0,R,0,1};
    id++;

    std::vector<std::vector<int>>triangles;
    int numPoints = id;
    int offset = 0;//offset at beginning of begLevel shows number of points covered in all levels before begLevel
    for(int begLevel=0;begLevel<numLatitudes-1;begLevel++){
        if(begLevel==0){
            for(int j = 0;j<numLongitudes;j++){
                std::vector<int>temp;
                temp.push_back(offset);
                temp.push_back(offset+1+j);
                temp.push_back(offset+1 + (j+1)%numLongitudes);
                triangles.push_back(temp);
            }
            offset = offset + 1;
        }
        else if(begLevel==numLatitudes-2){
            for(int j=0;j<numLongitudes;j++){
                std::vector<int>temp;
                temp.push_back(offset+j);
                temp.push_back(offset+numLongitudes);
                temp.push_back(offset+(j+1)%numLongitudes);
                triangles.push_back(temp);
                
            }
            offset = offset + numLongitudes;
        }
        else{
            //points in this level will be -> offset, offset+1, ...., offset + numLongitudes -1 
            for(int j=0;j<numLongitudes;j++){

                std::vector<int>temp2;
                temp2.push_back(offset+j);
                temp2.push_back(offset+numLongitudes +j );
                temp2.push_back(offset+numLongitudes+(j+1)%numLongitudes);
                triangles.push_back(temp2);

                std::vector<int>temp1;
                temp1.push_back(offset+j);
                temp1.push_back(offset+numLongitudes+(j+1)%numLongitudes);
                temp1.push_back(offset+ (j+1)%numLongitudes);
                triangles.push_back(temp1);

            }
            offset = offset + numLongitudes;

        }
    }
    offset++;//to include the top most point

    for(int i = 0;i<offset;i++){
        outputfile<<points[i][0]<<","<<points[i][1]<<","<<points[i][2]<<",";
        
        outputfile<<points[i][0]/R<<","<<points[i][1]/R<<","<<points[i][2]/R<<",";//the normals of sphere

        outputfile<<points[i][3]<<","<<points[i][4]<<"\n";//the normals of sphere

    }
    outputfile<<"GL_TRIANGLES\n";
    for(int i = 0;i<triangles.size();i++){
        for(int j = 0;j<triangles[i].size();j++){
            outputfile<<triangles[i][j];
            if(j!=triangles[i].size()-1)outputfile<<',';
            else outputfile<<'\n';
        }
    }

}