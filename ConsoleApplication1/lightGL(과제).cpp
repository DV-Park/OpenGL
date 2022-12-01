#include <GL/glut.h>
#include <stdio.h>
 
GLboolean bLight0=GL_TRUE, bLight1=GL_FALSE;

GLfloat Ia=0.5, Id=0.5, Is=0.5;				
GLfloat Ka=0.5, Kd=0.5, Ks=0.5, Sn=25.0;	

GLfloat spot_cutoff = 23.5;		
GLfloat spot_expo = 2.0;		

GLfloat Rx = 40.0, Ry = 30.0, Rz = 0.0;		


void MyLightInit()	
{
	// �����ֺ���
	GLfloat MyGlobalAmbient[] = {0.2, 0.0, 0.0, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, MyGlobalAmbient);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);	// default (������ġ)
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);		// default (�������)

	// 0�� ����
	GLfloat light0_ambient[]={Ia, 0.0, 0.0, 1.0}; // 0�̸� ���� 1�̸� �� (��ġ�� ����, ���⼺ ����)
	GLfloat light0_diffuse[]={Id, 0.0, 0.0, 1.0};
	GLfloat light0_specular[]={Is, Is, Is, 1.0};
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);		// Ia: �ֺ���
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);		// Id: Ȯ�걤
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);		// Is: ��鱤

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);


	// 1�� ����
	GLfloat light1_ambient[]={0.0, Ia, 0.0, 1.0};
	GLfloat light1_diffuse[]={0.0, Id, 0.0, 1.0};
	GLfloat light1_specular[]={Is, Is, Is, 1.0};
	
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);	// Ia: �ֺ���
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);	// Id: Ȯ�걤
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);	// Is: ��鱤
}

void MyMaterialInit()
{
	GLfloat material_ambient[] = {Ka, Ka, Ka, 1.0};
	GLfloat material_diffuse[] = {Kd, Kd, Kd, 1.0};
	GLfloat material_specular[] = {Ks, Ks, Ks, 1.0};
	GLfloat material_shiniess[] = {Sn};
	//GLfloat material_emission[] = { 0.0,0.1,0.1,1.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);	// Ka: �ֺ��� ���
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);	// Kd: Ȯ�걤 ���
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular); // Ks: ��鱤 ���
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, material_shiniess); // n: ���� ���
	//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_emission); // �߱���

}
 
void MyReshape(int w, int h) {
	if ( w < h ) 
		glViewport(0, 0, (GLsizei) w, (GLsizei) w);
	else
		glViewport(0, 0, (GLsizei) h, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);				//�������
    glLoadIdentity();							//�׵���� �ε�
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);	//��������
}

void DoKeyboard(unsigned char key, int x, int y)
{
     switch(key) {
		// �ֺ����� ���� �� ��� ����
		case 'q': { Ia += 0.1;	Ka += 0.1; }  break;
		case 'a': if ( Ia > 0.1 ) { Ia -= 0.1;	Ka -= 0.1; }  break;
		
		// Ȯ�걤�� ���� �� ��� ����
		case 'e': { Id += 0.1;	Kd += 0.1; }  break;
		case 'd': if ( Id > 0.1 ) { Id -= 0.1;	Kd -= 0.1; }  break;
		
		// ��鱤�� ���� �� ��� ����
		case 'w': { Is += 0.1;	Ks += 0.1; }  break;
		case 's': if ( Is > 0.1 ) { Is -= 0.1;	Ks -= 0.1; }  break;
		case 'n': Sn += 5; break;
		case 'm': Sn -= 5; break;

		// ����Ʈ����Ʈ (����, ����¼�)
		case '1': spot_cutoff += 1.25;	break;
		case '2': spot_cutoff -= 1.25;	break;
		case '3': spot_expo += 1;	break;
		case '4': spot_expo -= 1;	break;

		// ȸ��
		case 'x': Rx += 10.0;	break;
		case 'y': Ry += 10.0;	break;
		case 'z': Rz += 10.0;	break;

		case 'i': // �ʱ�ȭ
			bLight0 = GL_TRUE; bLight1 = GL_FALSE;
			Ia = 0.5, Id = 0.5, Is = 0.5;				// ������ ���� 
			Ka = 0.5, Kd = 0.5, Ks = 0.5, Sn = 25.0;	// ������ ���� �ݻ� ��� (��üƯ���� ��Ÿ��)
			spot_cutoff = 50.0;		// ����Ʈ����Ʈ ���� 
			spot_expo = 2.0;		// ����Ʈ����Ʈ ����¼�
			Rx = 40.0, Ry = 30.0, Rz = 0.0;		// ȸ���� 
			break;
     }
     char info[128];
     sprintf_s(info, "a=(%.1f,%.1f), d=(%.1f,%.1f), s=(%.1f,%.1f,%.1f), spot_cutoff=(%.1f)", Ka,Ia, Kd,Id, Ks,Is, Sn, spot_cutoff);
     glutSetWindowTitle(info);
	 MyLightInit();
	 MyMaterialInit();
     glutPostRedisplay();
}

