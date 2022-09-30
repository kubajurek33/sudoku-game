#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include <cstring>
#include "Manager.h"
#include <stdio.h>
#include <stdlib.h>    
#include <time.h> 
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <Windows.h>


using namespace std;
using namespace sf;

class Display
{

public:

	Display(); // Konstruktor klasy
	~Display(); // Destruktor klasy

	void SetGame(); // Funkcja "ustawiaj�ca" diagram 9x9

	bool RunDisplay(RenderWindow& window); // Funkcja wy�wietlaj�ca gr�
	void DrawSudoku(RenderWindow& window); // Funkcja "rysuje" diagram 

	void MouseOverSquare(RenderWindow& window); // Funkcja sprawdzaj�ca czy kursor znajduj� si� nad poszczeg�lnymi kom�rkami
	void MouseOverButton(RenderWindow& window); // Funkcja sprawdzaj�ca czy kursor znajduj� si� nad poszczeg�lnymi przyciskami

	bool CheckSquare(); // Funkcja sprawdzaj�ca poprawno�� uzupe�nienia sudoku w ka�dym kwadracie 3x3
	bool CheckRow(); // Funkcja sprawdzaj�ca poprawno�� uzupe�nienia sudoku w ka�dym rz�dzie
	bool CheckColumn(); // Funkcja sprawdzaj�ca poprawno�� uzupe�nienia sudoku w ka�dej kolumnie
	bool CheckWin(); // Funkcja sprawdzaj�ca czy ka�dy warunek gry sudoku jest spe�niony

private:
	
	Font font; // Czcionka 
	Texture background, gamebackground; // T�o gry oraz t�o diagramu

	RectangleShape CheckButton, EndButton; // Przycisk Check, Reset
	Text CheckText, EndText; // Tekst przycisku Check, Reset

	RectangleShape Square[9][9]; // Dwuwymiarowa tablica okre�laj�ca kom�rki gry sudoku 
	Text SquareText[9][9]; // Dwuwymiarowa tablica okre�laj�ca zawarto�� kom�rki (cyfr�)
	int lockvalue[9][9]; // Dwuwymiarowa tablica okre�laj�ca czy kom�rka mo�e by� zmodyfikowana w trakcie gry

};

