#include "geombase.h"

class Renderer;

class Geom : public GeomBase {
public:
   int read(const char *filename);
   int render(Renderer *renderer, glm::mat4 rendermat,glm::mat4 viewrendermat,bool selectionMode) const;
   int id;
   Geom(int *idptr, const char *filename=NULL) {id = *idptr; *idptr = *idptr + 1;read(filename);}
   glm::mat4 getModelMatrix(){return modelMatrix;}
   
   void setModelMatrix(glm::mat4 model){modelMatrix = model;}
private:
   bool useDrawElements;
   int numIndices=-1;
   glm::mat4 modelMatrix;
};

