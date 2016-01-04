#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <vector>

class point4{
private:
	int x, y;
	int getX();
	int getY();
	void setX(int _x);
	void setY(int _y);
public:
	point4(int _x, int _y);
	point4();
	int X();
	int Y();
	void X(int _x);
	void Y(int _y);
	void reverseX();
	void reverseY();
	~point4();
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
	point4 getNextPoint4();
	bool hasNextPoint4();
	std::vector<point4> getAllPoints();
	~circle4();
};
#endif