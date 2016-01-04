// ConsoleApplication1.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
//
#include "ConsoleApplication1.h"
#include "iostream"
#include "vector"


using namespace std;

int point::getX(){
	return x;
}
int point::getY(){
	return y;
}

void point::setX(int _x){
	x = _x;
	//return this;
}
void point::setY(int _y){
	y = _y;
	//return this
}

point::point(int _x, int _y) :x(_x), y(_y){};
point::point() :x(0), y(0){};

int point::X(){
	return getX();
}
int point::Y(){
	return getY();
}

void point::X(int _x){
	setX(_x);
}
void point::Y(int _y){
	setY(_y);
}

void point::reverseX(){
	x = -x;
}
void point::reverseY(){
	y = -y;
}






void circle4::start(){
	d = -R / 2.0;
	X = 0;
	Y = R;
}

circle4::circle4(int radius){
	R = radius;

	start();
}

point circle4::getNextPoint(){
	if (d<0){
		X = X + 1;
		d = d + X;
	}
	else {
		Y = Y - 1;
		d = d - Y;
	}
	return point(X, Y);
}
bool circle4::hasNextPoint(){
	return Y > 0;
}
/*
vector<point> circle4::getAllPoints(){
	vector<point> points;
	point p;

	start();

	do{
		p = getNextPoint();
		points.push_back(p);

		p.reverseX();
		points.push_back(p);

		p.reverseY();
		points.push_back(p);

		p.reverseX();
		points.push_back(p);
	} while (hasNextPoint());

	return points;
}
*/

