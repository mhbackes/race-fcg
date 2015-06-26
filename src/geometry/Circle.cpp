/*
 * Circle.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Circle.h"

Circle::Circle() :
		Circle(Point(0, 0), 1) {
}

Circle::Circle(Point c, float r) {
	center = c;
	radius = r;
}

Point Circle::get_center() {
	return center;
}

float Circle::get_radius() {
	return radius;
}

bool Circle::contains(Point& p) {
	return center.distance(p) <= radius;
}

bool Circle::intersects(Bounding_box& b) {
	Point bot_left = b.get_bot_left();
	Point bot_right = b.get_bot_right();
	Point top_left = b.get_top_left();
	Point top_right = b.get_top_right();
	return contains(bot_left) || contains(bot_right) || contains(top_left)
			|| contains(top_right);
}

Circle::~Circle() {
// TODO Auto-generated destructor stub
}

