#include "Trie.h"




bool Trie::AppendWord(string word)
{
	if (word.length() == 0) return false;
	if (root.AppendWord(word))
	{
		change = true;
		return true;
	}
	else return false;
}

bool Trie::DeleteWord(string word)
{
	if (word.length() == 0) return false;
	if (SearchWord(word))
	{
		root.DeleteWord(word);
		change = true;
	}
	return SearchWord(word) ? false : true;

}

bool Trie::SearchWord(string word)
{
	if (word.length() == 0) return false;
	return root.SearchWord(word);
}

vector<string> Trie::PermutationSearch(string pre_word, string post_word, string tiles, int limit)
{
	
	if (not(tiles.length() == 0 || limit < 1))
	{
		set<string> values = root.PermutationSearch(pre_word, post_word, tiles, limit + post_word.size(), pre_word);
		vector<string> store(values.begin(), values.end());
		return store;
	}
	else
	{
		vector<string> store;
		return store;
	}

}

int Trie::Size()
{
	if (change) size = root.Size();
	return size;
}

void Trie::ListNodes() 
{
	root.ListNodes();
}