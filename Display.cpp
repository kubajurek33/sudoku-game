#include "Display.h"
#include <random>

Display::Display()
{
	// Wgranie czcionki oraz t�a z plik�w
	font.loadFromFile("assets/digital.ttf");
	background.loadFromFile("Images/background1.jpg");
	background.setSmooth(true);
	gamebackground.loadFromFile("Images/gamebackground.png");
	gamebackground.setSmooth(true);

	// Konfiguracja przycisku Check
	CheckText.setFont(font);
	CheckText.setCharacterSize(30);
	CheckText.setString("C");
	CheckButton.setSize(Vector2f(40, 40));
	CheckButton.setFillColor(Color::Black);

	// Konfiguracja przycisku Exit
	EndText.setFont(font);
	EndText.setCharacterSize(30);
	EndText.setString("R");
	EndButton.setSize(Vector2f(40, 40));
	EndButton.setFillColor(Color::Black);

}

Display::~Display()
{
}

// Funkcja ustawiaj�ca diagram
void Display::SetGame()
{
	// Zadeklarowanie tablicy dwuwymiarowej, przypisanie do niej wartosci (warto�� 0 oznacza, �e t� kom�rk� bedzie mozna modyfikowa�)
	int grid[9][9] = {{7,0,6, 1,2,8, 3,4,5},
					  {3,4,1, 7,6,5 ,8,9,0},
					  {2,0,5, 3,9,0 ,0,1,6},
					  {1,5,2, 9,0,6 ,4,7,8},
					  {6,7,0, 8,4,2 ,5,3,1},
					  {0,3,4, 5,1,0 ,6,0,9},
					  {4,1,7, 6,5,9 ,2,0,3},
					  {0,2,3, 4,8,0 ,9,6,7},
					  {9,6,8, 2,0,3 ,1,5,4}};

	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 8; j++)
		{
			// Konfiguracja ka�dej kom�rki 
			SquareText[i][j].setFont(font);
			SquareText[i][j].setCharacterSize(30);
			Square[i][j].setSize(Vector2f(40, 40));
			Square[i][j].setFillColor(Color::Black);

			// Je�eli warto�� kom�rki r�wna jest 0, otrzymuje ona pust� tre�� oraz czarny kolor czcionki
			// Ponadto do zmiennej lockvalue o takim samym indeksie przypisywana jest warto�� 1
			if (grid[j][i] == 0)
			{
				SquareText[i][j].setFillColor(Color::Black);
				SquareText[i][j].setString(" ");
				lockvalue[i][j] = 1;
			}

			// Je�eli warto�� kom�rki r�wna nie jest r�wna 0, otrzymuje ona tre�� r�wn� warto�ci przypisanej do tablicy grid oraz bia�y kolor czcionki
			// Ponadto do zmiennej lockvalue o takim samym indeksie przypisywana jest warto�� 0
			else
			{
				SquareText[i][j].setFillColor(Color::White);
				SquareText[i][j].setString(to_string(grid[j][i]));
				lockvalue[i][j] = 0;
			}


		}
	}

}


// Funkcja wy�wietlaj�ca gr�
bool Display::RunDisplay(RenderWindow& window)
{
	SetGame();
	Sprite b1(background);
	Sprite b2(gamebackground);

	Vector2f mouse(Mouse::getPosition(window));
	Manager manager;

	while (window.isOpen())
	{
		Event event;
		Vector2f mouse(Mouse::getPosition(window));
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) window.close();

			if (CheckButton.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left && (CheckWin()))
			{
				manager.EndMenu(); // Je�eli diagram zosta� uzupe�niony poprawnie oraz u�ytkownik naci�nie przycisk check wy�wietlone zostanie menu ko�cowe
				SetGame(); // Ponadto diagram zostanie ustawiony ponownie
			}

			if (EndButton.getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased)
			{
				SetGame(); // Je�eli u�ytkownik nacisnie przycisk reset diagram zostanie ustawiony ponownie
			}

		}

		// "Wyrysowanie t�a gry oraz t�a diagramu, u�ycie funkcji zadeklarowanych w klasie
		window.clear();
		window.draw(b1);
		window.draw(b2);
		DrawSudoku(window);
		MouseOverSquare(window);
		MouseOverButton(window);
		window.display();
	}

	SetGame();
	return true;
}


// Funkcja "Wyrysowuje" diagram
void Display::DrawSudoku(RenderWindow& window)
{

	Vector2f mouse(Mouse::getPosition(window));

	// Wyrysowanie ka�dego z 81 kwadrat�w oddalonych mi�dzy sob� o 65 pikseli
	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
		{
			int x = i * 65;
			int y = j * 65;

			SquareText[i - 1][j - 1].setPosition(x + 14, y);
			Square[i - 1][j - 1].setPosition(i * 65, j * 65);

			window.draw(Square[i - 1][j - 1]);
			window.draw(SquareText[i - 1][j - 1]);
		}
	}

	CheckButton.setPosition(8 * 65, 10 * 65);
	CheckText.setPosition((8 * 65)+14, 10 * 65);
	EndButton.setPosition(9 * 65, 10 * 65);
	EndText.setPosition((9 * 65) + 14, 10 * 65);

	window.draw(CheckButton);
	window.draw(CheckText);
	window.draw(EndButton);
	window.draw(EndText);

}


