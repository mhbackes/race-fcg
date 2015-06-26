/*
 * Track.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GAME_TRACK_H_
#define GAME_TRACK_H_

#include <vector>
#include "../geometry/Triangle.h"
#include "Car.h"

using std::vector;

class Track {
	vector<Triangle> track_parts;
public:
	Track();
	Track(vector<Triangle>& tp);
	bool contains(Car& car);

	virtual ~Track();
};

#endif /* GAME_TRACK_H_ */
