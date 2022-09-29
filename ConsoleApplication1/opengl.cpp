#include<GL/glut.h>
#include<stdio.h>

void MyDisplay();

int main() {
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("¹ÚÀç¹Î");
	glutDisplayFunc(MyDisplay);
	glutMainLoop();
	return 0;
}

void MyDisplay() {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPointSize(20.0);
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_POINTS);
		glVertex3f(0.0, 0.0, 0.0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.5, 0.5, 0.0);
	glEnd();

	glLineWidth(5);
	glBegin(GL_LINES);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(-1.0, 1.0, 0.0);
		glVertex3f(1.0, -1.0, 0.0);
		glVertex3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(-0.5, 0.0, 0.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glVertex3f(0.0, -1.0, 0.0);
	glEnd();

	glFlush();
}