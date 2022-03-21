#include <GL/glut.h>

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glRotatef(45.0, 1.0, 1.0, 1.0);
	glutWireCube(10.0);   // ��ʼ�Ա�
	glPopMatrix();
	


	glColor3f(0.0, 1.0, 0.0);
	glRotatef(45.0, 1.0, 1.0, 1.0);   //��ת��Ϊʹ��ʾ��Ϊ���
	glPushMatrix();
	glTranslatef(-10.0, -20.0, -10.0); //ƽ��,ʹ�ο�����ԭ���غ�
	glPushMatrix();
	glScalef(2.0, 1.0, 0.5);  //����	
	glPushMatrix();
	glTranslatef(10.0, 20.0, 10.0); //ʹ�ο���ص�ԭ����λ��
	glPushMatrix();
	glutWireCube(10.0);

	glFlush();
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat aspectRatio;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio = 1.0 * (GLfloat)w / (GLfloat)h;
	if (w <= h)
		glOrtho(-50.0, 50.0, -50.0 / aspectRatio, 50.0 / aspectRatio, -50.0, 50.0);
	else
		glOrtho(-50.0 * aspectRatio, 50.0 * aspectRatio, -50.0, 50.0, -50.0, 50.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("CubeScale");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutMainLoop();
	return 0;
}