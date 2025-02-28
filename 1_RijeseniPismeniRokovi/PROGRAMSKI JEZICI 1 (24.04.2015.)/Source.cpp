#include <iostream>
#include <cstring>
#include <fstream>

#pragma warning(disable:4996)

using namespace std;





class NebeskoTijelo
{
	friend ostream& operator<<(ostream&, NebeskoTijelo&);

public:

	NebeskoTijelo(double, double, char*);
	~NebeskoTijelo();

	void print(ostream&, int);

	virtual void ispisi(ostream&, int);

	bool operator<(NebeskoTijelo&);

	NebeskoTijelo& operator=(NebeskoTijelo&);

private:

	double masa;
	double poluprecnik;

	char* naziv;
};





NebeskoTijelo::NebeskoTijelo(double m = 0, double r = 0, char* str = NULL)								// Definicija podrazumjevanog konstruktora klase 'NebeskoTijelo'. 
{
	masa = m;

	poluprecnik = r;

	if (str)																							// Pazi, strlen(),strstr()...zaustavljaju rad programa ako je jedan od argumenata 'NULL' pokazivac.
	{
		naziv = new(char[strlen(str) + 1]);
		strcpy(naziv, str);

	}

	else naziv = NULL;
}





NebeskoTijelo::~NebeskoTijelo()																			// Definicija destruktora klase 'NebeskoTijelo' .
{
	delete[] naziv;
}





ostream& operator<<(ostream& izlaz, NebeskoTijelo& objekat)												// Kod preklapanja 'operator<<' vodi racuna o tome da '<<' moze biti i binarni operator 'left_shift'. 'izlaz' je samo drugo ime za 'cout' pa kada metoda kao rezultat vrati originalan 'cout' u originalan 'cout' taj cout koji je prihvatio rezultat podesava svoje atribute i ispisuje iste na standardni izlaz.
{
	izlaz << objekat.naziv << " " << objekat.masa << "[kg] " << objekat.poluprecnik << "[km]" << endl;

	return izlaz;
}





void NebeskoTijelo::print(ostream& izlaz, int sirina)													// 'izlaz' je samo drugo ime za objekat 'cout' 
{
	izlaz.width(sirina);																				//	pa ova naredba podesava atribut 'sirina ispisa <=> width' objekta 'cout'. Dakle, pri ispisu podataka, prvo se ispise 'sirina' vodecih bjelina, a zatim atributi objekta koji se ispisuje.

	izlaz << *this;																						// Originalan 'cout' = ovajNasPodeseni_cout, originalni cout podesava svoje atribute da budu u skladu sa zeljenim ispisom. Nakon podesavanja svojih atributa, 'cout' ih ispisuje na pocetni ekran .
}





void NebeskoTijelo::ispisi(ostream& izlaz, int sirina)
{
	print(izlaz, sirina);
}





bool NebeskoTijelo::operator<(NebeskoTijelo& objekat)
{
	if (this == &objekat)									// Pokriva slucaj, pozivajuci objekat i pozvani objekat zive na istoj adresi, to jest pozivajuci objekat je ujedno i pozvani objekat .
		return false;

	else if (this->masa < objekat.masa)						// Pokriva slucaj, masa pozivajuceg objekta jeste manja od mase pozvanog objekta.
		return true;

	else if (this->masa == objekat.masa)					// Pokriva slucaj, masa pozivajuceg objekta je jednaka masi pozvanog objekta.
		return false;

	else													// Pokriva slucaj, masa pozivajuceg objekta je veca od mase pozvanog objekta.
		return false;
}





NebeskoTijelo& NebeskoTijelo::operator=(NebeskoTijelo& objekat)				// Kada klasa posjeduje pokazivac na dinamicki alociran memorijski blok, postoji opasnost zvana plitko kopiranje !		Zato na ispitu i u praksi, ako klasa posjeduje pokazivac na dinamicki alociran memorijski blok, obavezno treba eksplicitno definisati metodu 'operator=' !!!
{
	if (this != &objekat)
	{
		this->masa = objekat.masa;

		this->poluprecnik = objekat.poluprecnik;

		delete[] this->naziv;

		this->naziv = new(char[strlen(objekat.naziv) + 1]);

		strcpy(this->naziv, objekat.naziv);
	}

	return *this;
}









