#include <iostream>
#include <cmath>

#define MAX 100											// Stepen polinoma je manji ili jednak broju 100 !

using namespace std;


class Polinom
{

	friend ostream& operator<<(ostream&, Polinom&);

public:

	Polinom(int);

	Polinom(double*, int);

	double operator()(double);

	Polinom& operator=(Polinom&);						//	Na ispitu, ako objekat neke klase kao polje ima pokazivac na dinamicki alociran memorijski blok, da ne bi doslo do PLITKOG kopiranja, 'konstruktor kopije i operator jednako' za tu klasu moramo EKSPLICITNO_SVOJERUCNO definisati !!!

	~Polinom() { delete[] koeficjenti; } 

private:

	int stepen;

	double* koeficjenti{};
};





Polinom::Polinom(int broj = 1)							// Parametri KORISNICKI DEFINISANOG PODRAZUMJEVANOG konstrktora moraju biti EKSPLICITNO inicijalizovani ! 
{
	stepen = (broj <= 0) ? 1 : broj;					// Od vrijednosti promjenjive stepen, zavisi velicina memorijskog bloka na koji pokazuje 'polje koeficjenti' .

	koeficjenti = new(double[stepen + 1]);				// Polinom stepena jednakog malom 'n' ima 'n+1' koeficjenata. Npr. P5(x) = a5X^5 + a4X^4 + a3X^3 + a2X^2 + a1X + a0...

	for (int i = stepen; i >= 0; i--)
		koeficjenti[i] = 0;								// U skladu sa tekstom zadatka svi koeficjenti moraju biti jednaki nuli. 
}





Polinom::Polinom(double* niz, int broj)		// Opcioni konstruktor(Moze ih biti vise od jednog!). Parametri opcionog konstruktora NE smiju biti eksplicitno inicijalizovani jer onda bi doslo do pobune ! Kompajler ne bih znao koji konstruktor je PODRAZUMJEVANI konstruktor. Npr. da sam inicijalizovao sve parametre ovog konstruktora, naredba Polinom p; bi prouzrokovala gresku.
{
	stepen = --broj;						// broj - predstavlja broj elemenata niza, ako niz ima recimo 3 elementa tada imamo 'polinom stepena 2',a takav polinom ima 3 koeficjenta !!!

	koeficjenti = new(double[stepen + 1]);	// Polinom stepena 'stepen' ima 'stepen + 1' koeficjenata !!!

	for (int i = stepen; i >= 0; i--)		// Idemo od 'vodeceg koeficjenta (to je koeficjent indeksa jednakog 'stepen')' ka slobodnom clanu (slobodan clan je polinom indeksa 0).
	{
		if (i == stepen && !niz[stepen])	// Ako je u 'niz' vodeci koeficjent jednak nuli, a mi definisemo polinom stepena --broj ,onda u skladu sa tekstom zadatka
			koeficjenti[i] = 1;				// vodeci koeficjent naseg novo_definisanog polinoma je jednak 1.
		else
			koeficjenti[i] = niz[i];		// Inicijalizacija koeficjenata
	}
}





double Polinom::operator()(double x)							// METODA kao rezultat vraca vrijednost polinoma(objekta koji je poziva) za tacku x.
{
	double rezultat = 0;										// Zbog sumiranja = 0;

	for (int i = stepen; i >= 0; i--)
		rezultat = rezultat + (koeficjenti[i] * pow(x, i));		// rezultat(na pocetku = 0) = rezultat + koeficjent[i](to je neki realan broj) * pow(x, i)_x=tacka_i=trenutni_stepen.
																// Funkcija 'pow' iz standradne biblioteke cmath broj x dize na stepen i
	return rezultat;
}





