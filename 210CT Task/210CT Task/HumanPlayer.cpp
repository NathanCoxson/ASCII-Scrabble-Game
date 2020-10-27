#include "HumanPlayer.h"

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>

using std::string;
using std::stringstream;
using std::getline;
using std::cout;
using std::cin;
using std::endl;


int HumanPlayer::Turn(Board& board, vector<Player*>& players)
{
	ValidatedWord valid_word;
	int word_x = 0;
	int word_y = 0;
	string dir;
	//stringstream format1;
	//stringstream format2;
	//stringstream format3;
	//stringstream format4;
	//string input1;
	//string input2;
	//string input3;
	//string input4;
	string word = "";
	string error = "---------------------------------------------------------------";

	//cout << std::flush;

	//cout << "\033c";

	string format_tiles;

	for (auto tile : tiles)
	{
		format_tiles += tile.letter;
	}

	do
	{
		system("CLS");
		board.Draw();

		cout << "---Player " << id << "'s Turn! " << endl;

		cout << "---------------------------------------------------------------" << endl;
		cout << "---To pass your turn type 'PASS', this will also give you a new hand!" << endl;
		cout << "---------------------------------------------------------------" << endl;

		CurrentTiles();

		cout << "---------------------------------------------------------------" << endl;
		for (auto& player : players)
		{
			cout << "---Player " << player->id << ": " << player->points << " Points. " << (player->last_action == PlayerAction::eWord ? "Played " + player->last_played_word + " last turn." : "Passed last turn.") << endl;
		}

		cout << "---------------------------------------------------------------" << endl;
		cout << error << endl;
		cout << "---------------------------------------------------------------" << endl;

		valid_word.valid = false;

		cout << "---------------------------------------------------------------" << endl;
		cout << "---Enter word:";

		UserInput(word);
		cout << endl;


		if (word == "PASS") { last_action = PlayerAction::ePass; return 0; }
		
		if (word == "BESTWORD") 
		{
			vector<string> words = board.word_trie.PermutationSearch("", "", format_tiles, 7);
			string selected_word = words[0];

			for (auto word : words)
			{
				if (WordPointCalculator(word).points > WordPointCalculator(selected_word).points)
				{
					if (word.length() > selected_word.length()) selected_word = word;
				}
			}

			word = selected_word;

			cout << "---------------------------------------------------------------" << endl;
			cout << "---Chosen word is: " << word << endl;
			cout << "---------------------------------------------------------------" << endl;
		}
		if (not(board.word_trie.SearchWord(word)))
		{ 
			error = "---ERROR: Invalid Word";
			continue;
		}
		if (word.length() == 0) continue;

		cout << "---------------------------------------------------------------" << endl;
		cout << "---Enter Direction (d or l):";

		UserInput(dir);
		cout << endl;


		if (dir != "d" && dir != "l") { error = "---ERROR: Invalid Direction"; continue; }

		cout << "---------------------------------------------------------------" << endl;
		cout << "---Enter X Coord:";

		UserInput(word_x);
		word_x--;
		cout << endl;


		if (word_x > 14 || word_x < 0) { error = "---ERROR: Invalid X Coordinate"; continue; }

		cout << "---------------------------------------------------------------" << endl;
		cout << "---Enter Y Coord:";

		UserInput(word_y);
		word_y--;
		cout << endl;

		if (word_y > 14 || word_y < 0) { error = "---ERROR: Invalid Y Coordinate"; continue; }

		valid_word = board.ApplyWord(word, (dir == "d" ? Direction::eTopToBottom : Direction::eLeftToRight), word_x, word_y, tiles);

		error = "---ERROR: Invalid Placement";

		

	} while (not(valid_word.valid));

	system("CLS");

	last_played_word = word;
	last_action = PlayerAction::eWord;
	return valid_word.points;
}

