#include "Square.h"





Square::Square(const double l, const double x, const double y) : Rectangle(l, l, x, y) {}




Square operator*(const Square& objectS, const double alfa)
{
	Square result(objectS.lenght * alfa, objectS.x1, objectS.x2);

	return result;
}





Square operator*(const double alfa, const Square& objectS)
{
	Square result(objectS.lenght * alfa, objectS.x1, objectS.y1);

	return result;
}





Square operator+(const Square& a, const Square& b)
{
	double i, newLenght, newHorizontal, newVertical;


	if (a.x2 < b.x1)
	{
		for (i = a.x2; i <= b.x2; i += 0.1);

		newLenght = a.lenght + i;
		newHorizontal = a.x1;
		newVertical = a.y1;
	}

	else if (b.x2 < a.x1)
	{
		for (i = b.x2; i <= a.x2; i += 0.1);

		newLenght = b.lenght + i;
		newHorizontal = b.x1;
		newVertical = b.y1;
	}

	else if (a.x1 == b.x1)
	{
		if (a.lenght > b.lenght)
		{
			newLenght = a.lenght;
			newHorizontal = a.x1;
			newVertical = a.y1;
		}

		else
		{
			newLenght = b.lenght;
			newHorizontal = b.x1;
			newVertical = b.y1;
		}
	}


	Square result(newHorizontal, newHorizontal, newVertical);

	return result;
}