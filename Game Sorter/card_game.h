#pragma once
#include "game.h"


class card_game : public game{
private:
	enum genre { DECKBUILDER, CCG, TRICK, DRAFTING, DEDUCTION, OTHER };
	genre game_genre;
	std::string genre_str;
public:
	card_game(std::string name, std::string genre_str, int max_players, int approx_minutes, double complexity);
	card_game(std::string name, std::string genre_str, int max_players, int approx_minutes, double complexity, int times_played, int play_counter, std::vector<std::string> winners);
	void play() override;
	void write(std::ofstream&) override;
	genre get_game_genre();
};

