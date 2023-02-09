#pragma once
#include <string>
#include <vector>

class game
{
protected:
	std::string name;
	int max_players,approx_minutes,times_played,play_counter;
	double complexity;
	std::vector<std::string> winners;
public:
	game(std::string name, int max_players, int approx_minutes, double complexity);
	game(std::string name, int max_players, int approx_minutes, double complexity,int times_played,int play_counter, std::vector<std::string> winners);
	virtual void play() = 0;
	void print();

	std::string get_name();
	int get_max_players();
	int get_approx_minutes();
	int get_times_played();
	int get_play_counter();
	void increase_play_counter();
	double get_complexity();
	virtual void write(std::ofstream&) = 0;
};

