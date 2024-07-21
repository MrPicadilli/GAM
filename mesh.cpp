#include "mesh.h"
#include "QFile"
#include "QTextStream"
#include "qdebug.h"



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
            //this->indice_current_face = i ;
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





sommet::sommet()
{

}
sommet::sommet(int indice_sommet, Point point){
    this->indice_sommet = indice_sommet;
    this->point = point;
}


face::face()
{
}
face::face(int verti1,int verti2,int verti3){
    this->indice_vertices.push_back(verti1);
    this->indice_vertices.push_back(verti2);
    this->indice_vertices.push_back(verti3);


}
face::face(int verti1,int verti2,int verti3,int face1,int face2,int face3){
    this->indice_face.push_back(face1);
    this->indice_face.push_back(face2);
    this->indice_face.push_back(face3);

    this->indice_vertices.push_back(verti1);
    this->indice_vertices.push_back(verti2);
    this->indice_vertices.push_back(verti3);

}




Mesh::Mesh(){

}
Mesh::~Mesh(){

}



void Mesh::edge_flip(int indice_face_neighbour1, int indice_face_neighbour2){


    std::cout<< "je dois flip : " << indice_face_neighbour1 << " et " << indice_face_neighbour2 << std::endl;

/*

    for(int i = 0 ; i<faces.size() ; i++){
        std::cout<< "face numero : " << faces[i].indice_current_face << std::endl;
        std::cout<< "face voisin 0 : " << faces[i].indice_face[0]  << " au coordonnées : " << faces[i].indice_vertices[0] << "," << faces[i].indice_vertices[1] << "," <<faces[i].indice_vertices[2] << std::endl;
        std::cout<< "face voisin 1 : " << faces[i].indice_face[1] << " au coordonnées : " << faces[i].indice_vertices[0] << "," << faces[i].indice_vertices[1] << "," <<faces[i].indice_vertices[2] << std::endl;
        std::cout<< "face voisin 2 : " << faces[i].indice_face[2] << " au coordonnées : " << faces[i].indice_vertices[0] << "," << faces[i].indice_vertices[1] << "," <<faces[i].indice_vertices[2] << std::endl;
     }
    */


    std::vector<face> copie = faces;
/*
    std::cout<< "face numero : " << faces[indice_face_neighbour1].indice_current_face << std::endl;
    std::cout<< "face voisin 0 : " << faces[indice_face_neighbour1].indice_face[0]  << " au coordonnées : " << faces[indice_face_neighbour1].indice_vertices[0] << "," << faces[indice_face_neighbour1].indice_vertices[1] << "," <<faces[indice_face_neighbour1].indice_vertices[2] << std::endl;
    std::cout<< "face voisin 1 : " << faces[indice_face_neighbour1].indice_face[1] << " au coordonnées : " << faces[indice_face_neighbour1].indice_vertices[0] << "," << faces[indice_face_neighbour1].indice_vertices[1] << "," <<faces[indice_face_neighbour1].indice_vertices[2] << std::endl;
    std::cout<< "face voisin 2 : " << faces[indice_face_neighbour1].indice_face[2] << " au coordonnées : " << faces[indice_face_neighbour1].indice_vertices[0] << "," << faces[indice_face_neighbour1].indice_vertices[1] << "," <<faces[indice_face_neighbour1].indice_vertices[2] << std::endl;

    std::cout<< "face numero : " << faces[indice_face_neighbour2].indice_current_face << std::endl;
    std::cout<< "face voisin 0 : " << faces[indice_face_neighbour2].indice_face[0]  << " au coordonnées : " << faces[indice_face_neighbour2].indice_vertices[0] << "," << faces[indice_face_neighbour2].indice_vertices[1] << "," <<faces[indice_face_neighbour2].indice_vertices[2] << std::endl;
    std::cout<< "face voisin 1 : " << faces[indice_face_neighbour2].indice_face[1] << " au coordonnées : " << faces[indice_face_neighbour2].indice_vertices[0] << "," << faces[indice_face_neighbour2].indice_vertices[1] << "," <<faces[indice_face_neighbour2].indice_vertices[2] << std::endl;
    std::cout<< "face voisin 2 : " << faces[indice_face_neighbour2].indice_face[2] << " au coordonnées : " << faces[indice_face_neighbour2].indice_vertices[0] << "," << faces[indice_face_neighbour2].indice_vertices[1] << "," <<faces[indice_face_neighbour2].indice_vertices[2] << std::endl;
*/
    int indice_point_arrete[2];
    int x = 0;


    //je prend l'arrete que je veux changer
     for(int i = 0 ; i < 3 ; i++ ){
         for(int j = 0 ; j < 3 ; j++ ){
             if(vertices[faces[indice_face_neighbour2].indice_vertices[i]].indice_sommet == vertices[faces[indice_face_neighbour1].indice_vertices[j]].indice_sommet){
                indice_point_arrete[x] = vertices[faces[indice_face_neighbour2].indice_vertices[i]].indice_sommet;
                x++;
             }

         }
     }

     std::cout<< "je suis l'arrete :   " <<indice_point_arrete[0] <<  "," <<indice_point_arrete[1]<< std::endl;



    int temp;
    // l'autre point du triangle
     for(int i = 0 ; i < 3 ; i++ ){


         if(faces[indice_face_neighbour2].indice_vertices[i] == indice_point_arrete[0] && faces[indice_face_neighbour2].indice_vertices[(i+1)%3] == indice_point_arrete[1]){
            std::cout << "ce triangle coucou respecte le sens du tableau " << indice_face_neighbour2 << " : " <<indice_point_arrete[0] <<"," << indice_point_arrete[1] <<std::endl;

         }
         if(faces[indice_face_neighbour1].indice_vertices[i] == indice_point_arrete[0] && faces[indice_face_neighbour1].indice_vertices[(i+1)%3] == indice_point_arrete[1]){
             std::cout << "ce triangle respecte le sens du tableau " << indice_face_neighbour1  << " : " <<indice_point_arrete[0] <<"," << indice_point_arrete[1] <<std::endl;
             temp = indice_face_neighbour1;
             indice_face_neighbour1 = indice_face_neighbour2;
             indice_face_neighbour2 = temp;
         }

     }

     int indice_point_face_droite;
     int indice_point_face_gauche;

     for(int i = 0 ; i < 3 ; i++ ){
         if(faces[indice_face_neighbour1].indice_vertices[i] != indice_point_arrete[0] && faces[indice_face_neighbour1].indice_vertices[i] != indice_point_arrete[1]){
             indice_point_face_droite = faces[indice_face_neighbour1].indice_vertices[i];
         }
         if(faces[indice_face_neighbour2].indice_vertices[i] != indice_point_arrete[0] && faces[indice_face_neighbour2].indice_vertices[i] != indice_point_arrete[1]){
            indice_point_face_gauche = faces[indice_face_neighbour2].indice_vertices[i];
         }
     }

     face triangle_gauche = faces[indice_face_neighbour2];
     face triangle_droite = faces[indice_face_neighbour1];

     //c'est tjr indice_face_neighbour2 qui a le sens trigo par rapport a l'arrete que l'on veut flip
     /*
     std::cout<< "indice_point_face pour le triangle de droite : " << indice_point_face_droite  << std::endl;

     std::cout<< "indice_point_face pour le triangle de gauche : " << indice_point_face_gauche  << std::endl;
     */

// mise a jour des vertices correcte
     for(int i = 0 ; i < 3 ; i++ ){
         if(faces[indice_face_neighbour1].indice_vertices[i] == indice_point_arrete[0]){
             faces[indice_face_neighbour1].indice_vertices[i] = indice_point_face_gauche;
         }
         if( faces[indice_face_neighbour2].indice_vertices[i] == indice_point_arrete[1]){
             faces[indice_face_neighbour2].indice_vertices[i] = indice_point_face_droite;
         }
     }


    int triangle_haut = indice_face_neighbour1;
    int triangle_bas = indice_face_neighbour2;

     //mise a jour voisin des voisins
/*
    std::cout << "nouvel arrete :  = " << indice_point_face_droite << indice_point_face_gauche << std::endl;
    std::cout << "indice_face_neighbour1 = " << indice_face_neighbour1 << indice_face_neighbour2 << std::endl;
*/
    int indice_point_tHaut;
    int indice_point_tBas;

    for(int i = 0 ; i < 3 ; i++ ){
        if(faces[triangle_haut].indice_vertices[i] != indice_point_face_gauche && faces[triangle_haut].indice_vertices[i] != indice_point_face_droite){
            indice_point_tHaut = i;
        }
        if(faces[triangle_bas].indice_vertices[i] != indice_point_face_gauche && faces[triangle_bas].indice_vertices[i] != indice_point_face_droite){
            indice_point_tBas = i;
        }
    }
    std::cout << "triangle bas - haut= " << triangle_bas << triangle_haut << std::endl;

/*
    std::cout<< "face numero : " << faces[triangle_haut].indice_current_face << std::endl;
    std::cout<< "face voisin 0 : " << faces[triangle_haut].indice_face[0]  << " au coordonnées : " << faces[triangle_haut].indice_vertices[0] << "," << faces[triangle_haut].indice_vertices[1] << "," <<faces[triangle_haut].indice_vertices[2] << std::endl;
    std::cout<< "face voisin 1 : " << faces[triangle_haut].indice_face[1] << " au coordonnées : " << faces[triangle_haut].indice_vertices[0] << "," << faces[triangle_haut].indice_vertices[1] << "," <<faces[triangle_haut].indice_vertices[2] << std::endl;
    std::cout<< "face voisin 2 : " << faces[triangle_haut].indice_face[2] << " au coordonnées : " << faces[triangle_haut].indice_vertices[0] << "," << faces[triangle_haut].indice_vertices[1] << "," <<faces[triangle_haut].indice_vertices[2] << std::endl;

    std::cout<< "face numero : " << faces[triangle_bas].indice_current_face << std::endl;
    std::cout<< "face voisin 0 : " << faces[triangle_bas].indice_face[0]  << " au coordonnées : " << faces[triangle_bas].indice_vertices[0] << "," << faces[triangle_bas].indice_vertices[1] << "," <<faces[triangle_bas].indice_vertices[2] << std::endl;
    std::cout<< "face voisin 1 : " << faces[triangle_bas].indice_face[1] << " au coordonnées : " << faces[triangle_bas].indice_vertices[0] << "," << faces[triangle_bas].indice_vertices[1] << "," <<faces[triangle_bas].indice_vertices[2] << std::endl;
    std::cout<< "face voisin 2 : " << faces[triangle_bas].indice_face[2] << " au coordonnées : " << faces[triangle_bas].indice_vertices[0] << "," << faces[triangle_bas].indice_vertices[1] << "," <<faces[triangle_bas].indice_vertices[2] << std::endl;


    std::cout << "triangle bas - haut= " << triangle_bas << triangle_haut << std::endl;

    std::cout << "anciene arrete = " << faces[triangle_bas].indice_vertices[indice_point_tBas] << faces[triangle_haut].indice_vertices[indice_point_tHaut] << std::endl;

    std::cout << "le voisin du point en haut" << faces[triangle_haut].indice_face[indice_point_tHaut] << std::endl;
    */
    //met a jour 3 faux
    int suivant;
    for(int i = 0 ; i < 3 ; i++ ){
        if(faces[triangle_haut].indice_vertices[i] == indice_point_face_gauche){
            suivant = i == 2 ? 0 : i+1;

            faces[triangle_haut].indice_face[suivant] =triangle_gauche.indice_face[indice_point_tBas];
            suivant = suivant == 2 ? 0 : suivant+1;
            faces[triangle_haut].indice_face[suivant] = triangle_bas;


        }
        if(faces[triangle_bas].indice_vertices[i] == indice_point_face_droite){
            suivant = i == 2 ? 0 : i+1;
            faces[triangle_bas].indice_face[suivant] =triangle_droite.indice_face[indice_point_tHaut];
            suivant = suivant == 2 ? 0 : suivant+1;
            faces[triangle_bas].indice_face[suivant] = triangle_haut;


        }

}
    int face_bas_droite = triangle_droite.indice_face[indice_point_tHaut];
    int face_bas_gauche = triangle_gauche.indice_face[indice_point_tBas];

    for(int i = 0 ; i < 3 ; i++ ){
        if( face_bas_droite != -1){
            if(faces[face_bas_droite].indice_face[i] == triangle_haut ){
                faces[face_bas_droite].indice_face[i]  = triangle_bas;
            }
        }

        if(face_bas_gauche != -1){
            if(faces[face_bas_gauche].indice_face[i] == triangle_bas ){
                faces[face_bas_gauche].indice_face[i]  = triangle_haut;
            }
        }

    }



    for(int i = 0 ; i<faces.size() ; i++){
        std::cout<< "face numero : " << faces[i].indice_current_face << std::endl;
        std::cout<< "face voisin 0 : " << faces[i].indice_face[0]  << " au coordonnées : " << faces[i].indice_vertices[0] << "," << faces[i].indice_vertices[1] << "," <<faces[i].indice_vertices[2] << std::endl;
        std::cout<< "face voisin 1 : " << faces[i].indice_face[1] << " au coordonnées : " << faces[i].indice_vertices[0] << "," << faces[i].indice_vertices[1] << "," <<faces[i].indice_vertices[2] << std::endl;
        std::cout<< "face voisin 2 : " << faces[i].indice_face[2] << " au coordonnées : " << faces[i].indice_vertices[0] << "," << faces[i].indice_vertices[1] << "," <<faces[i].indice_vertices[2] << std::endl;
     }


/*
     std::cout<< "arrete : " << indice_point_arrete[0] << " , " << indice_point_arrete[1]  << std::endl;

     //std::cout<< "oppose f0 : " << indice_point_face1 << " f1 : " << indice_point_face2  << std::endl;

     std::cout<< "face numero : " << faces[indice_face_neighbour1].indice_current_face << std::endl;
     std::cout<< "face voisin 0 : " << faces[indice_face_neighbour1].indice_face[0]  << " au coordonnées : " << faces[indice_face_neighbour1].indice_vertices[0] << "," << faces[indice_face_neighbour1].indice_vertices[1] << "," <<faces[indice_face_neighbour1].indice_vertices[2] << std::endl;
     std::cout<< "face voisin 1 : " << faces[indice_face_neighbour1].indice_face[1] << " au coordonnées : " << faces[indice_face_neighbour1].indice_vertices[0] << "," << faces[indice_face_neighbour1].indice_vertices[1] << "," <<faces[indice_face_neighbour1].indice_vertices[2] << std::endl;
     std::cout<< "face voisin 2 : " << faces[indice_face_neighbour1].indice_face[2] << " au coordonnées : " << faces[indice_face_neighbour1].indice_vertices[0] << "," << faces[indice_face_neighbour1].indice_vertices[1] << "," <<faces[indice_face_neighbour1].indice_vertices[2] << std::endl;

     std::cout<< "face numero : " << faces[indice_face_neighbour2].indice_current_face << std::endl;
     std::cout<< "face voisin 0 : " << faces[indice_face_neighbour2].indice_face[0]  << " au coordonnées : " << faces[indice_face_neighbour2].indice_vertices[0] << "," << faces[indice_face_neighbour2].indice_vertices[1] << "," <<faces[indice_face_neighbour2].indice_vertices[2] << std::endl;
     std::cout<< "face voisin 1 : " << faces[indice_face_neighbour2].indice_face[1] << " au coordonnées : " << faces[indice_face_neighbour2].indice_vertices[0] << "," << faces[indice_face_neighbour2].indice_vertices[1] << "," <<faces[indice_face_neighbour2].indice_vertices[2] << std::endl;
     std::cout<< "face voisin 2 : " << faces[indice_face_neighbour2].indice_face[2] << " au coordonnées : " << faces[indice_face_neighbour2].indice_vertices[0] << "," << faces[indice_face_neighbour2].indice_vertices[1] << "," <<faces[indice_face_neighbour2].indice_vertices[2] << std::endl;
*/
    return;

}

