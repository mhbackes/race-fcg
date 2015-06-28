/*
 * CheckPoint.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GAME_CHECKPOINT_H_
#define GAME_CHECKPOINT_H_

#include "../geometry/Circle.h"

struct Checkpoint : public Circle{
	Checkpoint();
	Checkpoint(Point& center, float radius);
	virtual ~Checkpoint();
};

#endif /* GAME_CHECKPOINT_H_ */
