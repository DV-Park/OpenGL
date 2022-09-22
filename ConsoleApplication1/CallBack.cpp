#include<GL/glut.h>
#include<stdio.h>

void MyDisplay();
void MyReShape(int newWidth, int newHeight);
void MyKeyboard(unsigned char KeyPressed, int x, int y);

int main() {
	//glutInitWindowPosition(200, 100);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutCreateWindow("�����");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //�׵���� �ε�
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(MyDisplay); //ȭ�� ���鶧 call
	glutReshapeFunc(MyReShape); //ó�� ������ ����, ũ�� ������ �� call
	glutKeyboardFunc(MyKeyboard); //���ڹ� ���� Ű�� ������ �� call (�Լ�,���� �� Ư�� Ű - glutSpecialFunc())
	glutMainLoop();
	return 0;
}

void MyDisplay() {
	printf("MyDisplay...");
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

void MyReShape(int newWidth, int newHeight) {
	printf("ReShape...");
	glViewport(0, 0, newWidth, newHeight);
	GLfloat widthFactor = (GLfloat)newWidth / (GLfloat)300;
	GLfloat heightFactor = (GLfloat)newHeight / (GLfloat)300;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1.0 * widthFactor, 1.0 * widthFactor, -1 * heightFactor, 1.0 * heightFactor, -1.0, -1.0);
}

void MyKeyboard(unsigned char KeyPressed, int x, int y) {
	switch (KeyPressed) {
	case 'Q':
		exit(0);break;
	case 'q':
		exit(0);break;
	case 27: //escŰ �ƽ�Ű�ڵ尪
		exit(0);break;
	}
}