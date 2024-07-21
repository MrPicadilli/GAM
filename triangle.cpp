#include "triangle.h"

triangle::triangle()
{
    void glPointDraw(const Point & p) {
        glVertex3f(p._x, p._y, p._z);
    }
}
