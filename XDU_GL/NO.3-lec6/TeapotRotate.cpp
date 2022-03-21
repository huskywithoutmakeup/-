#include <stdlib.h>
#include <GL/glut.h>

int RunMode = 1;		//1Ϊ�ƶ�ģʽ��0Ϊ��ֹģʽ
double angle = 0;  //��ʼλ��
double speed = 0.5;
int depth = 600;
int start = 20;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void myKey(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':RunMode = 1;    //run
		glutPostRedisplay();
		break;
	case 's':RunMode = 0;    //stop
		glutPostRedisplay();
		break;
	case 'u':RunMode = 1;    //�����ٶ�
		speed = 0.5;
		glutPostRedisplay();
		break;
	case 'd':RunMode = 1;    //�����ٶ�
		speed = -0.5;
		glutPostRedisplay();
		break;
	case 27:
		exit(1);
	}
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//�ƶ�ͼ��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (angle > 360)
		angle = 0;
	else
		angle = angle + speed;

	//glTranslated(0.0, -40.0, -200);//�����������Ƶ�����ͼ��
	glRotated(angle, 0, 1, 0);

	glColor3f(0.8, 0.8, 0.8);
	glutSolidTeapot(60);

	//ǿ��ִ�л�ͼ�������������������ʾ
	glFlush();
	glutSwapBuffers();
	glLoadIdentity();

	if (RunMode == 1) {
		glutPostRedisplay();	// ���������ػ�
	}
}

void ChangeSize(GLsizei w, GLsizei h)
{
	float ratio;
	if (h == 0)
		h = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	ratio = 1.0 * (float)w / (float)h;

	gluPerspective(50, ratio, start, depth);
	glEnable(GL_DEPTH_TEST);

	gluLookAt(0, 50, 240, 0, 0, 0, 0, 0, -1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(800, 400);
	glutCreateWindow("TeapotRotate");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(myKey);

	glutMainLoop();
	return 0;
}