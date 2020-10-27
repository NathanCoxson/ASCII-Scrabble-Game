#include "WordSet.h"

#include <fstream>

WordSet::WordSet() {}

WordSet::WordSet(string path)
{
	/*
	This class on initialisation will take a dictionary of words given and sort out the legal words into a vector.
	Big-O: O(nk)
	*/
	string text;
	std::ifstream TextFile(path);
	bool valid;

	while (getline(TextFile, text)) {

		valid = true;
		for (int i = 0; i < text.size(); i++)
		{
			if (int(text[i]) < 97 || int(text[i]) > 122)
			{
				valid = false;
				break;
			}
		}

		if (valid)
		{
			Legal.push_back(WordPointCalculator(text));
		}
	}

	TextFile.close();

	BinaryMergeSort(Legal, Legal.size(), 64);
}

