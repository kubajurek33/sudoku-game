#include "Manager.h"
#include <SFML/Graphics.hpp>
#include<string>


using namespace sf;
using namespace std;

RenderWindow window(sf::VideoMode(700, 700), "Sudoku!");

Manager::Manager()
{
	// Wgranie czcionki oraz t�a z plik�w
	font.loadFromFile("assets/digital.ttf");
	background.loadFromFile("Images/background1.jpg");
	background.setSmooth(true);

	// Konfiguracja tytu�u gry
	Title.setFillColor(sf::Color::Black);
	Title.setFont(font);
	Title.setCharacterSize(70);
	Title.setString("SUDOKU GAME!");
	Title.setPosition(172, 50);

	// Konfiguracja przycisku "Start" oraz jego zawarto�ci w postaci tekstu
	PlayButton.setSize(sf::Vector2f(200, 50));
	PlayButton.setPosition(250, 270);
	PlayButton.setFillColor(sf::Color::Black);
	PlayText.setFillColor(sf::Color::White);
	PlayText.setFont(font);
	PlayText.setCharacterSize(20);
	PlayText.setString("Start");
	PlayText.setPosition(330, 280);

	// Konfiguracja przycisku "Zakoncz" oraz jego zawarto�ci w postaci tekstu
	ExitButton.setSize(sf::Vector2f(200, 50));
	ExitButton.setPosition(250, 370);
	ExitButton.setFillColor(sf::Color::Black);
	ExitText.setFillColor(sf::Color::White);
	ExitText.setFont(font);
	ExitText.setCharacterSize(20);
	ExitText.setString("Zakoncz");
	ExitText.setPosition(315, 380);
}

Manager::~Manager()
{
}

// Funkcja Run przy u�yciu p�tli wykonuje jedn� z 3 funkcji w zale�no�ci od stanu programu
void Manager::Run()
{
	while (1)
	{
		switch (state)
		{
		case GameState::MENU:
			GameMenu();
			break;
		case GameState::GAME:
			Play();
			break;
		case GameState::ENDMENU:
			EndMenu();
			break;
		}
	}
}

//Funkcja wy�wietlaj�ca Menu
void Manager::GameMenu()
{
	state = MENU;
	while (state == MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (PlayButton.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				state = GAME; // Je�eli kursor znajduj� si� nad przyciskiem "zagraj" oraz nast�pi�o klikni�cie lewego przycisku myszy zostanie wy�wietlona gra
			if (ExitButton.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				window.close(); // Je�eli kursor znajduj� si� nad przyciskiem "zakoncz" oraz nast�pi�o klikni�cie lewego przycisku myszy program zostanie zako�czony
		}

		// Poni�sze funkcje pod�wietlaj� poszczeg�lne przyciski w momencie najechania na nie kursorem
		if (PlayButton.getGlobalBounds().contains(mouse))
		{
			PlayButton.setFillColor(Color::Yellow);
			PlayText.setFillColor(Color::Black);
		}
		else
		{
			PlayButton.setFillColor(Color::Black);
			PlayText.setFillColor(Color::White);
		}
		if (ExitButton.getGlobalBounds().contains(mouse))
		{
			ExitButton.setFillColor(Color::Yellow);
			ExitText.setFillColor(Color::Black);
		}
		else
		{
			ExitButton.setFillColor(Color::Black);
			ExitText.setFillColor(Color::White);
		}

		// "Narysowanie" oraz wy�wietlenie t�a, tytu�u oraz przycisk�w
		window.clear();
		Sprite b(background);
		window.draw(b);
		window.draw(PlayButton);
		window.draw(PlayText);
		window.draw(ExitButton);
		window.draw(ExitText);
		window.draw(Title);
		window.display();
	}
}

// Funkcja wy�wietlaj�ca gr� g��wn� przy u�yciu funkcji RunDisplay z klasy Display
void Manager::Play()
{

	while (state == GAME && window.isOpen())
	{

		Event event;
		Display display;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();
			if (display.RunDisplay(window))
				state = GAME;
			else
				state = ENDMENU;
		}
		window.clear();
		window.display();
	}

}

// Funkcja wy�wietlaj�ca Menu ko�cowe (po uko�czeniu gry)
void Manager::EndMenu()
{
	state = ENDMENU;
	// Ustawienie tytu�u informuj�cego o uko�czeniu gry
	Title.setCharacterSize(55);
	Title.setString("Gratulacje ukonczyles gre!");
	Title.setPosition(40, 150);

	// Ustawienie tre�ci przycisku z "zagraj" na "zagraj ponownie"
	PlayText.setCharacterSize(20);
	PlayText.setString("Zagraj ponownie");
	PlayText.setPosition(290, 280);

	while (state == ENDMENU && window.isOpen())
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (PlayButton.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				state = GAME; // Je�eli kursor znajduj� si� nad przyciskiem "zagraj" oraz nast�pi�o klikni�cie lewego przycisku myszy zostanie ponownie wy�wietlona gra
			if (ExitButton.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				window.close(); // Je�eli kursor znajduj� si� nad przyciskiem "zakoncz" oraz nast�pi�o klikni�cie lewego przycisku myszy program zostanie zako�czony
		}

		// Poni�sze funkcje pod�wietlaj� poszczeg�lne przyciski w momencie najechania na nie kursorem
		if (PlayButton.getGlobalBounds().contains(mouse))
		{
			PlayButton.setFillColor(Color::Yellow);
			PlayText.setFillColor(Color::Black);
		}
		else
		{
			PlayButton.setFillColor(Color::Black);
			PlayText.setFillColor(Color::White);
		}
		if (ExitButton.getGlobalBounds().contains(mouse))
		{
			ExitButton.setFillColor(Color::Yellow);
			ExitText.setFillColor(Color::Black);
		}
		else
		{
			ExitButton.setFillColor(Color::Black);
			ExitText.setFillColor(Color::White);
		}

		// "Narysowanie" oraz wy�wietlenie t�a, tytu�u oraz przycisk�w
		window.clear();
		Sprite b(background);
		window.draw(b);
		window.draw(PlayButton);
		window.draw(PlayText);
		window.draw(ExitButton);
		window.draw(ExitText);
		window.draw(Title);
		window.display();
	}
}
