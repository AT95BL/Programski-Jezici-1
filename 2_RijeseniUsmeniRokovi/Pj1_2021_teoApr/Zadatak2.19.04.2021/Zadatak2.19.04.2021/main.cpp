#include <iostream>

using namespace std;

class RedniBroj
{
	
private:

	const int serialNumber;

public:

	RedniBroj(const int x) : serialNumber(x) {}

	void printSN()
	{
		cout << serialNumber << "." << endl;
	}
};
/*
	Iz definicije gornje klase vidimo da ista ima konstantan atribut, a to je 'const int serialNumber'.
	Prema principima OOP, prilikom kreiranja novog objekta '-instance neke klase' poziva se odgovarajuca
	posebna metoda 'Constructor' te klase koja automatski taj objekat pretvara u inteligentan komad memorijskog prostora.

	Napominjem da sve navedeno u ovom tekstu vazi i za sablonske klase !!!

	Naime, u programskom jeziku C++, konstantni atributi objekta se inicijalizuju operatorom koji nazivamo
	inicijalizator ':' i inicijalizacija tih konstantnih atributa se vrsi tako sto se nakon navodjenja 
	argumenata konstruktora -tj.parametara omedjenih sa parom zagrada () redom navode -inicijalizator-(vrijednost
	koja ce biti pridruzena konstantnom atributu)-definicija metode omedjena sa parom zagrada {}. Vidjeti 'line 14'.

	Takodje napominjem da se atributi objekta ne-okarakterisani sa specifikatorom 'const' mogu inicijalizovati
	upotrebom inicijalizatora ':' - naravno sve u sklopu definicije odgovarajuce Constructor-ske metode.

	Pri radu sa objektima koji posjeduju konstantne atribute treba biti pazljiv, narocito pri izvodjenju
	razlicitih matematickih,logickih...operacija.
	Recimo za 'line 46' naredba b = a; dovela bih do fatalne greske jer nemamo pravo mjenjati konstantan atribut/objekat.

	Konstantni atributi se inicijalizuju samo prilikom kreiranja novog objekta jer u protivnom ne bi imalo smisla
	iste okarakterisati sa 'const' .
*/




int main(void)
{
	RedniBroj a(1), b(2);

	a.printSN();

	return 0;
}
