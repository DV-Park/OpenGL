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
	glutCreateWindow("¹ÚÀç¹Î");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	return 0;
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glColor3f(0.1, 0.1, 0.1);
	glBegin(GL_POLYGON);
		glVertex3f(-0.9, -0.9, 0.1);
		glVertex3f(0.9, -0.9, 0.1);
		glVertex3f(0.9, 0.9, 0.1);
		glVertex3f(-0.9, 0.9, 0.1);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
		glVertex3f(-0.5, -0.5, 0.5);
		glVertex3f(0.5, -0.5, 0.5);
		glVertex3f(0.0, 0.5, 0.5);
	glEnd();
	glDepthMask(GL_TRUE);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		glVertex3f(-0.9, -0.9, 0.1);
		glVertex3f(0.9, -0.9, 0.1);
		glVertex3f(0.9, 0.9, 0.1);
		glVertex3f(-0.9, 0.9, 0.1);
	glEnd();
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glBegin(GL_TRIANGLES);
		glVertex3f(0.5, 0.5, 0.05);
		glVertex3f(-0.5, 0.5, 0.05);
		glVertex3f(0.5, -0.5, 0.05);
	glEnd();


	glFlush();
}

void MyReshape(int w, int h) {
	Width = w; Height = h;
	WidthFactor = (GLfloat)Width / (GLfloat)400;
	HeightFactor = (GLfloat)Height / (GLfloat)400;

	glutPostRedisplay();
}