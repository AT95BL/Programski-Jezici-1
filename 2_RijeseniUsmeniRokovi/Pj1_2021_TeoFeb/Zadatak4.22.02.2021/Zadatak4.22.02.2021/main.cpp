#include <iostream>

/*
	Za 'operator<<' vrlo je vazno znati da razlikujemo 2 slucaja, a to su:

	1. 'operator<<' za ulancano ispisivanje podataka na standardni izlaz, recimo std::cout<< "Moje ime je" <<std::endl;
    2. 'operator<<' kao unarni operator LEFT_SHIFT koji sve bitove POSTOJECEG tekuceg objekta pomjera u lijevo
	                za broj CJELOBROJNIH pozicija naveden sa desne strane istog operatora.
					Takvi podatci mogu biti signed/unsigned sto sada trenutno nije ni bitno...

*/





class MyComplexNumber
{

private:

	double x, y;

public:

	MyComplexNumber(const int a, const int b)
	{
		x = a;
		y = b;
	}

	// Operator ulancanog pozivanja za ispis se najcesce realizuje kao prijateljska funkcija .
	friend std::ostream& operator<<(std::ostream& out, MyComplexNumber& nmb) // Obratiti paznju std::ostream& je povratni tip, a metoda kao argument zbog std::ostream& prihvata POSTOJECI objekat klase 'ostream' tako da 'out' postaje nadimak za 'cout' !
	{
		if (!nmb.x && !nmb.y)
			out << 0;

		else if (nmb.x && !nmb.y)
			out << nmb.x;

		else if (!nmb.x && nmb.y)
			out << nmb.y << "i";

		else if (!nmb.x && (nmb.y == 1))
			out << "i";

		else if (!nmb.x && (nmb.y == -1))
			out << "-i";

		else if (nmb.x && (nmb.y == 1))
			out << nmb.x << " + i";

		else if (nmb.x && (nmb.y == -1))
			out << nmb.x << " - i";

		else if (nmb.x && (nmb.y > 0))
			out << nmb.x << " + " << nmb.y << "i";

		else if (nmb.x && (nmb.y < 0))
			out << nmb.x << " - " << -1 * nmb.y << "i";
			
		return out;										// Povratna vrijednost koja nikako ne smije biti zanemarena ! Ona omugacava lancano pozivanje.
	}
};		// Prostorno-vremenski skup ali jako ilustrativan primjerak. Za ispit predlazem recimo class myGravity{ const g = 9.81; public()... }





class MyIntForIlustration
{
private:

	int myNumber;

public:

	MyIntForIlustration(const int nmb)
	{
		myNumber = nmb;
	}


	bool operator<<(int nmb)
	{
		while (nmb)
		{
			myNumber *= 2;
			nmb--;
		}

		return true;
	}

};




int main()
{
	MyComplexNumber zero(0, 0), z1(5, 0), z2(0, 5);
	MyComplexNumber z3(10, 15), z4(-10, 15), z5(10, -15), z6(-25, -30);

	std::cout << zero << std::endl;
	std::cout << z1 << std::endl << z2 << std::endl;
	std::cout << z3 << std::endl << z4 << std::endl << z5 << std::endl << z6 << std::endl;	// Lancano pozivanje.

	MyIntForIlustration nmb(2021);

	std::cout << (nmb << 2) << std::endl;
}