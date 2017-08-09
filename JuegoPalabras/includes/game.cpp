#include "game.h"

std::vector<std::string> wordContainer;
std::vector<std::string> usedWords;

std::string langFiles[MAX_LANGS] =
{
	"es-es",
	"en-en"
};

bool WordExists(std::string word)
{
	if (std::find(wordContainer.begin(), wordContainer.end(), word) != wordContainer.end())
		return true;
	else
		return false;
}

bool IsUsed(std::string word)
{
	if (std::find(usedWords.begin(), usedWords.end(), word) != usedWords.end())
		return true;
	else
		return false;
}

bool WordFits(std::string word, char lastChar)
{
	if (word[0] == lastChar)
		return true;
	else
		return false;
}

bool IsFinished(char lastChar)
{
	// We check if there is any non-used word that starts with the last letter of the word
	for (auto wordStr : wordContainer)
	{
		if (wordStr[0] == lastChar && !IsUsed(wordStr))
			return false;
		else
			continue;
	}

	return true;
}

std::string FindWord(char lastChar)
{
	for (auto wordStr : wordContainer)
	{
		if (wordStr[0] == lastChar && !IsUsed(wordStr))
			return wordStr;
	}

	return "";
}

void StartGame(GameType gType, int lang)
{
	if (!StoreWords(langFiles[lang], wordContainer))
		return;

	char lastChar;
	bool finished = false;
	bool firstRound = true;
	switch (gType)
	{
	case TYPE_VS:
	{
		bool playerTurn = true;
		while (!finished)
		{
			if (playerTurn)
			{
				std::cout << "Tu turno!" << std::endl;

				if (!firstRound)
					std::cout << "Introduce una palabra que empiece por '" << lastChar << "'!" << std::endl;

				std::string word;
				do {
					std::cout << "Palabra: ";
					std::cin >> word;

					std::transform(word.begin(), word.end(), word.begin(), ::tolower);

					if (!WordExists(word))
					{
						std::cout << "La palabra '" << word << "' no esta en el diccionario!" << std::endl << std::endl;
						continue;
					}

					if (IsUsed(word))
					{
						std::cout << "La palabra '" << word << "' ya ha sido utilizada!" << std::endl << std::endl;
						continue;
					}

					if (!firstRound)
					{
						if (!WordFits(word, lastChar))
						{
							std::cout << "La palabra '" << word << "' no empieza por '" << lastChar << "'" << std::endl << std::endl;
							continue;
						}
					}
					else
						firstRound = false;

					std::cout << std::endl;
					usedWords.push_back(word);
					lastChar = word[word.length() - 1];
					break;
				} while (true);

				if (IsFinished(lastChar))
				{
					finished = true;
					std::cout << "Enhorabuena! Has ganado contra la maquina!" << std::endl;
					system("pause");
					return;
				}
				else
					playerTurn = false;
			}
			else
			{
				std::string word = FindWord(lastChar);
				std::cout << "El ordenador elige la palabra: " << word << std::endl;

				lastChar = word[word.length() - 1];

				if (IsFinished(lastChar))
				{
					std::cout << "No quedan palabras que empiecen por " << lastChar << "!" << std::endl;
					std::cout << "Gana el ordenador!" << std::endl;
					finished = true;
					system("pause");
					return;
				}

				std::cout << std::endl;
				usedWords.push_back(word);
				playerTurn = true;
			}
		}

		break;
	} // case TYPE_VS

	case TYPE_AUTO:
	{
		bool bot1Turn = true;

		while (!finished)
		{
			std::chrono::milliseconds sTime(1000);
			//std::this_thread::sleep_for(sTime);

			if (bot1Turn)
			{
				std::cout << "Bot 1: ";

				if (firstRound)
				{
					srand(time(NULL));
					int random = rand() % wordContainer.size();

					std::string word = wordContainer[random];
					std::cout << word.c_str() << std::endl << std::endl;;

					firstRound = false;
					bot1Turn = false;

					lastChar = word[word.length() - 1];
					usedWords.push_back(word);
					continue;
				}
			}
			else
				std::cout << "Bot 2: ";

			std::string word = FindWord(lastChar);
			std::cout << word.c_str() << std::endl << std::endl;

			lastChar = word[word.length() - 1];
			usedWords.push_back(word);

			if (IsFinished(lastChar))
			{
				std::cout << "No quedan mas palabras que empiecen por '" << lastChar << "'!" << std::endl;
				
				if (bot1Turn)
					std::cout << "Gana el Bot 1!" << std::endl;
				else
					std::cout << "Gana el Bot 2!" << std::endl;

				finished = true;
				system("pause");
				return;
			}
			else
				bot1Turn = !bot1Turn;
		}

		break;
	} // case TYPE_AUTO
	}
}