#include "geombase.h"

class Renderer;

class Geom : public GeomBase {
public:
   int read(const char *filename);
   int render(Renderer *renderer, glm::mat4 rendermat,glm::mat4 viewrendermat) const;
   Geom(const char *filename=NULL,int idV = 0) {id = idV;read(filename); }
   int id;
private:
   bool useDrawElements;
   int numIndices=-1;
   
};

