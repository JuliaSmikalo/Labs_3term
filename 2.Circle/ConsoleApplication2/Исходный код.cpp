#include <glut.h>
#include "circle.h"

void display() 
{ 
	glClear(GL_COLOR_BUFFER_BIT); 
	glColor3f(0,0,1); 

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 800, 0.0, 600);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(400, 300, 0);

	circle4 c = circle4(100);
	point4 p;
	std::vector<point4> points = c.getAllPoints();
	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
	/*
	do{
		p = c.getNextPoint4();
		glVertex2f(p.X(), p.Y());	
	} while (c.hasNextPoint4());
	*/

	do{
		p = points.back();
		points.pop_back();
		glVertex2f(p.X(), p.Y());
	} while (!points.empty());

	glEnd();

	glFlush(); 
	glutSwapBuffers();
}

int main(int argc, char **argv) 
{ 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(800, 600); 
	glutInitWindowPosition(100, 143);
	glutCreateWindow("Круг"); 
	glClearColor(1.0, 1.0, 1.0, 1.0); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluOrtho2D(0.0, 800, 0.0, 600); 
	glutDisplayFunc(display); 
	glutMainLoop(); 
}
