/*
 * Car.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GAME_CAR_H_
#define GAME_CAR_H_

#include "../geometry/Rectangle.h"
#include "../geometry/Angle.h"

struct Race;

class Car {
	Race* race;
	Rectangle position;
	float speed;
	float gas_acceleration;
	float idle_acceleration;
	float brake_acceleration;
	Angle turn_angle;

	void limit_speed(float min, float max);
public:
	static const float MAX_SPEED;
	static const float MIN_SPEED;
	static const float MAX_SPEED_OUTSIDE_TRACK;
	static const float MIN_SPEED_OUTSIDE_TRACK;

	Car();
	Car(Race* race, Rectangle& pos, float ga, float ia, float ba, Angle ta);
	void gas();
	void idle();
	void brake();
	void turn_left();
	void turn_right();
	void update();

	bool is_on_track();

	bool intersects(Rectangle& r);
	bool intersects(Car& c);

	Rectangle& get_position();

	virtual ~Car();
};

#endif /* GAME_CAR_H_ */
