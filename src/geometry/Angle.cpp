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
	if (this->angle >= 360)
		this->angle -= 360;
	if (this->angle < 0)
		this->angle += 360;
}

void Angle::counter_clockwise(float angle) {
	this->angle += angle;
	if (this->angle >= 360)
		this->angle -= 360;
	if (this->angle < 0)
		this->angle += 360;
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

Angle::Angle(const Angle& angle) : Angle(angle.angle) {
}

double Angle::sin() {
	return std::sin(get_rad());
}

double Angle::cos() {
	return std::cos(get_rad());
}

Angle::~Angle() {
	// TODO Auto-generated destructor stub
}

Angle::Angle() : Angle(0) {
}
