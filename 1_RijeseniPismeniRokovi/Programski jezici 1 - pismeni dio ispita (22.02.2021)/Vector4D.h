#pragma once

#ifndef Vector4D_h
#define Vector4D_h

#include "Vector3D.h"





class Vector4D : public Vector3D
{

public:

	void printSomething() const override;

private:

	double w;

public:

	Vector4D();
	Vector4D(const double, const double, const double, const double);
	//Vector4D(const Vector4D&);


	virtual double getX() const override;
	virtual double getY() const override;
	virtual double getZ() const override;
	double getW() const;


	friend Vector4D operator+(const Vector4D&, const Vector4D&);

	friend Vector4D operator*(const Vector4D&, const double);
	friend Vector4D operator*(const double, const Vector4D&);

	friend double operator*(const Vector4D&, const Vector4D&);


	bool operator==(const Vector4D&) const;


	Vector4D operator-()const;

	static Vector4D zeroPoint(const Vector4D&);
};





#endif Vector4D_h