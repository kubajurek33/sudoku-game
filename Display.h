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

	void SetGame(); // Funkcja "ustawiaj¹ca" diagram 9x9

	bool RunDisplay(RenderWindow& window); // Funkcja wyœwietlaj¹ca grê
	void DrawSudoku(RenderWindow& window); // Funkcja "rysuje" diagram 

	void MouseOverSquare(RenderWindow& window); // Funkcja sprawdzaj¹ca czy kursor znajdujê siê nad poszczególnymi komórkami
	void MouseOverButton(RenderWindow& window); // Funkcja sprawdzaj¹ca czy kursor znajdujê siê nad poszczególnymi przyciskami

	bool CheckSquare(); // Funkcja sprawdzaj¹ca poprawnoœæ uzupe³nienia sudoku w ka¿dym kwadracie 3x3
	bool CheckRow(); // Funkcja sprawdzaj¹ca poprawnoœæ uzupe³nienia sudoku w ka¿dym rzêdzie
	bool CheckColumn(); // Funkcja sprawdzaj¹ca poprawnoœæ uzupe³nienia sudoku w ka¿dej kolumnie
	bool CheckWin(); // Funkcja sprawdzaj¹ca czy ka¿dy warunek gry sudoku jest spe³niony

private:
	
	Font font; // Czcionka 
	Texture background, gamebackground; // T³o gry oraz t³o diagramu

	RectangleShape CheckButton, EndButton; // Przycisk Check, Reset
	Text CheckText, EndText; // Tekst przycisku Check, Reset

	RectangleShape Square[9][9]; // Dwuwymiarowa tablica okreœlaj¹ca komórki gry sudoku 
	Text SquareText[9][9]; // Dwuwymiarowa tablica okreœlaj¹ca zawartoœæ komórki (cyfrê)
	int lockvalue[9][9]; // Dwuwymiarowa tablica okreœlaj¹ca czy komórka mo¿e byæ zmodyfikowana w trakcie gry

};

