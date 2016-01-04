#include <windows.h>
#include <GL/glut.h> 
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

float cameraAngleToRotateX = 0;
float cameraAngleToRotateY = 15;
float depth = -40;
float time = 0;
const float START_SPEED = 1;
const float START_ANGLE = 45;
const float RADIUS = 1;
const float G = 0.05;
const float GROUND_SIZE = 20;
int refreshMills = 20;

class Cannonball {
public:
	float startSpeed;
	float startAngle;
	float radius;
	float x; 
	float y;
	float z;
	float startPosX;
	float startPosY;

	Cannonball(float startX, float startY, float startZ, float speed, float angle, float r) {
		x = startX;
		y = startY;
		z = startZ;
		startSpeed = speed;
		startAngle = angle;
		radius = r;
		startPosX = startX;
		startPosY = startY;
	}

	void draw()
	{
		glPushMatrix();
		glTranslatef(x, y, z);
		glLineWidth(1.0);
		glColor3f(0, 0, 0);

		glutWireSphere(radius, 16, 16);
		glPopMatrix();
	}

};


class CannonGun{
public:
	float angle;
	float radius;
	float height;
	float x;
	float y;
	float z;
	CannonGun(float startX, float startY, float startZ, float _angle, float _radius, float _height){
		x = startX;
		y = startY;
		z = startZ;
		angle = _angle;
		radius = _radius;
		height = _height;
	}

	void draw()
	{
		glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(90, 0.0f, 1.0f, 0.0f);
		glRotatef(360 - angle, 1.0f, 0.0f, 0.0f);
		glLineWidth(1.0);
		glColor3f(0, 0, 0);
		GLUquadric* qobj = gluNewQuadric();
		gluQuadricNormals(qobj, GLU_SMOOTH);
		gluCylinder(qobj, radius, radius, height, 32, 32);
		glPopMatrix();
	}
};

CannonGun Gun(RADIUS,RADIUS,0, 60, RADIUS, 5);
Cannonball ball(Gun.height *cos(Gun.angle/180*M_PI) + Gun.x, Gun.height*sin(Gun.angle / 180 * M_PI) + Gun.y, 0, START_SPEED, Gun.angle, RADIUS);

void initGL() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}



void DrawGround(float size)
{

	glLineWidth(2.0);

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(size, 0, 0);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, size, 0);
	glEnd();

}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, depth);
	glRotatef(cameraAngleToRotateY, 1.0f, 0.0f, 0.0f);
	glRotatef(cameraAngleToRotateX, 0.0f, 1.0f, 0.0f);

	ball.draw(); Gun.draw();
	DrawGround(GROUND_SIZE);

	glutSwapBuffers();


}

void timer(int value) {

	ball.y = ball.startSpeed*sin((ball.startAngle) / 180 * M_PI)*time - G*time*time / 2 + ball.startPosY;
	if (ball.y >= 0) {
		ball.x = ball.startSpeed*cos((ball.startAngle) / 180 * M_PI)*time + ball.startPosX;
	}
	else {
		ball.y = 0;
	}
	time += 0.5;
	glutPostRedisplay();
	if (ball.y > 0 || time <= 1) {
		glutTimerFunc(refreshMills, timer, 0);
	}

}

void keyboardPress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case('a') : case('A') :
	{
					cameraAngleToRotateX += 5;
					break;
	}
	case('d') : case('D') :
	{
					cameraAngleToRotateX -= 5;
					break;
	}
	case('w') : case('W') :
	{
					cameraAngleToRotateY += 5;
					break;
	}
	case('s') : case('S') :
	{
					cameraAngleToRotateY -= 5;
					break;
	}
	case('q') : case('Q') :
	{
					depth -= 1;
					break;
	}
	case('e') : case('E') :
	{
					depth += 1;
					break;
	}case('u') : case('U') :
	{
		Gun.angle += 5;
		ball.x = Gun.height*cos(Gun.angle / 180 * M_PI) + Gun.x;
		ball.y = Gun.height*sin(Gun.angle / 180 * M_PI) + Gun.y;
		ball.startPosX = ball.x;
		ball.startPosY = ball.y;
		ball.startAngle = Gun.angle;
		break;
	}case('j') : case('J') :
	{
		Gun.angle -= 5;
		ball.x = Gun.height*cos(Gun.angle / 180 * M_PI) + Gun.x;
		ball.y = Gun.height*sin(Gun.angle / 180 * M_PI) + Gun.y;
		ball.startPosX = ball.x;
		ball.startPosY = ball.y;
		ball.startAngle = Gun.angle;
		break;
	}
	case(' ') :
	{
				  glutTimerFunc(0, timer, 0);
	}
	default:
		break;
	}
	glutPostRedisplay();
}


void reshape(GLsizei width, GLsizei height) {  
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Title");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardPress);
	initGL();
	glutMainLoop();
	return 0;
}