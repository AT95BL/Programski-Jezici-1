#pragma once
#ifndef  Square_h
#define Square_h

#include "Rectangle.h"





class Square : virtual public Rectangle
{

public:

	Square(const double, const double, const double);

		
	friend Square operator*(const Square&, const double);	// Jer prijateljstvo nije nasljedno !

	friend Square operator*(const double, const Square&);   // Jer prijateljstvo nije nasljedno !

	friend Square operator+(const Square&, const Square&);	// Jer prijateljstvo nije nasljedno !

	
};


#endif // ! Square_h
