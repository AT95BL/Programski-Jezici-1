#include <iostream>
#include <cstring>
#include <fstream>

#pragma warning(disable:4996)

using namespace std;





class ElementarnaCestica
{
	friend ostream& operator<<(ostream&, ElementarnaCestica&);

private:

	double masa;
	double kinetickaEnergija;

	char* naziv{};																				// Pazi, atribut 'naziv' je pokazivac na dinamicki alociran memorijski_blok. Naredba 'ElementarnaCestica a, b; a = b;' vodi ka plitkom kopiranju sto kasnije cesto vodi ka padu programa ili nezeljenim rezultatima. Zato, kad korisnicki definisana klasa ima 'atribut koji pokazuje na dinamicki alociran memorijski blok' moramo eksplicitno preklopiti 'operator=' kako bih izbjegli greske koje kasnije obaraju program i na ispitu prekidaju bodovanje !!!

public:

	ElementarnaCestica(double, double, char*);
	~ElementarnaCestica() { delete[] naziv; }

	ElementarnaCestica& operator=(ElementarnaCestica&);

	void print(ostream&, int);

	virtual void ispisi(ostream&, int);

	bool operator>(ElementarnaCestica&);
	
};





ElementarnaCestica::ElementarnaCestica(double m = 0, double k = 0, char* str = NULL)			// Definicija podrazumjevanog konstruktora klase 'ElementarnaCestica'. Kao treci argument ,ovaj konstruktor prihvata samo 'char*' , dakle eksplicitno/implicitno char* str = "KonstantanString" ne moze proci kao treci argument ovog konstruktora jer je tipa 'const char*'.			char *str = new(char[strlen(KonstantanString)+1]); strcpy(str, "KonstantanString"); => 'str' moze predati kao argument ovog konstruktora ! 
{
	masa = m;

	kinetickaEnergija = k;

	if (str)
	{
		naziv = new(char[strlen(str) + 1]);

		strcpy(naziv, str);
	}

	else naziv = NULL;
}





ElementarnaCestica& ElementarnaCestica::operator=(ElementarnaCestica& objekat)		// Parametar 'objekat' je samo drugo ime za neki POSTOJECI objekat klase 'ElementarnaCestica' to jeste za objekat koji se nalazi desno od 'operatora dodjele vrijednosti ='.
{
	if (this != &objekat)															// Ako pozivajuci(tekuci -onaj ko se nalazi lijevo od =) objekat i pozvani(-onaj koji se nalazi desno od =) objekat 'ne STANUJU' na istoj adresi , tada sadrzaj tekuceg objekta treba preurediti tako da pri izlasku iz 'operator= metode klase ElementarnaCestica' tekuci i pozvani objekat budu istoga sadrzaja !!! Npr. Elementarna cestica a, b; a = a; je naredba koja preskace ovaj 'if' dok naredba a = b; ulazi u ovaj 'if'.
	{
		this->masa = objekat.masa;													// Nova inicijalizacija atributa 'masa' tekuceg objekta.

		this->kinetickaEnergija = objekat.kinetickaEnergija;						// Nova inicijalizacija atributa 'kinetickaEnergija' tekuceg objekta.

		delete[] this->naziv;														// Dolazi do redefinicije pokazivaca, 'naziv' pokazuje na neki memorijski blok koji ocigledno vise nije potreban jer mjenjamo komplet sadrzaj tekuceg objekta pa moramo prvo osloboditi taj memorijski blok jer ne zelimo da nas program bezveze trosi memorijske resurse.

		if (objekat.naziv)															// Funkcija 'strcpy' kao prvi/drugi argument prima 'char*, const char* koji su != NULL'.
		{
			this->naziv = new(char[strlen(objekat.naziv) + 1]);

			strcpy(this->naziv, objekat.naziv);
		}
		else this->naziv = NULL;
	}

	return *this;																	// Kao rezultat svoga rada, ova metoda vraca 'drugo ime' za tekuci objekat. Procitaj Laslo Kraus referenca kao parametar/povratni_tip metode/funkcije !!!

}





