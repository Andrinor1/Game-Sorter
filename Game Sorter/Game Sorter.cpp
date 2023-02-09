#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include "game.h"
#include "board_game.h"
#include "card_game.h"

bool max_players_low_comparison(game* l, game* r) { return l->get_max_players() < r->get_max_players(); }
bool max_players_high_comparison(game* l, game* r) { return l->get_max_players() > r->get_max_players(); }
bool approximate_time_low_comparison(game* l, game* r) { return l->get_approx_minutes() < r->get_approx_minutes(); }
bool approximate_time_high_comparison(game* l, game* r) { return l->get_approx_minutes() > r->get_approx_minutes(); }
bool times_played_low_comparison(game* l, game* r) { return l->get_times_played() < r->get_times_played(); }
bool times_played_high_comparison(game* l, game* r) { return l->get_times_played() > r->get_times_played(); }
bool recently_played_comparison(game* l, game* r) { return l->get_play_counter() > r->get_play_counter(); }
bool game_type_comparison(game* l, game* r) {
	board_game* bg_l = dynamic_cast<board_game*>(l);
	board_game* bg_r = dynamic_cast<board_game*>(r);
	if (bg_l && !bg_r) {
		return true;
	}
	else if (!bg_l && bg_r) {
		return false;
	}
	return false;
}

void recommend(std::vector<game*> games, int max_time, int players) {
	games.erase(std::remove_if(games.begin(), games.end(), [max_time, players](game* g)->bool {
		return (g->get_approx_minutes() > max_time || g->get_max_players() < players);
		}), games.end());
	std::sort(games.begin(), games.end(), recently_played_comparison);
	std::cout << std::endl << "Here are some recommendations!" << std::endl << std::endl;
	for (game* g : games) {
		g->print();
		std::cout << std::endl;
	}
}

int user_num_input(int max) {
	while (1) {
		std::string in_str;
		std::getline(std::cin, in_str);
		try {
			int input = std::stoi(in_str);
			if (input <= max && input > 0) {
				return input;
			}
			else {
				std::cout << "Invalid input." << std::endl;
			}
		}
		catch (std::invalid_argument e) {
			std::cout << "Invalid argument." << std::endl;
		}
		catch (std::exception e) {
			std::cout << "An unknown problem occurred." << std::endl;
		}
	}

}

std::vector<game*> read_from_file(std::string file_path) {
	std::fstream in_stream;
	std::vector<game*> games;
	in_stream.open(file_path);
	if (!in_stream.is_open()) {
		std::cout << "No file found!" << std::endl;
		return games;
	}
	std::string line;
	std::getline(in_stream, line);
	while (std::getline(in_stream, line)) {
		std::stringstream ss(line);

		std::string type, name, genre_str, temp;
		std::getline(ss, type, ',');
		std::getline(ss, genre_str, ',');
		std::getline(ss, name, ',');
		int max_players, approx_mins, times_played, play_counter, num_winners;
		double complexity;

		std::getline(ss, temp, ',');
		max_players = std::stoi(temp);

		std::getline(ss, temp, ',');
		approx_mins = std::stoi(temp);

		std::getline(ss, temp, ',');
		times_played = std::stoi(temp);

		std::getline(ss, temp, ',');
		play_counter = std::stoi(temp);

		std::getline(ss, temp, ',');
		complexity = std::stod(temp);

		std::getline(ss, temp, ',');
		num_winners = std::stoi(temp);

		std::vector<std::string> winners;
		for (int i = 0; i < num_winners; i++) {
			std::getline(ss, temp, ',');
			winners.push_back(temp);
		}
		if ((type == "board")) {
			board_game* bg = new board_game(name, genre_str, max_players, approx_mins, complexity, times_played, play_counter, winners);
			games.push_back(bg);
		}
		else if ((type == "card")) {
			card_game* cg = new card_game(name, genre_str, max_players, approx_mins, complexity, times_played, play_counter, winners);
			games.push_back(cg);
		}

	}
	in_stream.close();
	return games;
}

