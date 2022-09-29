#include<GL/glut.h>
#include<stdio.h>

void MyDisplay();
void MyReShape(int newWidth, int newHeight);
void MyKeyboard(unsigned char KeyPressed, int x, int y);
void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y);
void MyMouseMove(GLint X, GLint Y);
void MySpecial(int KeyPressed, int x, int y);
void MyMainMenu(int entryID);
void MyMainMenu2(int entryID);
void MyIdle();
void MyTimer(int value);

void MyCreateList();

bool IsDrawSphere, IsDrawTorus, IsDrawTeapot;
GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;
GLfloat r_val = 0.5, g_val = 0.5, b_val = 0.5, Delta = 1.0;
GLint WindowX = 600, WindowY = 600;
int MyListID;

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA); //GLUT_DOUBLE�� ��� �� ���� ���۸�
	glutInitWindowSize(WindowX, WindowY);
	glutCreateWindow("�����");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //�׵���� �ε�
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(MyDisplay); //ȭ�� ���鶧 call
	glutReshapeFunc(MyReShape); //ó�� ������ ����, ũ�� ������ �� call
	glutKeyboardFunc(MyKeyboard); //���ڹ� ���� Ű�� ������ �� call (�Լ�,���� �� Ư�� Ű - glutSpecialFunc())
	glutMouseFunc(MyMouseClick);  //���콺 ��ư�� Ŭ���ϰų� ������ �� call
	glutMotionFunc(MyMouseMove); //���콺 ��ư�� ���� ���¿��� ������ �� call
	glutSpecialFunc(MySpecial);
	//glutPassiveMotionFunc(MyPassive); //���콺 ��ư�� ������ ���� ���¿��� ������ �� call
	//glutEntryFunc(MyEntry); //���콺�� ������ ������ ���ų� ������ ���� �� call

	GLint MyMainMenuID = glutCreateMenu(MyMainMenu); //�޴� �ݹ� AttachMenu�� ���� ��ư ����
	glutSetMenu(MyMainMenuID);
	glutAddMenuEntry("Draw Sphere", 1);
	glutAddMenuEntry("Draw Torus", 2);
	glutAddMenuEntry("Draw Teapot", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	GLint MyMainMenuID2 = glutCreateMenu(MyMainMenu2);
	glutSetMenu(MyMainMenuID2);
	glutAddMenuEntry("Translate", 1);
	glutAddMenuEntry("Rotate", 2);
	glutAddMenuEntry("Scale", 3);
	glutAttachMenu(GLUT_LEFT_BUTTON);

	glutIdleFunc(MyIdle); //Idle ���¿��� call

	glutTimerFunc(40, MyTimer, 10); //40ms ��� �� MyTimer(10) ȣ��
	
	MyCreateList();

	glutMainLoop();
	return 0;
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutReshapeWindow(WindowX, WindowY);
	//printf("MyDisplay...");
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0, 0, 300, 300);
	glColor3f(r_val, g_val, b_val);

	//glRotatef(45, 1.0, 1.0, 1.0);
	glutWireCube(0.5);

	glColor3f(r_val, g_val, b_val);
	glViewport(0, 300, 300, 300);
	glutWireSphere(0.5, 20, 20);

	glColor3f(r_val, g_val, b_val);
	glViewport(300, 300, 300, 300);
	glutWireCone(0.5, 0.5, 20, 20);

	glColor3f(r_val, g_val, b_val);
	glViewport(300, 0, 300, 300);
	glutWireTorus(0.1, 0.5, 20, 20);

	//glBegin(GL_POLYGON);  //�ݽð���� ������ �߿�
	//	glColor3fv(MyColors[0]); glVertex3fv(MyVertices[0]); 
	//	glColor3fv(MyColors[3]); glVertex3fv(MyVertices[3]); 
	//	glColor3fv(MyColors[2]); glVertex3fv(MyVertices[2]); 
	//	glColor3fv(MyColors[1]); glVertex3fv(MyVertices[1]); 
	//glEnd();

	glViewport(0, 0, 300, 300);
	glCallList(MyListID);

	glFlush();
}

void MyReShape(int newWidth, int newHeight) {
	//printf("R:%f, G:%f, B:%f  ", r_val, g_val, b_val);
	glViewport(0, 0, newWidth, newHeight);
	GLfloat widthFactor = (GLfloat)newWidth / (GLfloat)300;
	GLfloat heightFactor = (GLfloat)newHeight / (GLfloat)300;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1.0 * widthFactor, 1.0 * widthFactor, -1 * heightFactor, 1.0 * heightFactor, -1.0, -1.0);
}

void MyKeyboard(unsigned char KeyPressed, int x, int y) {
	switch (KeyPressed) {
	case 'R':
		if (r_val < 1.0)
			r_val += 0.1;
		break;
	case 'G':
		if (g_val < 1.0)
			g_val += 0.1;
		break;
	case 'B':
		if (b_val < 1.0)
			b_val += 0.1;
		break;
	case 'r':
		r_val = 1;
		g_val = 0;
		b_val = 0;
		break;
	case 'g':
		r_val = 0;
		g_val = 1;
		b_val = 0;
		break;
	case 'b':
		r_val = 0;
		g_val = 0;
		b_val = 1;
		break;

	case 'Q':
		exit(0);break;
	case 'q':
		exit(0);break;
	case 27: //escŰ �ƽ�Ű�ڵ尪
		exit(0);break;
	}
	glutPostRedisplay(); //���� display call
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		TopLeftX = X;
		TopLeftY = Y;
	}
}

void MyMouseMove(GLint X, GLint Y) {
}

void MySpecial(int KeyPressed, int x, int y) {
	GLint X = glutGet(GLUT_WINDOW_X);
	GLint Y = glutGet(GLUT_WINDOW_Y);
	switch (KeyPressed) {
	case GLUT_KEY_LEFT:
		WindowX = X - 10;
		break;
	case GLUT_KEY_RIGHT:
		WindowX = X + 10;
		break;
	case GLUT_KEY_UP:
		WindowY = Y - 10;
		break;
	case GLUT_KEY_DOWN:
		WindowY = Y + 10;
		break;
	}
	glutPostRedisplay();
}

void MyMainMenu(int entryID) {
	if (entryID == 1)
		IsDrawSphere = true;
	else if (entryID == 2)
		IsDrawTorus = true;
	else if (entryID == 3)
		IsDrawTeapot = true;
	glutPostRedisplay();
}

void MyMainMenu2(int entryID) {
	if (entryID == 1)
		glTranslatef(0.2, 0.2, 0.2);
	else if (entryID == 2)
		glRotatef(30, 0, 0, 0);
	else if (entryID == 3)
		glScalef(2.0, 2.0, 2.0);

	glutPostRedisplay();
}

void MyIdle() {
	Delta+=0.0001;
	glutPostRedisplay();
}

void MyTimer(int value) {
	Delta += 0.0001 * value;
	glutPostRedisplay();
	glutTimerFunc(10, MyTimer, 100);
}

void MyCreateList() {
	MyListID = glGenLists(1);
	glNewList(MyListID, GL_COMPILE);
	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.5, 0.5);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, -0.5, 0.0);
		glVertex3f(0.5, 0.5, 0.0);
		glVertex3f(-0.5, 0.5, 0.0);
	glEnd();
	glEndList();
}