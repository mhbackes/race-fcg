/*
 * Track.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Track.h"

Track::Track() {
}

Track::Track(vector<Triangle>& tps) {
	track_parts = tps;
}

bool Track::contains(Car& car) {
	Rectangle car_pos = car.get_position();
	vector<Point> car_vertex = car_pos.get_vertex();
	for(Point& v : car_vertex){
		for(Triangle& t : track_parts){
			if(!t.contains(v))
				return false;
		}
	}
	return true;
}

Track::~Track() {
	// TODO Auto-generated destructor stub
}

