#pragma once
#include <stdlib.h>
class particle
{
private:
	float x;
	float y;
	float x_vec;
	float y_vec;
	float speed = 0;
public:
	particle(float X, float Y) {
		x = X;
		y = Y;
		x_vec = rand() % 5;
		y_vec = rand() % 5;
	}

	float getX();
	float getY();

	void move();
	void bounce();

	bool isCollision();

};

