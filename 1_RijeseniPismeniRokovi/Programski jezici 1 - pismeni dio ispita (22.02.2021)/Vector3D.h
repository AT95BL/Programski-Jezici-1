#pragma once

#ifndef Vector3D_h
#define Vector3D_h

#include "IPrintable.h"
#include <cmath>



class Vector4D;
class Vector2D;

class Vector3D : public IPrintable
{
	friend class Vector4D;
	friend class Vector2D;

public:

	virtual void printSomething()const override;


private:

	double x, y, z;

public:

	Vector3D();
	Vector3D(const double, const double, const double);
	Vector3D(const Vector3D&);


	friend Vector3D operator+(const Vector3D&, const Vector3D&);

	friend Vector3D operator*(Vector3D&, const double);
	friend Vector3D operator*(const double, Vector3D&);

	friend double  operator*(const Vector3D&, const Vector3D&);
	

	Vector3D& operator-();


	virtual bool operator==(const Vector3D&) const;


	static Vector3D zeroPoint(Vector3D&);


	virtual double getX() const;
	virtual double getY() const;
	virtual double getZ() const;

	operator Vector4D() const;
	operator Vector2D() const;

};





#endif Vector3D_h