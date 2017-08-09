#include "filereader.h"

bool SanitizeWord(std::string& word)
{
	std::transform(word.begin(), word.end(), word.begin(), ::tolower);

	char specialChars[11] = { 'á', 'ä', 'é', 'ë', 'í', 'ï', 'ó', 'ö', 'ú', 'ü', 'ñ' };
	for (int i = 0; i < 11; ++i)
	{
		std::size_t pos = word.find(specialChars[i]);
		while (pos != std::string::npos)
		{
			std::cout << "Modificando " << word.c_str() << " a ";
			switch (i)
			{
			case 0:
			case 1:
				word[pos] = 'a';
				break;

			case 2:
			case 3:
				word[pos] = 'e';
				break;

			case 4:
			case 5:
				word[pos] = 'i';
				break;

			case 6:
			case 7:
				word[pos] = 'o';
				break;

			case 8:
			case 9:
				word[pos] = 'u';
				break;

			case 10:
				word[pos] = 'n';
				break;
			}

			std::cout << word.c_str() << std::endl;
			pos = word.find(specialChars[i]);
		}
	}

	if (word.find_first_not_of("abcdefghijklmnopqrstuvwxyz") == std::string::npos)
		return true;
	else
		return false;
}

bool StoreWords(std::string fileName, std::vector<std::string>& wordContainer)
{
	if (fileName.find('/') == std::string::npos)
		fileName.insert(0, "words/");

	if (fileName.find('.') == std::string::npos)
		fileName += ".words";

	std::ifstream file(fileName);
	if (!file)
	{
		std::cout << "[ERROR] No se ha encontrado el archivo: '" << fileName.c_str() << "'" << std::endl;
		system("pause");
		return false;
	}

	while (file.is_open() && file.good())
	{
		std::string line;
		while (getline(file, line))
			if (line.length() > 1) // Ignore 'a', 'b', etc
				if (SanitizeWord(line))
					wordContainer.push_back(line);
				else
					std::cout << "Eliminando " << line << std::endl;
	}

	file.close();

	std::cout << std::endl << "Se han cargado " << wordContainer.size() << " palabras." << std::endl;
	system("pause");
	system("cls");
	return true;
}
