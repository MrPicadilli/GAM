#ifndef MESH_H
#define MESH_H

//#include <QGLWidget> //UpgradeQt6: #include <QOpenGLWidget>
#include <QOpenGLWidget>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
// TO MODIFY
class Iterator_on_vertices;
class Iterator_on_faces;
class Circulator_on_vertices;
class Circulator_on_faces;
class Mesh;
class Point;
class sommet;
class face;


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





class Point
{
public:
    double _x;
    double _y;
    double _z;

    Point():_x(),_y(),_z() {}
    Point(float x_, float y_, float z_):_x(x_),_y(y_),_z(z_) {}
    Point operator-(Point a){return Point(this->_x-a._x,this->_y-a._y,this->_z-a._z);}
    Point operator/(Point a){
        float x = this->_y * a._z - this->_z * a._y;
        float y = this->_z * a._x - this->_x * a._z;
        float z = this->_x * a._y - this->_y * a._x;
        return Point(x,y,z);
    }
    double distance(Point a){
        return sqrt(pow(this->_x - a._x,2) + pow((this->_y - a._y),2) + pow((this->_z - a._z),2));

    }
    double operator*(Point a){
        return this->_x * a._x + this->_y * a._y + this->_z * a._z ;
    }
    void operator=(const Point v){
        _x = v._x;
        _y = v._y;
        _z = v._z;
    }

    Point operator+(const Point v){
        return Point(_x + v._x, _y + v._y, _z + v._z);
    }

    Point operator*(double a){
        return Point(this->_x * a , this->_y * a , this->_z * a) ;
    }
    Point operator/(double a){
        return Point(this->_x / a , this->_y / a , this->_z / a) ;
    }
    double length() const{
        return sqrt(_x*_x + _y*_y + _z*_z);
    }
    double dotProduct( const Point v1){
        return _x*v1._x + _y*v1._y + _z*v1._z;
    }

    Point crossProduct(const Point v1){
        return Point(_y*v1._z - _z*v1._y,
                _z*v1._x - _x*v1._z,
                _x*v1._y - _y*v1._x);
    }

};


class sommet
{
public:
    int indice_sommet;
    Point point;
    sommet();
    sommet(int indice_face, Point point);
};



class face
{
public:
    int indice_current_face;
    std::vector<int> indice_face;
    std::vector<int> indice_vertices;
    Point center_circ_circle;

    face();
    face(int verti1,int verti2,int verti3);
    face(int verti1,int verti2,int verti3,int face1,int face2,int face3);


};


//** TP : TO MODIFY

class Mesh
{

public:
    // (Q ou STL)Vector of vertices
      std::vector<sommet> vertices;
    // (Q ou STL)Vector of faces
      std::vector<face> faces;
    // Those who do not know about STL Vectors should have a look at cplusplus.com examples
    Mesh(); // Constructors automatically called to initialize a Mesh (default strategy)
    ~Mesh(); // Destructor automatically called before a Mesh is destroyed (default strategy)
    face& find_face(int indice_face);
    void drawMesh(std::string file);
    void drawMeshWireFrame();
    Iterator_on_faces faces_past_the_end();
    Iterator_on_vertices vertices_past_the_end();
    Iterator_on_vertices vertices_begin();
    Iterator_on_faces faces_begin();
    Circulator_on_faces incident_faces(sommet &v);
    void split_triangle(int  indice_f ,Point p);
    void edge_flip(int indice_face_neighbour1, int indice_face_neighbour2);
    int orientation(Point p1,Point p2, Point p3);
    int in_triangle(face f, Point p);
    void put_point_in_mesh(Point p);
    void create_mesh_bounding_box(float taille, int nb_subdivision);
    int in_circle_circonscrit(int indice_face, Point inconnu);
    bool inside_triangle(Point X, Point Y);
    void Delaunay_lawson();
    double tangeante(Point BA, Point BC);
    double cosinus(Point BA, Point BC);
    double sinus(Point BA, Point BC);
    void Voronoi();


};

#endif // MESH_H




