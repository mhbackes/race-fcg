/*
 * Game.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Race.h"
#include "Checkpoint.h"
#include "../geometry/Point.h"

#include <stdio.h>

#include <iostream>
using std::cout;
using std::endl;


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
	checkpoints.push_back(Checkpoint(center, radius));
}

bool Race::parse_checkpoints(char *cp_path) {

	FILE* cp_file = fopen(cp_path, "r");
	float x,y,radius;
	int nPar;

	if (cp_file == NULL) {
		std::cout << "Failed to open " << cp_path << endl;
		return false;
	}

	fseek(cp_file, 0, SEEK_END);
	if (!ftell(cp_file)) {
		std::cout << "Empty checkpoints file" << endl;
		return false;
	}

	fseek(cp_file, 0, SEEK_SET);
	nPar = fscanf(cp_file,"%f %f %f\n", &x, &y, &radius);
	while(nPar != EOF) {
		if (nPar != 3)
			return false;

		this->add_checkpoint(Point(x, y), radius);
		nPar = fscanf(cp_file,"%f %f %f\n", &x, &y, &radius);
	}

	return true;
}
