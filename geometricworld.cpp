#include "geometricworld.h"



GeometricWorld::GeometricWorld()
{
    //double width=0.5, depth=0.6, height=0.8;
    _mesh.drawMesh("C:/Users/dietf/OneDrive/Documents/geo_algo_maillage/GAM2022_Seance1/gam/data/castle.off");


}


void GeometricWorld::change_file(std::string file){

    _mesh.drawMesh(file);
}


// The following functions could be displaced into a module OpenGLDisplayGeometricWorld that would include mesh.h

// Draw a Point
void glPointDraw(const Point & p) {
    glVertex3f(p._x, p._y, p._z);
}

//Example with a bBox
void GeometricWorld::draw() {


    Point infinity =Point(0,0,-5);

    for(int i = 0; i<_mesh.faces.size();i++){
        if(i%3 == 0){
            //blue
            glColor3d(0,0,1);

        }
        else if(i%3==1){
            //green
            glColor3d(0,1,0);

        }
        else{
            //red
            glColor3d(1,0,0);
        }

        if(i==0){
            glColor3d(1,1,1);
        }
        if(i == 5){
            glColor3d(0,1,1);

        }
        glBegin(GL_TRIANGLES);
        glPointDraw(_mesh.vertices[ _mesh.faces[i].indice_vertices[0]].point);
        glPointDraw(_mesh.vertices[ _mesh.faces[i].indice_vertices[1]].point);
        glPointDraw(_mesh.vertices[ _mesh.faces[i].indice_vertices[2]].point);
        glEnd();

        if(_mesh.faces[i].indice_face[0] == -1){
            glBegin(GL_LINE_STRIP);

            glColor3d(1,1,1);

            glPointDraw(_mesh.vertices[ _mesh.faces[i].indice_vertices[1]].point);
            glPointDraw(infinity );
            glBegin(GL_LINE_STRIP);
            glColor3d(1,1,1);
            glPointDraw(infinity );
            glPointDraw(_mesh.vertices[ _mesh.faces[i].indice_vertices[2]].point);
            glEnd();

        }


    }

}

//Example with a wireframe bBox
void GeometricWorld::drawWireFrame() {

    for(int i =0;i<_mesh.faces.size();i++){
        for(int y=0;y<=2;y++){
            glBegin(GL_LINE_STRIP);
            glColor3d(1,1,1);


            if(y%3 == 0){
                glPointDraw(_mesh.vertices[ _mesh.faces[i].indice_vertices[0]].point);
                glPointDraw(_mesh.vertices[ _mesh.faces[i].indice_vertices[1]].point);
            }
            else if(y%3==1){
                glPointDraw(_mesh.vertices[ _mesh.faces[i].indice_vertices[1]].point);
                glPointDraw(_mesh.vertices[ _mesh.faces[i].indice_vertices[2]].point);
            }
            else{
                glPointDraw(_mesh.vertices[ _mesh.faces[i].indice_vertices[0]].point);
                glPointDraw(_mesh.vertices[ _mesh.faces[i].indice_vertices[2]].point);
            }

            glEnd();
        }

    }


    for(int i =0;i<_mesh.faces.size();i++){
        for(int y=0;y<=2;y++){
            glBegin(GL_LINE_STRIP);
            glColor3d(0.5,0.1,0.8);

                if(y%3 == 0){
                    if(_mesh.faces[i].indice_face[0] != -1){
                        glPointDraw(_mesh.faces[i].center_circ_circle);

                        glPointDraw(_mesh.faces[_mesh.faces[i].indice_face[0]].center_circ_circle);
                    }

                }
                else if(y%3==1){
                    if(_mesh.faces[i].indice_face[1] != -1){
                        glPointDraw(_mesh.faces[i].center_circ_circle);
                        glPointDraw(_mesh.faces[_mesh.faces[i].indice_face[1]].center_circ_circle);
                    }

                }
                else{
                    if(_mesh.faces[i].indice_face[2] != -1){
                        glPointDraw(_mesh.faces[i].center_circ_circle);
                        glPointDraw(_mesh.faces[_mesh.faces[i].indice_face[2]].center_circ_circle);
                    }


                }


            }

            glEnd();
        }




}

