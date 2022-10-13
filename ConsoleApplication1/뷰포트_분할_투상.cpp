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

	glLoadIdentity();	//항등 행렬로 초기화
	glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 5.0);	//기본 투상을 평해 투상으로 설정, 가시부피를 2배 크기로 ... 1
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	Width = 500;Height = 500;
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(Width, Height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("박재민");
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

	glLoadIdentity();	//항등 행렬로 초기화
	glOrtho(-2.0 * WidthFactor, 2.0 * WidthFactor, -2.0 * HeightFactor, 2.0 * HeightFactor, 0.5, 5.0);	//기본 투상을 평해 투상으로 설정, 가시부피를 2배 크기로 ... 1 (왜곡 방지를 위해 비율로 설정)
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, Width / 2, Height / 2); // 좌 하단 뷰포트 생성, 모델 뷰 행렬
	glPushMatrix();
		gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		DrawScene();
	glPopMatrix();
	glViewport(Width / 2, 0, Width / 2, Height / 2);	// 우 하단 뷰포트 생성, 모델 뷰 행렬
	glPushMatrix();
		gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		DrawScene();
	glPopMatrix();
	glViewport(0, Height / 2, Width / 2, Height / 2);	// 좌 상단 뷰포트 생성, 모델 뷰 행렬
	glPushMatrix();
		gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
		DrawScene();
	glPopMatrix();
	glViewport(Width / 2, Height / 2, Width / 2, Height / 2);	// 우 상단 뷰포트 생성, 모델 뷰 행렬
	glMatrixMode(GL_PROJECTION); //원근투상을 위한 투상 행렬 설정
	glPushMatrix();
		glLoadIdentity();
		gluPerspective(30, (GLdouble)Width/(GLdouble)Height, 3.0, 50.0);	// 원근 투상 가시 부피 설정 (시야각 30, 종횡비 1, 전방 절단면 0.5, 후방 절단면 50), (왜곡 방지를 위해 종횡비 비율로 설정)
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);	// 시점 설정
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
	glBegin(GL_QUADS);	// ...1 에서의 기본 투상 설정 된 평행 투상 (주전자 바닥)
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