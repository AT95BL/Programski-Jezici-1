#include <iostream>
#include "Set.h"
#include "Rectangle.h"
#include "Square.h"




int main()
{   
	int array1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	ICollection<int>* ptr = new Set(10, array1);
	std::shared_ptr<ICollection<int>> ptr1, ptr2;

	*ptr += 11;
	*ptr += 12;
	*(*ptr += 13) += 14;

	(*ptr) + 144000;
    
	std::cout << "Pocetna kolekcija: " << std::endl;
	ptr->printCollection();
	std::cout << std::endl;

	ptr->searchForElements([](int X) {return X % 2; }, ptr1);
	ptr->filtrateElements([](int X){ return X % 2; }, ptr2);
	
	std::cout << "Rezultat pretrage: " << std::endl;
	ptr1->printCollection();
	std::cout << std::endl;


	std::cout << "Rezultat filtriranja: " << std::endl;
	ptr2->printCollection();
	std::cout << std::endl;

	std::cout << "Pocetna kolekcija nakon uklanjanja elemenata: " << std::endl;
	ptr->deleteElements([](int X) { return X % 2; });
	ptr->printCollection();

	
	
	Square x(5, 1, 1), y(6, 2, 2);

	

	

	return 0;
}