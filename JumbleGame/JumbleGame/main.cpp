// Container Includes
#include "HTable.h"
#include "BST.h"
#include "DynArray.h"
// Leak Detection
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
// Other Inlcudes
#include <string>
#include <random>
//#include <ctime>
#include <iostream>
#include <conio.h>
#include "Timer.h"
#include <algorithm>
#include "ConsoleFunctions.h"
using namespace KSUN;
//using namespace std;

// Define Number of Buckets
const unsigned int BUCKETS = 5011;
// Define Number of Words in Dictionary
const unsigned int WORDS = 110307;
// Hash Function for Dictionary
unsigned int dictHash(const string& toHash)
{
	unsigned int seed = 1;
	for (unsigned int i = 0; i < toHash.length(); ++i)
	{
		seed *= toHash[i] * i + 1;
	}
	return seed % BUCKETS;
}

// Function Prototypes
void loadDictionary(HTable<string>& dict, const char* filePath);
string getRandomWord(HTable<string>& dict);
string shuffle(string arr, unsigned int arrSize);
bool descendSort(unsigned int i, unsigned int j){ return i > j; }

// Begin Main Function
int main(int argc, char** argv)
{
	Console::SetWindowSize(52, 30);
	Console::SetBufferSize(52, 30);
	Console::CursorVisible(false);
	// Leak Detection Test
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//	_CrtSetBreakAlloc();
	srand(static_cast<unsigned int>(time(nullptr)));
	// Declare and Initialize Hash Table for Dictionary
	HTable<string> dictionary(BUCKETS, dictHash);
	loadDictionary(dictionary, "engldict.txt");
	dictionary.printTableData();
	bool replay = true;
	bool newRound = false;
	unsigned int score = 0;

	DynArray<unsigned int> highScores;
	fstream fin;
	fin.open("scores.txt", ios_base::in);
	unsigned int count;
	if (fin.is_open())
	{
		fin >> count;
		if (count != 0)
		{
			unsigned int toAdd;
			for (unsigned int i = 0; i < count; i++)
			{
				fin >> toAdd;
				highScores.append(toAdd);
			}
		}
		fin.close();
	}

	while (replay || newRound)
	{
		newRound = false;
		string randomWord;
		string shuffled;
		randomWord = getRandomWord(dictionary);
		shuffled = shuffle(randomWord, randomWord.length());
		DynArray<char> letters;
		for (unsigned int i = 0; i < 6; ++i)
			letters.append(shuffled[i]);

		Timer timer;
		string userInput;
		BST<string> guessedWords;
		DynArray<string> words;
		if (replay == true)
			score = 0;
		else
			score = score;
		unsigned int Scores[5] = { 0 };
		for (unsigned int i = 0; i < 5; i++)
			Scores[i] = highScores[i];
		std::sort(Scores, Scores + 5, descendSort);
		while (timer.getElapsedTime() < 60000)
		{

			// User Input
			if (_kbhit())
			{
				char ch = _getch();
				if (ch == '\r')
				{
					if (!guessedWords.find(userInput))
					{
						if (strcmp(userInput.c_str(), randomWord.c_str()) == 0)
						{
							newRound = true;
							replay = false;
						}
						words.append(userInput);
						guessedWords.insert(userInput);
						if (dictionary.find(userInput) != -1)
						{
							unsigned int sum = 1;
							for (unsigned int i = 1; i < userInput.length(); i++)
							{
								sum *= userInput.length() - i;
							}
							score += sum;
						}
					}
					userInput.clear();
					for (unsigned int i = 0; i < 6; ++i)
						letters[i] = shuffled[i];
				}
				if (ch == '\b')
				{
					if (userInput.length() != 0)
					{
						for (unsigned int i = 0; i < 6; i++)
						{
							if (letters[i] == ' ')
							{
								letters[i] = userInput[userInput.length() - 1];
								break;
							}
						}
						userInput.erase(userInput.length() - 1);
					}
				}
				for (unsigned int i = 0; i < 6; i++)
				{
					if (ch == letters[i])
					{
						letters[i] = ' ';
						if (-32 == ch)
							_getch();

						// did the user press a-z?
						else if (isalpha(ch))
						{
							userInput += tolower(ch);
						}
						break;
					}
				}
			}
			// Display
			system("cls");
			// Scrambled Word Display
			Console::ForegroundColor(Cyan);
			cout << "Scrambled Word\n";
			Console::ForegroundColor(White);
			cout << shuffled;
			// Input Display
			Console::ForegroundColor(White);
			Console::SetCursorPosition(0, 2);
			cout << userInput;
			// Guessed Words Display
			Console::ForegroundColor(White);
			Console::SetCursorPosition(17, 0);
			cout << "Guessed Words";
			for (unsigned int i = 0; i < words.size(); i++)
			{
				Console::SetCursorPosition(17, i + 1);
				if (dictionary.find(words[i]) != -1)
				{
					Console::ForegroundColor(Green);
					cout << words[i];
				}
				else
				{
					Console::ForegroundColor(Red);
					cout << words[i];
				}
			}
			// Score Display
			Console::ForegroundColor(White);
			Console::SetCursorPosition(33, 0);
			cout << "Score: ";
			Console::ForegroundColor(Yellow);
			cout << score;
			// Time Display
			Console::ForegroundColor(White);
			Console::SetCursorPosition(Console::WindowWidth() - 8, 0);
			cout << "Time: ";
			if ((60 - timer.getElapsedTime() / 1000) <= 10)
				Console::ForegroundColor(Red);
			else if (((60 - timer.getElapsedTime() / 1000) > 10) && ((60 - timer.getElapsedTime() / 1000) <= 20))
				Console::ForegroundColor(Yellow);
			else
				Console::ForegroundColor(Green);
			cout << 60 - timer.getElapsedTime() / 1000;
			// High Score Display
			Console::ForegroundColor(White);
			Console::SetCursorPosition(33, 5);
			cout << "High Scores";
			unsigned int toLoop;
			if (highScores.size() > 5)
				toLoop = 5;
			else
				toLoop = highScores.size();
			for (unsigned int i = 1; i < toLoop + 1; i++)
			{
				//if ()
				Console::SetCursorPosition(33, 5 + i);
				cout << i << ": " << Scores[i - 1];
			}
			Console::ResetColor();
			//Console::Lock(false);
		}
		if (newRound == false)
		{
			Console::ForegroundColor(White);
			Console::SetCursorPosition(10, 20);
			cout << "You didn't find the word.";
			Console::SetCursorPosition(10, 21);
			cout << "The correct word was " << randomWord;
			Console::SetCursorPosition(10, 23);
			cout << "Would you like to play again? Y/N ";
			bool input = false;
			while (!input)
			{
				if (_kbhit())
				{
					char ch = _getch();
					switch (tolower(ch))
					{
					case 'y':
					{
						fstream fout;
						fout.open("scores.txt", ios_base::out);
						if (fout.is_open())
						{
							unsigned int scores[6] = { 0 };
							highScores.append(score);
							for (unsigned int i = 0; i < highScores.size(); i++)
								scores[i] = highScores[i];
							if (highScores.size() > 5)
								fout << 5 << '\n';
							else
								fout << highScores.size() << '\n';
							std::sort(scores, scores + 5, descendSort);
							for (unsigned int i = 0; i < 5; i++)
								fout << scores[i] << '\n';
							for (unsigned int i = 0; i < highScores.size(); i++)
								highScores[i] = scores[i];
							fout.close();
						}
						replay = true;
						newRound = false;
						input = true;
						Console::SetCursorPosition(10, 24);
						cout << "Starting New Game...";
						Sleep(2000);
					}
						break;
					case 'n':
					{
						fstream fout;
						fout.open("scores.txt", ios_base::out);
						if (fout.is_open())
						{
							unsigned int scores[6] = { 0 };
							highScores.append(score);
							for (unsigned int i = 0; i < highScores.size(); i++)
								scores[i] = highScores[i];
							if (highScores.size() > 5)
								fout << 5 << '\n';
							else
								fout << highScores.size() << '\n';
							std::sort(scores, scores + 5, descendSort);
							for (unsigned int i = 0; i < 5; i++)
								fout << scores[i] << '\n';
							for (unsigned int i = 0; i < highScores.size(); i++)
								highScores[i] = scores[i];
							fout.close();
						}
						return 0;
					}
						break;
					}
				}
			}
		}
		else
		{
			Console::ForegroundColor(White);
			Console::SetCursorPosition(9, 20);
			cout << "Congradulations! You Found the word!";
			Console::SetCursorPosition(10, 21);
			cout << "The word was " << randomWord;
			Console::SetCursorPosition(8, 22);
			cout << "Would you like to play the next round? Y/N ";
			bool input = false;
			while (!input)
			{
				if (_kbhit())
				{
					char ch = _getch();
					switch (tolower(ch))
					{
					case 'y':
					{
						replay = false;
						newRound = true;
						input = true;
						Console::SetCursorPosition(10, 23);
						cout << "Starting Next Round...";
						Sleep(1500);
					}
						break;
					case 'n':
					{
						fstream fout;
						fout.open("scores.txt", ios_base::out);
						if (fout.is_open())
						{
							unsigned int scores[6] = { 0 };
							highScores.append(score);
							for (unsigned int i = 0; i < highScores.size(); i++)
								scores[i] = highScores[i];
							if (highScores.size() > 5)
								fout << 5 << '\n';
							else
								fout << highScores.size() << '\n';
							std::sort(scores, scores + 5, descendSort);
							for (unsigned int i = 0; i < 5; i++)
								fout << scores[i] << '\n';
							for (unsigned int i = 0; i < highScores.size(); i++)
								highScores[i] = scores[i];
							fout.close();
						}
						break;
					}
						Sleep(2000);
					}
				}
			}

		}
	}
}

