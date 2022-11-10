#include<GL/glut.h>
#include<stdio.h>

void MyDisplay();
void MyReshape(int w, int h);
void DrawScene();
int Width, Height;
GLfloat WidthFactor, HeightFactor;

void Init() {
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();	//항등 행렬로 초기화
	glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 5.0);
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
	GLdouble eqn1[4] = { 0.0,1.0,0.0,0.0 }; // 평면의 법선 벡터
	GLdouble eqn2[4] = { -1.0,0.0,0.0,0.0 }; //
	GLdouble eqn3[4] = { 1.0,1.0,0.0,0.0 }; // 평면의법선 벡터
	GLdouble eqn4[4] = { 1.0,1.0,0.0,0.5 }; // Ax+By+Cz+D=0

	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);

	

	glTranslatef(0.0, 0.0, -5.0);
	//glRotatef(90.0, 1.0, 0.0, 0.0); //2

	glClipPlane(GL_CLIP_PLANE0, eqn1);//1
	//glClipPlane(GL_CLIP_PLANE0, eqn2);//2
	glEnable(GL_CLIP_PLANE0);

	glutWireSphere(1.0, 20, 16);

	glFlush();
}

void MyReshape(int w, int h) {
	Width = w; Height = h;
	WidthFactor = (GLfloat)Width / (GLfloat)500;
	HeightFactor = (GLfloat)Height / (GLfloat)500;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, (GLdouble)Width / (GLdouble)Height, 3.0, 50.0);

	glutPostRedisplay();
}