ostream& operator<<(ostream& izlaz, ElementarnaCestica& objekat)												// Prijatelj klase nije clan klase vec je neko ko moze da pristupi svim clanovima klase bez obzira na specifikator pristupa. Dakle ova funkcija nije metoda klase 'ElementarnaCestica' pa pri njenoj definiciji moramo naglasiti da objekat 'objekat' poziva '.' neki od svojih atributa. NA ISPITU NEMOJ DA TE PONESE PA DA U DEFINICIJI PRIJATELJA_KLASE MANIPULISES POLJIMA KLASE KAO STO SA NJIMA MANIPULISES UNUTAR METODE. Parametar izlaz je samo drugo ime za objekat 'cout' .
{
	izlaz << objekat.naziv << " " << objekat.masa << "[kg] " << objekat.kinetickaEnergija << "[Mev]" << endl;

	return izlaz;																								// Kao rezultat svoga rada, funkcija vraca 'drugo ime' za objekat 'cout' klase ostream. Naravno taj objekat se vraca u originalu, sa atributima/poljima podesenim u skladu sa definicijom ove funkcije.
}





void ElementarnaCestica::print(ostream& izlaz, int sirina)
{
	izlaz.width(sirina);																				// <=> cout.width; jer 'izlaz' je samo drugo ime za objekat 'cout' klase 'ostream' .

	izlaz << *this;
}





void ElementarnaCestica::ispisi(ostream& izlaz, int sirina)
{
	print(izlaz, sirina);
}





bool ElementarnaCestica::operator>(ElementarnaCestica& objekat)
{
	if (this == &objekat)
		return false;

	else if (this->masa > objekat.masa)
		return true;

	else return false;
}










template <class T>
class Lista
{

private:


	struct Element								// struktura/slog 'Element' je zapravo klasa definisana unutar klase 'Lista' !		 'Element' je dakle 'private:' polje klase 'Lista'. Poljima klase 'Element' mozemo pristupiti iskljucivo unutar klase 'Element, Lista' i prijateljem klase 'Lista' !!!. To znaci , pokusaj definisanja metode_vezane_za_klasu_Element klase 'Lista' izvan klase 'Lista' dovodi do greske prilikom prevodjenja programa jer mi onda pokusavamo globalno pristupiti 'private' clanu klase Element.  
	{
		T* pokazivac;								

		struct Element* sljedeciCvor;

		Element(T& objekat)						// Argument ovog konstruktora je neki postojeci objekat klase/tipa 'T'.
		{
			pokazivac = &objekat;				// Sada 'pokazivac' sadrzi ADRESU nekog postojeceg objekta ciji ime je navedeno kao parametar konstruktora klase 'Element' . 

			sljedeciCvor = NULL;
		}

	}*glava, *rep;
	
	int brojacCvorova;


public:





	Lista() : glava(NULL), rep(NULL), brojacCvorova(0) {};										// Definicija podrazumjevanog eksplicitno definisanog konstruktora klase Lista. Na pocetku je lista prazna !!!





	~Lista()																					// Podrazumjevani destruktor klase 'Lista' .
	{

		while (glava)																			// Od prvog do posljednjeg cvora u listi(skacemo od prvog cvora do NULL):
		{
			Element* pglava = glava->sljedeciCvor;												// -Obezbjedi mjesto za skok, tako da 'glava' uvijek skoci na pocetak liste.	Jezikom masine: 'pglava' pokazuje na adresu sljedbenika od cvora na ciju adresu pokazuje 'glava'

			delete glava;																		// -Obrisi cvor, a zatim														Jezikom masine:  oslobodi memorijski blok (brisemo skalar delete, a ne delete[] kao da brisemo niz skalara)

			glava = pglava;																		// skoci na iduci cvor.															Jezikom masine: u 'glava' upisimo adresu cvora cija je adresa upisana u pokazivac 'pglava'. Unisti objekat 'pglava' Sto znaci svakom novom iteracijom ove petlje definise se i inicijalizuje objekat 'pglava a zatim se unisti isti !!!

			brojacCvorova--;
		}
	}		





	Lista& operator+=(T& objekat)
	{
		if (!glava)																				// Ako je lista prazna.
		{
			glava = rep = new Element(objekat);													

		}

		else
		{
			rep->sljedeciCvor = new Element(objekat);

			rep = rep->sljedeciCvor;
		}
		
		brojacCvorova++;

		return *this;
	}





