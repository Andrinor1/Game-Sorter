#include "game.h"
#include <iostream>
#include <algorithm>

game::game(std::string name, int max_players, int approx_minutes, double complexity) {
	this->name = name;
	this->max_players = max_players;
	this->approx_minutes = approx_minutes;
	this->complexity = complexity;
	this->times_played = 0;
	this->play_counter = 0;
}

game::game(std::string name, int max_players, int approx_minutes, double complexity, int times_played, int play_counter, std::vector<std::string> winners) : game(name,max_players,approx_minutes,complexity) {
	this->times_played = times_played;
	this->play_counter = play_counter;
	this->winners = winners;
}

void game::print() {
	std::cout << name << " is designed for up to " << max_players << " players." << std::endl << "It should take around " << approx_minutes << " minutes to play." << std::endl << "It is ranked " << complexity << "/10 in terms of complexity." << std::endl
		<<"It has been played " << times_played << " times total." << std::endl << "The people who have won this game are: ";
	std::for_each(winners.begin(), winners.end(), [](std::string w)->void {std::cout << w << " ";});
	std::cout << std::endl;
}

std::string game::get_name() {
	return name;
}
int game::get_max_players() {
	return max_players;
}
int game::get_approx_minutes() {
	return approx_minutes;
}
int game::get_times_played() {
	return times_played;
}
int game::get_play_counter() {
	return play_counter;
}
double game::get_complexity() {
	return complexity;
}
void game::increase_play_counter() {
	play_counter++;
}