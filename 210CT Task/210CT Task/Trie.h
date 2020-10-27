#pragma once

#include "Node.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

class Trie
{
private:

	Node root;
	int size = 0;
	bool change = false;

public:


	///<summary>
	///This function will append a string into the Trie structure. Returns true if successful.
	///</summary>
	bool AppendWord(string word);

	///<summary>
	///This function will remove a string from the Trie structure. Returns true if successful.
	///</summary>
	bool DeleteWord(string word);

	///<summary>
	///This function will search for a string in the Trie structure. Returns true if it has been found.
	///</summary>
	bool SearchWord(string word);

	///<summary>
	///This function will return a vector of permutations given certain conditions. <para/>
	///All permutations will start with pre_word and end with post_word and all values will be unique.  <para/>
	///Permutations will only consist of the tiles provided. A "#" can be substituted for all possible 26 characters. <para/>
	///Permutations will only be as long as the limit size, not including the pre_word and post_word conditions.
	///</summary>
	vector<string> PermutationSearch(string pre_word, string post_word, string tiles, int limit);

	///<summary>
	///Returns the amount of string stored in the Trie at the current time.
	///</summary>
	int Size();

	///<summary>
	///Debug function. Do not use. <3
	///</summary>
	void ListNodes();

};