// To find orientation of ordered triplet (p1, p2, p3).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int Mesh::orientation(Point p1, Point p2, Point p3)
{

    int val = (p2._y - p1._y) * (p3._x - p2._x) - (p2._x - p1._x) * (p3._y - p2._y);
    if(val == 0)
        return 0;
    return val > 0 ? -1 : 1; // clock or counterclock wise
}

int Mesh::in_triangle(face f, Point p)
{
    Point p1 = vertices[f.indice_vertices[0]].point;
    Point p2 = vertices[f.indice_vertices[1]].point;
    Point p3 = vertices[f.indice_vertices[2]].point;
    int val1 = orientation(p,p2,p3);
    int val2 = orientation(p1,p,p3);
    int val3 = orientation(p1,p2,p);
    //std::cout << "v1,2,3 : " << val1 << ", " << val2 << ", " << val3  << " face :" << f.indice_current_face<< std::endl;
    if(val1 > 0 && val2 >0 && val3>0 ){
        return 1;
    }
    else if(val1 >= 0 && val2 >= 0 && val3 >= 0)
        return 0;
    else
        return -1;

}
// Returns the square of distance between two input points
double sqDist_2D(Point p1, Point p2)
{
    return (p1._x-p2._x)*(p1._x-p2._x) + (p1._y-p2._y)*(p1._y-p2._y);
}
void Mesh::put_point_in_mesh(Point p){
    int indice_face_to_split = -1;
    //std::cout<< "point a inserer : " << p._x << "," << p._y << std::endl;
    for(int i = 0 ; i<faces.size() ; i++){
        //std::cout << "je suis dedans?" << this->in_triangle(faces[i], p) << std::endl;
        if(this->in_triangle(faces[i], p) > 0){
            //dans le mesh mais pas dans les boundary fait
            indice_face_to_split = i;
            this->split_triangle(indice_face_to_split, p);
            return ;
        }
        else if(this->in_triangle(faces[i], p) == 0){
            //dans le mesh dans les boundary pas fait
            return;
        }

    }
    return;

    //en dehor


    //on cherche l'indice du point le plus proche
    int indice_plus_proche = 0;
    for (int i=1; i<vertices.size(); i++)
        if (sqDist_2D(p, vertices[i].point) < sqDist_2D(p, vertices[indice_plus_proche].point))
            indice_plus_proche = i;
    int indice_triangle_proche;
    // on cherche le triangle le plus proche
    for(int i =0; i<faces.size() ; i++ ){
        for(int y =0; y<3;y++){
            if(faces[i].indice_vertices[y] == indice_plus_proche){
                indice_triangle_proche = i;
                break;
            }
        }
    }

    int indice_sommet_to_put = vertices.size();
    vertices.push_back(sommet(indice_sommet_to_put,p));
    sommet p1_limite, p2_limite;
    //on cherche les 2 point frontieres

    int last_orientation ;
    int indice_triangle_iterator;
    bool one_edge_at_frontiere = false;
    int indice_triangle_before;
    int decision;




    for(int tourne = 0; tourne < 2 ; tourne++){

        for(int y =0; y<3;y++){

            if(faces[indice_triangle_proche].indice_vertices[y] == indice_plus_proche && tourne == 0 ){
                p1_limite = vertices[indice_plus_proche];
                p2_limite = vertices[faces[indice_triangle_proche].indice_vertices[y==2 ? 0 : y+1]];
                //p1_limite = y == 0 ? vertices[faces[indice_triangle_proche].indice_vertices[1]] :  y == 1 ? vertices[faces[indice_triangle_proche].indice_vertices[2]] : vertices[faces[indice_triangle_proche].indice_vertices[0]];
                //p2_limite = y == 0 ? vertices[faces[indice_triangle_proche].indice_vertices[2]] :  y == 1 ? vertices[faces[indice_triangle_proche].indice_vertices[0]] : vertices[faces[indice_triangle_proche].indice_vertices[1]];
                break;
            }
            else if(faces[indice_triangle_proche].indice_vertices[y] == indice_plus_proche && tourne == 1 ){
                p1_limite = vertices[indice_plus_proche];
                p2_limite = vertices[faces[indice_triangle_proche].indice_vertices[y==0 ? 2 : y-1]];
                //std::cout << "je tourne !!!!!!!!!!!!!!!!!!!!!" << std::endl;

                //p1_limite = y == 0 ? vertices[faces[indice_triangle_proche].indice_vertices[1]] :  y == 1 ? vertices[faces[indice_triangle_proche].indice_vertices[2]] : vertices[faces[indice_triangle_proche].indice_vertices[0]];
                //p2_limite = y == 0 ? vertices[faces[indice_triangle_proche].indice_vertices[2]] :  y == 1 ? vertices[faces[indice_triangle_proche].indice_vertices[0]] : vertices[faces[indice_triangle_proche].indice_vertices[1]];
                break;
            }
        }

        last_orientation = this->orientation(p,p1_limite.point,p2_limite.point);
        indice_triangle_iterator = indice_triangle_proche;
        std::cout << "last_orientation : " << last_orientation << std::endl;

        while(last_orientation == this->orientation(p,p1_limite.point,p2_limite.point)){
            //parcourir le long de l'enveloppe convex
            if(last_orientation == -1){
                faces.push_back(face(indice_sommet_to_put,p2_limite.indice_sommet,p1_limite.indice_sommet,indice_triangle_iterator,-1,-1));
            }
            else if(last_orientation == 1){
                faces.push_back(face(indice_sommet_to_put,p1_limite.indice_sommet,p2_limite.indice_sommet,indice_triangle_iterator,-1,-1));
            }

            std::cout << "triangle de depart :  "<<indice_triangle_iterator << std::endl;
            one_edge_at_frontiere = false;

            //on se deplace a la prochaine face
            for(int i =0;i<3;i++){
                if(faces[indice_triangle_iterator].indice_vertices[i] != p1_limite.indice_sommet && faces[indice_triangle_iterator].indice_vertices[i] != p2_limite.indice_sommet){
                    decision = last_orientation == -1 ?  i==2 ? i%2 : i+1   :  i==0 ? 2 : i-1 ;
                    if(faces[indice_triangle_iterator].indice_face[decision] != -1){
                        std::cout << "faces[indice_triangle_iterator].indice_vertices[i]  :  "<<faces[indice_triangle_iterator].indice_vertices[i]  << std::endl;
                        indice_triangle_before = indice_triangle_iterator;
                        indice_triangle_iterator = faces[indice_triangle_iterator].indice_face[decision];
                        break;
                    }

                }
            }
            std::cout << "triangle sur lequel on a itéré :  "<<indice_triangle_iterator << std::endl;


            while(one_edge_at_frontiere == false){

                //on recupere la frontiere actuel
                for(int y =0; y<3;y++){//faire qqchose ici car tjr meme arrete quand on va le prendre sur l'autre face
                    if(faces[indice_triangle_iterator].indice_face[y] == -1 && p2_limite.indice_sommet != faces[indice_triangle_iterator].indice_vertices[y] ){
                        if(last_orientation == -1){
                            p1_limite = y == 0 ? vertices[faces[indice_triangle_iterator].indice_vertices[1]] :  y == 1 ? vertices[faces[indice_triangle_iterator].indice_vertices[2]] : vertices[faces[indice_triangle_iterator].indice_vertices[0]];
                            p2_limite = y == 0 ? vertices[faces[indice_triangle_iterator].indice_vertices[2]] :  y == 1 ? vertices[faces[indice_triangle_iterator].indice_vertices[0]] : vertices[faces[indice_triangle_iterator].indice_vertices[1]];

                        }
                        else{
                            p2_limite = y == 0 ? vertices[faces[indice_triangle_iterator].indice_vertices[1]] :  y == 1 ? vertices[faces[indice_triangle_iterator].indice_vertices[2]] : vertices[faces[indice_triangle_iterator].indice_vertices[0]];
                            p1_limite = y == 0 ? vertices[faces[indice_triangle_iterator].indice_vertices[2]] :  y == 1 ? vertices[faces[indice_triangle_iterator].indice_vertices[0]] : vertices[faces[indice_triangle_iterator].indice_vertices[1]];
                        }
                        one_edge_at_frontiere = true;
                        break;
                    }
                }


                //on se met au prochain triangle
                if(one_edge_at_frontiere == false){
                    std::cout << "triangle sans frontiere"  << std::endl;

                    for(int i = 0 ; i<3;i++){
                        if(faces[indice_triangle_iterator].indice_face[i] == indice_triangle_before){
                            //std::cout << "faces[indice_triangle_iterator].indice_vertices[i]  :  "<<faces[indice_triangle_iterator].indice_vertices[i]  << std::endl;
                            indice_triangle_before = indice_triangle_iterator;
                            decision = last_orientation == -1 ?  i==2 ? i%2 : i+1   :  i==0 ? 2 : i-1 ;

                            indice_triangle_iterator = faces[indice_triangle_iterator].indice_face[decision];
                            break;

                        }
                    }
                    std::cout << "triangle sur lequel on a itéré :  "<<indice_triangle_iterator << std::endl;
                }
            }

            std::cout << "p1 :  " << p1_limite.indice_sommet << " : "<<p1_limite.point._x << "," << p1_limite.point._y << "," << p1_limite.point._z << std::endl;
            std::cout << "p2 :  " << p2_limite.indice_sommet << " : " <<p2_limite.point._x << "," << p2_limite.point._y << "," << p2_limite.point._z << std::endl;

            std::cout<<std::endl;
            if(this->orientation(p,p1_limite.point,p2_limite.point) == -1){
                std::cout << "horaire" << std::endl;
            }
            else{
                std::cout << "anti horaire" << std::endl;
            }
            std::cout<<std::endl;

        }


    }

    std::cout << "orientation :  "<< last_orientation << std::endl;

    // on navigue d'abord par la gauche par rapport a l'impact p -> point plus proche
    std::cout << "indice_plus_proche :  "<<indice_plus_proche << std::endl;
    std::cout << "indice_triangle_proche :  "<<indice_triangle_proche << std::endl;

    //forcement en dehors

    // il faut prendre le point le plus proche du convex de mon mesh
    // parcourir en bas en longeant mes triangles sur le convex pour trouver la teangeante du bas
    // revenir au point le plus proche pour aller vers le haut et refaire les tests dd'orientation
    // a chaque etape du parcour du convex relier le point aux triangle du convex et les creer avcec leur voisin
//https://www.geeksforgeeks.org/dynamic-convex-hull-adding-points-existing-convex-hull/


}

