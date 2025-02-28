#include <iostream>
#include <cstring>
#pragma warning(disable : 4996)



class Osnovna
{

public:

	virtual void print() const = 0;		// Klasa 'Osnovna' je apstraktna !
	virtual ~Osnovna() {}						
};





class Izvedena1 : public Osnovna
{
private:

	char* ptr1;

public:

	Izvedena1() { ptr1 = new(char[strlen("This is LinuxLand in a silent nights ") + 1]); strcpy(ptr1, "This is LinuxLand in a silent nights "); }

	virtual void print() const override
	{
		std::cout << ptr1;
	}

	~Izvedena1() { delete[] ptr1; std::cout << "I1" << std::endl; }
};





class Izvedena2 : public Osnovna
{
	char* ptr1;

public:

	Izvedena2() { ptr1 = new(char[strlen("you can hear the Windows machines rebooting.") + 1]); strcpy(ptr1, "you can hear the Windows machines rebooting."); }

	virtual void print() const override
	{
		std::cout << ptr1;
	}

	~Izvedena2() { delete[] ptr1; std::cout << "I2" << std::endl; }
};





int main()
{
	Osnovna* other[2];

	other[0] = new Izvedena1;
	other[1] = new Izvedena2;

	other[0]->print();
	other[1]->print();

	delete other[0];
	std::cout << std::endl;
	delete other[1];

	return 0;
}