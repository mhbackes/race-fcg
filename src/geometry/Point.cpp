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

float Point::distance_x(Point& p){
	return fabs(x - p.x);
}

float Point::distance_y(Point& p){
	return fabs(y - p.y);
}

string Point::to_string() {
	stringstream stream;
	stream << "(" << x << ", " << y << ")";
	return stream.str();
}

Angle Point::angle(Point& a, Point& b) {
	float dxa = distance_x(a);
	float dxb = distance_x(b);
	float dya = distance_y(a);
	float dyb = distance_y(b);
	float dista = distance(a);
	float distb = distance(b);
	float angle = acos((dxa * dxb + dya * dyb) / (dista * distb));
	return Angle(angle * 180 / M_PI);
}
