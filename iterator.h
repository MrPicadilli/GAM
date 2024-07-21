#ifndef ITERATOR_H
#define ITERATOR_H

//#include "mesh.h"


class Circulator_on_vertices {
 public:
    int indice_current_sommet;
    int indice_current_face;

    Mesh *addresse_mesh;
    int center;
  Circulator_on_vertices();
  Circulator_on_vertices(int center, Mesh *addresse_mesh );

  int Next();
  int Current();

  int operator++();
  int operator*();

};







class Iterator_on_vertices {
 public:
    int indice_vertices;
    Mesh *addresse_mesh;
    Iterator_on_vertices();

  Iterator_on_vertices(int indice_vertices, Mesh *addresse_mesh );

  int operator++();
  int operator*();

};

class Circulator_on_faces {
 public:
    int indice_current_face;
    Mesh *addresse_mesh;
    int center;
  Circulator_on_faces();
  Circulator_on_faces(int indice_center, Mesh *addresse_mesh );

  int Next();
  int Current();

  int operator++();
  int operator*();

};



class Iterator_on_faces {
 public:
    int indice_face;
    Mesh *addresse_mesh;
    Iterator_on_faces();
  Iterator_on_faces(int indice_face, Mesh *addresse_mesh );

  int operator++();
  int operator*();

};








#endif // ITERATOR_H
