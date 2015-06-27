/*
 * Angle.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Angle.h"
#include <cmath>

Angle::Angle(float angle) {
	this->angle = angle;
}

void Angle::clockwise(float angle) {
	this->angle -= angle;
	this->angle = limit(this->angle);
}

void Angle::counter_clockwise(float angle) {
	this->angle += angle;
	this->angle = limit(this->angle);
}

float Angle::get_degree() {
	return angle;
}

float Angle::get_rad() {
	return angle * M_PI / 180;
}

void Angle::clockwise(Angle angle) {
	clockwise(angle.get_degree());
}

void Angle::counter_clockwise(Angle angle) {
	counter_clockwise(angle.get_degree());
}

Angle::Angle(const Angle& angle) :
		Angle(angle.angle) {
}

double Angle::sin() {
	return std::sin(get_rad());
}

double Angle::cos() {
	return std::cos(get_rad());
}

double Angle::limit(double angle) {
	if (angle >= 360)
		angle -= 360;
	if (angle < 0)
		angle += 360;
	return angle;
}

Angle::~Angle() {
	// TODO Auto-generated destructor stub
}

Angle::Angle() :
		Angle(0) {
}
