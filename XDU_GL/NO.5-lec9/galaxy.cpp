#include<GL/glut.h>
#include <math.h>

#define pi 3.14

GLfloat angle_ES = 0.0f;      //���������̫������ת�Ƕ�
GLfloat speed_ES = 0.005f;    //����������ת�ٶ�
GLfloat angle_ME = 0.0f;      //��������ڵ������ת�Ƕ�
GLfloat speed_ME = 0.015f;    //�����Ƶ���ת�ٶ�
GLfloat angle_self = 0.0f;    //��ת�Ƕ�
GLfloat speed_self = 1.0f;    //��ת�ٶ�
//�������Ǽ�����-��-�� ��ת�ٶȵı��� Ϊ 1-5-3
GLfloat distance_ES = 2.5f; //����������̫���ľ���
GLfloat distance_ME = 0.5f; //�������������ľ���

GLfloat earthPosX = 2.5f;  //���������
GLfloat earthPosZ = 0.0f;
GLfloat monthPosX = 3.0f;  //����������
GLfloat monthPosZ = 0.0f;


GLfloat n = 6000;//���ɹ������

void init()
{
	GLfloat whiteLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glColor3f(0.0, 0.0, 0.0);
	glEnable(GL_LIGHTING);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);


	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_DEPTH_TEST);

	glShadeModel(GL_SMOOTH);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(30, 1.0f, 1.0f, 1.0f);


	//SUN
	glPushMatrix();
	glRotatef(angle_self, 0.0f, 1.0f, 0.0f); 	//��ת
	glColor3f(1.0f, 0.0f, 0.0f);
	glDisable(GL_LIGHTING);
	glutWireSphere(0.6, 30, 30);
	glPopMatrix();

	//EARTH
	glPushMatrix();
	glTranslatef(earthPosX, 0.0f, earthPosZ);       //����λ��
	glRotatef(5 * angle_self, 0.0f, 1.0f, 0.0f);	//��ת
	glColor3f(0.0f, 0.0f, 1.0f);
	glEnable(GL_LIGHTING);
	glutWireSphere(0.3, 30, 30);
	glPopMatrix();

	//MOON
	glPushMatrix();
	glTranslatef(monthPosX, 0.0f, monthPosZ);       //����λ��
	glRotatef(3 * angle_self, 0.0f, 1.0f, 0.0f);	//��ת
	glColor3f(1.0f, 1.0f, 1.0f);
	glEnable(GL_LIGHTING);
	glutWireSphere(0.15, 20, 20);
	glPopMatrix();

	//SUN-EARTH LINE
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 1.0f, 1.0f);
	for (int i = 0; i < n; i++)
	{
		glVertex3f(distance_ES * cos(2 * pi * i / n), 0.0f, distance_ES * sin(2 * pi * i / n));
	}
	glEnd();
	glFlush();
	glPopMatrix();

	//EARTH-MOON LINE
	glPushMatrix();
	glTranslatef(earthPosX, 0, earthPosZ);  //�ƶ���ǰ����ϵԭ��������
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 1.0f, 1.0f);
	for (int i = 0; i < n; i++)
	{
		glVertex3f(distance_ME * cos(2 * pi * i / n), 0.0f, distance_ME * sin(2 * pi * i / n));
	}
	glEnd();
	glFlush();
	glPopMatrix();
	glutSwapBuffers();
}

void timerFunction(int value)
{
	earthPosX = distance_ES * cos(angle_ES * pi); 	//�����x��z����
	earthPosZ = distance_ES * sin(angle_ES * pi);
	monthPosX = earthPosX + distance_ME * cos(angle_ME * pi);//������x��z����
	monthPosZ = earthPosZ + distance_ME * sin(angle_ME * pi);

	angle_ES += speed_ES;     //���սǶ�����
	angle_ME += speed_ME;     //���½Ƕ�����
	angle_self += speed_self; //��ת�Ƕ�����

	if (angle_self > 360)
	{
		angle_self = 0.0f;
	}
	glutPostRedisplay();
	glutTimerFunc(33, timerFunction, 1);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat aspecratio = (GLfloat)w / (GLfloat)h;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-3, 3, -3 / aspecratio, 3 / aspecratio, -6.0, 6.0);
	else
		glOrtho(-3 * aspecratio, 3 * aspecratio, -3, 3, -6, 6.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 500);
	glutCreateWindow("Galaxy");
	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);

	glutTimerFunc(33, timerFunction, 1);
	glutMainLoop();

	return 0;
}