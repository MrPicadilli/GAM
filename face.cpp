#include "face.h"

face::face()
{
}
face::face(int verti1,int verti2,int verti3,int face1,int face2,int face3){
    this->indice_face.push_back(face1);
    this->indice_face.push_back(face2);
    this->indice_face.push_back(face3);

    this->indice_vertices.push_back(verti1);
    this->indice_vertices.push_back(verti2);
    this->indice_vertices.push_back(verti3);

}
