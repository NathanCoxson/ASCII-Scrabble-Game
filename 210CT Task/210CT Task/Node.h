#pragma once

#include <string>
#include <map>
#include <vector>
#include <set>



using std::vector;
using std::string;
using std::map;
using std::set;


///<summary>
///This class represents a node in a Trie structure.
///</summary>
class Node
{
public:

	bool terminal = false;
	int order = 0;
	Node* children[26] = {nullptr};
	
	Node();
	Node(int l) : order(l) {};
	~Node();

	///<summary>
	///This function will append a character to a node and call the next node for the next character in the string
	///</summary>
	bool AppendWord(string word);

	///<summary>
	///This function will delete a relevant node as long as it has no other children
	///</summary>
	bool DeleteWord(string word);

	///<summary>
	///This function will call itself if the next letter in the string is a valid child
	///</summary>
	bool SearchWord(string word);

	///<summary>
	///This function will call itself if the child node exists for each tile character
	///</summary>
	set<string> PermutationSearch(string pre_word, string post_word, string tiles, int limit, string traversed_word);

	int Size();

	void ListNodes();

	///<summary>
	///This function will return true if a node has the same children and terminality
	///</summary>
	bool CompareNode(Node* other);

private:
	///<summary>
	///This function will return the reference to a child given a character
	///</summary>
	Node* GetChild(char letter);

	///<summary>
	///This function will create a child node with a specified letter and increased order if it doesn't already exist.
	///</summary>
	bool CreateChildNode(char letter, int level);

	///<summary>
	///This function will return true if a child node with a specified letter exists
	///</summary>
	bool CheckChildNode(char letter);

	///<summary>
	///This function will delete a child node with a specified letter if it exists.
	///</summary>
	bool DeleteChildNode(char letter);

	

	
};

