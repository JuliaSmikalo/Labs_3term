#include "circle.h"
#include "iostream"
#include "vector"


using namespace std;

point4::point4(int _x, int _y) :x(_x), y(_y){};
point4::point4() :x(0), y(0){};

int point4::getX(){
	return x;
}
int point4::getY(){
	return y;
}

void point4::setX(int _x){
	x = _x;
	//return this;
}
void point4::setY(int _y){
	y = _y;
	//return this
}


int point4::X(){
	return getX();
}
int point4::Y(){
	return getY();
}

void point4::X(int _x){
	setX(_x);
}
void point4::Y(int _y){
	setY(_y);
}

void point4::reverseX(){
	x = -x;
}
void point4::reverseY(){
	y = -y;
}

point4::~point4(){}



circle4::circle4(int radius){
	R = radius;

	start();
}

void circle4::start(){
	d = -R / 2.0;
	X = 0;
	Y = R;
}


point4 circle4::getNextPoint4(){
	if (d<0){
		X = X + 1;
		d = d + X;
	}
	else {
		Y = Y - 1;
		d = d - Y;
	}
	return point4(X, Y);
}
bool circle4::hasNextPoint4(){
	return Y > 0;
}

vector<point4> circle4::getAllPoints(){
	vector<point4> points;
	point4 p;

	start();

	do{
		p = getNextPoint4();
		points.push_back(p);
	} while (hasNextPoint4());
	
	int size = points.size();
	for (int i = size - 1; i > 0; i--){
		p = points[i];
		p.reverseY();
		points.push_back(p);
	}
	for (int i = 2 * size - 2; i > size; i--){
		p = points[i];
		p.reverseX();
		points.push_back(p);
	}
	for (int i = size - 1; i >= 0; i--){
		p = points[i];
		p.reverseX();
		points.push_back(p);
	}
	points.push_back(points[0]);

	return points;
}

circle4::~circle4(){}