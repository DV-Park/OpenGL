#include<GL/glut.h>
#include<stdio.h>

void MyDisplay();
void MyReShape(int newWidth, int newHeight);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(300, 300);
	glutCreateWindow("¹ÚÀç¹Î");

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReShape);

	glutMainLoop();

	return 0;
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, 300, 300);
	glColor3f(1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	//CTM=I
	glRotatef(45.0, 0.0, 0.0, 1.0);	//CTM=CTM*R=I*R=R
	glTranslatef(0.6, 0.0, 0.0);	//CTM=CTM*T=R*T
	glutSolidCube(0.3);	//P'=CTM*P=(R*T)*P
	glFlush();


}

void MyReShape(int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	GLfloat widthFactor = (GLfloat)newWidth / (GLfloat)300;
	GLfloat heightFactor = (GLfloat)newHeight / (GLfloat)300;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}