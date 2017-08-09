#include "includes/mainmenu.h"

int main()
{
	WelcomeMessage();
	ShowMenu();

	std::string selection;
	while (DoSelection(selection))
		ShowMenu();

	return 0;
}
