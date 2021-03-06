/*
 * Race.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GAME_GAME_H_
#define GAME_RACE_H_

#include "AICar.h"
#include "Car.h"
#include "Track.h"
#include "Checkpoint.h"
#include "Camera.h"
#include "Terrain.h"
#include "Skybox.h"
#include <vector>
#include <ctime>
using std::vector;

struct Race {
	static const clock_t clocks_per_frame;

	Camera camera;
	Car player_car;
	vector<AICar> ai_cars;
	Track track;
	Terrain terrain;
	clock_t start_time, curr_time;
	vector<Checkpoint> checkpoints;
	Skybox skybox;
	bool paused;
	int max_lap;

	void reset_time();
	void update();
	bool finished();

	void add_checkpoint(Point center, float radius);

	bool parse_checkpoints(char *cp_path);

	Race();
	virtual ~Race();
};

#endif /* GAME_GAME_H_ */
