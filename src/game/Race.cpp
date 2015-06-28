/*
 * Game.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Race.h"
#include "Checkpoint.h"
#include "../geometry/Point.h"

#include <vector>

#include <string>

#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

const clock_t Race::clocks_per_frame = 0;

Race::Race() {
	// TODO Auto-generated constructor stub
}

void Race::update() {
	player_car.update();
	for(AICar& car : ai_cars){
		car.update();
	}
	curr_time = clock();
}

Race::~Race() {
	// TODO Auto-generated destructor stub
}

void Race::reset_time() {
	start_time = curr_time = clock();
}

void Race::add_checkpoint(Point center, float radius) {
	Checkpoint new_checkpoint = Checkpoint(center, radius);
	checkpoints.push_back(new_checkpoint);
}

bool Race::parse_checkpoints(char *cp_path) {

	ifstream file;
    file.open(cp_path);
    std::string input;

	if (!file.good())
		return false;

	while(!file.eof()) {
		std::getline(file, input);
		std::vector<char> buffer(input.begin(), input.end());
		buffer.push_back('\0');

		char *end;
		float x = strtof(&buffer[0], &end);
		float y = strtof(end, NULL);
		float radius = strtof(&buffer[3], &end);

		Point new_point = Point(x, y);
		this->add_checkpoint(new_point, radius);
	}
	return true;
}