void Mesh::split_triangle(int indice_f ,Point p){
    int indice_sommet_to_put = vertices.size();
//fani dupont

    std::cout<<"\n"<<"\n"<<"\n"<<std::endl;
    sommet sommet_to_put(indice_sommet_to_put,p);
    this->vertices.push_back(sommet_to_put);
    this->faces[indice_f];
    int f2 = faces.size();
    int f3 = f2+1;


    //mise a jour des triangles voisins
    for(int i =0;i<3;i++){
        if(this->faces[indice_f].indice_face[0] != -1){
            if(faces[this->faces[indice_f].indice_face[0]].indice_face[i] == indice_f){
                faces[this->faces[indice_f].indice_face[0]].indice_face[i] = f2;
            }
        }
        if(this->faces[indice_f].indice_face[1] != -1){
            if(faces[this->faces[indice_f].indice_face[1]].indice_face[i] == indice_f){
                faces[this->faces[indice_f].indice_face[1]].indice_face[i] = f3;
            }
        }

    }

    //insertion des faces

    //std::cout<< "oppose du triangle de nouveau : " << this->faces[indice_f].indice_face[0]  << std::endl;

    //std::cout<< "face numero : " << faces[indice_f].indice_current_face  << " indice_f : " << indice_f << std::endl;

    faces.push_back(face(this->faces[indice_f].indice_vertices[1],this->faces[indice_f].indice_vertices[2],indice_sommet_to_put,f3,indice_f,this->faces[indice_f].indice_face[0]));

    faces[f2].indice_current_face = f2;

    faces.push_back(face(this->faces[indice_f].indice_vertices[2],this->faces[indice_f].indice_vertices[0],indice_sommet_to_put,indice_f,f2, this->faces[indice_f].indice_face[1]));
    faces[f3].indice_current_face = f3;

    faces[indice_f].indice_face[0] = f2;
    faces[indice_f].indice_face[1] = f3;
    faces[indice_f].indice_vertices[2] = indice_sommet_to_put;



    //Point milieurA = Point((vertices[faces[0].indice_vertices[0]].point._x + vertices[faces[0].indice_vertices[1]].point._x)/2
    //prendre un sommet et le relier a la cible
    //prendre un segment du triangle et le produit scalaire pour savoir dans quel direction je dois me diriger pour m'approcher de la cible
    //dans chaque triangle faire un test sur chaque segment pour savoir si la cible est a l'interieur de mon triangle
    //spliter mon triangle


    return ;
}
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real_distribution.hpp>
void Mesh::create_mesh_bounding_box(float taille, int nb_subdivision){
    float x,y ;
    boost::random::mt19937 gen;
    boost::random::uniform_real_distribution<> dist(0, 10);
    for(int i =0; i< nb_subdivision ; i++){
        x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/taille));
        y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/taille));
        put_point_in_mesh(Point(dist(gen),dist(gen),0));
        std::cout << dist(gen) << std::endl;

    }
}