template <class T>
class Lista
{

private:

	struct Element
	{
		T* pokazivac;					//	Private data_member potklase_Element klase Lista. Moze da se inicijalizuje adresom nekog postojeceg objekta tipa 'T'. 

		struct Element* sljedeci;		//  Private data_member podtlase_Element klase Lista. Moze da se inicijalizuje adresom objekta podtlase 'Element' klase 'Lista'.

		Element(T& objekat)				//	'Parametar objekat' konstruktora 'Element' je samo drugo ime za neki postojeci objekat(za objekat koji je izvan klase poslat kao argument ove metode).
		{
			pokazivac = &objekat;		//  Pokazivac 'pokazivac' se inicijalizuje adresom postojeceg objekta.

			sljedeci = NULL;			//  Rezime: Ova klasa 'Element' koja je potklasa klase 'Lista' ima dva atributa: 'pokazivac na tip T' i 'pokazivac na klasu Element'. Pri svakom novom definisanju objekta klase 'Element' poziva se konstruktor 'Element(T&)' i inicijalizuje navedena dva atributa.
		}

	}*glava, * rep;

	int brojacCvorova;


public:


	Lista() : glava(NULL), rep(NULL), brojacCvorova(0) {}





	Lista& dodaj(T& objekat)																			// Procitaj, Laslo Kraus, referenca kao parametar, povratni tip metode/funkcije. Podklasa 'Element' je private data_member klase 'Lista'. Elementima podklase 'Element' mozemo pristupiti samo unutar klase 'Lista' jer kao sto vidimo iz definicije klase 'Element' svi data_members i methods su pod specifikatorom private.
	{

		if (!glava)																						// Ako je lista prazna
		{
			glava = rep = new Element(objekat);															// novi cvor jednostavno dodamo u listu.

			brojacCvorova++;

			//	cout << objekat << " dodat u listu." << endl;												
		}

		else																							// Ako lista nije prazna. Novi cvor treba dodati na kraj liste. PRIMJERA RADI, RECIMO DA IMAMO OBJEKAT KLASE Lista SA POKAZIVACEM 'glava' USMJERENIM SA SAMO JEDAN OBJEKAT POTKLASE 'Element' KLASE 'Lista'.
		{
			rep->sljedeci = new Element(objekat);														//																TADA 'rep' POKAZUJE NA TAJ (JEDINI)POSTOJECI CVOR, A 'sljedeci' TOG CVORA POKAZUJE NA 'NULL'. ONO STA MI RADIMO JESTE, TAJ rep->sljedeci SA 'NULL' PREUSMJERAVAMO NA NOVO_ZAUZETI MEMORIJSKI BLOK U KOJEM SE SMJESTA OBJEKAT POTKLASE 'Element'. ZBOG PODRAZUMJEVANOG KONSTRUKTORA TE KLASE, TAJ PODATAK SE ODMAH EKSPLICITNO INICIJALIZUJE.

			rep = rep->sljedeci;																		//																'rep' SADA SKACE, TO JEST POKAZUJE NA ADRESU TOG NOVODEFINISANOG OBJEKTA, A OVAJ MEHANIZAM PRI SVAKOJ ITERACIJI OMOGUCAVA SKAKANJE 'rep-A" NA NOVODEFINISANI OBJEKAT POTKLASE 'Element'. 

			brojacCvorova++;

			//	cout << objekat << " dodat u listu." << endl;
		}

		return *this;
	}





	~Lista()
	{
		if (glava)
		{
			while (glava)
			{
				Element* pglava = glava->sljedeci;

				//cout << "Sadrzaj: " << *(glava->pokazivac) << " uklonjen iz liste." << endl;

				delete glava;

				brojacCvorova--;

				glava = pglava;
			}
		}

		cout << "Broj elemenata u listi: " << brojacCvorova << endl;
	}





