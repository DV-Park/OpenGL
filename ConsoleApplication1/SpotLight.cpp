#include <GL/glut.h>
// ������ Ư��
bool Light0On, Light1On;
void MyLightInit()
{
	// 0�� ����
	GLfloat light0_ambient[] = { 1.0, 0.0, 0.0, 1.0 }; // Ia:�ֺ��� Ư�� (RGBA)
	GLfloat light0_diffuse[] = { 1.0, 0.0, 0.0, 1.0 }; // Id:Ȯ�걤 Ư�� (RGBA)
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // Is:��鱤 Ư��
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient); // Ia ����
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse); // Id ����
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular); // Is ����
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0); // �Ÿ� ����(���)
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2); // �Ÿ� ����(1����)
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0); // �Ÿ� ����(2����)

	// 1�� ����
	GLfloat light1_ambient[] = { 0.0, 1.0, 0.0, 1.0 }; // Ia:�ֺ��� Ư�� (RGBA)
	GLfloat light1_diffuse[] = { 0.0, 1.0, 0.0, 1.0 }; // Id:Ȯ�걤 Ư�� (RGBA)
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // Is:��鱤 Ư��
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient); // Ia ����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse); // Id ����
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular); // Is ����

}
// ��ü�� Ư��
void MyMaterialInit()
{
	GLfloat material_ambient[] = { 0.2, 0.2, 0.2, 1.0 }; // Ka:�ֺ��� ��� (����?)
	GLfloat material_diffuse[] = { 0.8, 0.8, 0.8, 1.0 }; // Kd:Ȯ�걤 ��� (����?)
	GLfloat material_specular[] = { 1.0, 1.0, 1.0, 1.0 }; // Ks:��鱤 ���
	GLfloat material_shiniess[] = { 25.0 }; // n:���� ���
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient); // Ka ����
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);// Kd ����
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular); // Ks ����
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shiniess);// n ����
}
void MyReshape(int w, int h) {
	if (w < h)
		glViewport(0, 0, (GLsizei)w, (GLsizei)w);
	else
		glViewport(0, 0, (GLsizei)h, (GLsizei)h);
	glMatrixMode(GL_PROJECTION); // �������
	glLoadIdentity(); // �׵���� �ε�
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // ��������
}
void DoDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	// ������ Ȱ��ȭ
	glEnable(GL_LIGHTING);

	if (Light0On) {
		// 0�� ���� ��ġ
		glEnable(GL_LIGHT0);
		GLfloat light0_position[] = { -5.0, -10.0, -5.0, 1.0 }; // ������ ��ġ
		glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	}
	else glDisable(GL_LIGHT0);

	//// 1�� ���� ��ġ
	if (Light1On) {
		glEnable(GL_LIGHT1);
		GLfloat light1_position[] = { 3.0,3.0,3.0,3.0 }; // ������ ��ġ (������ �Ű������� 0 �Ǵ� 1)
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

		GLfloat spot_Direction[] = { -1.0,-1.0,-1.0 }; // �������κ����� �������� ����
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_Direction);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 40.0); // ���� 0-90��(p. 545)
		glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 12.0); // ����¼� (���ð���� ����)
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
	glutCreateWindow("�����");
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
	MyLightInit(); // ������ Ư��
	MyMaterialInit(); // ��ü�� Ư��
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
