#pragma once

#ifndef IShape_h
#define IShape_h
// #include <iostream>
/*

	Definisati interfejs IShape koji predstavlja zatvoreni geometrijski oblik i omogućava dobavljanje njegove površine. 
	Interfejs IShape treba da sadrži čistu virtuelnu metodu kojom se provjerava da li se tačka u 2D prostoru koja je parametar metode nalazi unutar 
	zatvorenog geometrijskog oblika predstavljenog objektom implementirajuće klase.

*/





class IShape
{

public:

	virtual double area() const = 0;

	virtual bool pointInside(const double, const double) const = 0;


	//virtual void printShape() const = 0;
};



#endif _Shape_h