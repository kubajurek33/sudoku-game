#include "Manager.h"
#include <SFML/Graphics.hpp>
#include<string>


using namespace sf;
using namespace std;

RenderWindow window(sf::VideoMode(700, 700), "Sudoku!");

Manager::Manager()
{
	// Wgranie czcionki oraz t³a z plików
	font.loadFromFile("assets/digital.ttf");
	background.loadFromFile("Images/background1.jpg");
	background.setSmooth(true);

	// Konfiguracja tytu³u gry
	Title.setFillColor(sf::Color::Black);
	Title.setFont(font);
	Title.setCharacterSize(70);
	Title.setString("SUDOKU GAME!");
	Title.setPosition(172, 50);

	// Konfiguracja przycisku "Start" oraz jego zawartoœci w postaci tekstu
	PlayButton.setSize(sf::Vector2f(200, 50));
	PlayButton.setPosition(250, 270);
	PlayButton.setFillColor(sf::Color::Black);
	PlayText.setFillColor(sf::Color::White);
	PlayText.setFont(font);
	PlayText.setCharacterSize(20);
	PlayText.setString("Start");
	PlayText.setPosition(330, 280);

	// Konfiguracja przycisku "Zakoncz" oraz jego zawartoœci w postaci tekstu
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

// Funkcja Run przy u¿yciu pêtli wykonuje jedn¹ z 3 funkcji w zale¿noœci od stanu programu
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

//Funkcja wyœwietlaj¹ca Menu
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
				state = GAME; // Je¿eli kursor znajdujê siê nad przyciskiem "zagraj" oraz nast¹pi³o klikniêcie lewego przycisku myszy zostanie wyœwietlona gra
			if (ExitButton.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				window.close(); // Je¿eli kursor znajdujê siê nad przyciskiem "zakoncz" oraz nast¹pi³o klikniêcie lewego przycisku myszy program zostanie zakoñczony
		}

		// Poni¿sze funkcje podœwietlaj¹ poszczególne przyciski w momencie najechania na nie kursorem
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

		// "Narysowanie" oraz wyœwietlenie t³a, tytu³u oraz przycisków
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

// Funkcja wyœwietlaj¹ca grê g³ówn¹ przy u¿yciu funkcji RunDisplay z klasy Display
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

// Funkcja wyœwietlaj¹ca Menu koñcowe (po ukoñczeniu gry)
void Manager::EndMenu()
{
	state = ENDMENU;
	// Ustawienie tytu³u informuj¹cego o ukoñczeniu gry
	Title.setCharacterSize(55);
	Title.setString("Gratulacje ukonczyles gre!");
	Title.setPosition(40, 150);

	// Ustawienie treœci przycisku z "zagraj" na "zagraj ponownie"
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
				state = GAME; // Je¿eli kursor znajdujê siê nad przyciskiem "zagraj" oraz nast¹pi³o klikniêcie lewego przycisku myszy zostanie ponownie wyœwietlona gra
			if (ExitButton.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
				window.close(); // Je¿eli kursor znajdujê siê nad przyciskiem "zakoncz" oraz nast¹pi³o klikniêcie lewego przycisku myszy program zostanie zakoñczony
		}

		// Poni¿sze funkcje podœwietlaj¹ poszczególne przyciski w momencie najechania na nie kursorem
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

		// "Narysowanie" oraz wyœwietlenie t³a, tytu³u oraz przycisków
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
