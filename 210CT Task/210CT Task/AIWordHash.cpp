#include "AIWordHash.h"

#include <random>
//#include <filesystem>

//namespace fs = std::filesystem;

AIWordHash::AIWordHash()
{

}

AIWordHash::AIWordHash(WordSet& words)
{
	
	//std::string path = "AIMapHashes/";
	//for (const auto& entry : fs::directory_iterator(path))
	//{
	//	string file_path = entry.path().string();
	//	map_file_paths.push_back(file_path);
	//}

	//for (auto entry : map_file_paths)
	//{
	//	cout << entry << endl;
	//}

	int hit = 0;
	int miss = 0;
	int supermiss = 0;
	
	for (int i = 0; i < 1000; i++)
	{
		cout << i << endl;
		string tiles = "aaaaaaaaabbccddddeeeeeeeeeeeeffggghhiiiiiiiiijkllllmmnnnnnnooooooooppqrrrrrrssssttttttuuuuvvwwxyyz";
		string word = "";
		std::random_device generator;
	

		for (int j = 0; j < 7; j++)
		{
			std::uniform_int_distribution<int> distribution(0, tiles.length() - 1);
			int random_integer = distribution(generator);
			word += tiles[random_integer];
			tiles.erase(random_integer, 1);
		}
		BinaryInsertionSort(word, 0, word.size());

		

		SearchResult find = BinarySearch(map_file_paths, "AIMapHashes/" + word + ".txt");
		cout << map_file_paths[find.index] << " " << find.result << endl;
		cout << word << " " << map_file_paths[find.index] << endl;
		if (find.result)
		{
			AIMapRead(map_file_paths[find.index], word_map);
			cout << word_map[word].size() << " is the size" << endl;
			if (word_map[word].size() != 0) hit++;
			else miss++;
			word_map.clear();
		}
		else supermiss++;


	}

	cout << hit << " hits!" << endl;
	cout << miss << " misses!" << endl;
	cout << supermiss << " supermisses!" << endl;

	while (true) {}
	cout << "BEGINNING AI HASH" << endl;
	int count = 0;
	int count2 = 0;


	string sorted_word = "hellosab";
	BinaryInsertionSort(sorted_word, 0, sorted_word.size());
	vector<string> possible_words;

	/*for (auto word : words.Legal)
	{
		string other_sorted_word = word.word;
		BinaryInsertionSort(other_sorted_word, 0, other_sorted_word.size());
		if (WordInOtherWord(other_sorted_word, sorted_word)) { possible_words.push_back(word.word); }
	}
	cout << "BOOP" << endl;
	for (auto word : possible_words)
	{
		cout << word << endl;
	}

	while (true) {}*/


	for (auto word : words.Legal)
	{
		if (word.word.length() > 14 || word.word.length() < 4) { continue; }
		//cout << "STORING WORD" << endl;
		string sorted_word = word.word;
		//cout << "SORTING WORD - " << sorted_word << endl;
		BinaryInsertionSort(sorted_word, 0, sorted_word.size());
		//cout << "SORTED WORD - " << sorted_word << endl;
		//cout << "PUSHING WORD" << endl;
		word_map[sorted_word].push_back(word.word);
		//cout << "PUSHED WORD" << endl;
		count++;
		//cout << count << endl;
		if (count % 100 == 0) { cout << count2 << endl; count2++; }
	}
	cout << "ENDING AI HASH" << endl;

	cout << "BEGINNING SECONDARY HASH" << endl;
	int count3 = 0;
	int count4 = 0;
	cout << word_map.size() << endl;

	
	map<string, vector<string>> base_word_map;

	string first_hash;
	for (auto hash : word_map)
	{
		if (count3 % 1000 == 0)
		{
			first_hash = hash.first;
		}

		
		//count4 = 0;
		for (auto word : words.Legal)
		{
			if (word.word.length() > 14 || word.word.length() < 4) { continue; }
			string sorted_word2 = word.word;
			BinaryInsertionSort(sorted_word2, 0, sorted_word2.size());
			if (WordInOtherWord(sorted_word2, hash.first))
			{
				bool valid2 = true;
				for (auto word2 : hash.second)
				{
					if (word2 == word.word) { valid2 = false; break; }
				}

				if (valid2)
				{
					//cout << "ADDING " << word.word << " TO " << hash.first << " WITH CURRENT SIZE " << hash.second.size() << endl;
					base_word_map[hash.first].push_back(word.word);
					
					//cout << "CHECKING NEXT SIZE " << hash.second.size() << endl;
					//count4++;
				}
			}
		}

		count3++;
		if (count3 % 1000 == 0)
		{
			cout << count3 << endl;
			AIMapWrite("AIMapHashes/" + first_hash + ".txt", base_word_map);
			base_word_map.clear();
		}
	}
	AIMapWrite("AIMapHashes/" + first_hash + ".txt", base_word_map);
	base_word_map.clear();

	//AIMapWrite("AIMAP.txt", word_map);

	map<string, vector<string>> second_word_map;

	/*AIMapRead("AIMAP.txt", second_word_map);

	

	for (auto hash : second_word_map)
	{
		cout << "HASHES FOR: " << hash.first << " with size " << hash.second.size() << endl;
		for (auto word : hash.second)
		{
			cout << word << endl;
		}
	}*/
	cout << "FINISHED WRITING MAP!!!!" << endl;

	while (true) {}

	/*for (auto word : words.Legal)
	{
		string sorted_word = word.word;
		BinaryInsertionSort(sorted_word, 0, sorted_word.size());
		count4 = 0;
		for (auto hash : word_map)
		{
			if (hash.first.length() < sorted_word.length()) { continue; }
			
			if (hash.first.find_first_not_of(sorted_word) != string::npos)
			{
				bool valid = true;
				for (auto word2 : hash.second)
				{
					if (word2.word == word.word) { valid = false; }
				}

				if (valid)
				{
					word_map[sorted_word].push_back(word);
					count2++;
				}
			}
		}
		count3++;
		cout << count3 << " " << count4 << endl;
	}*/
	cout << "ENDING SECONDARY HASH" << endl;

}


AIWordHash::~AIWordHash()
{
}
