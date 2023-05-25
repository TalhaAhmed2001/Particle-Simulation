#include "particle.h"

using namespace std;

void particle::setPath() {
	/*switch (rand() % 13) {
	case 0:
		path = "images/particle0.png";
		break;
	case 1:
		path = "images/particle1.png";
		break;
	case 2:
		path = "images/particle2.png";
		break;
	case 3:
		path = "images/particle3.png";
		break;
	case 4:
		path = "images/particle4.png";
		break;
	case 5:
		path = "images/particle5.png";
		break;
	case 6:
		path = "images/particle6.png";
		break;
	case 7:
		path = "images/particle7.png";
		break;
	case 8:
		path = "images/particle8.png";
		break;
	case 9:
		path = "images/particle9.png";
		break;
	case 10:
		path = "images/particle10.png";
		break;
	case 11:
		path = "images/particle11.png";
		break;
	case 12:
		path = "images/particle12.png";
		break;
	}*/
}

int particle::getXVec() {
	return x_vec;
}

int particle::getYVec() {
	return y_vec;
}

float particle::getX() {
	return x;
}

int particle::getColor()
{
	return color;
}

float particle::getY() {
	return y;
}

void particle::setX(float X) {
	x = X;
	rect.x = X;

	if (getX() < 0) {
		setXVec(-getXVec());
		setX(0);
	}
	else if (getX() + size > 720) {
		setXVec(-getXVec());
		setX(720-size);
	}
}

void particle::setY(float Y) {
	y = Y;
	rect.y = Y;

	if (getY() < 0) {
		setYVec(-getYVec());
		setY(0);
	}
	else if (getY() + size > 720) {
		setYVec(-getYVec());
		setY(720-size);
		//setYVec(0);
	}
}

void particle::setXVec(int X_vec) {
	x_vec = X_vec;
}

void particle::setYVec(int Y_vec) {
	y_vec = Y_vec;
}

void particle::bounce() {
	int x_0 = getXVec();
	int y_0 = getYVec();
	setXVec(-1 * getXVec());
	setYVec(-1 * getYVec());

	setX(getX() + 1.5 * speed * getXVec());
	setY(getY() + 1.5 * speed * getYVec());

	//cout << "x = " << x_0 << ", " << getXVec() << "y = " << y_0 << ", " << getYVec() << "\n";
}

void particle::bounce(int x_vec, int y_vec) {
	
	setXVec(x_vec);
	setYVec(y_vec);

	setX(getX() + 1.5 * speed * getXVec());
	setY(getY() + 1.5 * speed * getYVec());

	//cout << "x = " << x_0 << ", " << getXVec() << "y = " << y_0 << ", " << getYVec() << "\n";
}

string particle::getPath() {
	return path;
}

void particle::move() {
	setX(getX() + speed * getXVec());
	setY(getY() + speed * getYVec());
	//setY(getY() + 2);
	//setYVec(getYVec() -  0.01 * abs(getYVec()));
}

bool particle::detCollision(int x0, int y0, int x1, int y1) {
	x0 = x0 + size/2;
	x1 = x1 + size/2;
	y0 = y0 + size/2;
	y1 = y1 + size/2;

	int eucliddist = (int)sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));
	if (eucliddist <= (size)) {
		//cout << "ed = " << eucliddist << "\n";
		return true;
	}
	return false;

}

SDL_Rect particle::getRect() {
	return rect;
}