ostream& operator<<(ostream& izlaz, Polinom& polinom)
{
	int kontrolna = 0;										// Detektor nula polinoma.

	for (int i = polinom.stepen; i >= 0; i--)				// Prolazimo kroz sve koeficjente da bih prebrojali koliko je koeficjenata jednako nuli.		
		if (!polinom.koeficjenti[i])						// Svaki put kada je neki od koeficjenata jednak nuli,
			kontrolna++;									// inkrementujemo brojac.

	if (--kontrolna == polinom.stepen)						// Primjer i pojasnjenje zasto '--kontrolna'. Brojac ide od nula, a mi recimo imamo nula polinom 2.stepena. Taj polinom ima 3 koeficjenta ,a kako je svaki od koeficjenata jednak 0 to ce se brojac 'kontrolna' inkrementovati 3 puta. 'kontrolna = 3 ,stepen = 2' a kako su sva tri koeficjenta jednaka nuli --3 == 2 pa ovo jeste nula polinom.
		izlaz << 0;											// Ispisi nulu , jer nema smisla pisati 0X^n + 0X^n-1+......0X^0

	else																// Ako polinom koji poziva ovu funkciju, nije nula polinom !
	{
		for (int i = polinom.stepen; i >= 0; i--)						// Ispisujemo od vodeceg koeficjenta ka slobodnom clanu !
		{
			if (polinom.koeficjenti[i] > 0 && i > 1)					// Provjeravamo, da li ispred koeficjenta treba napisati '+' .
				izlaz << "+" << polinom.koeficjenti[i] << "X^" << i;

			else if (polinom.koeficjenti[i] < 0 && i > 1)
				izlaz << polinom.koeficjenti[i] << "X^" << i;

			else if (!polinom.koeficjenti[i] && i > 1)					// Ako je koeficjent uz X^n, n > 1 jednak nuli, preskoci ga pri ispisu. Nema smisla pisati +0X^15,16,17...
				izlaz << " ";

			else if (polinom.koeficjenti[i] > 0 && i == 1)				// Provjeravamo da li uz X^1=X imamo pozitivan koeficjent ispred kojeg treba dopisati znak '+'. 
				izlaz << "+" << polinom.koeficjenti[i] << "X";

			else if (polinom.koeficjenti[i] < 0 && i == 1)
				izlaz << polinom.koeficjenti[i] << "X";

			else if (!polinom.koeficjenti[i] && i == 1)					// Ako je uz X^1=X koeficjent 0, preskoci X pri ispisu polinoma.
				izlaz << " ";

			else if (polinom.koeficjenti[i] > 0 && !i)					// Provjeravamo da li ispred slobodnog clana treba napisati znak '+'
				izlaz << "+" << polinom.koeficjenti[i];

			else
				izlaz << polinom.koeficjenti[i];
		}
	}

	return izlaz;														// Ova funkcija kao rezultat mora da vrati referencu klase ostream !!!
}





Polinom& Polinom::operator=(Polinom& objekat)							// Da ne bih doslo do Plitkog kopiranja, recimo naredbe: Polinom p1, p2; p1 = p2; moramo definisati operator= za klasu Polinom !!! 
{
	if (this != &objekat)												// Prvo provjerimo da li je pozivaoc(this) ujedno i pozvani(&objekat). 
	{
		stepen = objekat.stepen;

		delete[] koeficjenti;											// Prije dereferenciranje OBAVEZNO oslobadjamo memorisjki blok !!!

		koeficjenti = new(double[stepen + 1]);

		for (int i = objekat.stepen; i >= 0; i--)
			koeficjenti[i] = objekat.koeficjenti[i];
	}

	return *this;														// Procitaj (Laslo Kraus...), referenca kao parametar/povrtana_vrijednost funkcije !!! 
}





class Integral
{

public:

	Integral() : A(0), B(0) {};											// Naredba 'Polinom polinom;' predstavlja definisanje objekta 'polinom' i poziv podrazumjevanog konstruktora klase 'Polinom'. Besmisleno je dodatno taj objekat set-ovati na NULAPOLINOM. Cak i da hocemo to da izvedemo moramo prvo definisati globalni objekat Polinom NULAPOLINOM...

	Integral(double, double, Polinom&);

	Polinom& getPolinom();

	operator double();

private:

	double A, B;

	Polinom polinom;
};





Integral::Integral(double x, double y, Polinom& p)
{
	A = x;

	B = y;

	polinom = p;												 // Ovde 'operator=' klase Polinom igra veliku ulogu. Umjesto plitkog imamo duboko kopiranje sto omogucava nesmetan rad programa bez padanja.
}





Polinom& Integral::getPolinom() { return this->polinom; }		// Objekat 'polinom' je private date_member klase Polinom. To znaci: 1. Ako bi povrtatni tip ovde metode (umjesto P&) bio 'Polinom' kopirao bi se 'polinom' objekat ,a tu kopiju bih odma pojeo Destructor klase Polinom ! 2. Nas scenario, posto je objekat 'polinom' private data member klase Polinom moze mu se pristupiti iskljucivo unutar te klase ili prijateljskom funkcijom/klasom te klase. Tako da ova metoda, definisana na ovakav nacin mi samo omogucava narednu...cout << I.getPolinom(); i ispise se sadrzaj tog polinoma. Greska bi bilo reci Polinom p1 = I1.getPolinom()...





Integral::operator double()										// Rezultat metode odstupa od ocekivanog, sa nekim od asistenata/profesora provjeri koncept/realizaciju ove ideje !!!
{
	double deltaX = abs(A - B), suma = 0;

	while (deltaX >= 0.0001)
	{
		suma += polinom(deltaX);

		deltaX /= 2;
	}

	return abs(suma);
}





