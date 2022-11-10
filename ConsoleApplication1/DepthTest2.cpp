#include<GL/glut.h>
#include<stdio.h>

void MyDisplay();
void MyReshape(int w, int h);
void DrawScene();
int Width, Height;
GLfloat WidthFactor, HeightFactor;


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	Width = 400;Height = 400;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(500, 400);
	glutCreateWindow("박재민");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); //near 1, far -1 로 수정하던지
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	return 0;
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0); //시점을  -1 -> 1로 수정하던지

	glColor3f(1.0, 0.0, 0.0);
	glutSolidTeapot(0.3);

	glTranslatef(-0.6, 0.0, -0.5);
	glColor3f(0.0, 1.0, 0.0);
	glutSolidCube(0.5);

	glTranslatef(0.3, 0.2, 0.8);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidCube(0.5);


	glFlush();
}

void MyReshape(int w, int h) {
	Width = w; Height = h;
	WidthFactor = (GLfloat)Width / (GLfloat)400;
	HeightFactor = (GLfloat)Height / (GLfloat)400;

	glutPostRedisplay();
}