#include<GL/glut.h>
#include<stdio.h>

void MyDisplay();
void MyReShape(int newWidth, int newHeight);
void MyKeyboard(unsigned char KeyPressed, int x, int y);
void MyMove(int KeyPressed, int x, int y);

GLfloat r_val = 0.5, g_val = 0.5, b_val = 0.5;
GLint WX = 30, WY = 30;

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(WX, WY);
	glutCreateWindow("¹ÚÀç¹Î");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReShape); 
	glutKeyboardFunc(MyKeyboard); 
	glutSpecialFunc(MyMove);

	glutMainLoop();

	return 0;
}

void MyDisplay() {
	glutPositionWindow(WX, WY);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glViewport(0, 0, 300, 300);
	glColor3f(r_val, g_val, b_val);

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

	glFlush();
	
}

void MyReShape(int newWidth, int newHeight) {
	glViewport(0, 0, newWidth, newHeight);
	GLfloat widthFactor = (GLfloat)newWidth / (GLfloat)300;
	GLfloat heightFactor = (GLfloat)newHeight / (GLfloat)300;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
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
	}
	glutPostRedisplay();
}

void MyMove(int KeyPressed, int x, int y) {
	GLint X = glutGet(GLUT_WINDOW_X);
	GLint Y = glutGet(GLUT_WINDOW_Y);
	switch (KeyPressed) {
	case GLUT_KEY_LEFT:
		WX = X - 10;
		break;
	case GLUT_KEY_RIGHT:
		WX = X + 10;
		break;
	case GLUT_KEY_UP:
		WY = Y - 10;
		break;
	case GLUT_KEY_DOWN:
		WY = Y + 10;
		break;
	}
	glutPostRedisplay();
}