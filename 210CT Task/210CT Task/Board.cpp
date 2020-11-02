#include "Board.h"
#include "Trie.h"

#include <iostream>

using std::cout;
using std::endl;


Board::Board() {}

Board::Board(WordSet w)
{

	//Triple Word Scores
	board_coordinates[0][0] = Square(4);
	board_coordinates[7][0] = Square(4);
	board_coordinates[14][0] = Square(4);
	board_coordinates[0][7] = Square(4);
	board_coordinates[14][7] = Square(4);
	board_coordinates[0][14] = Square(4);
	board_coordinates[7][14] = Square(4);
	board_coordinates[14][14] = Square(4);

	//Double Word Scores
	board_coordinates[7][7] = Square(3);
	board_coordinates[1][1] = Square(3);
	board_coordinates[2][2] = Square(3);
	board_coordinates[3][3] = Square(3);
	board_coordinates[4][4] = Square(3);
	board_coordinates[13][1] = Square(3);
	board_coordinates[12][2] = Square(3);
	board_coordinates[11][3] = Square(3);
	board_coordinates[10][4] = Square(3);
	board_coordinates[1][13] = Square(3);
	board_coordinates[2][12] = Square(3);
	board_coordinates[3][11] = Square(3);
	board_coordinates[4][10] = Square(3);
	board_coordinates[13][13] = Square(3);
	board_coordinates[12][12] = Square(3);
	board_coordinates[11][11] = Square(3);
	board_coordinates[10][10] = Square(3);

	//Triple Letter Scores
	board_coordinates[5][1] = Square(2);
	board_coordinates[9][1] = Square(2);
	board_coordinates[1][5] = Square(2);
	board_coordinates[5][5] = Square(2);
	board_coordinates[9][5] = Square(2);
	board_coordinates[13][5] = Square(2);
	board_coordinates[1][9] = Square(2);
	board_coordinates[5][9] = Square(2);
	board_coordinates[9][9] = Square(2);
	board_coordinates[13][9] = Square(2);
	board_coordinates[5][13] = Square(2);
	board_coordinates[9][13] = Square(2);

	//Double Letter Scores
	board_coordinates[3][0] = Square(1);
	board_coordinates[11][0] = Square(1);
	board_coordinates[6][2] = Square(1);
	board_coordinates[8][2] = Square(1);
	board_coordinates[0][3] = Square(1);
	board_coordinates[7][3] = Square(1);
	board_coordinates[14][3] = Square(1);
	board_coordinates[2][6] = Square(1);
	board_coordinates[6][6] = Square(1);
	board_coordinates[8][6] = Square(1);
	board_coordinates[12][6] = Square(1);
	board_coordinates[3][7] = Square(1);
	board_coordinates[11][7] = Square(1);
	board_coordinates[2][8] = Square(1);
	board_coordinates[6][8] = Square(1);
	board_coordinates[8][8] = Square(1);
	board_coordinates[12][8] = Square(1);
	board_coordinates[0][11] = Square(1);
	board_coordinates[7][11] = Square(1);
	board_coordinates[14][11] = Square(1);
	board_coordinates[6][12] = Square(1);
	board_coordinates[8][12] = Square(1);
	board_coordinates[3][14] = Square(1);
	board_coordinates[11][14] = Square(1);

	starting_coordinates[7][7] = true;

	words = w;

	

	for (auto word : words.Legal)
	{
		word_trie.AppendWord(word.word);
	}

}

Board::~Board()
{
}

string Board::GetWord(Direction dir, int x, int y)
{
	string word = "";
	int x_count = 0;
	int y_count = 0;
	int x_increment = 0;
	int y_increment = 0;

	switch (dir)
	{
	default:
		return "";

	case Direction::eTopToBottom:
		y_increment = 1;
		break;

	case Direction::eLeftToRight:
		x_increment = 1;
		break;
	}
	while (true)
	{
		if (x + x_count > 14 || y + y_count > 14) return word;

		if (board_coordinates[x + x_count][y + y_count].tile.blank) return word;

		word += board_coordinates[x + x_count][y + y_count].tile.letter;

		x_count += x_increment;
		y_count += y_increment;
	}
	
}