	T& operator[](int x)
	{

		Element* pglava = glava;																// 'pglava' sada pokazuje na prvi Element u listi. Nalazimo se unutar klase 'Lista', svaki rad sa pokazivacem 'glava' moze dovesti do skretanja tog pokazivaca sa prvog clana liste sto vodi ka brojnim nezeljnim posljedicama (Najcesce ka memory leak !!!)!!!  Zato za prolazak kroz listu, prvo definisemo pomocni pokazivac koji ce imati ulogu manipulatora indeksa.

		for (int i = 0; i < x; i++, pglava = pglava->sljedeci);									// Na pocetku 'pglava = glava' , 'pglava' pokazuje na prvi cvor u listi. Radi se o jednostruko uvezanoj listi pa uobicajena pokazivacka aritmetika NE VAZI !!!     Npr. 'pglava + 1' nas moze odvesti bilo gdje, cvorovi nisu na uzastopnim memorijskim lokacijama !!!     Ovako, pri svakoj iteraciji (dok god je i < x) 'pglava' skace sa cvora na cvor sto na kraju rezultuje time da  pokazivac 'pglava' pokazuje na adresu  x_tog cvor u listi . 

		return *(pglava->pokazivac);															// 'pglava' pokazuje na x_ti cvor u listi. Atribut 'pokazivac' tog cvora je usmjeren na adresu postojeceg objekta, *(pglava->pokazivac) je samo drugo ime (referenca) za taj postojeci objekat. Tako da povratni tip ove metode je 'drugo ime' za postojeci objekat tipa 'T' .

	}





	int brojElemenata()
	{
		int kopijaBrojacCvorova = brojacCvorova;													// brojacCvorova je private_data_member klase 'Lista'. Moze mu se pristupiti iskljucivo unutar te klase ili prijateljem te klase. Zato mi prvo definisemo lokalni objekat 'kopijaBrojacCvorova' u koji se kopira sadrzaj brojacCvorova.

		return kopijaBrojacCvorova;																	// Sadrzaj 'kopijaBrojacaCvorova se ovdje jos jednom kopira i vrati kazo rezultat rada ove metode. Uvijek vodi racuna o atributima, pitaj se kog su specifikatora jer ovdje se zna desiti nalet 'return brojacCvorova' pa jos ako bih povratni tip metode bio 'int&' to onda vodi ka zaustavljanju rada programa jer trazis globalni pristup skrivenom zasticenom podatku.
	}





	void sortiraj()																			// Posto radimo sa potklasom 'Element' klase 'Lista' definiciju ove metode cemo navesti unutar klase 'Lista'.
	{
		if (glava)
		{


			Element* pglava = glava;														// Da ne bih doslo do nezeljenih posljedica, 'pglava' prolazi kroz listu, tako da data_member 'glava' uvijek pokazuje na prvi cvor u listi.


			for (; pglava && pglava->sljedeci; pglava = pglava->sljedeci)					// Podsjetnik, for(int i = 0; i < n-1; i++). 
			{


				Element* min = pglava, * p;
				T sadrzaj;

				for (p = pglava->sljedeci; p; p = p->sljedeci)								// Prethodna petlja 'for (; pglava && pglava->sljedeci; pglava = pglava->sljedeci)' pozicionira pokazivac 'pglava' . Sadrzaj cvora na ciju adresu pokazuje 'pglava' poredimo sa svim ostalim pocevsi od 'pglava->sljedeci' pa na dalje 'p = pglava->sljedeci. Poredak se radi sve dok ne dodjemo do posljednjeg cvora u listi 'rep->next = NULL' pa kada 'p' skoci sa 'rep' na NULL napustamo petlju.					
					if (!(*(min->pokazivac) < *(p->pokazivac)))								// Kad god je 'p != NULL' mi poredimo SADRZAJ pokazivaca !!! 
						min = p;															// 'min' ima ulogu detektora SWAP sadrzaja !	

				if (min != pglava)															// Ako 'min' vise ne pokazuje tamo gdje pokazuje i 'pglava' to je znak da trebamo SWAP sadrzaje cvorova cije su adrese na dohvatu tih  pokazivaca.
				{
					 sadrzaj = *(min->pokazivac);

					*(min->pokazivac) = *(pglava->pokazivac);

					*(pglava->pokazivac) = sadrzaj;
				}
			}
		}

		else { cout << "Lista je prazna ! \a" << endl; }
	}


};	//	Zapamti, kraj definicije klase, strukture se zavrsava sa ';' .	Na ispitu, nemoj zaboraviti rucno postaviti simbol ';' !!!









