/*
 * CheckPoint.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GAME_CHECKPOINT_H_
#define GAME_CHECKPOINT_H_

#include "../geometry/Circle.h"
#include "glm/glm.hpp"
#include "GL/glew.h"
#include "GL/freeglut.h"

struct Checkpoint: public Circle {
	Checkpoint();
	Checkpoint(Point& center, float radius);
	void draw(glm::mat4& mvp, GLuint modelID, GLuint matrixID);
	virtual ~Checkpoint();
};

#endif /* GAME_CHECKPOINT_H_ */