ValidatedWord Board::WordCheck(string word, Direction dir, DirectionType dir_type, int x, int y)
{
	int x_count = 0;
	int y_count = 0;
	int x_increment = 0;
	int y_increment = 0;

	bool new_word = false;
	int blank_tile_count = 0;
	bool additional_word = false;
	int taken_tile_count = 0;

	int word_points = 0;
	int word_points_multiplier = 1;
	string word_pre;
	string word_post;
	string word_complete;
	WordIntersection word_intersection = WordIntersection::eNone;


	/*Detertmine if the word being checked is horizontal or vertical*/
	switch (dir)
	{
	default:
		return ValidatedWord();

	case Direction::eTopToBottom:
		y_increment = 1;
		break;

	case Direction::eLeftToRight:
		x_increment = 1;
		break;
	}

	/*Make sure that each character in the word being applied is going on a blank tile or is the same character*/
	for (auto character : word)
	{
		if (board_coordinates[x + x_count][y + y_count].tile.letter == character)
		{
			taken_tile_count++;
			word_intersection = WordIntersection::eInner;
		}
		else if (board_coordinates[x + x_count][y + y_count].tile.blank)
		{
			blank_tile_count++;
		}
		else { return ValidatedWord(); }

		x_count += x_increment;
		y_count += y_increment;
	}

	/*If there are no blank tiles, it's a valid play but entirely an intersection and no points are awarded*/
	if (blank_tile_count == 0 && dir_type == DirectionType::eEquivalent) { return ValidatedWord(); }
	else if (blank_tile_count == 0 && dir_type == DirectionType::eOpposite) { return ValidatedWord(true, 0, word_intersection); }

	//If it is an equivalent check, then the end of the word is required rather than the next tile from x & y
	if (dir_type == DirectionType::eEquivalent && x_increment == 1) { x_count = word.length() - 1; }
	else if (dir_type == DirectionType::eEquivalent && y_increment == 1) { y_count = word.length() - 1; }
	else { x_count = 0; y_count = 0; }

	//Find the entire word along the provided direction and x & y coords
	for (int i = 0; i < 2;) {
		x_count += x_increment;
		y_count += y_increment;

		if ((x + x_count > 14 || x + x_count < 0 || y + y_count > 14 || y + y_count < 0))
		{
			i++;
			x_increment = -x_increment;
			y_increment = -y_increment;
			x_count = 0;
			y_count = 0;

			continue;
		}
		else if (board_coordinates[x + x_count][y + y_count].tile.blank)
		{

			i++;
			x_increment = -x_increment;
			y_increment = -y_increment;
			x_count = 0;
			y_count = 0;

			continue;
		}

		if (i == 0) { word_post += board_coordinates[x + x_count][y + y_count].tile.letter; }
		if (i == 1) { word_pre = board_coordinates[x + x_count][y + y_count].tile.letter + word_pre; }

		if (board_coordinates[x + x_count][y + y_count].WordMultiplier() > word_points_multiplier) { word_points_multiplier = board_coordinates[x + x_count][y + y_count].WordMultiplier(); }
	}

	word_complete = word_pre + word + word_post;

	if (not(word_intersection) && word_complete != word) { word_intersection = WordIntersection::eOuter; }
	//If the complete word is equivalent to the inputted word and it's an opposite direction type, return no points
	if (word_complete == word && dir_type == DirectionType::eOpposite) { return ValidatedWord(true, 0, word_intersection); }

	//Identify if the full word is legal
	if (not(word_trie.SearchWord(word_complete))) { return ValidatedWord(); }

	//Get the point value of the inserted word parts, considering letter multipliers
	x_count = 0;
	y_count = 0;

	for (auto character : word)
	{
		//If the letter multiplier tile is blank, as in hasn't been used, use the multiplier
		if (board_coordinates[x + x_count][y + y_count].tile.blank) { word_points += board_coordinates[x + x_count][y + y_count].LetterMultiplier() * LetterPointCalculator(character); }
		else { word_points += LetterPointCalculator(character); }

		//If the current tile has a word multiplier that is greater than the current stored one, store that value
		if (board_coordinates[x + x_count][y + y_count].WordMultiplier() > word_points_multiplier) { word_points_multiplier = board_coordinates[x + x_count][y + y_count].WordMultiplier(); }

		x_count += x_increment;
		y_count += y_increment;
	}

	//Get the point value of the pre and post parts of the word 
	for (auto character : word_pre) { word_points += LetterPointCalculator(character); }
	for (auto character : word_post) { word_points += LetterPointCalculator(character); }

	//Multiply the points by the highest word point multiplier
	word_points *= word_points_multiplier;

	return ValidatedWord(true, word_points, word_intersection);
}

