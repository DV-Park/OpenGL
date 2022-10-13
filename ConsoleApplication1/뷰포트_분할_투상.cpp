#include<GL/glut.h>
#include<stdio.h>

void MyDisplay();
void MyReshape(int w, int h);
void DrawScene();
int Width, Height;
GLfloat WidthFactor, HeightFactor;

void Init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();	//�׵� ��ķ� �ʱ�ȭ
	glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 5.0);	//�⺻ ������ ���� �������� ����, ���ú��Ǹ� 2�� ũ��� ... 1
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	Width = 500;Height = 500;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("�����");
	Init();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	return 0;
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();	//�׵� ��ķ� �ʱ�ȭ
	glOrtho(-2.0 * WidthFactor, 2.0 * WidthFactor, -2.0 * HeightFactor, 2.0 * HeightFactor, 0.5, 5.0);	//�⺻ ������ ���� �������� ����, ���ú��Ǹ� 2�� ũ��� ... 1 (�ְ� ������ ���� ������ ����)
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, Width / 2, Height / 2); // �� �ϴ� ����Ʈ ����, �� �� ���
	glPushMatrix();
		gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		DrawScene();
	glPopMatrix();
	glViewport(Width / 2, 0, Width / 2, Height / 2);	// �� �ϴ� ����Ʈ ����, �� �� ���
	glPushMatrix();
		gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		DrawScene();
	glPopMatrix();
	glViewport(0, Height / 2, Width / 2, Height / 2);	// �� ��� ����Ʈ ����, �� �� ���
	glPushMatrix();
		gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
		DrawScene();
	glPopMatrix();
	glViewport(Width / 2, Height / 2, Width / 2, Height / 2);	// �� ��� ����Ʈ ����, �� �� ���
	glMatrixMode(GL_PROJECTION); //���������� ���� ���� ��� ����
	glPushMatrix();
		glLoadIdentity();
		gluPerspective(30, (GLdouble)Width/(GLdouble)Height, 3.0, 50.0);	// ���� ���� ���� ���� ���� (�þ߰� 30, ��Ⱦ�� 1, ���� ���ܸ� 0.5, �Ĺ� ���ܸ� 50), (�ְ� ������ ���� ��Ⱦ�� ������ ����)
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);	// ���� ����
			DrawScene();
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glFlush();
}

void MyReshape(int w, int h) {
	Width = w; Height = h;
	WidthFactor = (GLfloat)Width / (GLfloat)500;
	HeightFactor = (GLfloat)Height / (GLfloat)500;


	glutPostRedisplay();
}

void DrawScene() {
	glColor3f(0.7, 0.7, 0.7);
	glPushMatrix();
	glTranslatef(0.0, -1.0, 0.0);
	glBegin(GL_QUADS);	// ...1 ������ �⺻ ���� ���� �� ���� ���� (������ �ٴ�)
		glVertex3f(2.0, 0.0, 2.0);
		glVertex3f(2.0, 0.0, -2.0);
		glVertex3f(-2.0, 0.0, -2.0);
		glVertex3f(-2.0, 0.0, 2.0);
	glEnd();
	glPopMatrix();
	glColor3f(0.3, 0.3, 0.7);
	glPushMatrix();
		glTranslatef(0.0, 0.0, -0.5);
		glutWireTeapot(1.0);
	glPopMatrix();
}