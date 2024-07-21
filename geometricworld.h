#ifndef GEOMETRICWORLD_H
#define GEOMETRICWORLD_H

#include "mesh.h"

class GeometricWorld //Here used to create a singleton instance
{
  QVector<Point> _bBox;  // Bounding box
public :
  GeometricWorld();
  void change_file(std::string file);
  void draw();
  void drawWireFrame();
  Circulator_on_vertices adjacent_vertices(sommet &  v);
  // ** TP Can be extended with further elements;
  Mesh _mesh;
};


#endif // GEOMETRICWORLD_H
