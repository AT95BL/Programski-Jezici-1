#include "Rectangle.h"





Rectangle::Rectangle() :lenght(0), height(0), x1(0), x2(0), x3(0), x4(0), y1(0), y2(0), y3(0), y4(0) {}





Rectangle::Rectangle(const double l, const double h, const double x, const double y)
	:lenght(l), height(h),
	x1(x), x2(x + l), x3(x), x4(x + l),
	y1(y), y2(y), y3(y + h), y4(y + h) {};





double Rectangle::area() const 
{
	return (this->lenght) * (this->height);
}





bool Rectangle::pointInside(const double x, const double y) const
{
	if (x >= this->x1 && x <= this->x2 && y >= this->y1 && y <= this->y3)
		return false;

	return true;
	
}





bool Rectangle::Intersects(const Rectangle& objectR) const
{
	
	bool result = false;

	for(double i = this->x1; i <= this->x2; i += 0.1)
		for (double j = this->y1; j <= this->y3; j += 0.1)
		{

			result = objectR.pointInside(i, j);

			if (result)
				return true;
		}

	return false;
}





/*static*/ bool Rectangle::Intersects(const Rectangle& a, const Rectangle& b)
{
	bool result = false;

	for(double i = a.x1; i <= a.x2; i += 0.1)
		for (double j = a.y1; j <= a.y3; j += 0.1)
		{
			result = b.pointInside(i, j);

			if (result)
				return true;
		}

	return false;
}




Rectangle operator*(const Rectangle& objectR, const double alfa)
{
	Rectangle result(objectR.lenght * alfa, objectR.height * alfa, objectR.x1, objectR.y1);

	return result;
}





Rectangle operator*(const double alfa, const Rectangle& objectR)
{
	Rectangle result(objectR.lenght * alfa, objectR.height * alfa, objectR.x1, objectR.y1);

	return result;
}





Rectangle operator+(const Rectangle& o1, const Rectangle& o2)
{
	double newLenght = 0, newHeight = 0, newHorizontal = 0, newVertical = 0;
	double i, j;

	if (o1.x2 < o2.x1)										// Stolovi su udaljeni, object1 je lijevo od object2,
	{
		for (i = o1.x2; i <= o2.x2; i += 0.1);				// racunamo rastojanje od desne ivice prvog stola do kraja drugog stola.

		newLenght = o1.lenght + i;							// (sirina prvog stola) + (taj razmak + sirina drugog stola) = (sirina novog stola).
		newHorizontal = o1.x1;								
	}

	else if(o1.x1 > o2.x2)									// Stolovi su udaljeni, object2 je lijevo od object1,
	{
		for (i = o2.x2; i <= o1.x2; i += 0.1);				// racunamo rastojanje od desne ivice drugog stola do kraja prvog stola.

		newLenght = o2.lenght + i;							// (sirina prvog stola) + (taj razmak + sirina drugog stola) = (sirina novog stola).
		newHorizontal = o2.x2;
	}

	else if (o1.x1 == o2.x2)								// Stolovi se podudaraju,
	{
		if (o1.lenght >= o2.lenght)							// pri cemu je prvi stol siri od drugog, to jeste u 2D drugi stol je uvucen u prvi stol.
		{
			newLenght = o1.lenght;
			newHorizontal = o1.x1;
		}
		else												// Pri cemu je prvi stol uvucen u drugi stol.
		{
			newLenght = o2.lenght;						
			newHorizontal = o2.x1;
		}
	}

	
	if (o1.y3 < o2.y1)										// Prvi stol je ispod drugog stola,
	{
		for (j = o1.y3; j <= o2.y3; j += 0.1);				// racunamo/mjerimo rastojanje od gornje lijeve ivice prvog stola do gornje lijeve ivice drugog stola.

		newHeight = o1.height + j;							// (visina prvog stola) + (rastojanje izmedju stolova) + (visina drugog stola) = visina rezultata.
		newVertical = o1.y1;
	}
	
	else if (o1.y1 > o2.y3)									// Prvi stol je iznad drugog stola,
	{
		for (j = o2.y3; j <= o1.y3; j += 0.1);				// racunamo/mjerimo rastojanje od gornje lijeve ivice drugog stola do gornje lijeve ivice prvog stola.

		newHeight = o2.height + j;							// ...
		newVertical = o2.y1;
	}

	else if (o1.y1 == o2.y2)								// Ako su stolovi uvuceni jedan u drugi.
	{
		if (o1.height >= o2.height)
		{
			newHeight = o1.height;
			newVertical = o1.y1;
		}
		else
		{
			newHeight = o2.height;
			newVertical = o2.y1;
		}
	}


	Rectangle result(newLenght, newHeight, newHorizontal, newVertical);


	return result;
}