#include<GL/glut.h>
#include<stdio.h>

void MyDisplay();
void MyReShape(int newWidth, int newHeight);
void MyMainMenuLeft(int entryID);
void MyMainMenuRight(int entryID);

bool IsTrans, IsRota, IsScale, IsSphere, IsTorus, IsTeapot;

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutCreateWindow("¹ÚÀç¹Î");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 10.0, 0.0, 10.0, -1.0, 10.0);
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReShape);

	GLint MyMainMenuID = glutCreateMenu(MyMainMenuLeft);
	glutSetMenu(MyMainMenuID);
	glutAddMenuEntry("Draw Sphere", 1);
	glutAddMenuEntry("Draw Torus", 2);
	glutAddMenuEntry("Draw Teapot", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	GLint MyMainMenuID2 = glutCreateMenu(MyMainMenuRight);
	glutSetMenu(MyMainMenuID2);
	glutAddMenuEntry("Translate", 1);
	glutAddMenuEntry("Rotate", 2);
	glutAddMenuEntry("Scale", 3);
	glutAttachMenu(GLUT_LEFT_BUTTON);
	glutPostRedisplay();
	glutMainLoop();
	return 0;
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);

	if(IsTrans)
		glTranslatef(0.2, 0.2, 0.2);
	else if(IsRota)
		glRotatef(30, 1.0, 1.0, 1.0);
	else if(IsScale)
		glScalef(2.0, 2.0, 2.0);

	if(IsSphere)
		glutWireSphere(0.5, 20, 20);
	else if(IsTorus)
		glutWireTorus(0.1, 0.5, 20, 20);
	else if(IsTeapot)
		glutWireTeapot(0.5);

	glFlush();
}

void MyReShape(int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	GLfloat widthFactor = (GLfloat)newWidth / (GLfloat)300;
	GLfloat heightFactor = (GLfloat)newHeight / (GLfloat)300;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void MyMainMenuLeft(int entryID) {
	if (entryID == 1) {
		IsSphere = true;
		IsTorus = false;
		IsTeapot = false;
	}
	else if (entryID == 2){
		IsSphere = false;
		IsTorus = true;
		IsTeapot = false;
	}
	else if (entryID == 3){
		IsSphere = false;
		IsTorus = false;
		IsTeapot = true;
	}

	glutPostRedisplay();
}

void MyMainMenuRight(int entryID) {
	if (entryID == 1) {
		IsTrans = true;
		IsRota = false;
		IsScale = false;
	}
	else if (entryID == 2) {
		IsTrans = false;
		IsRota = true;
		IsScale = false;
	}
	else if (entryID == 3) {
		IsTrans = false;
		IsRota = false;
		IsScale = true;
	}

	glutPostRedisplay();
}