#include <GL/glut.h>
// 광원의 특성
bool Light0On, Light1On;
void MyLightInit()
{
	// 0번 광원
	GLfloat light0_ambient[] = { 1.0, 0.0, 0.0, 1.0 }; // Ia:주변광 특성 (RGBA)
	GLfloat light0_diffuse[] = { 1.0, 0.0, 0.0, 1.0 }; // Id:확산광 특성 (RGBA)
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // Is:경면광 특성
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient); // Ia 설정
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse); // Id 설정
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular); // Is 설정
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0); // 거리 감쇠(상수)
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2); // 거리 감쇠(1차항)
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0); // 거리 감쇠(2차항)

	// 1번 광원
	GLfloat light1_ambient[] = { 0.0, 1.0, 0.0, 1.0 }; // Ia:주변광 특성 (RGBA)
	GLfloat light1_diffuse[] = { 0.0, 1.0, 0.0, 1.0 }; // Id:확산광 특성 (RGBA)
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // Is:경면광 특성
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient); // Ia 설정
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse); // Id 설정
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular); // Is 설정

}
// 물체의 특성
void MyMaterialInit()
{
	GLfloat material_ambient[] = { 0.2, 0.2, 0.2, 1.0 }; // Ka:주변광 계수 (세기?)
	GLfloat material_diffuse[] = { 0.8, 0.8, 0.8, 1.0 }; // Kd:확산광 계수 (세기?)
	GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // Ks:경면광 계수
	GLfloat material_shiniess[] = { 25.0 }; // n:광택 계수
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient); // Ka 설정
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);// Kd 설정
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular); // Ks 설정
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shiniess);// n 설정
}
void MyReshape(int w, int h) {
	if (w < h)
		glViewport(0, 0, (GLsizei)w, (GLsizei)w);
	else
		glViewport(0, 0, (GLsizei)h, (GLsizei)h);
	glMatrixMode(GL_PROJECTION); // 투상행렬
	glLoadIdentity(); // 항등행렬 로드
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // 평행투상
}
void DoDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	// 조명기능 활성화
	glEnable(GL_LIGHTING);

	if (Light0On) {
		// 0번 광원 배치
		glEnable(GL_LIGHT0);
		GLfloat light0_position[] = { -5.0, -10.0, -5.0, 1.0 }; // 광원의 위치
		glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	}
	else glDisable(GL_LIGHT0);

	//// 1번 광원 배치
	if (Light1On) {
		glEnable(GL_LIGHT1);
		GLfloat light1_position[] = { 3.0,3.0,3.0,3.0 }; // 광원의 위치 (마지막 매개변수가 0 또는 1)
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

		GLfloat spot_Direction[] = { -1.0,-1.0,-1.0 }; // 원점으로부터의 광원벡터 방향
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_Direction);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 40.0); // 조명각 0-90도(p. 545)
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 12.0); // 조명승수 (광택계수와 유사)
	}
	else glDisable(GL_LIGHT1);

	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();
	glFlush();
}
void MyMainMenuRight(int entryID) {
	if (entryID == 1) {
		Light0On = true;
	}
	else if (entryID == 2) {
		Light0On = false;
	}
	else if (entryID == 3) {
		Light1On = true;
	}
	else if (entryID == 4) {
		Light1On = false;
	}

	glutPostRedisplay();
}
int main()
{
	glutCreateWindow("박재민");
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	MyLightInit(); // 광원의 특성
	MyMaterialInit(); // 물체의 특성
	glutDisplayFunc(DoDisplay);
	glutReshapeFunc(MyReshape);

	GLint MyMainMenuID = glutCreateMenu(MyMainMenuRight);
	glutSetMenu(MyMainMenuID);
	glutAddMenuEntry("Light 0, On", 1);
	glutAddMenuEntry("Light 0, Off", 2);
	glutAddMenuEntry("Light 1, On", 3);
	glutAddMenuEntry("Light 1, Off", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}
