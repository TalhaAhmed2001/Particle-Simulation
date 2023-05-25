#pragma once
#include <stdlib.h>
#include <iostream>
#include <SDL.h>
#include <stdio.h>
using namespace std;

class particle
{
private:
	float x;
	float y;
	int x_vec = 50 - rand() % 100;
	int y_vec = 50 - rand() % 100;
	float speed = 0.1;
	SDL_Rect rect;
	int size = 8;
	int color;
public:
	string path = "images/particle0.png";
	void setPath();
	particle(float X, float Y) {
		x = X;
		y = Y;
		/*x_vec = 5 - (rand() % 10);
		y_vec = 5 - (rand() % 10);*/
		rect.x = X;
		rect.y = Y;
		rect.w = size;
		rect.h = size;
		color = rand() % 3;
		cout << "x_vec = " << x_vec << " , y_vec = " << y_vec << "\n";
		//setPath();
		//cout << path << "\n";
	}

	void setX(float X);
	void setY(float Y);

	void setXVec(int X_vec);
	void setYVec(int Y_vec);
	
	float getX();
	float getY();

	int getColor();

	int getXVec();
	int getYVec();

	SDL_Rect getRect();

	void move();
	void bounce();
	void bounce(int x_vec, int y_vec);

	string getPath();
	bool detCollision(int x0, int y0, int x1, int y1);

};

