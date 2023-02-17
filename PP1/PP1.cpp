#include<stdio.h>
#include<ctime>
#include<cstdlib>
#include"conio2.h"

#define LEG_X 1
#define LEG_Y 1
#define RAMKA_X 45
#define RAMKA_Y 1
#define L_WYPELNIEN (SIZE*SIZE/4)

void wpisywanie(char **gra, int SIZE, int zn, int *liczbaJedynekKol, int *liczbaZerKol, int *liczbaJedynekWi, int *liczbaZerWi, int dx, int dy, bool *nieMozesz, bool *nieMozeszDlaKolumn, bool &mozesz, int &nrPowt3, bool czyWpisac)
{
	nieMozesz[0] = false;
	nieMozesz[1] = false;
	nieMozesz[2] = false;
	mozesz = false;
	//spr. reguly 3 dla kolumn
	if (liczbaJedynekKol[dx] + liczbaZerKol[dx] == SIZE - 1) {
		for (int i = 0; i < SIZE; i++) {
			if (liczbaZerKol[i] + liczbaJedynekKol[i] != SIZE) continue;
			if (nieMozesz[2]) break;
			for (int j = 0; j < SIZE; j++) {
				if (i != dx) {
					if (gra[i][j] != gra[dx][j]) {
						if (gra[i][j] == zn && j == dy)
							if (j == SIZE - 1) {
								nieMozesz[2] = true;
								nieMozeszDlaKolumn[1] = true; //regula 3 - nie mozesz wpisac, bo sa takie same kolumny
								nrPowt3 = i;
								break;
							}
							else
								continue;
						else
							break;
					}
					else if (j == SIZE - 1) {
						nieMozesz[2] = true; //sa takie same
						nieMozeszDlaKolumn[1] = true;
						nrPowt3 = i;
					}
				}
				else break;
			}
		}
	}
	//spr. reguly 3 dla wierszy
	if (liczbaJedynekWi[dy] + liczbaZerWi[dy] == SIZE - 1) {
		for (int i = 0; i < SIZE; i++) {
			if (liczbaZerWi[i] + liczbaJedynekWi[i] != SIZE) continue;
			if (nieMozesz[2]) break;
			for (int j = 0; j < SIZE; j++) {
				if (i != dy) {
					if (gra[j][i] != gra[j][dy]) {
						if (gra[j][i] == zn && j == dx)
							if (j == SIZE - 1) {
								nieMozesz[2] = true;
								nieMozeszDlaKolumn[1] = false; //regula 3 - nie mozesz wpisac, bo sa takie same wiersze
								break;
								nrPowt3 = i;
							}
							else
								continue;
						else
							break;
					}
					else if (j == SIZE - 1) {
						nieMozesz[2] = true; //sa takie same
						nieMozeszDlaKolumn[1] = false;
						nrPowt3 = i;
					}
				}
				else break;
			}
		}
	}
	//spr. reguly 1
	if ((dx >= 2 && gra[dx - 2][dy] == zn && gra[dx - 1][dy] == zn) || (dx <= SIZE - 3 && gra[dx + 1][dy] == zn && gra[dx + 2][dy] == zn) || (dy >= 2 && gra[dx][dy - 2] == zn && gra[dx][dy - 1] == zn) || (dy <= SIZE - 3 && gra[dx][dy + 1] == zn && gra[dx][dy + 2] == zn) || (dx >= 1 && dx <= SIZE - 2 && gra[dx - 1][dy] == zn && gra[dx + 1][dy] == zn) || (dy >= 1 && dy <= SIZE - 2 && gra[dx][dy - 1] == zn && gra[dx][dy + 1] == zn))
		nieMozesz[0] = true;
	//spr. reguly 2 dla zer
	if (zn == 48 && (liczbaZerKol[dx] == SIZE / 2 || liczbaZerWi[dy] == SIZE / 2))
	{
		nieMozesz[1] = true;
		if (liczbaZerKol[dy] == SIZE / 2) nieMozeszDlaKolumn[0] = true;
		else if (liczbaZerWi[dy] == SIZE / 2) nieMozeszDlaKolumn[0] = false;
	}
	//spr. reguly 2 dla jedynek
	if (zn == 49 && (liczbaJedynekKol[dx] == SIZE / 2 || liczbaJedynekWi[dy] == SIZE / 2))
	{
		nieMozesz[1] = true;
		if (liczbaJedynekKol[dy] == SIZE / 2) nieMozeszDlaKolumn[0] = true;
		else if (liczbaJedynekWi[dy] == SIZE / 2) nieMozeszDlaKolumn[0] = false;
	}
	if (!nieMozesz[0] && !nieMozesz[1] && !nieMozesz[2]) {
		if (czyWpisac) {
			if (zn == 48) {
				if (gra[dx][dy] == '1') {
					liczbaJedynekKol[dx]--;
					liczbaJedynekWi[dy]--;
					liczbaZerKol[dx]++;
					liczbaZerWi[dy]++;
				}
				else if (gra[dx][dy] == ' ') {
					liczbaZerKol[dx]++;
					liczbaZerWi[dy]++;
				}
			}
			else {
				if (gra[dx][dy] == '0') {
					liczbaZerKol[dx]--;
					liczbaZerWi[dy]--;
					liczbaJedynekKol[dx]++;
					liczbaJedynekWi[dy]++;
				}
				else if (gra[dx][dy] == ' ') {
					liczbaJedynekKol[dx]++;
					liczbaJedynekWi[dy]++;
				}
			}
			gra[dx][dy] = zn;
		}
		mozesz = true;
	}
}

