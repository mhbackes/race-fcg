/*
 * Boundingbox.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Boundingbox.h"

Bounding_box::Bounding_box(float xmin, float ymin, float xmax, float ymax) {
	this->p0 = Point(xmin, ymin);
	this->p1 = Point(xmax, ymax);
}

Bounding_box::Bounding_box(Point center, float height, float base) {
	float half_height = height / 2;
	float half_base = base / 2;
	float xmin = center.x - half_base;
	float ymin = center.y - half_height;
	float xmax = center.x + half_base;
	float ymax = center.y + half_height;
	this->p0 = Point(xmin, ymin);
	this->p1 = Point(xmax, ymax);
}

Bounding_box::~Bounding_box() {
	// TODO Auto-generated destructor stub
}

bool Bounding_box::intersects(Bounding_box& b) {
	return p0.x <= b.p1.x && p1.x >= b.p0.x && p1.y >= b.p0.y && p0.y <= b.p1.y;
}

Point Bounding_box::get_bot_left() {
	return p0;
}

Point Bounding_box::get_top_left() {
	return Point(p0.x, p1.y);
}

Point Bounding_box::get_bot_right() {
	return Point(p1.x, p0.y);
}

Point Bounding_box::get_top_right() {
	return p1;
}
