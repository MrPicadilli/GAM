#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QGLWidget> //UpgradeQt6: #include <QOpenGLWidget>


class triangle
{
private:
    QVector<int> vertices;
    QVector<int> faces;
public:
    triangle();
    triangle(QVector<int> vertices, QVector<int> faces);

};

#endif // TRIANGLE_H