// Funkcja sprawdzajaca czy kursor znajduje sie nad cyfr�, funkcja zmieniajaca wartosc kazdego kwadratu przy wcisnieciu cyfry z klawiatury
void Display::MouseOverSquare(RenderWindow& window)
{
	Vector2f mouse(Mouse::getPosition(window));

	for (int i = 1; i <= 9; i++)
	{
		for (int j = 1; j <= 9; j++)
		{
			if (Square[i - 1][j - 1].getGlobalBounds().contains(mouse))
			{
				if (lockvalue[i - 1][j - 1] == 1) // Je�eli kursor znajduje si� nad kwadratem kt�ry jest modyfikowalny(warto�� lockvalue dla tego indeksu jest r�wna 1) nast�puje zmiana cyfry naci�ni�tej na klawiaturze
				{
					Square[i - 1][j - 1].setFillColor(Color::Red); // Je�eli kursor znajduje si� nad modyfikowalnym kwadratem jego kolor zmienia si� na czerwony
					if (Keyboard::isKeyPressed(Keyboard::Num1)) SquareText[i - 1][j - 1].setString("1");
					if (Keyboard::isKeyPressed(Keyboard::Num2)) SquareText[i - 1][j - 1].setString("2");
					if (Keyboard::isKeyPressed(Keyboard::Num3)) SquareText[i - 1][j - 1].setString("3");
					if (Keyboard::isKeyPressed(Keyboard::Num4)) SquareText[i - 1][j - 1].setString("4");
					if (Keyboard::isKeyPressed(Keyboard::Num5)) SquareText[i - 1][j - 1].setString("5");
					if (Keyboard::isKeyPressed(Keyboard::Num6)) SquareText[i - 1][j - 1].setString("6");
					if (Keyboard::isKeyPressed(Keyboard::Num7)) SquareText[i - 1][j - 1].setString("7");
					if (Keyboard::isKeyPressed(Keyboard::Num8)) SquareText[i - 1][j - 1].setString("8");
					if (Keyboard::isKeyPressed(Keyboard::Num9)) SquareText[i - 1][j - 1].setString("9");
					if (Keyboard::isKeyPressed(Keyboard::Num0)) SquareText[i - 1][j - 1].setString(" ");
				}
				
			}
			else // Ka�dy kwadrat ma kolor zielony(gdy jest modyfikowalne) lub kolor czerwony(gdy ma zablokowan� warto��)
			{
				if (lockvalue[i - 1][j - 1] == 1)
				{
					 Square[i - 1][j - 1].setFillColor(Color::Green); 
				}
				
				else
				{
					Square[i - 1][j - 1].setFillColor(Color::Black);
				}
			}
		}
	}
}
void Display::MouseOverButton(RenderWindow& window) // Funkcja sprawdzajaca czy kursor znajduje sie nad przyciskami
{
	Vector2f mouse(Mouse::getPosition(window));

	if (CheckButton.getGlobalBounds().contains(mouse))
	{
		CheckButton.setFillColor(Color::Yellow);
		CheckText.setFillColor(Color::Black);
	}
	else
	{
		CheckButton.setFillColor(Color::Black);
		CheckText.setFillColor(Color::White);
	}

	if (EndButton.getGlobalBounds().contains(mouse))
	{
		EndButton.setFillColor(Color::Yellow);
		EndText.setFillColor(Color::Black);
	}
	else
	{
		EndButton.setFillColor(Color::Black);
		EndText.setFillColor(Color::White);
	}
}



bool Display::CheckRow() //Funkcja sprawdzaj�ca czy elementy w poszczeg�lnych wierszach si� nie powtarzaj�(dodatkowo funkcja sprawdza czy ka�da kom�rka jest uzupe�niona liczb�)
{
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			string a = SquareText[i][j].getString();
			if (a == " ") return false;
			for (int k = j+1; k <= 8; k++)
			{
				string b = SquareText[i][k].getString();
				if (a == b)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool Display::CheckColumn() //Funkcja sprawdzaj�ca czy elementy w poszczeg�lnych kolumnach si� nie powtarzaj�
{
	for (int i = 0; i <= 8; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			string a = SquareText[j][i].getString();
			for (int k = j + 1; k <= 8; k++)
			{
				string b = SquareText[k][i].getString();

				if (a == b)
				{
					return false;
				}
			}
		}
	}
	return true;
}


bool Display::CheckSquare() //Funkcja sprawdzaj�ca czy elementy w poszczeg�lnych kwadratach o rozmiarze 3x3 si� nie powtarzaj�
{
	for (int x = 0; x <= 6; x = x + 3)
	{
		for (int y = 0; y <= 6; y = y + 3)
		{
			char tab[9]; 
			int l = 0;
			for (int i = 0; i <= 2; i++)
			{
				for (int j = 0; j <= 2; j++)
				{
					string a = SquareText[i + x][j + y].getString();
					tab[l] = a[0];
					l++;
				}
			}
			for (int k = 0; k <= 7; k++)
			{
				for (int m = k + 1; m <= 8; m++)
				{
					if (tab[k] == tab[m]) return false;
				}
			}
		}
	}
	return true;
}


bool Display::CheckWin() //Funkcja sprawdzaj�ca wszystkie 3 warunki uko�czenia gry(brak powt�rze� w kolumnach, wierszach i kwadratach)
{
	if (CheckRow() && CheckColumn() && CheckSquare())
	{
		return true;
	}
	else 
	{
		return false;
	}
	
}
