#include <cstdlib>
#include "mainmenu.h"
#include "game.h"

void WelcomeMessage()
{
	std::cout << "######################################" << std::endl;
	std::cout << "# Bienvenido a el Juego de Palabras! #" << std::endl;
	std::cout << "#         Creado por 0xKirby         #" << std::endl;
	std::cout << "######################################" << std::endl;
	std::cout << std::endl;
	system("pause");
}

void ShowMenu()
{
	system("cls");
	std::cout << "1) Jugar contra la maquina" << std::endl;
	std::cout << "2) Ver a la maquina jugar" << std::endl;
	std::cout << "3) Como funciona el juego?" << std::endl;
	std::cout << std::endl;
}
#define MAX_OPTIONS	3

bool IsValid(char selection)
{
	if (!std::isdigit(selection))
		return false;

	int sel = selection - '0';
	if (sel > MAX_OPTIONS || sel == 0)
		return false;

	return true;
}

bool DoSelection(std::string selection)
{
	std::cout << "> ";
	std::cin >> selection;

	while (!IsValid(selection[0]))
	{
		ShowMenu();
		std::cout << "Por favor elige una de las " << MAX_OPTIONS << " opciones!" << std::endl;
		std::cout << "> ";

		std::cin >> selection;
	}

	system("cls");
	int select = selection[0] - '0';
	int language;
	switch (select)
	{
	case 1:
	case 2:
		std::cout << "Elige el lenguaje: " << std::endl;
		
		for (int i = 0; i < MAX_LANGS; ++i)
			std::cout << i + 1 << ") " << langFiles[i].c_str() << std::endl;

		do {
			std::cin >> language;
			language -= 1;
		} while (language < 0 || language > MAX_LANGS);

		StartGame(GameType(select - 1), language);
		break;

	case 3:
		std::cout << "El juego es simple! El jugador debe introducir una palabra, y el oponente" << std::endl;
		std::cout << "debe introducir una palabra que empiece por la letra que acaba la anterior." << std::endl;
		std::cout << "No se puede repetir palabras! El jugador que se quede sin palabras, pierde!" << std::endl;
		std::cout << std::endl << "Ejemplo: " << std::endl << "Jugador 1: Zapato"
			<< std::endl << "Jugador 2: Orca" << std::endl;

		system("pause");
		return true;
	}

	return false;
}
