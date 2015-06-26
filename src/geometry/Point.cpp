/*
 * Point.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Point.h"
#include <cmath>

Point::Point(float x, float y) {
	this->x = x;
	this->y = y;
}

void Point::move(float dx, float dy) {
	x += dx;
	y += dy;
}

Point::Point() : Point(0,0) {
}

Point::~Point() {
	// TODO Auto-generated destructor stub
}

float Point::distance(Point& p) {
	float diff_x = x - p.x;
	float diff_y = y - p.y;
	return sqrt(diff_x * diff_x + diff_y * diff_y);
}
