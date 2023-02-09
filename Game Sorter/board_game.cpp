#include "board_game.h"
#include <iostream>
#include <fstream>

board_game::board_game(std::string name, std::string genre_str, int max_players, int approx_minutes, double complexity) : game(name, max_players, approx_minutes, complexity) {
	if (genre_str == "area") {
		game_genre = AREA;
	}
	else if (genre_str == "deduction") {
		game_genre = DEDUCTION;
	}
	else if (genre_str == "euro") {
		game_genre = EURO;
	}
	else if (genre_str == "engine") {
		game_genre = ENGINE;
	}
	else if (genre_str == "rpg") {
		game_genre = RPG;
	}
	else {
		game_genre = OTHER;
	}
	this->genre_str = genre_str;
}

board_game::board_game(std::string name, std::string genre_str, int max_players, int approx_minutes, double complexity, int times_played, int play_counter, std::vector<std::string> winners) : game(name, max_players, approx_minutes, complexity, times_played, play_counter, winners) {
	if (genre_str == "area") {
		game_genre = AREA;
	}
	else if (genre_str == "deduction") {
		game_genre = DEDUCTION;
	}
	else if (genre_str == "euro") {
		game_genre = EURO;
	}
	else if (genre_str == "engine") {
		game_genre = ENGINE;
	}
	else if (genre_str == "rpg") {
		game_genre = RPG;
	}
	else {
		game_genre = OTHER;
	}
	this->genre_str = genre_str;
}

void board_game::play() {
	play_counter = 0;
	times_played++;
	std::cout << "You played the board game: " << name << ". Who won?\t";
	std::string winner;
	std::getline(std::cin, winner);
	winners.push_back(winner);
	times_played++;
}
void board_game::write(std::ofstream& of) {
	of << "board," << genre_str << "," << name << "," << max_players << "," << approx_minutes << "," << times_played << "," << play_counter << "," << complexity << "," << winners.size() << ",";
	for (int i = 0; i < winners.size(); i++) {
		of << winners[i] << ",";
	}
	of << std::endl;
}
board_game::genre board_game::get_game_genre() {
	return game_genre;
}