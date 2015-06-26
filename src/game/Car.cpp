/*
 * Car.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Car.h"
#include "Race.h"

const float Car::MAX_SPEED = 100;
const float Car::MIN_SPEED = -20;
const float Car::MAX_SPEED_OUTSIDE_TRACK = 40;
const float Car::MIN_SPEED_OUTSIDE_TRACK = -5;

Car::Car() {
	this->race = nullptr;
	this->position = Rectangle();
	this->speed = 0;
	this->gas_acceleration = 1;
	this->idle_acceleration = -0.5;
	this->brake_acceleration = -1;
	this->turn_angle = 1;
}

void Car::gas() {
	speed += gas_acceleration;
	limit_speed(MIN_SPEED, MAX_SPEED);
}

void Car::idle() {
	speed += idle_acceleration;
	limit_speed(0, MIN_SPEED);
}

void Car::brake() {
	speed += brake_acceleration;
	limit_speed(MIN_SPEED, MAX_SPEED);
}

void Car::limit_speed(float min, float max) {
	if (speed > max)
		speed = max;
	if (speed < min)
		speed = min;
}

Car::Car(Race *r, Rectangle& pos, float ga, float ia, float ba, Angle ta) {
	race = r;
	position = pos;
	gas_acceleration = ga;
	idle_acceleration = ia;
	brake_acceleration = ba;
	turn_angle = ta;
	speed = 0;
}

void Car::turn_left() {
	if (speed != 0)
		position.rotate_counter_clockwise(turn_angle);
}

void Car::turn_right() {
	if (speed != 0)
		position.rotate_clockwise(turn_angle);
}

void Car::update() {
	if (!is_on_track())
		limit_speed(MIN_SPEED_OUTSIDE_TRACK, MAX_SPEED_OUTSIDE_TRACK);
	float dx = speed * position.get_angle().cos();
	float dy = speed * position.get_angle().sin();
	Rectangle new_pos = position;
	position.move(dx, dy);
	// TODO check collisions with other objects

	// if no collision
	position = new_pos;
}

bool Car::intersects(Rectangle& r) {
	return position.intersects(r);
}

bool Car::intersects(Car& c) {
	return intersects(c.get_position());
}

Rectangle& Car::get_position() {
	return position;
}

bool Car::is_on_track() {
	Track& t = race->track;
	return t.contains(*this);
}

Car::~Car() {
	// TODO Auto-generated destructor stub
}

