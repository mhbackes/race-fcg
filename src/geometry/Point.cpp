/*
 * Point.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Point.h"
#include <cmath>
#include <sstream>
using std::stringstream;

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

string Point::to_string() {
	stringstream stream;
	stream << "(" << x << ", " << y << ")";
	return stream.str();
}

Angle Point::angle(Point& a, Point& b) {
	float distpa = distance(a);
	float distpb = distance(b);
	float distab = a.distance(b);
	float angle = acos((distpa * distpa + distpb * distpb + distab * distab) / (2 * distpa * distpb));
	return Angle(angle * 180 / M_PI);
}
