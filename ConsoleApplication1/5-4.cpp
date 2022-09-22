#include<GL/glut.h>
#include<stdio.h>

void MyDisplay();

int main() {
	//glutInitWindowPosition(200, 100);
	//glutInitWindowSize(500, 500);
	glutCreateWindow("¹ÚÀç¹Î");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}

void MyDisplay() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(100, 100, 300, 300);
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_POLYGON);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, -0.5, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);
	glEnd();

	glFlush();
}