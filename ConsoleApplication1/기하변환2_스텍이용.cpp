#include<GL/glut.h>
#include<stdio.h>

void MyDisplay();
void MyReShape(int newWidth, int newHeight);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(700, 700);
	glutCreateWindow("¹ÚÀç¹Î");

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReShape);

	glutMainLoop();

	return 0;
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 700, 700);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glutSolidTeapot(0.05);

		glPushMatrix();
		glTranslatef(0.1, 0.1, 0.0);
		glutSolidTeapot(0.05);

			glPushMatrix();
			glScalef(0.5, 0.5, 0.5);
			glTranslatef(0.5, -0.1, 0.0);
			glRotatef(45.0, 0.0, 0.0, 1.0);
			glutSolidTeapot(0.05);
			glPopMatrix();

			glColor3f(1.0, 0.0, 0.0);
			glTranslatef(-0.4, 0.15, 0.0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			glScalef(2.0, 2.0, 2.0);
			glutSolidTeapot(0.05);
			glPopMatrix();

		glColor3f(0.0, 0.0, 1.0);
		glTranslatef(0.0, -0.5, 0.0);
		glutSolidTeapot(0.05);

	glFlush();

}

void MyReShape(int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	GLfloat widthFactor = (GLfloat)newWidth / (GLfloat)300;
	GLfloat heightFactor = (GLfloat)newHeight / (GLfloat)300;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}