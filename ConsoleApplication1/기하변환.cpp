#include<GL/glut.h>
#include<stdio.h>

void MyDisplay();
void MyReShape(int newWidth, int newHeight);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutCreateWindow("¹ÚÀç¹Î");

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReShape);

	glutMainLoop();

	return 0;
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 500, 500);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(0.5, 1.0, 1.0);
	glTranslatef(0.5, 0.0, 0.0);
	
	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(0.0, 0.5);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(-0.5, -0.5);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2f(0.5, -0.5);
	glEnd();

	glLoadIdentity();
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(0.75, 0.75, 0.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glScalef(0.25, 0.25, 0.25);
	glutWireSphere(0.5, 10, 20);
	glFlush();

}

void MyReShape(int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	GLfloat widthFactor = (GLfloat)newWidth / (GLfloat)300;
	GLfloat heightFactor = (GLfloat)newHeight / (GLfloat)300;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}