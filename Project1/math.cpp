#include "math.h"

Math::Vector::Vector(double x, double y) {
	this->x = x;
	this->y = y;
}

Math::Vector::Vector(SDL_Point point1, SDL_Point point2) {
	this->x = point2.x - point1.x;
	this->y = point2.y - point1.y;
}

void Math::Vector::normalize() {
	int len = getDistance();
	if (len != 0) {
		x /= len;
		y /= len;
	}
}

double Math::Vector::getX() const {
	return x;
}

double Math::Vector::getY() const {
	return y;
}

void Math::Vector::setX(double val) {
	x = val;
}

void Math::Vector::setY(double val) {
	y = val;
}

double Math::Vector::getDistance() {
	return sqrt(x * x + y * y);
}

Math::Vector Math::Vector::operator+(const Math::Vector& other) {
	return Math::Vector(x + other.x, y + other.y);
}

Math::Vector Math::Vector::operator-(const Math::Vector& other) {
	return Math::Vector(x + other.x, y + other.y);
}

double Math::Vector::operator*(const Math::Vector& other) {
	return x * other.x + y * other.y;
}

Math::Vector Math::Vector::operator*(double scalar) {
	return Math::Vector(x * scalar, y * scalar);
}

Math::Vector Math::Vector::operator/(double scalar) {
	return Math::Vector(x / scalar, y / scalar);
}