	T& operator()(int x)
	{
		
			Element* pglava = glava;															// PAZI!!! 'glava' uvijek pokazuje na pocetak liste. Taj pokazivac ne smije skretati (U protivnom moze doci do neceg nezeljenog!) pa mi kroz listu prolazimo pomocu pomocnog pokazivaca 'pglava'.

			for (int i = 0; i < x; i++)															// Cvorovi liste se ne nalaze na uzastopnim memorijskim lokacijama. Naredba 'pglava + x' ne pomjera 'pglava' na x_ti cvor vec negdje nama beznacajno u memoriji, uopste kod dinamicki alocirane memorije NE VAZI LOGIKA STANDARDNE POKAZIVACKE ARITMETIKE !!!
				pglava = pglava->sljedeciCvor;													// Zeljeno skakanje pokazivaca 'pglava' sa cvora na cvor je ostvarivo iskljucivo ovakvim mehanizmom !!!

			return *(pglava->pokazivac);														// 'pglava' doskoci na x_ti cvor u listi. Zatim pristupi njegovom polju 'pokazivac' , a to polje pokazuje na neki postojeci_originalni objekat tipa 'T'. Dakle: 'pglava <=> adresa x_tog cvora'		, 'pglava->pokazivac <=> adresa_nekog_spoljasnjeg_postojeceg_objekta'	, *(pglava->pokazivac) <=> vrijednost tog_nekog_spoljasnjeg_postojeceg_objekta pa kada se kao rezultat rada ove metode vrati referenca mi u stvari vracamo nista drugo nego 'drugo_ime' za taj postojeci objekat tipa/klase 'T' .
	}





	int operator()()
	{ 
		int kopija_brojacCvorova = brojacCvorova;												// 'brojacCvorova' je private: data_member klase Lista. Njega u originalu mozemo koristiti iskljucivo unutar te klase ili preko prijatelja te klase. Zato mi kopiramo njegov sadrzaj u lokalnu promjenjivu, 
		return kopija_brojacCvorova;															// funkcija kao rezultat vraca tu cifru i mi tu cifru mozemo koristiti mimo klase 'Lista'.  Dakle, naredba 'return brojacCvorova; ' znaci da mi private data member -u dajemo novo ime koje vazi izvan klase 'Lista' i tako ga koristimo, takva naredba krsi standard C++-a i program naravno pada. Zakljucak, NE MOZES GLOBALNO KORISTITI private: DATA_MEMBER-E IZVAN NJIHOVIH KLASA.
	}





	void sortiraj()
	{
		if (!glava)																				// Ako je lista prazna, samo napusti metodu.
			return;


		Element* pglava = glava;																// 'glava' uvijek pokazuje na pocetak liste. Pomocni pokazivac 'pglava' ce biti nas vodic kroz listu.
		

		for (; pglava && pglava->sljedeciCvor; pglava = pglava->sljedeciCvor)					// Posto je 'pglava' vec inicijalizovan , pokazuje na pocetak nase liste prva naredba 'for' petlje je prazna ';'	Uslov 'pglava && pglava->sljedeciCvor' sa programerskog aspekta gledanja znaci "Ako postoje barem dva cvora u nasoj listi" !!! 
		{

			Element* min = pglava, * p;															// 'min' se pozicionira na prvi cvor u listi, a 'p' se pozicionira na prvog sljedbenika od 'min'.  Kada se sa programerskog aspekta gledanja ova naredba nadoveze na prethodnu to bi bilo "Posto postoje barem dva cvora, usporedimo ih!" .
			T sadrzaj;

			for (p = pglava->sljedeciCvor; p; p = p->sljedeciCvor)								//  'p' skace sa cvora na cvor sve dok ne dodje do 'rep'-a liste.
				if (!(*(min->pokazivac) > *(p->pokazivac)))										//  Pri svakom skoku sadrzaj cvora cija adresa je pohranjena u 'min' se poredi sa sadrzajem cvora cija adresa je pohranjena u 'p'
					min = p;																	//  ,a svaki narusen poredak se prati 'min'. Tako da pri zavrsetku gornje 'for' petlje 'min' je pozicioniran na cvor ciji sadrzaj treba da se zamjeni sa sadrzajem na koji pokazuje 'pglava; .
			
															

			if (min != pglava)
			{
				 sadrzaj = *(min->pokazivac);													//  Ovaj 'sadrzaj' treba da se upise na cvor cija se adresa nalazi u 'pglava' ,a sadrzaj cvora cija se adresa nalazi u 'pglava' treba da se upise tamo gdje pokazuje 'min' .

				*(min->pokazivac) = *(pglava->pokazivac);

				*(pglava->pokazivac) = sadrzaj;
			}
		}
	}
};










