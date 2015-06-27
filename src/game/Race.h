/*
 * Race.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GAME_GAME_H_
#define GAME_RACE_H_

#include "Car.h"
#include "Track.h"
#include "Checkpoint.h"
#include "Camera.h"
#include <vector>
#include <ctime>
using std::vector;

struct Race {
	static const clock_t clocks_per_frame;

	Camera camera;
	Car player_car;
	Track track;
	clock_t start_time, curr_time;
	vector<Checkpoint> checkpoints;

	Car dummy_car;

	void reset_time();
	void update();

	Race();
	virtual ~Race();
};

#endif /* GAME_GAME_H_ */