int Mesh::in_circle_circonscrit(int indice_face,Point inconnu){
    Point a = vertices[faces[indice_face].indice_vertices[0]].point;
    Point b = vertices[faces[indice_face].indice_vertices[1]].point;
    Point c = vertices[faces[indice_face].indice_vertices[2]].point;

    Point x = Point(a._x,a._y,a._x*a._x+a._y*a._y);
    Point y = Point(b._x,b._y,b._x*b._x+b._y*b._y);
    Point z = Point(c._x,c._y,c._x*c._x+c._y*c._y);
    Point inco = Point(inconnu._x,inconnu._y,inconnu._x*inconnu._x+inconnu._y*inconnu._y);

    Point A = y - x;
    Point B = z - x;
    int temp = A / B * (inco - x);

    return temp<0;
}

double Mesh::tangeante(Point BA, Point BC){
    return  BA.crossProduct(BC).length() / BA.dotProduct(BC);
}

double Mesh::sinus(Point BA, Point BC){

    double sin_b  = BA.crossProduct(BC).length() ;
    double dist = (BA.length() * BC.length());

    return sin_b / dist;

}

double Mesh::cosinus(Point BA, Point BC){

    double cos_b  = BA.dotProduct(BC) / (BA.length() * BC.length());

    return cos_b;
}