void init_los(char **gra, bool **graBool, int SIZE, int *liczbaJedynekKol, int *liczbaZerKol, int *liczbaJedynekWi, int *liczbaZerWi, bool **czyMoznaKGra, bool **czyMoznaJGra, int **uzupelnienieJ, bool *nieMozesz, bool *nieMozeszDlaKolumn, bool &mozesz, int &nrPowt3)
{
	int los_x, los_y, los_liczba, los_i = L_WYPELNIEN; //losowa liczba, jest rowna liczbie pol ktore zostana wylosowane na pocz. programu
	for (int i = 0; i < SIZE; i++) {
		liczbaZerKol[i] = 0;
		liczbaZerWi[i] = 0;
		liczbaJedynekKol[i] = 0;
		liczbaJedynekWi[i] = 0;
		for (int j = 0; j < SIZE; j++) {
			gra[i][j] = ' ';
			graBool[i][j] = false;
			czyMoznaKGra[i][j] = true; //czy mozna wpisac w dane pole - po wcisnieciu 'k'
			czyMoznaJGra[i][j] = true; //czy jednoznaczne - po wc. 'j'
			uzupelnienieJ[i][j] = -1;
		}
	}
	while (los_i) {
		los_x = rand() % SIZE;
		los_y = rand() % SIZE;
		los_liczba = (rand() % 2) + 48;
		if (!graBool[los_x][los_y]) {
			wpisywanie(gra, SIZE, los_liczba, liczbaJedynekKol, liczbaZerKol, liczbaJedynekWi, liczbaZerWi, los_x, los_y, nieMozesz, nieMozeszDlaKolumn, mozesz, nrPowt3, true);
			if (mozesz) {
				graBool[los_x][los_y] = true;
				los_i--;
			}
		}
	}
	nieMozesz[0] = false;
	nieMozesz[1] = false;
	nieMozesz[2] = false;
	mozesz = false;
	los_i = L_WYPELNIEN;
}

