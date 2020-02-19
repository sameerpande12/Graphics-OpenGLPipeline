mkdir -p build
g++ genSphereVertices.cpp -o genSphere
./genSphere
rm genSphere
g++ genPlaneVertices.cpp -o genPlane 
./genPlane
rm genPlane
make
./build/main