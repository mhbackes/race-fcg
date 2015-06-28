/*
 * AICar.cpp
 *
 *  Created on: Jun 27, 2015
 *      Author: mhbackes
 */

#include "AICar.h"
#include "Race.h"
#include <iostream>

AICar::AICar() :
		Car() {
	// TODO Auto-generated constructor stub

}

AICar::AICar(Race* race, Rectangle& pos, float ga, float ia, float ba, Angle ta) :
		Car(race, pos, ga, ia, ba, ta) {
}

bool AICar::collides(Rectangle& new_pos) {
	for (AICar& car : race->ai_cars) {
		Car* car_p = &car;
		if (this != &car && car.intersects(new_pos))
			return true;
	}
	return race->player_car.intersects(new_pos);
}

Direction AICar::direction(Point& destination) {
	Point& center = position.get_center();
	Angle angle = position.get_angle() + Angle(180);
	Point ahead;
	ahead.x = angle.cos() + center.x;
	ahead.y = angle.sin() + center.y;
	float cross_product = (ahead.x - center.x) * (destination.y - center.y)
			- (ahead.y - center.y) * (destination.x - center.x);
	std::cout << cross_product;
	if (cross_product > 1) {
		std::cout << " Right" << std::endl;
		return RIGHT;
	}
	if (cross_product < -1) {
		std::cout << " Left" << std::endl;
		return LEFT;
	}
	std::cout << " Straight" << std::endl;
	return STRAIGHT;

}

void AICar::update() {
	inputs();
	Car::update();
}

void AICar::inputs() {
	Direction d = direction(race->checkpoints[checkpoint].center);
	switch (d) {
	case LEFT:
		turn_left();
		break;
	case RIGHT:
		turn_right();
	}
	gas();
}

AICar::~AICar() {
// TODO Auto-generated destructor stub
}