int main() {
	int SIZE = 12, SIZEtmp;
	int rozmiar[3] = { 1,2,0 }; //tablica wykorzystywana przy wpisywaniu rozmiaru mapy przez gracza
	srand(time(NULL));
	int zn = 0, x = RAMKA_X + 1, y = RAMKA_Y + 1, attr = 7, back = 0, zero = 0, uzup = 0, load = 0, nrPowt3 = 0; //uzup - pobiera klawisz po kliknieciu j (czy jest on 'w'), nrPowt3 - numer kolumny lub wiersza który siê powtarza zgodnie z regu³¹ nr 3
	int dx, dy; //polozenie x i y kursora wzgledem PLANSZY
	char txt[32];
	char podpowiedz[13][100]; //wyswietlana podpowiedz; 13 to liczba mozliwych wariantow podpowiedzi
	char **gra = new char *[99]; //tablica, w ktorej beda wpisywane 0 i 1
	bool **graBool = new bool *[99]; //true - CYFRA WPISANA PRZY INICJALIZACJI, false - CYFRA WPISANA PRZEZ GRACZA lub PUSTA
	bool **czyMoznaKGra = new bool *[99]; //true - w dane pole mozna wpisac przynajmniej jedna cyfre, false - nie mozna nic wpisac (zaswietli sie)
	bool **czyMoznaJGra = new bool *[99]; //true - w dane pole mozna wpisac zero lub obie cyfry, false - w dane pole mozna wpisac tylko jedna cyfre 0 lub 1 (zaswietli sie)
	int **uzupelnienieJ = new int *[99]; //przyjmuje wartosci 0 i 1, w zaleznosci od tego, ktora z cyfr mozna uzupelnic pole jednoznaczne
	for (int i = 0; i < 99; i++) {
		gra[i] = new char[99];
		graBool[i] = new bool[99];
		czyMoznaKGra[i] = new bool[99];
		czyMoznaJGra[i] = new bool[99];
		uzupelnienieJ[i] = new int[99];
	}
	//tablice przechowuj¹ce liczbe zer i jedynek w wierszach i kolumnach
	int *liczbaZerKol = new int[99];
	int *liczbaZerWi = new int[99];
	int *liczbaJedynekKol = new int[99];
	int *liczbaJedynekWi = new int[99];
	bool czyMoznaKJ[2] = { true,true }; //czy mozna w dane pole (np. w trakcie wykonywania petli) wpisac 0 lub 1 ---> [0] = true -> mozna wpisac 0 / = false -> nie mozna wpisac 0; [1] = true -> mozna wpisac 1 / = false -> nie mozna wpisac 1;
	for (int i = 0; i < SIZE; i++) {
		liczbaZerKol[i] = 0;
		liczbaZerWi[i] = 0;
		liczbaJedynekKol[i] = 0;
		liczbaJedynekWi[i] = 0;
		for (int j = 0; j < SIZE; j++) {
			gra[i][j] = ' ';
			graBool[i][j] = false;
			czyMoznaKGra[i][j] = true; //czy mozna wpisac w dane pole - po wcisnieciu 'k'
			czyMoznaJGra[i][j] = true; //czy jednoznaczne - po wc. 'j'
			uzupelnienieJ[i][j] = -1;
		}
	}
	bool czyMoznaA = true; //automatyczna detekcja; true - mozna zakonczyc gre, false - nie mozna zakonczyc gry
						   //plansza domyslna
	int planszaDomX0[20] = { 0, 1, 1, 2, 2, 5, 5, 5, 5, 5, 6, 6, 6, 7, 7, 7, 9, 11, 11, 11 };
	int planszaDomY0[20] = { 7, 1, 3, 9, 10, 2, 3, 5, 9, 10, 7, 10, 11, 3, 4, 9, 3, 3, 7, 10 };
	int planszaDomX1[16] = { 0, 1, 2, 2, 3, 3, 3, 3, 4, 8, 8, 8, 9, 10, 10, 11 };
	int planszaDomY1[16] = { 4, 8, 4, 6, 0, 3, 6, 11, 8, 1, 5, 6, 11, 4, 8, 0 };
	//nieMozesz[0] - true = nie mozesz wpisac danej cyfry, bo lamiesz regule 1, false - nie lamiesz reguly 1; [1] - true = lamiesz regule 2; [2] - true = lamiesz regule 3
	bool nieMozesz[3] = { false, false, false };
	bool nieMozeszDlaKolumn[2] = { false, false }; //[0] - dla reguly 2; true - kolumny maja za duzo 0/1, false - wiersze maja za duzo 0/1; [1] - dla reguly 3; true - sa takie same kolumny, false - takie same wiersze
												   //mozesz - true = mozesz wpisac dana cyfre, nie jest lamana zadna regula, automatic - true = tryb automatyczny wlaczony
	bool mozesz = false, automatic = false;
	//[i] = true -> podpowiedz nr i ma zostac wypisana na ekranie
	bool podpowiedzBool[13];
	for (int i = 0; i < 13; i++) podpowiedzBool[i] = false;


#ifndef __cplusplus
	Conio2_Init();
#endif

	settitle("Patryk Pardej 165249");
	do {
		SIZEtmp = SIZE;
		textbackground(BLACK);
		clrscr();
		textcolor(7);

		//RAMKA
		for (int i = RAMKA_Y; i <= SIZE + RAMKA_Y + 1; i++) {
			gotoxy(RAMKA_X, i);
			cputs("#");
			gotoxy(SIZE + RAMKA_X + 1, i);
			cputs("#");
		}
		for (int i = RAMKA_X + 1; i <= SIZE + RAMKA_X; i++) {
			gotoxy(i, RAMKA_Y);
			cputs("#");
			gotoxy(i, SIZE + RAMKA_Y + 1);
			cputs("#");
		}

		//automatyczna detekcja konca gry
		czyMoznaA = true;
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				if (!graBool[i][j] && gra[i][j] == ' ') {
					czyMoznaKJ[0] = true;
					czyMoznaKJ[1] = true;
					for (int k = 48; k <= 49; k++) {
						wpisywanie(gra, SIZE, k, liczbaJedynekKol, liczbaZerKol, liczbaJedynekWi, liczbaZerWi, i, j, nieMozesz, nieMozeszDlaKolumn, mozesz, nrPowt3, false);
						if (nieMozesz[0] || nieMozesz[1] || nieMozesz[2])
							czyMoznaKJ[k - 48] = false;
						if (!czyMoznaKJ[0] && !czyMoznaKJ[1]) {
							czyMoznaA = false;
							break;
						}
					}
				}
				if (!czyMoznaA) break;
			}
			if (!czyMoznaA) break;
		}

		//WPISANIE 0 i 1 GRACZA Z TABLICY GRA
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < SIZE; j++) {
				gotoxy(i + RAMKA_X + 1, j + RAMKA_Y + 1);
				if (graBool[i][j]) {
					textcolor(0);
					textbackground(14);
				}
				if (!czyMoznaKGra[i][j])
					textbackground(5);
				if (!czyMoznaJGra[i][j])
					textbackground(2);
				putch(gra[i][j]);
				textcolor(7);
				textbackground(0);
			}
		}
		dx = x - RAMKA_X - 1;
		dy = y - RAMKA_Y - 1;
		//LEGENDA
		gotoxy(LEG_X, LEG_Y);
		cputs("Imie i nazwisko: Patryk Pardej");
		gotoxy(LEG_X, LEG_Y + 1);
		cputs("Nr indeksu: 165249");
		gotoxy(LEG_X, LEG_Y + 2);
		cputs("Zaimplementowane: abcdefghijklmn");
		if (zero) sprintf(txt, "kod klawisza: 0x00 0x%02x", zn);
		else sprintf(txt, "kod klawisza: 0x%02x", zn);
		gotoxy(LEG_X, LEG_Y + 3);
		cputs(txt);
		gotoxy(LEG_X, LEG_Y + 4);
		sprintf(txt, "polozenie x/dx: %d, %d", x, dx);
		cputs(txt);
		gotoxy(LEG_X, LEG_Y + 5);
		sprintf(txt, "polozenie y/dy: %d, %d", y, dy);
		cputs(txt);
		gotoxy(LEG_X, LEG_Y + 6);
		cputs("ESC = wyjscie");
		gotoxy(LEG_X, LEG_Y + 7);
		cputs("strzalki = poruszanie");
		gotoxy(LEG_X, LEG_Y + 8);
		cputs("01 - wpisanie 0 lub 1");
		gotoxy(LEG_X, LEG_Y + 9);
		cputs("o - losowe wypelnienie pol");
		gotoxy(LEG_X, LEG_Y + 10);
		cputs("p - podpowiedz dla pola");
		gotoxy(LEG_X, LEG_Y + 11);
		cputs("r - wybor rozmiaru planszy");
		gotoxy(LEG_X, LEG_Y + 12);
		cputs("k - zaznaczenie pustych pol,");
		gotoxy(LEG_X, LEG_Y + 13);
		cputs("sprawdzenie mozliwosci ukonczenia gry");
		gotoxy(LEG_X, LEG_Y + 14);
		cputs("j - podswietlenie jednoznaczych pol");
		gotoxy(LEG_X, LEG_Y + 15);
		cputs("w - uzupelnienie jednoznaczych pol");
		gotoxy(LEG_X, LEG_Y + 16);
		cputs("(po uprzednim wcisnieciu 'j')");
		gotoxy(LEG_X, LEG_Y + 17);
		cputs("s - zapis gry");
		gotoxy(LEG_X, LEG_Y + 18);
		cputs("l - wczytanie gry");
		gotoxy(LEG_X, LEG_Y + 19);
		cputs("n - nowa gra (12x12)");
		gotoxy(LEG_X, LEG_Y + 20);
		cputs("a - automatyczna detekcja konca gry");
		gotoxy(LEG_X, LEG_Y + 21);
		if (automatic) cputs("Automatyczna detekcja konca gry wlaczona.");
		else cputs("Automatyczna detekcja konca gry wylaczona.");
		gotoxy(LEG_X, LEG_Y + 22);
		if (!czyMoznaA && automatic) cputs("NIE MOZNA ZAKONCZYC GRY.");
		for (int i = 0; i < 13; i++) {
			if (podpowiedzBool[i]) {
				gotoxy(LEG_X, LEG_Y + 23 + i);
				cputs(podpowiedz[i]);
			}
		}
		gotoxy(RAMKA_X + SIZE + 3, RAMKA_Y);
		cputs("01");
		gotoxy(RAMKA_X, RAMKA_Y + SIZE + 3);
		cputs("0");
		gotoxy(RAMKA_X, RAMKA_Y + SIZE + 4);
		cputs("1");
		for (int i = 0; i < SIZE; i++) {
			textcolor(7);
			gotoxy(RAMKA_X + SIZE + 3, RAMKA_Y + 1 + i);
			if (liczbaZerWi[i] >= SIZE / 2) textcolor(4);
			sprintf(txt, "%d", liczbaZerWi[i]);
			cputs(txt);
			textcolor(7);
			gotoxy(RAMKA_X + SIZE + 4, RAMKA_Y + 1 + i);
			if (liczbaJedynekWi[i] >= SIZE / 2) textcolor(4);
			sprintf(txt, "%d", liczbaJedynekWi[i]);
			cputs(txt);
			textcolor(7);
			gotoxy(RAMKA_X + 1 + i, RAMKA_Y + SIZE + 3);
			if (liczbaZerKol[i] >= SIZE / 2) textcolor(4);
			sprintf(txt, "%d", liczbaZerKol[i]);
			cputs(txt);
			textcolor(7);
			gotoxy(RAMKA_X + 1 + i, RAMKA_Y + SIZE + 4);
			if (liczbaJedynekKol[i] >= SIZE / 2) textcolor(4);
			sprintf(txt, "%d", liczbaJedynekKol[i]);
			cputs(txt);
		}
		textcolor(7);

		gotoxy(x, y);
		textcolor(attr);
		textbackground(back);

		// czekamy na naciœniêcie klawisza i odczytujemy jego kod,
		// wiêkszoœæ kodów klawiszy odpowiada ich znakom, np.
		// a to 'a', 2 to '2', + to '+', ale niektóre klawisze
		// specjalne, np. strza³ki s¹ zg³aszane jako dwa kolejne znaki,
		// z których pierwszy jest zerem, np. strza³ka w górê
		// to zero i 'H'
		zero = 0;
		nieMozesz[0] = false;
		nieMozesz[1] = false;
		nieMozesz[2] = false;
		mozesz = false;
		czyMoznaKJ[0] = true;
		czyMoznaKJ[1] = true;
		for (int i = 0; i < 13; i++) podpowiedzBool[i] = false;
		zn = getch();
		for (int i = 0; i < SIZE; i++)
			for (int j = 0; j < SIZE; j++) {
				if (zn != 's' && zn != 'S' && load == 1) czyMoznaKGra[i][j] = true;
				if (zn != 'w' && zn != 'W' && zn != 's' && zn != 'S' && uzup == 1) czyMoznaJGra[i][j] = true;
			}
		// nie chcemy, aby klawisz 'H' dzia³a³ jako strza³ka w górê
		// wiêc sprawdzamy, czy pierwszym znakiem by³o zero
		if (zn != 'w' && zn != 'W' && zn != 's' && zn != 'S' && uzup == 1) uzup = 0;
		if (zn != 's' && zn != 'S' && load == 1) load = 0;
		if (zn == 0) {
			zero = 1;		// je¿eli tak, to czytamy
			zn = getch();		// kolejny znak wiedz¹c ju¿, ¿e bêdzie to znak specjalny
			if (zn == 0x48) {
				if (y == RAMKA_Y + 1) y = RAMKA_Y + SIZE; //granice mapy
				else y--;
			}
			else if (zn == 0x50) {
				if (y == RAMKA_Y + SIZE) y = RAMKA_Y + 1; //granice mapy
				else y++;
			}
			else if (zn == 0x4b) {
				if (x == RAMKA_X + 1) x = RAMKA_X + SIZE; //granice mapy
				else x--;
			}
			else if (zn == 0x4d) {
				if (x == RAMKA_X + SIZE) x = RAMKA_X + 1; //granice mapy
				else x++;
			}
		}
		else if (zn == 48 || zn == 49) {
			if (!graBool[dx][dy]) {
				wpisywanie(gra, SIZE, zn, liczbaJedynekKol, liczbaZerKol, liczbaJedynekWi, liczbaZerWi, dx, dy, nieMozesz, nieMozeszDlaKolumn, mozesz, nrPowt3, true);
			}
		}
		else if (zn == 8 && gra[dx][dy] != ' ' && !graBool[dx][dy]) {
			if (gra[dx][dy] == 48) {
				liczbaZerKol[dx]--;
				liczbaZerWi[dy]--;
			}
			else {
				liczbaJedynekKol[dx]--;
				liczbaJedynekWi[dy]--;
			}
			gra[dx][dy] = ' ';
		}
		else if (zn == 'n' || zn == 'N')
		{
			SIZE = 12;
			for (int i = 0; i < SIZE; i++) {
				liczbaZerKol[i] = 0;
				liczbaZerWi[i] = 0;
				liczbaJedynekKol[i] = 0;
				liczbaJedynekWi[i] = 0;
				for (int j = 0; j < SIZE; j++) {
					gra[i][j] = ' ';
					graBool[i][j] = false;
					czyMoznaKGra[i][j] = true;
					czyMoznaJGra[i][j] = true;
					uzupelnienieJ[i][j] = -1;
				}
			}
			for (int i = 0; i < 20; i++) {
				gra[planszaDomX0[i]][planszaDomY0[i]] = '0';
				graBool[planszaDomX0[i]][planszaDomY0[i]] = true;
			}
			for (int i = 0; i < 16; i++) {
				gra[planszaDomX1[i]][planszaDomY1[i]] = '1';
				graBool[planszaDomX1[i]][planszaDomY1[i]] = true;
			}
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					if (gra[i][j] == '0') liczbaZerKol[i]++;
					if (gra[j][i] == '0') liczbaZerWi[i]++;
					if (gra[i][j] == '1') liczbaJedynekKol[i]++;
					if (gra[j][i] == '1') liczbaJedynekWi[i]++;
				}
			}
		}
		else if (zn == 'o' || zn == 'O') {
			init_los(gra, graBool, SIZE, liczbaJedynekKol, liczbaZerKol, liczbaJedynekWi, liczbaZerWi, czyMoznaKGra, czyMoznaJGra, uzupelnienieJ, nieMozesz, nieMozeszDlaKolumn, mozesz, nrPowt3);
		}
		else if (zn == 'p' || zn == 'P') {
			for (int i = 0; i < 13; i++) podpowiedzBool[i] = false;
			if (graBool[dx][dy]) {
				podpowiedzBool[0] = true;
				sprintf(podpowiedz[0], "Pole niemodyfikowalne.");
			}
			else {
				for (int i = 48; i <= 49; i++) {
					wpisywanie(gra, SIZE, i, liczbaJedynekKol, liczbaZerKol, liczbaJedynekWi, liczbaZerWi, dx, dy, nieMozesz, nieMozeszDlaKolumn, mozesz, nrPowt3, false);
					if (mozesz) {
						podpowiedzBool[1 + (i - 48)] = true;
						sprintf(podpowiedz[1 + (i - 48)], "Mozesz tu wpisac %d.", i - 48);
					}
					if (nieMozesz[0]) {
						podpowiedzBool[3 + (i - 48)] = true;
						sprintf(podpowiedz[3 + (i - 48)], "Nie mozesz tu wpisac %d, bo bedzie to trzecia ta sama cyfra z rzedu.", i - 48);
					}
					if (nieMozesz[1] && nieMozeszDlaKolumn[0]) {
						podpowiedzBool[5 + (i - 48)] = true;
						sprintf(podpowiedz[5 + (i - 48)], "Nie mozesz tu wpisac %d, bo w tej kolumnie znajduje sie juz maksymalna liczba tej cyfry.", i - 48);
					}
					if (nieMozesz[1] && !nieMozeszDlaKolumn[0]) {
						podpowiedzBool[7 + (i - 48)] = true;
						sprintf(podpowiedz[7 + (i - 48)], "Nie mozesz tu wpisac %d, bo w tym wierszu znajduje sie juz maksymalna liczba tej cyfry.", i - 48);
					}
					if (nieMozesz[2] && nieMozeszDlaKolumn[1]) {
						podpowiedzBool[9 + (i - 48)] = true;
						sprintf(podpowiedz[9 + (i - 48)], "Nie mozesz tu wpisac %d, bo istnieje juz taka kolumna o numerze %d.", i - 48, nrPowt3);
					}
					if (nieMozesz[2] && !nieMozeszDlaKolumn[1]) {
						podpowiedzBool[11 + (i - 48)] = true;
						sprintf(podpowiedz[11 + (i - 48)], "Nie mozesz tu wpisac %d, bo istnieje juz taki wiersz o numerze %d.", i - 48, nrPowt3);
					}
				}
			}
		}
		else if (zn == 'r' || zn == 'R') {
			SIZE = 0;
			gotoxy(LEG_X, LEG_Y + 23);
			cputs("Wpisz wybrany rozmiar planszy: ");
			int it = 0, mnoznik = 1, ilecyfr = 0;
			char nazwa[7];
			while (true) {
				rozmiar[it] = getch();
				if (rozmiar[it] == 13) break;
				sprintf(txt, "%d", rozmiar[it] - 48);
				cputs(txt);
				it++;
			}
			ilecyfr = it;
			it--;
			do {
				mnoznik = 1;
				for (int i = 0; i < ilecyfr - it - 1; i++)
					mnoznik = mnoznik * 10;
				SIZE = SIZE + (rozmiar[it] - 48) * mnoznik;
				it--;
			} while (it != -1);
			if (SIZE > 1) {
				for (int i = 0; i < SIZEtmp; i++) {
					liczbaZerKol[i] = 0;
					liczbaZerWi[i] = 0;
					liczbaJedynekKol[i] = 0;
					liczbaJedynekWi[i] = 0;
					for (int j = 0; j < SIZEtmp; j++) {
						gra[i][j] = ' ';
						graBool[i][j] = false;
						czyMoznaKGra[i][j] = true; //czy mozna wpisac w dane pole - po wcisnieciu 'k'
						czyMoznaJGra[i][j] = true; //czy jednoznaczne - po wc. 'j'
						uzupelnienieJ[i][j] = -1;
					}
				}
				FILE * plik;
				itoa(SIZE, nazwa, 10);
				nazwa[ilecyfr] = '.';
				nazwa[ilecyfr + 1] = 't';
				nazwa[ilecyfr + 2] = 'x';
				nazwa[ilecyfr + 3] = 't';
				nazwa[ilecyfr + 4] = '\0';
				plik = fopen(nazwa, "r");
				if (plik == NULL)
					init_los(gra, graBool, SIZE, liczbaJedynekKol, liczbaZerKol, liczbaJedynekWi, liczbaZerWi, czyMoznaKGra, czyMoznaJGra, uzupelnienieJ, nieMozesz, nieMozeszDlaKolumn, mozesz, nrPowt3);
				else {
					int c = 0;
					for (int i = 0; i < SIZE * SIZE + SIZE * 2; i++) {
						fseek(plik, i, SEEK_SET);
						int getc = fgetc(plik);
						if (getc == 48) {
							gra[c%SIZE][c / SIZE] = '0';
							graBool[c%SIZE][c / SIZE] = true;
						}
						else if (getc == 49) {
							gra[c%SIZE][c / SIZE] = '1';
							graBool[c%SIZE][c / SIZE] = true;
						}
						else if (getc != 46) continue;
						c++;
					}
					//zliczenie cyfr 0 i 1 w kazdej kolumnie i wierszu
					for (int i = 0; i < SIZE; i++) {
						for (int j = 0; j < SIZE; j++) {
							if (gra[i][j] == '0') liczbaZerKol[i]++;
							if (gra[j][i] == '0') liczbaZerWi[i]++;
							if (gra[i][j] == '1') liczbaJedynekKol[i]++;
							if (gra[j][i] == '1') liczbaJedynekWi[i]++;
						}
					}
					fclose(plik);
				}
			}
			else {
				SIZE = SIZEtmp;
				cputs("Zly rozmiar planszy!");
			}
		}
		else if (zn == 'k' || zn == 'K') {
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					if (!graBool[i][j] && gra[i][j] == ' ') {
						czyMoznaKJ[0] = true;
						czyMoznaKJ[1] = true;
						for (int k = 48; k <= 49; k++) {
							wpisywanie(gra, SIZE, k, liczbaJedynekKol, liczbaZerKol, liczbaJedynekWi, liczbaZerWi, i, j, nieMozesz, nieMozeszDlaKolumn, mozesz, nrPowt3, false);
							if (nieMozesz[0] || nieMozesz[1] || nieMozesz[2])
								czyMoznaKJ[k - 48] = false;
							if (!czyMoznaKJ[0] && !czyMoznaKJ[1])
								czyMoznaKGra[i][j] = false;
						}
					}
				}
			}
			load = 1;
		}
		else if (zn == 'j' || zn == 'J') {
			for (int i = 0; i < SIZE; i++) {
				for (int j = 0; j < SIZE; j++) {
					if (!graBool[i][j] && gra[i][j] == ' ') {
						czyMoznaKJ[0] = true;
						czyMoznaKJ[1] = true;
						for (int k = 48; k <= 49; k++) {
							wpisywanie(gra, SIZE, k, liczbaJedynekKol, liczbaZerKol, liczbaJedynekWi, liczbaZerWi, i, j, nieMozesz, nieMozeszDlaKolumn, mozesz, nrPowt3, false);
							if (nieMozesz[0] || nieMozesz[1] || nieMozesz[2])
								czyMoznaKJ[k - 48] = false;
						}
						if (!czyMoznaKJ[0] && czyMoznaKJ[1]) {
							czyMoznaJGra[i][j] = false;
							uzupelnienieJ[i][j] = 1;
						}
						else if (czyMoznaKJ[0] && !czyMoznaKJ[1]) {
							czyMoznaJGra[i][j] = false;
							uzupelnienieJ[i][j] = 0;
						}
					}
				}
			}
			uzup = 1;
		}
		else if ((zn == 'w' || zn == 'W') && uzup == 1) {
			for (int i = 0; i < SIZE; i++)
				for (int j = 0; j < SIZE; j++) {
					if (!czyMoznaJGra[i][j])
					{
						wpisywanie(gra, SIZE, uzupelnienieJ[i][j] + 48, liczbaJedynekKol, liczbaZerKol, liczbaJedynekWi, liczbaZerWi, i, j, nieMozesz, nieMozeszDlaKolumn, mozesz, nrPowt3, false);
						if (mozesz) {
							gra[i][j] = uzupelnienieJ[i][j] + 48;
							if (uzupelnienieJ[i][j] == 0) {
								liczbaZerKol[i]++;
								liczbaZerWi[j]++;
							}
							else {
								liczbaJedynekKol[i]++;
								liczbaJedynekWi[j]++;
							}
						}
						uzupelnienieJ[i][j] = -1;
					}
				}
		}
		else if (zn == 'a' || zn == 'A') {
			if (automatic) automatic = false;
			else automatic = true;
		}
		else if (zn == 's' || zn == 'S') {
			FILE * plik;
			gotoxy(LEG_X, LEG_Y + 23);
			cputs("Podaj nazwe pliku: ");
			char nazwa[50] = {};
			for (int i = 0; i < 50; i++)
			{
				nazwa[i] = getche();
				if (nazwa[i] == 0x0d) {
					nazwa[i] = '\0';
					break;
				}
			}
			plik = fopen(nazwa, "w");
			fprintf(plik, "%d\n", SIZE);
			for (int i = 0; i < SIZE * SIZE; i++) {
				if (gra[i%SIZE][i / SIZE] != ' ') fprintf(plik, "%c", gra[i%SIZE][i / SIZE]);
				else fprintf(plik, ".");
				fprintf(plik, "%d", graBool[i%SIZE][i / SIZE]);
				fprintf(plik, "%d", czyMoznaKGra[i%SIZE][i / SIZE]);
				fprintf(plik, "%d", czyMoznaJGra[i%SIZE][i / SIZE]);
				if (i % SIZE == SIZE - 1) fprintf(plik, "\n");
				else fprintf(plik, " ");
			}
			fclose(plik);
		}
		else if (zn == 'l' || zn == 'L') {
			uzup = 1;
			load = 1;
			FILE * plik;
			gotoxy(LEG_X, LEG_Y + 23);
			cputs("Podaj nazwe pliku: ");
			char nazwa[50] = {};
			for (int i = 0; i < 50; i++)
			{
				nazwa[i] = getche();
				if (nazwa[i] == 0x0d) {
					nazwa[i] = '\0';
					break;
				}
			}
			plik = fopen(nazwa, "r");
			if (plik != NULL) {
				for (int i = 0; i < SIZE; i++) {
					liczbaZerKol[i] = 0;
					liczbaZerWi[i] = 0;
					liczbaJedynekKol[i] = 0;
					liczbaJedynekWi[i] = 0;
					for (int j = 0; j < SIZE; j++) {
						gra[i][j] = ' ';
						graBool[i][j] = false;
						czyMoznaKGra[i][j] = true; //czy mozna wpisac w dane pole - po wcisnieciu 'k'
						czyMoznaJGra[i][j] = true; //czy jednoznaczne - po wc. 'j'
						uzupelnienieJ[i][j] = -1;
					}
				}
				char sizeC[3];
				fseek(plik, 0, SEEK_SET);
				fgets(sizeC, 3, plik);
				SIZE = atoi(sizeC);
				int c = 0;
				while (true) {
					fseek(plik, 0, SEEK_CUR);
					int get = fgetc(plik);
					if (get != 48 && get != 49 && get != 46) continue;
					if (get == 48)
						gra[c%SIZE][c / SIZE] = '0';
					else if (get == 49)
						gra[c%SIZE][c / SIZE] = '1';
					fseek(plik, 0, SEEK_CUR);
					get = fgetc(plik);
					if (get != 48 && get != 49 && get != 46) continue;
					if (get == 48)
						graBool[c%SIZE][c / SIZE] = false;
					else if (get == 49)
						graBool[c%SIZE][c / SIZE] = true;
					fseek(plik, 0, SEEK_CUR);
					get = fgetc(plik);
					if (get != 48 && get != 49 && get != 46) continue;
					if (get == 48)
						czyMoznaKGra[c%SIZE][c / SIZE] = false;
					else if (get == 49)
						czyMoznaKGra[c%SIZE][c / SIZE] = true;
					fseek(plik, 0, SEEK_CUR);
					get = fgetc(plik);
					if (get != 48 && get != 49 && get != 46) continue;
					if (get == 48)
						czyMoznaJGra[c%SIZE][c / SIZE] = false;
					else if (get == 49)
						czyMoznaJGra[c%SIZE][c / SIZE] = true;
					c++;
					if (c == SIZE * SIZE) break;
				}
				//zliczenie cyfr 0 i 1 w kazdej kolumnie i wierszu
				for (int i = 0; i < SIZE; i++) {
					for (int j = 0; j < SIZE; j++) {
						if (gra[i][j] == '0') liczbaZerKol[i]++;
						if (gra[j][i] == '0') liczbaZerWi[i]++;
						if (gra[i][j] == '1') liczbaJedynekKol[i]++;
						if (gra[j][i] == '1') liczbaJedynekWi[i]++;
					}
				}
				fclose(plik);
			}
			else {
				cputs("Nie ma takiego pliku!");
			}
		}
	} while (zn != 27);

	for (int i = 0; i < 99; i++) {
		delete[] gra[i];
		delete[] graBool[i];
		delete[] czyMoznaKGra[i];
		delete[] czyMoznaJGra[i];
		delete[] uzupelnienieJ[i];
	}
	delete[] gra;
	delete[] graBool;
	delete[] czyMoznaKGra;
	delete[] czyMoznaJGra;
	delete[] uzupelnienieJ;
	delete[] liczbaZerKol;
	delete[] liczbaZerWi;
	delete[] liczbaJedynekKol;
	delete[] liczbaJedynekWi;

	return 0;
}