void MyOpenBox() 
{
	// ��
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		glNormal3f(0.0, 0.0, 1.0);
        glVertex3f(-0.5, -0.3, 0.6);
        glVertex3f(0.5, -0.3, 0.6);
        glVertex3f(0.5, 0.3, 0.6);
        glVertex3f(-0.5, 0.3, 0.6);
    glEnd();

    // ��
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		glNormal3f(0.0, 0.0, -1.0);
        glVertex3f(-0.5, -0.3, -0.6);
		glVertex3f(-0.5, 0.3, -0.6);
        glVertex3f(0.5, 0.3, -0.6);
		glVertex3f(0.5, -0.3, -0.6);
    glEnd();
		
	// ����
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		glNormal3f(-1.0, 0.0, 0.0);
        glVertex3f(-0.5, -0.3, 0.6);
        glVertex3f(-0.5, 0.3, 0.6);
		glVertex3f(-0.5, 0.3, -0.6);
        glVertex3f(-0.5, -0.3, -0.6);
    glEnd();

	// ����
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		glNormal3f(1.0, 0.0, 0.0);
		glVertex3f(0.5, -0.3, 0.6);
		glVertex3f(0.5, -0.3, -0.6);
		glVertex3f(0.5, 0.3, -0.6);
        glVertex3f(0.5, 0.3, 0.6);
    glEnd();

	// �ϴ�
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		glNormal3f(0.0, -1.0, 0.0);
        glVertex3f(-0.5, -0.3, 0.6);
		glVertex3f(-0.5, -0.3, -0.6); 
		glVertex3f(0.5, -0.3, -0.6);
		glVertex3f(0.5, -0.3, 0.6);
    glEnd();

	/*
	// ���
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(-0.5, 0.3, 0.6);
		glVertex3f(0.5, 0.3, 0.6);
		glVertex3f(0.5, 0.3, -0.6);
		glVertex3f(-0.5, 0.3, -0.6); 
    glEnd();
	*/
}

void DoMenu(int value)
{
     switch(value) {
		case 1:
			bLight0 = GL_TRUE;
			break;
		case 2:
			bLight0 = GL_FALSE;
			break;
		case 3:
			bLight1 = GL_TRUE;
			break;
		case 4:
			bLight1 = GL_FALSE;
			break;
     }
     glutPostRedisplay();
}

void DoDisplay()
{
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glEnable(GL_DEPTH_TEST);
	 glEnable(GL_NORMALIZE);
     
	 // ������ Ȱ��ȭ
	 glEnable(GL_LIGHTING);
	 //glDisable(GL_LIGHTING);
 
	 // 0�� ���� ��ġ
      if ( bLight0 )
		glEnable(GL_LIGHT0);
	 else
		glDisable(GL_LIGHT0);
	 
	 GLfloat light0_position[] = {-5.0, 5.0, 5.0, 1.0};
	 glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	 // 1�� ���� ��ġ
      if ( bLight1 )
		glEnable(GL_LIGHT1);
	 else
		glDisable(GL_LIGHT1);
     GLfloat light1_position[] = {5.0, 5.0, 5.0, 1.0};	// ������ ��ġ
	 //GLfloat light1_position[] = {Px, Py, Pz, 1.0};
	 glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	 
	 // 1�� ���� Spotlight
	 GLfloat spot_direction[] = {-5.0, -5.0, -5.0};	// �������κ����� �������� ����(����-->��ǥ)
	 //GLfloat spot_direction[] = {-Px, -Py, -Pz};	// �������κ����� �������� ����(����-->��ǥ)
	 glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	 glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spot_cutoff);	// ���� 0~90��(p.545)
	 glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spot_expo);	// ����¼� (���ð���� ����)
 
	 glPushMatrix();
		glRotatef(Rx, 1.0, 0.0, 0.0);
		glRotatef(Ry, 0.0, 1.0, 0.0);
		glRotatef(Rz, 0.0, 0.0, 1.0);
	    MyOpenBox();
	 glPopMatrix();

	 glutSolidSphere(0.5, 50, 50);     
     glFlush();
}

int main()
{
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(600, 500);
    glutCreateWindow("OpenGL Lighting and Shading");
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

	// �޴�
	glutCreateMenu(DoMenu);
    glutAddMenuEntry("Light 0 ON",1);
    glutAddMenuEntry("Light 0 OFF",2);
    glutAddMenuEntry("Light 1 ON",3);
    glutAddMenuEntry("Light 1 OFF",4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

	MyLightInit();		// ���� ����
	MyMaterialInit();	// ������ ��� ����
    glutDisplayFunc(DoDisplay);
	glutReshapeFunc(MyReshape);
	glutKeyboardFunc(DoKeyboard);
    glutMainLoop();
    return 0;
}