class VelikoTijelo : public NebeskoTijelo
{

public:

	VelikoTijelo(double m, double r, char* str) : NebeskoTijelo(m, r, str) {};

	void ispisi(ostream&, int);

	int dodajSatelit(NebeskoTijelo&);

	void sortirajPremaMasi();

	NebeskoTijelo& operator[](int);

private:

	Lista<NebeskoTijelo> listaSatelita;
};





void VelikoTijelo::ispisi(ostream& izlaz, int sirina)
{
	NebeskoTijelo::print(izlaz, 0);

	for (int i = 0; i < this->listaSatelita.brojElemenata(); i++)
		listaSatelita[i].print(izlaz, sirina);							// listaSatelita[i] kao rezultat vraca referencu(DRUGO IME!!!) za vec postojeci objekat klase 'NebeskoTijelo' pa taj objekat poziva svoju metodu print(ostream&, int) sa odgovarajucim elementima.
}





int VelikoTijelo::dodajSatelit(NebeskoTijelo& objekat)
{
	listaSatelita.dodaj(objekat);
	return 1;
}





void VelikoTijelo::sortirajPremaMasi()
{
	listaSatelita.sortiraj();
}





NebeskoTijelo& VelikoTijelo::operator[](int x)
{
	return listaSatelita[x];							// Elementi liste su postojeci objekti. Metoda, kao rezultat vraca drugo ime za vec postojeci objekat.
}







int main()
{
	/*
	int objekat1 = 5, objekat2 = 25, objekat3 = 15, objekat4 = 20, objekat5 = 15;

	Lista<int> lista;

	lista.dodaj(objekat1);

	lista.dodaj(objekat2);

	lista.dodaj(objekat3);

	lista.dodaj(objekat4);

	lista.dodaj(objekat5);
	*/

	double m1 = 1.989e+030, m2 = 3.285e+023, m3 = 6.39e+023, m4 = 4.867e024, m5 = 5.972e024, m6 = 7.34767e+022;
	double r1 = 695800, r2 = 2440, r3 = 3390, r4 = 6052, r5 = 6371, r6 = 1700;





	char* nizImena[6];
	nizImena[0] = new(char[strlen("Sunce") + 1]); strcpy(nizImena[0], "Sunce");
	nizImena[1] = new(char[strlen("Merkur") + 1]); strcpy(nizImena[1], "Merkur");
	nizImena[2] = new(char[strlen("Mars") + 1]); strcpy(nizImena[2], "Mars");
	nizImena[3] = new(char[strlen("Venera") + 1]); strcpy(nizImena[3], "Venera");
	nizImena[4] = new(char[strlen("Zemlja") + 1]); strcpy(nizImena[4], "Zemlja");
	nizImena[5] = new(char[strlen("Mjesec") + 1]); strcpy(nizImena[5], "Mjesec");





	VelikoTijelo Sunce(m1, r1, nizImena[0]);

	NebeskoTijelo Merkur(m2, r2, nizImena[1]), Mars(m3, r3, nizImena[2]), Venera(m4, r4, nizImena[3]), Zemlja(m5, r5, nizImena[4]), Mjesec(m6, r6, nizImena[5]);





	Sunce.dodajSatelit(Merkur);
	Sunce.dodajSatelit(Venera);
	Sunce.dodajSatelit(Mars);
	Sunce.dodajSatelit(Zemlja);
	Sunce.dodajSatelit(Mjesec);

	Sunce.sortirajPremaMasi();

	Sunce.ispisi(cout, 15);





	fstream datoteka("ETFBL.txt");

	Sunce.ispisi(datoteka, 15);

	return 0;
}