/*
 * AICar.cpp
 *
 *  Created on: Jun 27, 2015
 *      Author: mhbackes
 */

#include "AICar.h"
#include "Race.h"

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

AICar::~AICar() {
	// TODO Auto-generated destructor stub
}

