#pragma once
#include <iostream>
#include <SDL.h>

namespace Math {
	class Vector {
	private:
		double x, y;
	public:
		Vector(double x = 0.0, double y = 0.0);
		Vector(SDL_Point point1, SDL_Point point2);

		double getX() const;
		double getY() const;

		void setX(double val);
		void setY(double val);

		double getDistance();

		Vector operator+(const Vector& other);
		Vector operator-(const Vector& other);
		double operator*(const Vector& other);

		// scalar operations

		Vector operator*(double scalar);
		Vector operator/(double scalar);

		friend std::ostream& operator << (std::ostream& os, const Vector& v) {
			os << "(" << v.x << "," << v.y << ")" << std::endl;
			return os;
		}
	};
}
