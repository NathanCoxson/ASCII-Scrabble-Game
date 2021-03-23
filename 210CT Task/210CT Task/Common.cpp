#include "Common.h"


#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>

using std::min;
using std::cin;
using std::getline;
using std::stringstream;


void UserInput(int& var)
{
	stringstream stream;
	string input;
	int output;

	getline(cin, input);

	stream << input;
	stream >> output;

	var = output;
}

void UserInput(string& var)
{
	stringstream stream;
	string input;
	string output;

	getline(cin, input);

	stream << input;
	stream >> output;

	var = output;
}

void UserInput(char& var)
{
	stringstream stream;
	string input;
	char output;

	getline(cin, input);

	stream << input;
	stream >> output;

	var = output;
}

SearchResult BinarySearch(vector<string>& words, string target)
{
	int start = 0;
	int end = words.size() - 1;
	int middle;

	while (start <= end)
	{
		middle = (start + end) / 2;

		if (words[middle+1] > target && words[middle] < target) { return SearchResult(true, middle);  }
		else if (words[middle] < target) { start = middle + 1; }
		else { end = middle - 1; }
	}
	return SearchResult();
}

SearchResult BinarySearch(vector<BasicWord>& words, string target)
{
	int start = 0;
	int end = words.size() - 1;
	int middle;

	while (start <= end)
	{
		middle = (start + end) / 2;

		if (words[middle].word > target) { end = middle - 1; }
		else if (words[middle].word < target) { start = middle + 1; }
		else { return SearchResult(true, middle); }
	}
	return SearchResult();
}

void BinaryInsertionSort(vector<BasicWord>& words, int start, int end)
{

	for (int i = start; i < (end - 1); i++)
	{
		if (words[i].word > words[i + 1].word)
		{
			int a = start;
			int b = i + 1;
			BasicWord target = words[i + 1];
			int location = 0;

			while (a <= b)
			{
				int middle = (a + b) / 2;
				if (target.word > words[middle].word && target.word < words[middle + 1].word)
				{
					location = (middle + 1);
					break;
				}
				else if (target.word < words[middle].word)
				{
					b = middle;
				}
				else
				{
					a = middle;
				}
				if (a == b)
				{
					location = (middle);
					break;
				}
			}

			for (int j = i + 1; j > (location); j--)
			{
				words[j] = words[j - 1];
			}
			words[location] = target;
		}
	}
}

void BinaryInsertionSort(string& word, int start, int end)
{
	//std::cout << "SORTING " << word << std::endl;

	for (int i = start; i < (end - 1); i++)
	{
		if (word[i] > word[i + 1])
		{
			int a = start;
			int b = i + 1;
			char target = word[i + 1];
			int location = 0;

			while (a <= b)
			{
				
				int middle = (a + b) / 2;
				//std::cout << word << " " << word[middle] << " " << target << " " << word[middle+1] << std::endl;
				//std::cout << "LOCATING Mid:" << middle << " A: " << a << " B: " << b << std::endl;
				if (target >= word[middle] && target <= word[middle + 1])
				{
					location = (middle + 1);
					//std::cout << "DECISION 1" << std::endl;
					break;
				}
				else if (target < word[middle])
				{
					b = middle;
					//std::cout << "DECISION 2" << std::endl;
				}
				else
				{
					a = middle;
					//std::cout << "DECISION 3" << std::endl;
				}
				if (a == b)
				{
					location = (middle);
					//std::cout << "DECISION 5" << std::endl;
					break;
				}
			}

			for (int j = i + 1; j > (location); j--)
			{
				word[j] = word[j - 1];
			}
			word[location] = target;
		}
	}
}

void BinaryMergeSort(vector<BasicWord>& words, int size, int block_size)
{
	for (int i = 0; i < size; i += block_size)
	{
		BinaryInsertionSort(words, i, min((i + block_size), (size)));
	}

	for (int j = block_size; j < size; j = 2 * j)
	{
		for (int left = 0; left < size; left += 2 * j)
		{
			int right = min((left + (2 * j) - 1), (size - 1));
			int mid = min(((left + j - 1)), (size - 1));
			Merge(words, left, mid, right);
		}
	}
}

void MergeSort(vector<BasicWord>& words, int size)
{
	for (int j = 1; j < size; j = 2 * j)
	{
		for (int left = 0; left < size; left += 2 * j)
		{
			int right = min((left + (2 * j) - 1), (size - 1));
			int mid = min(((left + j - 1)), (size - 1));
			Merge(words, left, mid, right);
		}
	}
}

void Merge(vector<BasicWord>& words, int start, int middle, int end)
{
	int left_section = middle - start + 1; int right_section = end - middle;
	vector<BasicWord> store1(left_section); vector<BasicWord> store2(right_section);

	for (int a = 0; a < left_section; a++) { store1[a] = words[start + a]; }
	for (int b = 0; b < right_section; b++) { store2[b] = words[middle + 1 + b]; }


	int i = 0; int j = 0; int k = start;
	while (i < left_section && j < right_section)
	{
		if (store1[i].word <= store2[j].word)
		{
			words[k] = store1[i];
			i++;
		}
		else
		{
			words[k] = store2[j];
			j++;
		}
		k++;
	}
	while (i < left_section)
	{
		words[k] = store1[i];
		i++;
		k++;
	}
	while (j < right_section)
	{
		words[k] = store2[j];
		j++;
		k++;
	}
}

int LetterPointCalculator(char letter)
{
	if (letter == 'e' || letter == 't' || letter == 'a' || letter == 'o' || letter == 'i' || letter == 'n' || letter == 's' || letter == 'r' || letter == 'l' || letter == 'u')
	{
		return 1;
	}
	else if (letter == 'd' || letter == 'g')
	{
		return 2;
	}
	else if (letter == 'c' || letter == 'm' || letter == 'p' || letter == 'b')
	{
		return 3;
	}
	else if (letter == 'f' || letter == 'h' || letter == 'v' || letter == 'w' || letter == 'y')
	{
		return 4;
	}
	else if (letter == 'k')
	{
		return 5;
	}
	else if (letter == 'x' || letter == 'j')
	{
		return 8;
	}
	else
	{
		return 10;
	}
}

BasicWord WordPointCalculator(string text)
{

	/*This take a string and calculates the point value of thr word given, returning it as a tuple of the word and point values.
	Big-O: O(n)
	*/
	int points = 0;
	for (auto letter : text)
	{
		points += LetterPointCalculator(letter);
	}
	return BasicWord(text, points);

}