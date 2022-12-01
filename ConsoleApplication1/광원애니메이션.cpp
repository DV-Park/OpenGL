#include<GL/glut.h>
#include<stdio.h>

static int SpinAngle = 0;


void InitLight() {
	GLfloat light0_ambient[] = { 0.5, 0.4, 0.3, 1.0 }; // 조명 특성
	GLfloat light0_diffuse[] = { 0.8, 0.7, 0.6, 1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	GLfloat material_ambient[] = { 0.4,0.4,0.4,1.0 }; // 물체 특성
	GLfloat material_diffuse[] = { 0.9,0.9,0.9,1.0 };
	GLfloat material_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat material_shininess[] = { 25.0 };

	glShadeModel(GL_SMOOTH); // 구로 셰이딩
	glEnable(GL_DEPTH_TEST); // 깊이 버퍼활성화
	glEnable(GL_LIGHTING); // 조명 기능 활성화
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
}

void MyDisplay() {
	GLfloat LightPosition[] = { 0.0,0.0,1.5,1.0 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();	// 1... 이전의 변환행렬 저장
	glTranslatef(0.0, 0.0, -5.0); // 2... 이동 변환 z축으로 -5
	glPushMatrix(); // 3... 이동한 좌표계 다시 저장
		glRotatef(SpinAngle, 1.0, 0.0, 0.0); // 4... 회전변환 x축 중심
		glLightfv(GL_LIGHT0, GL_POSITION, LightPosition); // 5... 광원의 위치 z축을 따라 1.5만큼 떨어진 곳
		glTranslatef(0.0, 0.0, 1.5); // 6... 좌표계 이동 -> z축으로 1.5
		glDisable(GL_LIGHTING); // 7... 광원 자체를 직접 그리기 위해 조명 비활성화
		glColor3f(0.9, 0.9, 0.9); 
		glutWireSphere(0.06, 10, 10); // 8... 백색 와이어 프레임으로 광원 모습 그림
		glEnable(GL_LIGHTING); // 9... 다시 조명 활성화
	glPopMatrix();
	glutSolidSphere(1.0, 400, 400); // 10... 실제 조명을 받을 원구 그림
	glPopMatrix();
	glFlush();
}

void MyReshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void MyMouse(int button, int state, int x, int y) {
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			SpinAngle = (SpinAngle + 15) % 360;
			glutPostRedisplay();
		}
		break;
	default:
		break;
	}
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("박재민");
	InitLight();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMouseFunc(MyMouse);
	glutMainLoop();
	return 0;
}