void loadDictionary(HTable<string>& dict, const char* filePath)
{
	fstream fin;
	fin.open(filePath, ios_base::in);
	if (fin.is_open())
	{
		string buffer;
		for (unsigned int i = 0; i < WORDS; i++)
		{
			fin >> buffer;
			bool aposFound = true;
			if (buffer.find('\'', 0) == buffer.npos)
			{
				aposFound = false;
			}
			if ((buffer.length() < 3) || (buffer.length() > 6) || aposFound)
				continue;
			else
				dict.insert(buffer);
		}
	}
}

string getRandomWord(HTable<string>& dict)
{
	random_device rd;   // non-deterministic generator
	mt19937 gen(rd());  // to seed mersenne twister.
	//bool repeat = true;
	while (true)
	{
		uniform_int_distribution<> buckDist(0, 5011); // distribute results between 1 and 6 inclusive.
		unsigned int bucketToSearch = buckDist(gen);
		SLLIter<string> bucketIter(dict[bucketToSearch]);
		uniform_int_distribution<> wordDist(0, dict[bucketToSearch].size());
		unsigned int wordToGet = wordDist(gen);
		for (unsigned int i = 0; i < wordToGet; ++bucketIter)
			i++;
		if (bucketIter.end())
			continue;
		if (bucketIter.current().length() == 6)
			return bucketIter.current();
	}
}

string shuffle(string toShuffle, unsigned int stringSize)
{
	if (stringSize > 1)
	{
		for (unsigned int i = 0; i < stringSize - 1; i++)
		{
			unsigned int newSpot = i + rand() / (RAND_MAX / (stringSize - i) + i);
			char tmp = toShuffle[newSpot];
			toShuffle[newSpot] = toShuffle[i];
			toShuffle[i] = tmp;
		}
	}
	return toShuffle;
}