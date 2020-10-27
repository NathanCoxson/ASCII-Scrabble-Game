#include "Node.h"


#include <iostream>


using std::cout;
using std::endl;

Node::Node()
{

}

Node::~Node()
{
	for (auto child : children)
	{
		delete child;
	}
}

Node* Node::GetChild(char letter)
{
	return children[int(letter) - 97];
}

bool Node::CreateChildNode(char letter, int level)
{
	if (!CheckChildNode(letter))
	{
		children[int(letter) - 97] = new Node(level);
		return true;
	}
	return false;
}

bool Node::CheckChildNode(char letter)
{
	if (int(letter) < 97 || int(letter) > 122) return false;

	return (GetChild(letter) != nullptr) ? true : false;
}

bool Node::DeleteChildNode(char letter)
{
	if (CheckChildNode(letter))
	{
		delete children[int(letter) - 97];
		children[int(letter) - 97] = nullptr;
		return true;
	}
	return false;
}

bool Node::CompareNode(Node* other)
{
	if (terminal != other->terminal) return false;
	for (int i = 0; i < 26; i++)
	{
		if (children[i] == nullptr && other->children[i] == nullptr) continue;
		else if (children[i] != nullptr && other->children[i] != nullptr)
		{
			if (children[i]->terminal != other->children[i]->terminal) return false;
		}
		else return false;
	}
	return true;
}

bool Node::AppendWord(string word)
{

	if (word.length() == 0)
	{
		terminal = true;
		return true;
	}

	CreateChildNode(word[0], order + 1);

	string cutword = word;
	cutword.erase(0, 1);

	return GetChild(word[0])->AppendWord(cutword);
}

bool Node::DeleteWord(string word)
{

	if (word.length() == 0)
	{

		terminal = false;

		for (auto child : children)
		{
			if (child != nullptr)
			{
				return false;
			}
		}
		return true;
	}

	string cutword = word;
	cutword.erase(0, 1);

	if (CheckChildNode(word[0]))
	{
		if (GetChild(word[0])->DeleteWord(cutword))
		{
			DeleteChildNode(word[0]);

			if (terminal) return false;
			for (auto child : children)
			{
				if (child != nullptr)
				{
					return false;
				}
			}
			return true;

		}
	}
	return false;

}

bool Node::SearchWord(string word)
{

	if (word.length() == 0)
	{
		return terminal;
	}

	if (CheckChildNode(word[0]))
	{
		string cutword = word;
		cutword.erase(0, 1);

		return GetChild(word[0])->SearchWord(cutword);
	}

	return false;
}

set<string> Node::PermutationSearch(string pre_word, string post_word, string tiles, int limit, string traversed_word)
{
	set<string> store;

	if (pre_word.length() > 0)
	{
		string cut_pre_word = pre_word;
		cut_pre_word.erase(0, 1);
		if (CheckChildNode(pre_word[0])) return GetChild(pre_word[0])->PermutationSearch(cut_pre_word, post_word, tiles, limit, traversed_word);
		else return store;
	}


	if (terminal && post_word.size() == 0) store.insert(traversed_word);

	if (limit == 0 || (tiles.length() == 0 && post_word.size() == 0)) return store;

	if (post_word.size() > 0 && order != 0)
	{
		if (CheckChildNode(post_word[0]))
		{
			string cut_post_word = post_word;
			cut_post_word.erase(0, 1);

			for (auto word : GetChild(post_word[0])->PermutationSearch("", cut_post_word, "", limit - 1, traversed_word + post_word[0]))
			{
				store.insert(word);
			}
		}
	}

	if (limit > post_word.size())
	{
		for (int i = 0; i < tiles.length(); i++)
		{
			
			string cut_tiles = tiles;
			cut_tiles.erase(i, 1);

			if (tiles[i] == '#')
			{
				int count = 0;
				for (auto child : children)
				{
					if (child != nullptr)
					{
						for (auto word : child->PermutationSearch("", post_word, cut_tiles, limit - 1, traversed_word + char(97 + count)))
						{
							store.insert(word);
						}
					}
					count++;
				}
			}
			else if (CheckChildNode(tiles[i]))
			{
				for (auto word : GetChild(tiles[i])->PermutationSearch("", post_word, cut_tiles, limit - 1, traversed_word + tiles[i]))
				{
					store.insert(word);
				}
			}
		}
	}
	
	return store;
}

int Node::Size()
{

	int total = 0;
	int amount_of_children = 0;

	for (auto child : children)
	{
		if (child != nullptr) amount_of_children++;
	}

	if (amount_of_children == 0) return 1;
	else
	{
		for (auto child : children)
		{
			if (child != nullptr) total += child->Size();
		}

		if (terminal) total++;

		return total;
	}
}

void Node::ListNodes()
{
	
	int count = 0;
	for (auto child : children)
	{
		if (child != nullptr)
		{
			cout << "NODE ORDER: " << order + 1 << " NODE VALUE: " << char(97 + count) << " AND TERMINAL IS " << (child->terminal ? "TRUE" : "FALSE") << endl; 
			child->ListNodes();
		}
		count++;
	}

	/*count = 0;
	for (auto child : children)
	{
		if (child != nullptr)
		{
			//cout << "CHILDREN OF NODE " << char(97 + count) << " AT ORDER " << order << endl;
			child->ListNodes();
		}
		count++;
	}*/
}

