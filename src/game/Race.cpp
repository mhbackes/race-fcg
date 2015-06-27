/*
 * Game.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Race.h"

const clock_t Race::clocks_per_frame = 0;

Race::Race() {
	// TODO Auto-generated constructor stub

}

void Race::update() {
	player_car.update();
	dummy_car.update();
	curr_time = clock();
}

Race::~Race() {
	// TODO Auto-generated destructor stub
}

void Race::reset_time() {
	start_time = curr_time = clock();
}
