#ifndef FACE_H
#define FACE_H

#include <QGLWidget> //UpgradeQt6: #include <QOpenGLWidget>


class face
{

public:
    QVector<int> indice_face;
    QVector<int> indice_vertices;

    face();
    face(int verti1,int verti2,int verti3,int face1,int face2,int face3);

};

#endif // FACE_H