ValidatedWord Board::ValidWord(string word, Direction dir, int x, int y, vector<Tile>& tiles)
{
	if (x > 14 || x < 0 || y > 15 || y < 0) { return ValidatedWord(); }

	int x_increment = 0;
	int y_increment = 0;
	int x_count = 0;
	int y_count = 0;

	int base_blanks = 0;
	int blanks = 0;
	string usable_tiles = "";
	string used_tiles = "";
	

	WordIntersection word_intersection = WordIntersection::eNone;
	int total_points = 0;

	Direction opp_dir;
	ValidatedWord valid_eqv_word;
	ValidatedWord valid_opp_word;

	switch (dir)
	{
	default:
		return ValidatedWord();
	case Direction::eTopToBottom:
		if (y + word.length() - 1 > 15) { return ValidatedWord(); }
		y_increment = 1;
		opp_dir = Direction::eLeftToRight;
		break;
	case Direction::eLeftToRight:
		if (x + word.length() - 1 > 15) { return ValidatedWord(); }
		x_increment = 1;
		opp_dir = Direction::eTopToBottom;
		break;
	}

	valid_eqv_word = WordCheck(word, dir, DirectionType::eEquivalent, x, y);

	if (not(valid_eqv_word.valid)) { return ValidatedWord(); }
	if (not(word_intersection)) { word_intersection = valid_eqv_word.intersection; }

	total_points += valid_eqv_word.points;

	for (auto tile : tiles)
	{
		if (tile.blank) { base_blanks++; blanks++; }
		else { usable_tiles += tile.letter; }
	}

	for (int i = 0; i < word.length(); i++)
	{
		/*Character just takes a single character and converts it to a string*/
		string character(1, word[i]);
		valid_opp_word = WordCheck(character, opp_dir, DirectionType::eOpposite, x + x_count, y + y_count);

		if (board_coordinates[x + x_count][y + y_count].tile.blank)
		{
			if (usable_tiles.find(word[i]) != string::npos)
			{
				used_tiles += word[i];
				usable_tiles.erase(usable_tiles.begin() + usable_tiles.find(word[i]));
			}
			else if (blanks > 0)
			{
				blanks--;
			}
			else
			{
				return ValidatedWord();
			}
		}

		if (not(valid_opp_word.valid)) { return ValidatedWord(); }
		if (not(word_intersection)) { word_intersection = valid_opp_word.intersection; }

		total_points += valid_opp_word.points;

		x_count += x_increment;
		y_count += y_increment;
	}

	if (word_intersection || starting_coordinates[x][y]) { return ValidatedWord(true, total_points, word_intersection, used_tiles, (base_blanks - blanks)); }

	return ValidatedWord();
}

ValidatedWord Board::ApplyWord(string word, Direction dir, int x, int y, vector<Tile>& tiles)
{

	ValidatedWord applied_word = ValidWord(word, dir, x, y, tiles);

	if (applied_word.valid || not(applied_word.points == 0))
	{
		int x_count = 0;
		int y_count = 0;
		int x_increment = 0;
		int y_increment = 0;

		switch (dir)
		{
		case Direction::eLeftToRight:
			x_increment = 1;
			break;
		case Direction::eTopToBottom:
			y_increment = 1;
			break;
		}

		for (int i = 0; i < word.length(); i++)
		{

			board_coordinates[x + x_count][y + y_count].tile.letter = word[i];
			board_coordinates[x + x_count][y + y_count].tile.blank = false;
			starting_coordinates[x + x_count][y + y_count] = true;

			x_count += x_increment;
			y_count += y_increment;

		}

		for (auto tile : applied_word.used_tiles)
		{
			for (int i = 0; i < tiles.size(); i++)
			{
				
				if (tile == tiles[i].letter) { tiles.erase(tiles.begin() + i); break; }
			}
		}

		for (int j = 0; j < applied_word.used_blanks; j++)
		{
			for (int i = 0; i < tiles.size(); i++)
			{
				if (tiles[i].blank) { tiles.erase(tiles.begin() + i); break; }
			}
		} 

		return ValidatedWord(true, applied_word.points);
	}

	return ValidatedWord(false, 0);

}

void Board::Draw()
{
	cout << "---------------------------------------------------------------" << endl;
	cout << "   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  " << endl;
	for (int i = 0; i < 15; i++)
	{
		if (i < 9) { cout << " " << (i + 1) << " "; }
		else { cout << (i + 1) << " "; }

		for (int j = 0; j < 15; j++)
		{
			cout << board_coordinates[j][i].ReturnLetter() << "   ";
		}
		cout << endl;
		cout << endl;
	}
	cout << "---------------------------------------------------------------" << endl;
}