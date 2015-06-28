/*
 * AICar.h
 *
 *  Created on: Jun 27, 2015
 *      Author: mhbackes
 */

#ifndef GAME_AICAR_H_
#define GAME_AICAR_H_

#include "Car.h"

struct Race;

struct AICar: public Car {
	AICar();
	AICar(Race* race, Rectangle& pos, float ga, float ia, float ba, Angle ta);
	bool collides(Rectangle& new_pos);
	virtual ~AICar();
};

#endif /* GAME_AICAR_H_ */