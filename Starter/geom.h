#include "geombase.h"

class Renderer;

class Geom : public GeomBase {
public:
   int read(const char *filename);
   int render(Renderer *renderer, glm::mat4 rendermat) const;
   Geom(const char *filename=NULL) { read(filename); }

};