class VelikaCestica : public ElementarnaCestica
{

private:

	Lista<ElementarnaCestica> lista;														// 'lista' je objekat klase 'Lista'. Kada se definise objekat klase 'VelikaCestica' njegov atribut 'lista' odmah prolazi krzo PODRAZUMJEVANI EKSPLICITNO korisnicki definisan konstruktor !!!


public:

	VelikaCestica(double m, double k, char* str) : ElementarnaCestica(m, k, str) {}			// VelikaCestica objekat; jeste naredba koja nece proci fazu prevodjenja programa jer ne postoji podrazumjevan konstruktor klase 'VelikaCestica'.	Posto je tekst zadatka takav kakav jeste, da bi u main()-u radili sa objektom klase 'VelikaCestica' moramo odmah pri definisanju tog objekta popuniti konstruktor tako da se njegov 'podobjekat' eksplicitno definise konstruktorom 'ElementarnaCestica(double, double, char*)'.  


	void ispisi(ostream&, int);

	void dodajUOrbitu(ElementarnaCestica&);

	void sortirajCestice();

	int brojElCestica();

	ElementarnaCestica& operator[](int);
};





void VelikaCestica::ispisi(ostream& izlaz, int sirina)
{
	ElementarnaCestica::ispisi(izlaz, 0);

	izlaz.width(sirina);

	for (int i = 0; i < lista(); i++)
		lista(i).print(izlaz, sirina);														// Lista(i) je samo drugo ime za neki postojeci objekat klase "ElementarnaCestica'.
}





void VelikaCestica::dodajUOrbitu(ElementarnaCestica& objekat)
{
	lista += objekat;
}





void VelikaCestica::sortirajCestice()
{
	lista.sortiraj();
}





ElementarnaCestica& VelikaCestica::operator[](int x)
{
	return lista(x);
}





int VelikaCestica::brojElCestica()										// Pomocna metoda, preko nje cu detektovati 'izuzetak' !
{
	int broj = lista();

	return broj;
}





int main()
{
	char* ime[4];
	ime[0] = new(char[strlen("Proton") + 1]); strcpy(ime[0], "proton");
	ime[1] = new(char[strlen("Elektron") + 1]); strcpy(ime[1], "elektron");
	ime[2] = new(char[strlen("Pozitron") + 1]); strcpy(ime[2], "pozitron");
	ime[3] = new(char[strlen("foton") + 1]); strcpy(ime[3], "foton");

	int i;




	VelikaCestica proton(1.167e-026, 2, ime[0]);
	VelikaCestica elektron(1.167e-026, 3, ime[1]);

	ElementarnaCestica	elektron1(9.1e-031, 5, ime[1]);
	ElementarnaCestica	pozitron1(1.167e-026, 2, ime[2]);
	ElementarnaCestica  foton(0, 2, ime[3]);
	ElementarnaCestica elektron2(1.167e-026, 4, ime[1]);





	elektron.dodajUOrbitu(foton);

	proton.dodajUOrbitu(elektron);
	proton.dodajUOrbitu(elektron1);
	proton.dodajUOrbitu(pozitron1);
	proton.dodajUOrbitu(elektron2);





	elektron.sortirajCestice();
	proton.sortirajCestice();




	try
	{
		for (i = 0; i < 101; i++)
		{
			if (i > proton.brojElCestica())
				throw i;

			proton.ispisi(cout, 15);
		}

	}
	
	catch(int x)
	{
		cout << "Prekoracenje! " << endl;
	}





	ofstream datoteka("Etf.txt");
	proton.ispisi(datoteka, 15);

	



	for (int i = 0; i < 4; i++)
		delete[] ime[i];

	return 0;
}