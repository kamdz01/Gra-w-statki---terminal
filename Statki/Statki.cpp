// Statki.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
// 0 to woda
// 1 to woda dookoła
// 10 + numer to statek
// 30 + numer to zatopione pole
// 3 to cały zatopiony statek
// 4 to strzał w wode
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define DEBUG

void clear()
{
	while (getchar() != '\n');
}

void init(int tab[10][10]) {
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++) {
			tab[i][j] = 0;
		}
	}
}

void wypisz(int tab[10][10]) {
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++) {
			printf_s("%d ", tab[i][j]);
			if (tab[i][j] < 10)
			{
				printf_s(" ");
			}
		}
		printf_s("\n");
	}
}

void wypiszpom(int tab[10][10])
{
	printf_s("  | ");
	for (int i = 0; i < 10; i++)
	{
		printf_s("%c ", 65 + i);
	}
	printf_s("\n");
	for (int i = 0; i < 10; i++)
	{
		if (i==9)
		{
			printf_s("%d| ", i + 1);
		}
		else
		{
			printf_s("%d | ", i + 1);
		}
		for (int j = 0; j < 10; j++) {
			if (tab[i][j] == 3)
			{
				printf_s("x ");
			}
			else if (tab[i][j] > 30)
			{
				printf_s("X ");
			}
			else if (tab[i][j] == 4)
			{
				printf_s("- ");
			}
			else
			{
				printf_s("O ");
			}
		}
		printf_s("\n");
	}
}

int sprawdz(int tab[10][10], int start[2], int x, int y)
{
	for (int i = start[0]; i < start[0] + x - 2; i++)
	{
		for (int j = start[1]; j < start[1] + y - 2; j++)
		{
			if (i < 0 || i>9 || j < 0 || j>9)
			{
				return 1;
			}

		}
	}

	for (int i = start[0]-1; i < start[0] + x - 1; i++)
	{
		for (int j = start[1]-1; j < start[1] + y - 1; j++)
		{
			if (i >= 0 && i <= 9 && j >= 0 && j <=9)
			{
				if (tab[i][j] > 10)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

int zaznacz(int tab[10][10], int start[2], int x, int y, int licznik)
{

	for (int i = start[0] - 1; i < start[0] + x - 1; i++)
	{
		for (int j = start[1] - 1; j < start[1] + y - 1; j++)
		{
			if (i >= 0 && i <= 9 && j >= 0 && j <= 9)
			{
				tab[i][j] = 1;
			}

		}
	}

	for (int i = start[0]; i < start[0] + x - 2; i++)
	{
		for (int j = start[1]; j < start[1] + y - 2; j++)
		{
			tab[i][j] =  licznik;
		}
	}
	return 0;
}

void statek(int tab[10][10], int rozmiar, int &licznik)
{
	for (int i = 0; i < 1; i++)
	{
		int start[2] = { (rand() % 10), (rand() % 10) };
		int kierunek = rand() % 2;
#ifdef DEBUG
		printf_s("%d %d %d \n", start[0], start[1], kierunek);
#endif // DEBUG
		if (kierunek == 0)
		{
			if (!sprawdz(tab, start, 3, rozmiar + 2))
			{
				zaznacz(tab, start, 3, rozmiar + 2, licznik);
#ifdef DEBUG
				wypisz(tab);
#endif // DEBUG
			}
			else
			{
				i--;
			}
		}
		if (kierunek == 1)
		{
			if (!sprawdz(tab, start, rozmiar + 2, 3))
			{
				zaznacz(tab, start, rozmiar + 2, 3, licznik);
#ifdef DEBUG
				wypisz(tab);
#endif // DEBUG
			}
			else
			{
				i--;
			}
		}
	}
	licznik++;
}

void rozmiesc(int tab[10][10])
{
	int licznik = 11;
	statek(tab, 4, licznik);
	for (int i = 0; i < 2; i++)
	{
		statek(tab, 3, licznik);
	}
	for (int i = 0; i < 3; i++)
	{
		statek(tab, 2, licznik);
	}
	for (int i = 0; i < 4; i++)
	{
		statek(tab, 1, licznik);
	}
#ifdef DEBUG
	printf_s("%d", licznik);
#endif // DEBUG
}

int znajdz(int tab[10][10], int wartosc)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++) {
			if (tab[i][j] == wartosc)
			{
				return 0;
			}
		}
	}
	return 1;
}

int zatop(int tab[10][10], int numer)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++) {
			if (tab[i][j] == numer)
			{
				tab[i][j] = 3;
			}
		}
	}
	if (znajdz(tab, numer))
	{
		return 1;
	}
	return 0;
}

void a(int tab[10][10])
{
	int strzal, licznik = 10;
	int pole[2] = { 0,0 };
	char polestr;

	while (licznik > 0)
	{
		printf_s("Podaj pole: ");
		scanf_s(" %c", &polestr, 2);
		scanf_s("%d", &pole[1]);
		clear();
		pole[0] = int(polestr);
if (pole[0] >= 65 && pole[0] <= 74)
		{
			pole[0] -= 65;
		}
		else if (pole[0] >= 97 && pole[0] <= 106)
		{
			pole[0] -= 97;
		}
		else
		{
			pole[0] = -1;
		}

		if (pole[1] < 1 || pole[1] > 10)
		{
			pole[0] = -1;
		}

		if (pole[0] == -1 || pole[1] == -1)
		{
			printf_s("Wprowadzono bledne dane!\n");
		}
		else
		{
			pole[1] --;
#ifdef DEBUG
			printf_s("%d %d\n", pole[0], pole[1]);
#endif // DEBUG

			strzal = tab[pole[1]][pole[0]];
#ifdef DEBUG
			printf_s("%d\n", strzal);
#endif // DEBUG
			if (strzal > 30 || strzal == 4 || strzal == 3)
			{
				printf_s("Juz strzeliles w to pole!\n");
			}
			else if (strzal > 10)
			{
				tab[pole[1]][pole[0]] += 20;
				if (!znajdz(tab, strzal))
				{
					printf_s("trafiony!\n");
				}
				else
				{
					printf_s("trafiony i zatopiony!\n");
					zatop(tab, strzal+20);
					licznik--;
				}
			}
			else
			{
				tab[pole[1]][pole[0]] = 4;
				printf_s("pudlo!\n");
			}
			wypiszpom(tab);
#ifdef DEBUG
			wypisz(tab);
#endif // debug
		}
	}
}

int main()
{
	int pole[2] = { 0,0 };
	srand(time(0));
    int plansza[10][10];
	init(plansza);
	printf_s("Plansza zainicjalizowana\n");
	rozmiesc(plansza);
	printf_s("Statki rozmieszczone\n");
	printf_s("Zaczynamy gre. Oznaczenia na mapie:\nX - statek trafiony\nx - statek zatopiony\n(-) - brak statku\nO - pole niesprawdzone\nPola podawaj w formacie [litera][liczba], np: A1, lub a1\n");
	wypiszpom(plansza);
	sprawdz_dane(plansza);
	printf_s("Wygrales! koniec gry");
}