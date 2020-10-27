#include "Scrabble.h"

#include <iostream>
#include <sstream>

using std::stringstream;
using std::getline;
using std::cout;
using std::cin;
using std::endl;


Scrabble::Scrabble(string path)
{
	cout << "---------------------------------------------------------------" << endl;
	cout << "---Performing basic setup. Please standby." << endl;
	board = new Board(WordSet(path));

	Setup();

	while (not(Won()))
	{
		Step();
	}

	End();

}

Scrabble::~Scrabble()
{


	for (auto& player : players)
	{
		delete player;
	}
	players.clear();

	delete board;
}

void Scrabble::Setup()
{
	int human_players = 0;
	bool human_players_chosen = false;

	int ai_players = 0;
	bool ai_players_chosen = false;

	while (not(human_players_chosen))
	{
		cout << "---------------------------------------------------------------" << endl;
		cout << "---Enter the amount of human players between 0 - 4: ";

		UserInput(human_players);
		cout << endl;

		if (human_players > 4)
		{
			cout << "---------------------------------------------------------------" << endl;
			cout << "---Too many human players" << endl;
			continue;
		}
		else if (human_players < 0)
		{
			cout << "---------------------------------------------------------------" << endl;
			cout << "---Too few human players" << endl;
			continue;
		}
		else { human_players_chosen = true; }
	}

	while (not(ai_players_chosen))
	{
		cout << "---------------------------------------------------------------" << endl;
		cout << "---Enter the amount of AI players between 0 - 4: ";

		UserInput(ai_players);
		cout << endl;

		if (ai_players > 4)
		{
			cout << "---------------------------------------------------------------" << endl;
			cout << "---Too many AI players" << endl;
			continue;
		}
		else if (ai_players < 0)
		{
			cout << "---------------------------------------------------------------" << endl;
			cout << "---Too few AI players" << endl;
			continue;
		}
		else { ai_players_chosen = true; }
	}

	for (int i = 1; i < human_players + 1; i++) { players.push_back(new HumanPlayer(i, PlayerType::eHuman)); }

	for (int i = human_players + 1; i < human_players + ai_players + 1; i++) { players.push_back(new AIPlayer(i, PlayerType::eAI)); }

	for (auto player : players) { player->Replenish(bag); }

	
}

void Scrabble::Step()
{

	for (auto& player : players)
	{
		
		player->points += player->Turn(*board, players);
		if (player->last_action == PlayerAction::ePass)
		{
			player->NewTiles(bag);
		}
		player->Replenish(bag);

		if (Won()) { system("CLS"); return; }
	}
	
}

bool Scrabble::Won()
{	
	for (auto& player : players) { if(player->last_action != PlayerAction::ePass) return false;  }

	if (bag.tiles.size() == 0) { return true; }

	return false;
}

void Scrabble::End()
{
	board->Draw();
	cout << "---------------------------------------------------------------" << endl;
	for (auto& player : players)
	{
		cout << "---Final Points for Player " << player->id << " : " << player->points << endl;
	}
	cout << "---------------------------------------------------------------" << endl;
	cout << "GAME END" << endl;
}