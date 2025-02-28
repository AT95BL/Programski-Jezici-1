#include "Vector2D.h"




Vector2D::Vector2D() {}
Vector2D::Vector2D(const double x, const double y) : Vector3D(x, y, 0) {}





double Vector2D::getX() const
{
	return Vector3D::getX();
}

double Vector2D::getY() const
{
	return Vector3D::getY();
}





void Vector2D::printSomething() const
{
	std::cout << "(" << getX() << ", " << getY() << ")" << std::endl;
}





Vector2D operator+(const Vector2D& a, const Vector2D& b)
{
	Vector2D res(a.getX() + b.getX(), a.getY() + b.getY());

	return res;
}





Vector2D operator*(const Vector2D& v, const double alfa)
{
	Vector2D res(v.getX() * alfa, v.getY() * alfa);

	return res;
}





Vector2D operator*(const double alfa, const Vector2D& v)
{
	Vector2D res(v.getX() * alfa, v.getY() * alfa);

	return res;
}





bool Vector2D::operator==(const Vector2D& other) const
{
	if ((this->getX() == other.getX()) && (this->getY() == other.getY()))
		return true;

	return false;
}





Vector3D::operator Vector2D() const
{
	Vector2D res(this->x, this->y);

	return res;
}





double operator*(const Vector2D& a, const Vector2D& b)
{
	Vector3D v1 = (Vector2D)a;
	Vector3D v2 = (Vector2D)b;

	return (v1 * v2);
}





Vector2D Vector2D::zeroPoint(const Vector2D& other)
{
	Vector2D zero2(0, 0);

	return zero2;
}