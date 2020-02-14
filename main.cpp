#include <glm/ext.hpp>
#include <iostream>
using namespace std;
int main(){
    // glm::mat4 translate = glm::translate(glm::mat4(1.f),glm::vec3(2.f,0.f,0.f));    
    // //this creates matrix such that matrix[3][0]=2;
    // // 1 0 0 0  t[0][0] 
    // // 0 1 0 0  t[1][0]
    // // 0 0 1 0  t[2][0]
    // // 2 0 0 1  t[3][0]

    
    // glm::vec4 v = glm::vec4(0,0,0,1);
    // glm::vec4 t = translate * v;
    // for(int i = 0;i<4;i++){
    //     for(int j = 0;j<4;j++){
    //         cout<<translate[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<endl;
    // for(int i =0;i<4;i++){
    //     cout<<t[i]<<endl;
    // }

    // glm::mat3 m = glm::mat3(1,2,3,4,5,6,7,8,9);
    // glm::mat3 n = glm::mat3(-1,2,-3,4,-5,6,-7,8,-9);

    // glm::mat3 r = m*n;
    // for(int i = 0;i<3;i++){
    //     for(int j = 0;j<3;j++){
    //         cout<<r[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    unsigned int indices[]={1,2,3,4,5,6,7,8};
    std::cout<<sizeof(indices)<<"\n";
    unsigned int x = 1;
    std::cout<<sizeof(x)<<'\n';

}