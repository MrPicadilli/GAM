#include "iterator.h"




Iterator_on_faces::Iterator_on_faces(){

    indice_face = 0;
    addresse_mesh = new Mesh();
}

Iterator_on_faces::Iterator_on_faces(int indice_face, Mesh *addresse_mesh ) {
    this->addresse_mesh = addresse_mesh;
    this->indice_face = indice_face;
}

// Define prefix increment operator.
int Iterator_on_faces::operator++()
{
    indice_face ++;
    return indice_face;
}

// Define prefix increment operator.
int Iterator_on_faces::operator*()
{
    return indice_face;
}

Iterator_on_vertices::Iterator_on_vertices(int indice_vertices, Mesh *addresse_mesh ) {
    this->addresse_mesh = addresse_mesh;
    this->indice_vertices = indice_vertices;
}


// Define prefix increment operator.
int Iterator_on_vertices::operator++()
{
    indice_vertices ++;
    return indice_vertices;}

// Define prefix increment operator.
int Iterator_on_vertices::operator*()
{
    return indice_vertices;
}


Circulator_on_faces::Circulator_on_faces(){
    this->center = 0;
    this->indice_current_face = 0;
    addresse_mesh = new Mesh();
}

Circulator_on_faces::Circulator_on_faces(int indice_center, Mesh *addresse_mesh ) {
    this->center = indice_center;
    this->indice_current_face = 0;
    indice_current_face = -1;
    this->addresse_mesh = addresse_mesh;

    for(unsigned long i =0; i< addresse_mesh->faces.size(); i++){
        for(unsigned long y =0 ; y< addresse_mesh->faces[i].indice_face.size();y++){
            if(indice_center == addresse_mesh->faces[i].indice_vertices[y]){
                this->indice_current_face = addresse_mesh->faces[i].indice_face[y+1];
            }
        }
    }
}



int Circulator_on_faces::Next() {
    for(unsigned long i =0; i< addresse_mesh->faces[this->indice_current_face].indice_face.size(); i++){
        if(center == addresse_mesh->faces[indice_current_face].indice_vertices[i]){
            this->indice_current_face = addresse_mesh->faces[indice_current_face].indice_face[i+1];
            break;
        }
    }

  return indice_current_face;
}


int Circulator_on_faces::Current() {
    return indice_current_face;
}
// Define prefix increment operator.
int Circulator_on_faces::operator++()
{
   return Next();
}

// Define prefix increment operator.
int Circulator_on_faces::operator*()
{
   return Current();
}

/*****Circulator on vertices******/




Circulator_on_vertices::Circulator_on_vertices(){
    this->center = 0;// To find orientation of ordered triplet (p1, p2, p3).
    // The function returns following values
    // 0 --> p, q and r are collinear
    // 1 --> Clockwise
    // 2 --> Counterclockwise
    this->indice_current_sommet = 0;
    addresse_mesh = new Mesh();
}

Circulator_on_vertices::Circulator_on_vertices(int center, Mesh *addresse_mesh ) {
    this->center = center;
    this->indice_current_sommet = 0;
    indice_current_sommet = -1;
    this->addresse_mesh = addresse_mesh;

    for(unsigned long i =0; i< addresse_mesh->faces.size(); i++){
        for(unsigned long y =0; y<addresse_mesh->faces[i].indice_vertices.size();y++){
            if(addresse_mesh->faces[i].indice_vertices[y] == center){
                this->indice_current_sommet = addresse_mesh->faces[i].indice_vertices[y%2+1] ;
                this->indice_current_face = i ;
                break;
            }
        }
        if(indice_current_sommet !=-1){
            break;
        }


    }
}


int Circulator_on_vertices::Next() {
    for(unsigned long i =0; i<addresse_mesh->faces[this->indice_current_face].indice_vertices.size();i++){
        if(addresse_mesh->faces[indice_current_face].indice_vertices[i] == center){
            this->indice_current_face = addresse_mesh->faces[indice_current_face].indice_face[i%2+1] ;
            this->indice_current_face = i ;
            break;
        }

    }

    for(unsigned long i =0; i<addresse_mesh->faces[this->indice_current_face].indice_vertices.size();i++){
        if(addresse_mesh->faces[indice_current_face].indice_vertices[i] == center){
            this->indice_current_sommet = addresse_mesh->faces[indice_current_face].indice_vertices[i%2+1] ;
            break;
        }

    }

  return indice_current_sommet;
}



int Circulator_on_vertices::Current() {
    return indice_current_sommet;
}
// Define prefix increment operator.
int Circulator_on_vertices::operator++()
{
   return Next();
}

// Define prefix increment operator.
int Circulator_on_vertices::operator*()
{
   return Current();
}


/*************************************/


Iterator_on_faces Mesh::faces_past_the_end() {
    return Iterator_on_faces(this->faces.size(),this);
}
Iterator_on_vertices Mesh::vertices_past_the_end() {
    return Iterator_on_vertices(this->vertices.size(),this);
}
Iterator_on_vertices Mesh::vertices_begin(){
    return Iterator_on_vertices(0,this);
}
Iterator_on_faces Mesh::faces_begin(){
    return Iterator_on_faces(0,this);
}


