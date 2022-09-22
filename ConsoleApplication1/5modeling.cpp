#include<GL/glut.h>
#include<stdio.h>

void MyDisplay();

int main() {
	//glutInitWindowPosition(200, 100);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(600, 600);
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
	glViewport(0, 0, 300, 300);
	glColor3f(1.0, 1.0, 1.0);

	glRotatef(45, 1.0, 1.0, 1.0);
	glutWireCube(0.5);

	glColor3f(1.0, 0.0, 0.0);
	glViewport(0, 300, 300, 300);
	glRotatef(90, 1.0, 1.0, 1.0);
	glutWireSphere(0.5, 20, 20);

	glColor3f(0.0, 0.0, 1.0);
	glRotatef(90, 1.0, 1.0, 1.0);
	glViewport(300, 300, 300, 300);
	glutWireCone(0.5, 0.5, 20, 20);

	glColor3f(0.0, 1.0, 0.0);
	glRotatef(90, 1.0, 1.0, 1.0);
	glViewport(300, 0, 300, 300);
	glutWireTorus(0.1, 0.5, 20, 20);

	glFlush();
}