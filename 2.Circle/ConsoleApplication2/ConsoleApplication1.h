#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <vector>

class point{
private:
	int x, y;
	int getX();
	int getY();
	void setX(int _x);
	void setY(int _y);
public:
	point(int _x, int _y) :x(_x), y(_y){};
	point() :x(0), y(0){};
	int X();
	int Y();
	void X(int _x);
	void Y(int _y);
	void reverseX();
	void reverseY();
};

class circle4{
private:
	int R;
	int X;
	int Y;
	
	float d;

	void start();
public:
	circle4(int radius);
	point getNextPoint();
	bool hasNextPoint();
};
#endif