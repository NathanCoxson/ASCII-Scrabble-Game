#include "AIPlayer.h"

int AIPlayer::Turn(Board& board, vector<Player*>& players)
{

	vector<string> playable_words;
	vector<AIPlay> plays;
	BasicWord best_play;
	ValidatedWord attempted_play;
	string format_tiles;


	for (auto tile : tiles)
	{
		format_tiles += tile.letter;
	}

	if (board.board_coordinates[7][7].tile.blank)
	{
		playable_words = board.word_trie.PermutationSearch("", "", format_tiles, 7);
		if (playable_words.size() != 0) best_play = ParseWords(playable_words, "");
		else return 0;
		last_action = PlayerAction::eWord;
		return board.ApplyWord(best_play.word, Direction::eLeftToRight, 7, 7, tiles).points;
	}

	plays = FindPlays(board);

	for (auto play : plays)
	{
		
		if (play.post) playable_words = board.word_trie.PermutationSearch("", play.preword, format_tiles, play.limit);
		else playable_words = board.word_trie.PermutationSearch(play.preword, "", format_tiles, play.limit);

		if (playable_words.size() != 0) best_play = ParseWords(playable_words, play.preword);
		else { continue; }
		
		
		if (play.post)
		{

			if (play.dir == Direction::eLeftToRight) attempted_play = board.ApplyWord(best_play.word, play.dir, play.x-(best_play.word.length()-1), play.y, tiles);
			else attempted_play = board.ApplyWord(best_play.word, play.dir, play.x, play.y-(best_play.word.length() - 1), tiles);
		}
		else
		{
			attempted_play = board.ApplyWord(best_play.word, play.dir, play.x, play.y, tiles);
		}

		if (attempted_play.valid)
		{
			last_played_word = best_play.word;
			last_action = PlayerAction::eWord;
			return attempted_play.points;
		}
	}

	last_action = PlayerAction::ePass;
	return 0;
}

BasicWord AIPlayer::ParseWords(vector<string> words, string pre)
{
	string selected_word = words[0];
	
	if (selected_word == pre && words.size() > 1) selected_word = words[1];

	for (auto word : words)
	{
		if (word == pre) { continue; }
		if (WordPointCalculator(word).points > WordPointCalculator(selected_word).points)
		{
			if (word.length() > selected_word.length()) selected_word = word;
		}
	}

	return WordPointCalculator(selected_word);
}

vector<AIPlay> AIPlayer::FindPlaysLtR(Board& board)
{
	vector<AIPlay> plays;
	string found_word;
	int stored_x = 0;
	int word_count = 0;
	int left_spaces = 0;
	int right_spaces = 0;
	bool word = false;

	for (int y = 0; y < 15; y++)
	{
		for (int x = 0; x < 15; x++)
		{
			
			if (not(board.board_coordinates[x][y].tile.blank))
			{
				if (not(word))
				{
					found_word = board.GetWord(Direction::eLeftToRight, x, y);
					word = true;
					stored_x = x;
					x += (found_word.size());
				}
				else
				{
					if (left_spaces - 1 > 0) plays.push_back(AIPlay(found_word, Direction::eLeftToRight, stored_x, y, left_spaces, true));
					if (right_spaces - 1 > 0) plays.push_back(AIPlay(found_word, Direction::eLeftToRight, stored_x, y, right_spaces, false));

					left_spaces = right_spaces;
					right_spaces = 0;
					found_word = board.GetWord(Direction::eLeftToRight, x, y);
					stored_x = x;
					x += (found_word.size());

				}
			}
			if (word) right_spaces++;
			else left_spaces++;

		}
		if (found_word != "")
		{
			if (left_spaces - 1 > 0) plays.push_back(AIPlay(found_word, Direction::eLeftToRight, stored_x, y, left_spaces, true));
			if (right_spaces - 1 > 0) plays.push_back(AIPlay(found_word, Direction::eLeftToRight, stored_x, y, right_spaces, false));
		}
		left_spaces = 0;
		right_spaces = 0;
		found_word = "";
		stored_x = 0;
	}

	return plays;
}

vector<AIPlay> AIPlayer::FindPlaysTtB(Board& board)
{
	vector<AIPlay> plays;
	string found_word;
	int stored_y = 0;
	int word_count = 0;
	int top_spaces = 0;
	int bottom_spaces = 0;
	bool word = false;

	for (int x = 0; x < 15; x++)
	{
		for (int y = 0; y < 15; y++)
		{

			if (not(board.board_coordinates[x][y].tile.blank))
			{
				if (not(word))
				{
					found_word = board.GetWord(Direction::eTopToBottom, x, y);
					word = true;
					stored_y = y;
					y += (found_word.size());
				}
				else
				{
					if (top_spaces - 1 > 0) plays.push_back(AIPlay(found_word, Direction::eTopToBottom, x, stored_y, top_spaces, true));
					if (bottom_spaces - 1 > 0) plays.push_back(AIPlay(found_word, Direction::eTopToBottom, x, stored_y, bottom_spaces, false));
					top_spaces = bottom_spaces;
					bottom_spaces = 0;
					found_word = board.GetWord(Direction::eTopToBottom, x, y);
					stored_y = y;
					y += (found_word.size());

				}
			}
			if (word) bottom_spaces++;
			else top_spaces++;

		}
		if (found_word != "")
		{
			if (top_spaces - 1 > 0) plays.push_back(AIPlay(found_word, Direction::eTopToBottom, x, stored_y, top_spaces, true));
			if (bottom_spaces - 1 > 0) plays.push_back(AIPlay(found_word, Direction::eTopToBottom, x, stored_y, bottom_spaces, false));
		}
		top_spaces = 0;
		bottom_spaces = 0;
		found_word = "";
		stored_y = 0;
	}

	return plays;
}


vector<AIPlay> AIPlayer::FindPlays(Board& board)
{
	vector<AIPlay> plays;

	std::random_device generator;
	std::uniform_int_distribution<int> distribution(0, 1);

	switch (distribution(generator))
	{
	case 0:
		for (auto play : FindPlaysTtB(board))
		{
			plays.push_back(play);
		}
		for (auto play : FindPlaysLtR(board))
		{
			plays.push_back(play);
		}
		break;
	case 1:
		for (auto play : FindPlaysLtR(board))
		{
			plays.push_back(play);
		}
		for (auto play : FindPlaysTtB(board))
		{
			plays.push_back(play);
		}
		break;
	}

	return plays;
}




