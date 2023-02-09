#include "card_game.h"
#include <iostream>
#include <fstream>

card_game::card_game(std::string name, std::string genre_str, int max_players, int approx_minutes, double complexity) : game(name, max_players, approx_minutes, complexity) {
	if (genre_str == "deckbuilder") {
		game_genre = DECKBUILDER;
	}
	else if (genre_str == "deduction") {
		game_genre = DEDUCTION;
	}
	else if (genre_str == "drafting") {
		game_genre = DRAFTING;
	}
	else if (genre_str == "ccg") {
		game_genre = CCG;
	}
	else if (genre_str == "trick") {
		game_genre = TRICK;
	}
	else {
		game_genre = OTHER;
	}
	this->genre_str = genre_str;
}

card_game::card_game(std::string name, std::string genre_str, int max_players, int approx_minutes, double complexity, int times_played, int play_counter, std::vector<std::string> winners) : game(name, max_players, approx_minutes, complexity, times_played, play_counter, winners) {
	if (genre_str == "deckbuilder") {
		game_genre = DECKBUILDER;
	}
	else if (genre_str == "deduction") {
		game_genre = DEDUCTION;
	}
	else if (genre_str == "drafting") {
		game_genre = DRAFTING;
	}
	else if (genre_str == "ccg") {
		game_genre = CCG;
	}
	else if (genre_str == "trick") {
		game_genre = TRICK;
	}
	else {
		game_genre = OTHER;
	}
	this->genre_str = genre_str;
}


void card_game::play() {
	play_counter = 0;
	times_played++;
	std::cout << "You played the card game: " << name << ". Who won?\t";
	std::string winner;
	std::getline(std::cin, winner);
	winners.push_back(winner);
	times_played++;
}

void card_game::write(std::ofstream& of) {
	of << "card," << genre_str << "," << name << "," << max_players << "," << approx_minutes << "," << times_played << "," << play_counter << "," << complexity << "," << winners.size() << ",";
	for (int i = 0; i < winners.size(); i++) {
		of << winners[i] << ",";
	}
	of << std::endl;
}

card_game::genre card_game::get_game_genre() {
	return game_genre;
}