#pragma once

#ifndef Vector2D_h
#define Vector2D_h

#include "Vector3D.h"





class Vector2D : public Vector3D
{

public:

	void printSomething() const override;

public:

	Vector2D();
	Vector2D(const double, const double);


	virtual double getX() const override;
	virtual double getY() const override;

	friend Vector2D operator+(const Vector2D&, const Vector2D&);

	friend Vector2D operator*(const Vector2D&, const double);
	friend Vector2D operator*(const double, const Vector2D&);

	friend double operator*(const Vector2D&, const Vector2D&);

	bool operator==(const Vector2D&) const;

	static Vector2D zeroPoint(const Vector2D&);

};






#endif Vector2D_h