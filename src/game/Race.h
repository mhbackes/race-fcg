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
using std::vector;

struct Race {
	Camera camera;
	Car player_car;
	Track track;
	vector<Checkpoint> checkpoints;

	void update();

	Race();
	virtual ~Race();
};

#endif /* GAME_GAME_H_ */
