#include <stdlib.h>
#include <GL/glut.h>

int RunMode = 1;		//1Ϊ�ƶ�ģʽ��0Ϊ��ֹģʽ
double z = 20;  //��ʼλ��
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

	if (z > depth)
		z = 20;
	else
		z = z + speed;

	glTranslated(0.0, 0.0, -z);
	glColor3f(0.8, 0.8, 0.8);
	glutWireCube(10);

	glPointSize(4);
	glBegin(GL_POINTS);
	glColor3f(0, 0, 1);
	glVertex3d(0, 0, 0);
	glEnd();

		//������ƽ���ߵ���·
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3d(0, 0, -depth);
	glVertex3d(0, 0, depth);
	glEnd();

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

	gluLookAt(-20, 10, 40, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(500, 200);
	glutInitWindowSize(800, 400);
	glutCreateWindow("Cube Move");

	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(myKey);

	glutMainLoop();
	return 0;
}