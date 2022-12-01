#include<GL/glut.h>
#define WIDTH 3
#define HEIGHT 3

GLubyte MyTexture[WIDTH][HEIGHT][3];

GLfloat mat_diffuse[] = { 0.25,0.25,1.,0. };
GLfloat mat_specular[] = { 1.,1.,1.,0. };
GLfloat light_position[] = { 10.,10.,20.,1. };

GLfloat MyPlane111[] = { 1.5,1.5,1.5,0.0 };
GLfloat MyPlane100[] = { 1.5,0.0,0.0,0.0 };
GLfloat Rx = 0.0, Ry = 0.0, Rz = 0.0;

void FillMyTextureCheck() {		// 11-2 �ڵ�(üũ���� �ؽ���)
	int s, t;
	for (s = 0;s < WIDTH; s++) {
		for (t = 0;t < HEIGHT;t++) {
			GLubyte intensity = ((s + t) % 2) * 255;
			MyTexture[s][t][0] = intensity;
			MyTexture[s][t][1] = intensity;
			MyTexture[s][t][2] = intensity;
		}
	}
}

void MyInit() {		//�ؽ���(�ڵ� 11-1, 11-2)
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	FillMyTextureCheck();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, &MyTexture[0][0][0]);

	//�ؽ��� �Ķ���� ����(p.606)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //Ȯ����� ���� (NEAREST ���� �����, LINEAR ��������)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //��Ұ��� ���� (NEAREST ���� �����, LINEAR ��������)

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //MODULATE-�ؽ��� ����� ����
	glEnable(GL_TEXTURE_2D);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR); //Eye - ��ü�� ������, Object - �ؽ��Ķ� ���� ������
	glTexGenfv(GL_S, GL_OBJECT_PLANE, MyPlane111);	// �������
	glEnable(GL_TEXTURE_GEN_S); //s����,t����
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR); //Eye - ��ü�� ������, Object - �ؽ��Ķ� ���� ������
	glTexGenfv(GL_T, GL_OBJECT_PLANE, MyPlane100);	// �������
	glEnable(GL_TEXTURE_GEN_T); //s����,t����
}

void MyReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40., (GLfloat)w / (GLfloat)h, 1., 10.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0., 0., 5., 0., 0., 0., 0., 1., 0.);
	glTranslatef(0., 0., -1.);
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glRotatef(Rx, 1.0, 0.0, 0.0);
		glRotatef(Ry, 0.0, 1.0, 0.0);
		glRotatef(Rz, 0.0, 0.0, 1.0);
		glutSolidSphere(1.5, 50, 50);
		//glutSolidTeapot(1.5);
	glPopMatrix();
	glutSwapBuffers();
}

void DoKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '1':Rx += 1;break;
	case '2':Ry += 1;break;
	case '3':Rz += 1;break;
	case 'i':Rx = Ry = Rz = 0;break;
	}
	glutPostRedisplay();
}

//int APIENTRY main(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) 
//{
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//
//	glutCreateWindow("�����");
//	glutKeyboardFunc(DoKeyboard);
//	glutReshapeFunc(MyReshape);
//	glutDisplayFunc(MyDisplay);
//	MyInit();
//	glutMainLoop();
//	return 0;
//}
int main() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutCreateWindow("�����");
	glutKeyboardFunc(DoKeyboard);
	glutReshapeFunc(MyReshape);
	glutDisplayFunc(MyDisplay);
	MyInit();
	glutMainLoop();
	return 0;
}