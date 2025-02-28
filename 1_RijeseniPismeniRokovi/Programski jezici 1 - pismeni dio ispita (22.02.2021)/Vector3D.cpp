#include "Vector3D.h"





void Vector3D::printSomething() const
{
	std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}





Vector3D::Vector3D()
{
	x = y = z = 0;
}





Vector3D::Vector3D(const double i, const double j, const double k)
{
	x = i;

	y = j;

	z = k;
}





Vector3D::Vector3D(const Vector3D& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}





Vector3D operator+(const Vector3D& a, const Vector3D& b) 
{
	Vector3D newV(a.x + b.x, a.y + b.y, a.z + b.z);

	return newV;
}





Vector3D operator*(Vector3D& v, const double alfa)
{
	Vector3D newV(v.x * alfa, v.y * alfa, v.z * alfa);

	return newV;
}




Vector3D operator*(const double alfa, Vector3D& v)
{
	Vector3D newV(v.x * alfa, v.y * alfa, v.z * alfa);

	return newV;
}





double pointDIstance(const double x, const double y)
{
	return sqrt((y - x) * (y - x));
}





double operator*(const Vector3D& A, const Vector3D& B)
{
	double r1, r2, r3;

	r1 = (pointDIstance(A.x, 0) + pointDIstance(A.y, 0) + pointDIstance(A.z, 0)); 
	r2 = (pointDIstance(B.x, 0) + pointDIstance(B.y, 0) + pointDIstance(B.z, 0));


	r3 = (A.x * B.x + A.y * B.y + A.z * B.z); // Ima predznak.
	r3 = r3 / (r1 * r2);

	return (r1 * r2 * r3);

}





Vector3D&  Vector3D::operator-()
{
	this->x *= (-1);
	this->y *= (-1);
	this->z *= (-1);

	return *this;
}





bool Vector3D::operator==(const Vector3D& other) const
{
	if ((this->x == other.x) && (this->y == other.y) && (this->z == other.z))
		return true;

	return false;
}





Vector3D Vector3D::zeroPoint(Vector3D& thisOne)
{
	Vector3D zero;

	return zero;
}





double Vector3D::getX() const { return this->x; }
double Vector3D::getY() const { return this->y; }
double Vector3D::getZ() const { return this->z; }