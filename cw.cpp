#include <vector>
#include <GL/glut.h>

GLUnurbsObj* nobj;
const int N = 6, K = 6;
float scale = 0.01f;
GLfloat ctlarray[][2] = {
        {-80*scale, 50*scale},
        {-60*scale, 90*scale},
        {-40*scale, 50*scale},
        {-20*scale, 90*scale},
        {0*scale, 50*scale},
        {20*scale, 90*scale},
};

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    nobj = gluNewNurbsRenderer();
    gluNurbsProperty(nobj, GLU_SAMPLING_TOLERANCE, 25.0);
}

float alpha(int i, int k, float t, const std::vector<float>& knot) {
    if(knot.at(i + k) - knot.at(i) < 0.01f) {
        return 0.0f;
    }
    return (t - knot.at(i)) / (knot.at(i + k) - knot.at(i));
}

float beta(int i, int k, float t, const std::vector<float>& knot) {
    if(knot.at(i + k + 1) - knot.at(i + 1) < 0.01f) {
        return 0.0f;
    }
    return (-t + knot.at(i + k + 1)) / (knot.at(i + k + 1) - knot.at(i + 1));
}

float basis(int i, int k, float t, const std::vector<float>& knot) {
    if (k == 0) {
        if (t >= knot.at(i) && t < knot.at(i + 1)) {
            return 1.0f;
        }
        return 0.0f;
    }
    float a = alpha(i, k, t, knot);
    float b = beta(i, k, t, knot);
    return a * basis(i, k - 1, t, knot) + b * basis(i + 1, k - 1, t, knot);
}

void DisplayCurve() {
    std::vector<float> knot(N + K, 0.0f);
    for(int i = K; i < N + K; ++i) {
        if (i < N + 1) {
            knot[i] = i + 1.0f - K;
        } else {
            knot[i] = N - 1.0f - K + 2.0f;
        }
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(4.0);
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    float dx = 0.5f;
    for (int i = 0; i < N; i++) {
        glVertex2f(ctlarray[i][0] + dx, ctlarray[i][1]);
    }
    for (float t = 0.0f; t < 2.0f; t += 0.005f) {
        std::pair<float, float> ptr = { 0.0f, 0.0f };
        for (int i = 0; i < N; i++) {
            float Nik = basis(i, K - 1, t, knot);
            ptr.first += ctlarray[i][0] * Nik;
            ptr.second += ctlarray[i][1] * Nik;
        }
        glVertex2f(ptr.first + dx, ptr.second);
    }

    for (float t = 0.0f; t < 2.0f; t += 0.005f) {
        for (int i = 0; i < N; i++) {
            glVertex2f(t - dx, basis(i, K - 1, t, knot) - 0.8);
        }
    }
    glEnd();
    glFlush();
}

int main() {
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(480, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("  ");
    init();
    glutDisplayFunc(DisplayCurve);
    glutMainLoop();
}
