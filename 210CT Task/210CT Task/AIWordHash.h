#pragma once

#include "WordSet.h"
#include "Common.h"

#include <map>
#include <iostream>

using std::cout;
using std::endl;
using std::map;


class AIWordHash
{
public:

	vector<string> map_file_paths;
	map<string, vector<string>> word_map;

	AIWordHash();
	AIWordHash(WordSet& words);
	~AIWordHash();
};