void write_sorted_games_to_file(std::vector<game*> games) {
	std::ofstream out_stream;
	out_stream.open("data\\games.csv");
	if (out_stream.is_open()) {
		out_stream << "Game type, Genre, Game name, max players, approximate minutes, times played, play counter, complexity, number of winners, winners(separated by commas)" << std::endl;
		std::for_each(games.begin(), games.end(), [&out_stream](game* g)->void {g->write(out_stream);});
	}
	else {
		std::cout << "Could not write to file data\\sorted-games.csv! Check permissions." << std::endl;
	}
}

std::vector<game*> sort_by_type(std::vector<game*> games, bool is_board_game) {
	std::vector<game*> sorted_games;
	for (int i = 0; i < games.size(); i++) {
		if (is_board_game) {
			board_game* bg = dynamic_cast<board_game*> (games.at(i));
			if (bg) {
				sorted_games.push_back(bg);
			}
		}
		else {
			card_game* cg = dynamic_cast<card_game*> (games.at(i));
			if (cg) {
				sorted_games.push_back(cg);
			}
		}
	}
	return sorted_games;
}

std::vector<game*> sort_by_max_players(std::vector<game*> games) {
	for (int i = 0; i < games.size(); i++) {
		for (int j = 0; j < games.size();j++) {
			if (games[i]->get_max_players() < games[j]->get_max_players()) {
				std::swap(games.at(i), games.at(j));
			}
		}
	}
	return games;
}

std::vector<game*> sort_by_approximate_time(std::vector<game*> games) {
	for (int i = 0; i < games.size(); i++) {
		for (int j = 0; j < games.size();j++) {
			if (games[i]->get_approx_minutes() < games[j]->get_approx_minutes()) {
				std::swap(games.at(i), games.at(j));
			}
		}
	}
	return games;
}

game* create_new_game() {
	std::string name, temp, type, genre_str;
	type = "";
	std::cout << "Enter your game's name:\t";
	std::getline(std::cin, name);
	std::cout << "How many maximum players does the game have?:\t";
	std::getline(std::cin, temp);
	int max_players = std::stod(temp);
	std::cout << "Enter your game's approximate length in minutes:\t";
	std::getline(std::cin, temp);
	int time = std::stoi(temp);
	std::cout << "How complex is your game on a scale from 0 to 10? Feel free to use decimals:\t";
	std::getline(std::cin, temp);
	double complexity = std::stod(temp);
	while (type != "board" && type != "card") {
		std::cout << "Is your game a board game or card game?:\t";
		std::getline(std::cin, type);
	}
	if (type == "board") {
		std::cout << "Enter the game's genre. Some examples are as follows:" << std::endl
			<< "\"area\": For area-control games such as Risk or Root." << std::endl
			<< "\"deduction\": For deduction games such as Clue or Secret Hitler." << std::endl
			<< "\"euro\": For Euro/Worker Placement games, such as Carcassonne or Catan." << std::endl
			<< "\"engine\": For engine-building games, such as Splendor or Terraforming Mars." << std::endl
			<< "\"rpg\": For Role-Playing games, typically with a legacy element, such as Gloomhaven or Descent." << std::endl
			<< "\"other\": For everything else!" << std::endl;
		std::getline(std::cin, genre_str);
		return new board_game(name, genre_str, max_players, time, complexity);
	}
	std::cout << "Enter the game's genre. Some examples are as follows:" << std::endl
		<< "\"deckbuilder\": For deck-building games such as Clank! and Dominion." << std::endl
		<< "\"deduction\": For deduction games such as Codenames or Werewolf." << std::endl
		<< "\"ccg\": For collectible card games, such as Magic: The Gathering or Pokemon." << std::endl
		<< "\"trick\": For trick-taking games, such as Euchre or Hearts." << std::endl
		<< "\"drafting\": For card drafting games, such as Sushi Go Party! and 7 Wonders." << std::endl
		<< "\"other\": For everything else!" << std::endl;
	std::getline(std::cin, genre_str);
	return new card_game(name, genre_str, max_players, time, complexity);
}

