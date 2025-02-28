#pragma once

#ifndef Rectangle_h
#define Rectangle_h

#include "Ishape.h"

/*

	Definisati imutabilnu klasu Rectangle koja predstavlja pravougaonik u 2D prostoru koji je poravnat sa koordinatnim osama i koja isključivo implementira interfejs IShape.

	Klasa Rectangle treba da sadrži nestatičku metodu intersects(...) i istoimenu statičku metodu kojima se provjerava da li je presjek dva pravougaonika neprazan skup.
	Omogućiti skaliranje pravougaonika u odnosu na njegov centar korištenjem komutativne operacije za množenje skalarom.
	Definisati operator+ tako da zbir dva objekta tipa Rectangle predstavlja pravougaonik minimalne površine koji u 2D prostoru u potpunosti obuhvata oba pravougaonika predstavljena operandima.
	Omogućiti ispis objekta koji predstavlja pravougaonik, tako da se na izlazni tok ispišu koordinate centra i dužine stranica.

*/




class Rectangle : public IShape
{
	
protected:

	const double lenght, height;
	const double x1, x2, x3, x4, y1, y2, y3, y4;

public:

	Rectangle();

	Rectangle(const double, const double, const double, const double);


	double area() const override;

	bool pointInside(const double, const double) const override;


	bool Intersects(const Rectangle&) const;

	static bool Intersects(const Rectangle&, const Rectangle&);


	friend Rectangle operator*(const Rectangle&, const double);

	friend Rectangle operator*(const double, const Rectangle&);


	friend Rectangle operator+(const Rectangle&, const Rectangle&);


	// void printShape() const override;
};





#endif Rectangle_h