#ifndef GLDISPLAYWIDGET_H
#define GLDISPLAYWIDGET_H

#include <QOpenGLWidget>
//#include <QGLWidget> // Module QtOpengL (classes QGLxxx in Qt4),
                     // with widget and graphics rendering classes descending from QGLWidget,
                     // deprecated and replaced by module QtGui (classes QOpenGLxxx )
                     // and module widgets (QWidget, QGraphicsView).
                     // UpgradeQt6: #include <QOpenGLWidget>
#include <QtWidgets>
#include <QTimer>
#include "geometricworld.h"   // Model

class GLDisplayWidget : public QOpenGLWidget //UpgradeQt6: public QOpenGLWidget
{
public:
    bool wire;
    bool delaunay;
    GeometricWorld _geomWorld; // The scene to be displayed

    explicit GLDisplayWidget(QWidget *parent = 0);

    void initializeGL(); // The scene may be initialized in this function since the GeometricWorld is a data member...
    void paintGL(); // Display the scene Gl
    void paintGLWire(); // Display the scene Gl

    void resizeGL(int width, int height);

protected:
    // Mouse Management
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:

    QTimer _timer; // To update the scene
    float _X, _Y ,_Z; // Translation
    float _angle; // Rotation

    QPoint _lastPosMouse; // To keep the last position of the mouse

};

#endif // GLDISPLAYWIDGET_H
