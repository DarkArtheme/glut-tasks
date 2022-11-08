#include <stdio.h>
#include <windows.h>
#include <gl/glut.h>
GLUnurbsObj* theNurb;
GLfloat ctlarray1[2][6][4] = {
        0.0, 0.0, 0.8, 1.0,
        0.5, 0.0, 0.8, 1.0,

        0.0, 0.5, 0.6, 1.0,
        0.5, 0.5, 0.6, 1.0,

        0.0, 0.0, 0.4, 1.0,
        0.5, 0.0, 0.4, 1.0,

        0.0, 0.5, 0.2, 1.0,
        0.5, 0.5, 0.2, 1.0,

        0.0, 0.0, -0.2, 1.0,
        0.5, 0.0, -0.2, 1.0,

        0.0, 0.5, -0.4, 1.0,
        0.5, 0.5, -0.4, 1.0
};

GLfloat ctlarray[2][6][4] = {
        0.0, -0.8, 0.0,1.0,
        0.0, -0.8, 0.5,1.0,
        0.5, -0.4, 0.0,1.0,
        0.5, -0.4, 0.5,1.0,
        0.0, 0.0, 0.0,1.0,
        0.0, 0.0, 0.5,1.0,
        0.5, 0.4, 0.0,1.0,
        0.5, 0.4, 0.5,1.0,
        0.0, 0.8, 0.0,1.0,
        0.0, 0.8, 0.5,1.0,
        0.5, 1.2, 0.0,1.0,
        0.5, 1.2, 0.5,1.0
};

void init()
{
    glClearColor(0.5, 0.75, 0.75, 1);
    theNurb = gluNewNurbsRenderer();
    gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
}
void Display()
{
    //массивы содержащие значения открытого равномерного узлового вектора в
    // направлениях u и w
    GLfloat knot[] = { 0.0,0.0,0.0,0.0,1.0,2.0,3.0,3.0,3.0,3.0 };
    GLfloat knot1[] = { 0.0,0.0,1.0,1.0 };
    glClear(GL_COLOR_BUFFER_BIT);
    glRotatef(0.1, 0.5, 0.5, 0.5);
    glColor3f(0, 0, 1);
    //  theNurb – NURBS объект,  6, 4 – количество элементов в массивах knot, knot1
    //  knot, knot1 – массивы содержащий значения узловых векторов,
    //  параметр ctlarray – указывает  на массив контрольных точек
    //  k = 3, k = 2 – степень плюс единица NURBS поверхности в направлениях u и w
    //  GL_MAP1_VERTEX_4 – тип Безье вычислителя для рациональных контрольных точек
    gluBeginSurface(theNurb);
    gluNurbsSurface(theNurb, 4, knot1, 10, knot, 4, 2*4, &ctlarray1[0][0][0], 2, 4, GL_MAP2_VERTEX_4);
    gluEndSurface(theNurb);
    glutPostRedisplay();
    glutSwapBuffers();
}
int main()
{
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(480, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("  ");
    init();
    glutDisplayFunc(Display);
    glutMainLoop();
}