void sorting_loop(std::vector<game*>& games) {
	bool flag = true;
	while (flag) {
		std::cout << "Select an option:" << std::endl
			<< "1. Show all games" << std::endl
			<< "2. Sort By Max Players" << std::endl
			<< "3. Sort By Approximate Time (minutes)" << std::endl
			<< "4. Sort By Number of Times Played" << std::endl
			<< "5. Sort By Most Recently Played" << std::endl
			<< "6. Sort By Board/Card Game" << std::endl
			<< "7. Recommend Options" << std::endl
			<< "8. Play a game" << std::endl
			<< "9. Save list" << std::endl
			<< "10. Add new game" << std::endl
			<< "11. Quit" << std::endl;
		int input = user_num_input(11);
		int input_2;
		switch (input) {
		case 1:
			for (int i = 0; i < games.size();i++) {
				games[i]->print();
				std::cout << std::endl;
			}
			break;
		case 2:
			std::cout << std::endl << "1. Sort by Highest" << std::endl << "2. Sort by Lowest" << std::endl << std::endl;
			input_2 = user_num_input(2);
			switch (input_2) {
			case 1:
				std::sort(games.begin(), games.end(), max_players_high_comparison);
				break;
			case 2:
				std::sort(games.begin(), games.end(), max_players_low_comparison);
				break;
			}
			break;
		case 3:
			std::cout << std::endl << "1. Sort by Highest" << std::endl << "2. Sort by Lowest" << std::endl << std::endl;
			input_2 = user_num_input(2);
			switch (input_2) {
			case 1:
				std::sort(games.begin(), games.end(), approximate_time_high_comparison);
				break;
			case 2:
				std::sort(games.begin(), games.end(), approximate_time_low_comparison);
				break;
			}
			break;
		case 4:
			std::cout << std::endl << "1. Sort by Highest" << std::endl << "2. Sort by Lowest" << std::endl << std::endl;
			input_2 = user_num_input(2);
			switch (input_2) {
			case 1:
				std::sort(games.begin(), games.end(), times_played_high_comparison);
				break;
			case 2:
				std::sort(games.begin(), games.end(), times_played_low_comparison);
				break;
			}
			break;
		case 5:
			std::sort(games.begin(), games.end(), recently_played_comparison);
			break;
		case 6:
			std::sort(games.begin(), games.end(), game_type_comparison);
			break;
		case 7:
		{
			std::cout << "Enter the amount of time you have (in minutes):" << std::endl;
			std::string temp;
			std::getline(std::cin, temp);
			int time_int;
			try {
				time_int = std::stoi(temp);
			}
			catch (std::exception e) {
				std::cout << "Invalid input." << std::endl;
				return;
			}
			std::cout << "Enter number of players:" << std::endl;
			int players;
			std::getline(std::cin, temp);
			try {
				players = std::stoi(temp);
			}
			catch (std::exception e) {
				std::cout << "Invalid input." << std::endl;
				return;
			}
			recommend(games, time_int, players);
			break;
		}
		case 8:
			std::cout << std::endl << "What game would you like to play?" << std::endl;
			for (int i = 0; i < games.size(); i++) {
				std::cout << i+1 << ": " << games.at(i)->get_name() << std::endl;
			}
			input_2 = user_num_input(games.size()) - 1;
			std::for_each(games.begin(), games.end(), [](game* g)->void {g->increase_play_counter();});
			games.at(input_2)->play();
			break;
		case 9:
			write_sorted_games_to_file(games);
			break;
		case 10:
		{
			game* new_game = create_new_game();
			games.push_back(new_game);
			break;
		}
		case 11:
			flag = false;
			break;
		}
	}
}

int main() {
	std::cout << "Welcome to Griffin's Game Sorter!" << std::endl << std::endl;
	std::vector<game*> games = read_from_file("data\\games.csv");

	sorting_loop(games);

	for (game* g : games) {
		delete g;
	}
}