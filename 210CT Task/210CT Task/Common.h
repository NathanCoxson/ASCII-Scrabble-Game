#pragma once

#include <vector>
#include <tuple>
#include <string>
#include <map>



using std::string;
using std::vector;
using std::map;


///<summary>
///Differentiates between the directions that words can be placed on the board.
///</summary>
enum Direction
{
	eTopToBottom = 'd',
	eLeftToRight = 'r'
};

///<summary>
///Diferentiates between directions for checking adjacent words.
///</summary>
enum DirectionType
{
	eEquivalent,
	eOpposite
};

///<summary>
///Differentiates between Human & AI players
///</summary>
enum PlayerType
{
	eBase,
	eHuman,
	eAI
};

///<summary>
///Differentiates between actions players can take
///</summary>
enum PlayerAction
{
	eNoAction,
	eWord,
	ePass
};

///<summary>
///Differentiates between a new word formed on the board and an additional word
///</summary>
enum WordType
{
	eNew,
	eAdditional
};

///<summary>
///Differentiates between intersections
///</summary>
enum WordIntersection
{
	eNone = false,
	eInner = true,
	eOuter = true
};

///<summary>
///This struct stores a word and its basic point value
///</summary>
struct BasicWord
{
	string word;
	int points;

	BasicWord(string w = "", int p = 0) : word(w), points(p) {}
};

///<summary>
///This struct stores a word and its final point value, as well as its intersection type and what tiles have been used
///</summary>
struct ValidatedWord
{
	bool valid;
	int points;
	WordIntersection intersection;
	string used_tiles;
	int used_blanks;

	ValidatedWord(bool v = false, int p = 0, WordIntersection i = WordIntersection::eNone, string ut = "", int ub = 0) : valid(v), points(p), intersection(i), used_tiles(ut), used_blanks{ub} {}
};

///<summary>
///This struct stores whether a search was successful and the index of the word
///</summary>
struct SearchResult
{
	bool result;
	int index;

	SearchResult(bool r = false, int i = 0) : result(r), index(i) {}
};

///<summary>
///This struct will store a tile value
///</summary>
struct Tile
{
	char letter;
	bool blank;

	Tile(char a = ' ', bool b = true) : letter(a), blank(b) {}
};

///<summary>
///This struct will store a possible play that an AI player can make
///</summary>
struct AIPlay
{
	string preword;
	Direction dir;
	int x;
	int y;
	int limit;
	bool post;

	AIPlay(string w, Direction d, int xc, int yc, int l, bool p) : preword(w), dir(d), x(xc), y(yc), limit(l), post(p) {}
};

///<summary>
///This function will take a user input and store it in the parameter reference
///</summary>
void UserInput(int& var);

///<summary>
///This function will take a user input and store it in the parameter reference
///</summary>
void UserInput(string& var);

///<summary>
///This function will take a user input and store it in the parameter reference
///</summary>
void UserInput(char& var);

///<summary>
///This function will find the location of a string within a vector of strings
///</summary>
SearchResult BinarySearch(vector<string>& words, string target);

///<summary>
///This function will find the location of a string within a vector of BasicWords
///</summary>
SearchResult BinarySearch(vector<BasicWord>& words, string target);

///<summary>
///This will perform Binary Insertion Sort on a vector of Basic Words
///</summary>
void BinaryInsertionSort(vector<BasicWord>& words, int start, int end);

///<summary>
///This will perform Binary Insertion Sort on a string
///</summary>
void BinaryInsertionSort(string& word, int start, int end);

///<summary>
///This will perform a merge between two sorted blocks
///</summary>
void Merge(vector<BasicWord>& words, int start, int middle, int end);

///<summary>
///This will perform merge sort on a vector of BasicWords
///</summary>
void MergeSort(vector<BasicWord>& words, int size);

///<summary>
///This will perform binary merge sort on a vector of BasicWords
///</summary>
void BinaryMergeSort(vector<BasicWord>& words, int size, int block_size);

///<summary>
///This will return the basic value of a letter
///</summary>
int LetterPointCalculator(char letter);

///<summary>
///This will return the basic value of a word
///</summary>
BasicWord WordPointCalculator(string text);
