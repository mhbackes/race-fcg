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

float AICar::direction(Point& destination) {
	Point& center = position.center;
	Angle angle = position.angle + Angle(180);
	Point ahead;
	ahead.x = angle.cos() + center.x;
	ahead.y = angle.sin() + center.y;
	float cross_product = (ahead.x - center.x) * (destination.y - center.y)
			- (ahead.y - center.y) * (destination.x - center.x);
	return cross_product;
}

void AICar::update() {
	inputs();
	Car::update();
}

void AICar::inputs() {
	float d = direction(race->checkpoints[checkpoint].center);
//std::cout << "Speed: " << speed << "\tCheck: " << checkpoint;
	if (d < -0.5) {
//	std::cout << "\tLEFT    ";
		turn_left();
	} else if (d > 0.5) {
//	std::cout << "\tRIGHT   ";
		turn_right();
	} //else
//	std::cout << "\tSTRAIGHT";
	if (speed <= 0.2) {
//	std::cout << "\tTOO_SLOW";
		gas();
	} else if (d > -0.5 && d < 0.5) {
//	std::cout << "\tOK_SPEED";
		gas();
	} else if (speed > 0 && (d < -1.45 || d > 1.45)) {
//	std::cout << "\tBREAK   ";
		brake();
	} //else {
//	std::cout << "\tNO_GAS  ";
//}
//std::cout << "\tDir: " << d << std::endl;
}

void AICar::update_checkpoint() {
	if (intersects(race->checkpoints[checkpoint])) {
		checkpoint++;
	}
	if (checkpoint >= race->checkpoints.size()) {
		checkpoint = 0;
		lap++;
	}
}

AICar::~AICar() {
// TODO Auto-generated destructor stub
}