void Mesh::Voronoi(){
    double cos_a, cos_b, cos_c;
    double sin_a, sin_b, sin_c;
    Point temp_a, temp_b, temp_c;
    Point a,b,c;
    Point ac, ab;
    double tan_a, tan_b, tan_c;
    double alpha, beta, gamma;
    double  denominateur;

    for (int i = 0; i < faces.size(); ++i) {
        a = vertices[faces[i].indice_vertices[0]].point;
        b = vertices[faces[i].indice_vertices[1]].point;
        c = vertices[faces[i].indice_vertices[2]].point;

        tan_a = tangeante(a-b,a-c);
        tan_b = tangeante(b-a,b-c);
        tan_c = tangeante(c-b,c-a);
        ac = c-a;
        ab = b-a;

        alpha = tan_b + tan_c;
        beta = tan_a + tan_c;
        gamma = tan_a + tan_b;

        cos_a = cosinus(b-a,c-a);
        sin_a = sinus(b-a,c-a);

        cos_b = cosinus(a-b,c-b);
        sin_b = sinus(a-b,c-b);

        cos_c = cosinus(b-c,a-c);
        sin_c = sinus(b-c,c-a);

        temp_a =  a * (cos_c*cos_a*sin_b + sin_c * cos_a * cos_b) ;
        temp_b =  b * (cos_b*cos_a*sin_c + sin_a * cos_c * cos_b) ;
        temp_c =  c * (cos_c*cos_b*sin_a + sin_b * cos_a * cos_c) ;
        denominateur =(2*(cos_b * cos_c * sin_a + cos_a*cos_c*sin_b + cos_a * cos_b * sin_c));
        faces[i].center_circ_circle = (temp_a + temp_b + temp_c) / denominateur;

        std::cout << "faces[i].center_circ_circle : " << faces[i].center_circ_circle._x << "," << faces[i].center_circ_circle._y << "," << faces[i].center_circ_circle._z << std::endl;

    }
}

