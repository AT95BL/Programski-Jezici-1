#include "Vector4D.h"





Vector4D::Vector4D()
{
	Vector3D::Vector3D(0, 0, 0);
	w = 0;
}





Vector4D::Vector4D(const double i, const double j, const double k, const double h):Vector3D(i, j, k)
{
	
	w = h;
}





void Vector4D::printSomething() const
{
	Vector3D v3(*this);

	std::cout << "(" << v3.x << ", " << v3.y << ", " << v3.z << ", " << w << ")" << std::endl;
}





double Vector4D::getX() const
{
	return Vector3D::getX();
}

double Vector4D::getY() const
{
	return Vector3D::getY();
}

double Vector4D::getZ() const
{
	return Vector3D::getZ();
}

double Vector4D::getW() const
{
	return this->w;
}





Vector4D operator+(const Vector4D& a, const Vector4D& b)
{
	Vector4D res(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ(), a.w + b.w);

	return res;
}





Vector4D operator*(const Vector4D& v, const double alfa)
{
	Vector4D res(v.getX() * alfa, v.getY() * alfa, v.getZ() * alfa, v.w * alfa);

	return res;
}


 


Vector4D operator*(const double alfa, const Vector4D& v)
{
	Vector4D res(v.getX() * alfa, v.getY() * alfa, v.getZ() * alfa, v.w * alfa);

	return res;
}





double pointDIstanceNew(const double x, const double y)
{
	return sqrt((y - x) * (y - x));
}





double operator*(const Vector4D& a, const Vector4D& b)
{
	double r1, r2, r3;

	r1 = pointDIstanceNew(a.getX(), 0) + pointDIstanceNew(a.getY(), 0) + pointDIstanceNew(a.getZ(), 0) + pointDIstanceNew(a.getW(), 0);
	r2 = pointDIstanceNew(b.getX(), 0) + pointDIstanceNew(b.getY(), 0) + pointDIstanceNew(b.getZ(), 0) + pointDIstanceNew(b.getW(), 0);

	r3 = a.getX() * b.getX() + a.getY() * b.getY() + a.getZ() * b.getZ() + a.getW() * b.getW();
	r3 /= (r1 * r2);

	return (r1 * r2 * r3);
}





bool Vector4D::operator==(const Vector4D& other) const
{
	if ((this->getX() == other.getX()) && (this->getY() == other.getY()) && (this->getZ() == other.getZ()) && (this->getW() == other.getW()))
		return true;

	return false;
}





Vector3D::operator Vector4D() const
{
	Vector4D res(this->x, this->y, this->z, 0);

	return res;
}





Vector4D Vector4D::operator-() const
{
	return (-1 * (*this));
}





Vector4D Vector4D::zeroPoint(const Vector4D& other)
{
	Vector4D zero4(0, 0, 0, 0);

	return zero4;

}