class Skup
{
	friend int getCardinal(Skup&);

public:

	Skup(int);

	Skup(Skup&);

	int operator+=(Integral&);

	Integral& operator-();

	~Skup() { delete[] niz; }

private:

	int front;

	int stanje;

	int kapacitet;

public:

	Integral* niz{};
};





Skup::Skup(int broj = 1)
{
	front = 0;

	stanje = 0;

	kapacitet = (broj > 0) ? broj : 1;

	niz = new(Integral[kapacitet]);
}





Skup::Skup(Skup& skup)
{
	front = skup.front;

	kapacitet = skup.kapacitet;

	stanje = skup.stanje;

	niz = new(Integral[kapacitet]);

	for (int i = skup.front; i < skup.stanje; i++)		// Konsultacije, zasto for(int i = 0; i < skup.stanje; i++)... izbacuje WARNING ?
		niz[i] = skup.niz[i];
}





int Skup::operator+=(Integral& objekat)
{
	if (!stanje)
	{
		niz[stanje++] = objekat;

		return 1;
	}

	else if (stanje < kapacitet)
	{
		for (int i = 0; i < stanje; i++)
			if ((double)niz[i] == (double)objekat)
				return 0;

		niz[stanje++] = objekat;

		return 1;
	}

	else if (stanje == kapacitet)
	{
		Skup pom(*this);

		kapacitet *= 2;

		delete[] niz;

		niz = new(Integral[kapacitet]);

		for (int i = pom.front; i < pom.stanje; i++)			// Konsultacije, zasto for(int i = 0; i < pom.stanje; i++)... izbacuje WARNING ?
			niz[i] = pom.niz[i];								

		niz[stanje++] = objekat;

		return 1;
	}


	return 0;
}





Integral& Skup::operator-() { return this->niz[front++]; }		// Pazi, rezultat ove metode ne mozes pohraniti u neku promjenjivu !!! 





int getCardinal(Skup& skup)
{
	int rezultat = skup.stanje;
	return rezultat;
}






int main()
{
	int n, stepenPom;

	double** matricaDbl, A = 1, B = 5, maximum = 0;

	Polinom* nizPolinoma;

	Integral* nizIntegrala;

	Skup skup;

	do
	{
		cout << "Koliko polinoma (n > 1):";
		cin >> n;

		cout << "Stepen tih polinoma (0 < stepen < " << MAX << "): ";
		cin >> stepenPom;

	} while (n < 1 || stepenPom < 1 || stepenPom > MAX);





	stepenPom++;





	matricaDbl = new(double* [n]);		// Niz pokazivaca. Prostor za 'n' pokazivaca na 'double'
	nizPolinoma = new(Polinom[n]);
	nizIntegrala = new(Integral[n]);



	for (int i = 0; i < n; i++)
	{
		matricaDbl[i] = new(double[stepenPom]);

		cout << i + 1 << ". Polinom: " << endl;

		for (int j = stepenPom - 1; j >= 0; j--)
		{
			cout << "Koeficjent uz X^" << j << " ";
			cin >> matricaDbl[i][j];
		}

		Polinom polinom(matricaDbl[i], stepenPom);

		nizPolinoma[i] = polinom;

		cout << "Granice integracije: ";
		cin >> A >> B;

		Integral integral(A, B, nizPolinoma[i]);

		nizIntegrala[i] = integral;

		if ((double)nizIntegrala[i] > maximum)
			maximum = (double)nizIntegrala[i];

		skup += nizIntegrala[i];
	}


							

	cout << maximum << endl;

	for (int i = 0; i < n; i++)
		delete[] matricaDbl[i];

	delete[] matricaDbl;

	return 0;
}
/*

	double niz1[3] = { 2, 3, 1 }, niz2[3] = { -3, 0, 1 }, niz3[3] = { 4 , 1, 5 };

	Polinom p, p0, p1(niz1, 3), p2(niz2, 3), p3(niz3, 3);

	cout << "Polinomi p, p0, p1, p2 ,p3 redom: " << endl << p << endl << p0 << endl << p1 << endl << p2 << endl << p3 << endl;
	cout << "Njihove vrijednosti u tacki X = 1 redom: " << endl << p(1) << endl << p0(1) << endl << p1(1) << endl << p2(1) << endl << p3(1) << endl;

	Integral i, i0(1, 5, p0), i1(1, 5, p1), i2(1, 5, p2), i3(1, 5, p3);

	Skup s1, s2;

	Skup s3(s1);

	s1 += i;
	s1 += i0;
	s1 += i1;
	s1 += i2;
	s1 += i3;


	for (int i = 0; i < 5; i++)
		cout << (double)s1.niz[i] << endl;

	return 0;





*/