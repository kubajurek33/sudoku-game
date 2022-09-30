#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Display.h"

using namespace sf;

class Manager
{
public:

	Manager(); // Konstruktor klasy
	~Manager(); // Destruktor klasy

	void Run(); // Funkcja uruchamiaj�ca w p�tli (w zale�no�ci od stanu) pozosta�e funkcje w klasie
	void GameMenu(); // Funkcja uruchamiaj�ca menu
	void Play(); // Funkcja uruchamiaj�ca gr�
	void EndMenu(); // Funkcja uruchamiaj�ca menu ko�cowe

private:

	enum GameState { MENU, GAME, ENDMENU }; // 3 Stany programu
	GameState state; // Zmienna okre�laj�ca stan programu

	RectangleShape PlayButton; // Przycisk u�yty w menu
	RectangleShape ExitButton; // Przycisk u�yty w menu

	Font font; // Czcionka
	Texture background; // T�o gry
	Sprite b;
	Text PlayText; // Tekst przycisku
	Text PlayText2; // Tekst przycisku
	Text ExitText; // Tekst przycisku
	Text Title; // Tytu� gry
	Text Title2; // Tytu� gry
};