void Mesh::Delaunay_lawson(){
    for (int i = 0; i < faces.size(); ++i) {
        for (int j = 0; j < 3; ++j) {
            //cas non delaunay je suis dans le cercle circonscrit alor que je n'appartiens pas au 3 points
            if(faces[i].indice_face[j] != -1){
                if(in_circle_circonscrit(this->faces[i].indice_face[j],this->vertices[this->faces[i].indice_vertices[j]].point ) == 1){
                    this->edge_flip(i,faces[i].indice_face[j]);
                    return;
                    //i=0;
                }
            }


        }
    }
}


void Mesh::drawMesh(std::string file){
    //double width=0.5, depth=0.5, height=0.5;
    //QLabel *testLabel= new QLabel;
    vertices.clear();
    faces.clear();

    float x,y,z;
    std::fstream myfile ;
    int vertex_count;
    int face_count = 0;
    int null_count = 0;
    myfile.open(file);

        myfile >> vertex_count;
        std::cout << vertex_count << '\n';

        myfile >> face_count;
        myfile >> null_count;

    for(int i = 0 ; i<vertex_count ; i++){
          myfile >> x;
          myfile >> y;
          myfile >> z;
          vertices.push_back(sommet(i,Point(x,y,z)));

          //vertices.push_back(sommet(i,Point(x*width,y*depth,z*height)));
         // std::cout << "i : " << i << '\n';
        //std::cout << "x : " << x << "y : " << y << "z : " << z << '\n';
        //std::cout << "x : " <<vertices[i].point._x  << ","<< vertices[i].point._y << "," << vertices[i].point._z << '\n';

        //std::cout << temp << '\n';
     }

for(int i = 0 ; i<face_count ; i++){
          myfile >> null_count;
          myfile >> x;
          myfile >> y;
          myfile >> z;
          faces.push_back(face(x,y,z));
        //std::cout << "x : " << x << "y : " << y << "z : " << z << '\n';
        //std::cout << temp << '\n';
      }
      myfile.close();
      std::map<std::pair<int,int>, std::pair<int,int>> mapo;
       std::pair<int,int> arrete;

      for(int i = 0 ; i<face_count ; i++){
          mapo.insert({{faces[i].indice_vertices[0],faces[i].indice_vertices[1]},{i,2}});
          mapo.insert({{faces[i].indice_vertices[1],faces[i].indice_vertices[2]},{i,0}});
          mapo.insert({{faces[i].indice_vertices[2],faces[i].indice_vertices[0]},{i,1}});
       }

      std:: cout << "face_count : " << face_count <<std::endl;
//ajout des voisin
      for(int i = 0 ; i<face_count ; i++){
          faces[i].indice_current_face = i;

          mapo.find({faces[i].indice_vertices[2],faces[i].indice_vertices[1]}) == mapo.end() ? faces[i].indice_face.push_back(-1) : faces[i].indice_face.push_back(mapo.find({faces[i].indice_vertices[2],faces[i].indice_vertices[1]})->second.first);
          mapo.find({faces[i].indice_vertices[0],faces[i].indice_vertices[2]}) == mapo.end() ? faces[i].indice_face.push_back(-1) : faces[i].indice_face.push_back(mapo.find({faces[i].indice_vertices[0],faces[i].indice_vertices[2]})->second.first);
          mapo.find({faces[i].indice_vertices[1],faces[i].indice_vertices[0]}) == mapo.end() ? faces[i].indice_face.push_back(-1) : faces[i].indice_face.push_back(mapo.find({faces[i].indice_vertices[1],faces[i].indice_vertices[0]})->second.first);

       }
/*
      for(int i = 0 ; i<faces.size() ; i++){
          std::cout<< "face numero : " << faces[i].indice_current_face << std::endl;
          std::cout<< "face voisin 0 : " << faces[i].indice_face[0]  << " au coordonnées : " << faces[i].indice_vertices[0] << "," << faces[i].indice_vertices[1] << "," <<faces[i].indice_vertices[2] << std::endl;
          std::cout<< "face voisin 1 : " << faces[i].indice_face[1] << " au coordonnées : " << faces[i].indice_vertices[0] << "," << faces[i].indice_vertices[1] << "," <<faces[i].indice_vertices[2] << std::endl;
          std::cout<< "face voisin 2 : " << faces[i].indice_face[2] << " au coordonnées : " << faces[i].indice_vertices[0] << "," << faces[i].indice_vertices[1] << "," <<faces[i].indice_vertices[2] << std::endl;
       }
      */


      //this->edge_flip(0,1); //va avec knight
      //1 = dedans
      //std::cout<< "je suis dans le cercle circonscrit du triangle "<<in_circle_circonscrit(0,Point(0.1,0,0)) << std::endl;
      //split_triangle(0,Point(1,1,0));
      //Circulator_on_vertices *circ = new Circulator_on_vertices(0,this);
      //Circulator_on_faces *circ_face = new Circulator_on_faces(0,this);
    create_mesh_bounding_box(10.0,10);
    //Delaunay_lawson();
      Voronoi();
       // put_point_in_mesh(Point(-4,0,0));
      for(int i = 0 ; i<faces.size() ; i++){
          std::cout<< "face numero : " << faces[i].indice_current_face << std::endl;
          std::cout<< "face voisin 0 : " << faces[i].indice_face[0]  << " au coordonnées : " << faces[i].indice_vertices[0] << "," << faces[i].indice_vertices[1] << "," <<faces[i].indice_vertices[2] << std::endl;
          std::cout<< "face voisin 1 : " << faces[i].indice_face[1] << " au coordonnées : " << faces[i].indice_vertices[0] << "," << faces[i].indice_vertices[1] << "," <<faces[i].indice_vertices[2] << std::endl;
          std::cout<< "face voisin 2 : " << faces[i].indice_face[2] << " au coordonnées : " << faces[i].indice_vertices[0] << "," << faces[i].indice_vertices[1] << "," <<faces[i].indice_vertices[2] << std::endl;
          std::cout<< "les points sont : " << vertices[faces[i].indice_vertices[0]].point._x << ", " << vertices[faces[i].indice_vertices[0]].point._y << "," << vertices[faces[i].indice_vertices[0]].point._z << std::endl;
          std::cout<< "les points sont : " << vertices[faces[i].indice_vertices[1]].point._x << ", " << vertices[faces[i].indice_vertices[1]].point._y << "," << vertices[faces[i].indice_vertices[1]].point._z << std::endl;
          std::cout<< "les points sont : " << vertices[faces[i].indice_vertices[2]].point._x << ", " << vertices[faces[i].indice_vertices[2]].point._y << "," << vertices[faces[i].indice_vertices[2]].point._z << std::endl;

      }


//put_point_in_mesh(Point(1,5,0));

}

face& Mesh::find_face(int indice_face){
    return this->faces[indice_face];
}
