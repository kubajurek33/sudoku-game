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

	void Run(); // Funkcja uruchamiaj¹ca w pêtli (w zale¿noœci od stanu) pozosta³e funkcje w klasie
	void GameMenu(); // Funkcja uruchamiaj¹ca menu
	void Play(); // Funkcja uruchamiaj¹ca grê
	void EndMenu(); // Funkcja uruchamiaj¹ca menu koñcowe

private:

	enum GameState { MENU, GAME, ENDMENU }; // 3 Stany programu
	GameState state; // Zmienna okreœlaj¹ca stan programu

	RectangleShape PlayButton; // Przycisk u¿yty w menu
	RectangleShape ExitButton; // Przycisk u¿yty w menu

	Font font; // Czcionka
	Texture background; // T³o gry
	Sprite b;
	Text PlayText; // Tekst przycisku
	Text PlayText2; // Tekst przycisku
	Text ExitText; // Tekst przycisku
	Text Title; // Tytu³ gry
	Text Title2; // Tytu³ gry
};
