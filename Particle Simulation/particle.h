#pragma once
#include <stdlib.h>
#include <iostream>
#include <SDL.h>

using namespace std;

class particle
{
private:
	float x;
	float y;
	float x_vec;
	float y_vec;
	float speed = 0;
	SDL_Rect rect;
public:
	particle(float X, float Y) {
		x = X;
		y = Y;
		x_vec = rand() % 5;
		y_vec = rand() % 5;
		rect.x = X;
		rect.y = Y;
		rect.w = 32;
		rect.h = 32;
	}

	float getX();
	float getY();
	SDL_Rect getRect();

	void move();
	void bounce();

	bool isCollision();

};

