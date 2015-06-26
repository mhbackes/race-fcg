/*
 * Camera.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GAME_CAMERA_H_
#define GAME_CAMERA_H_

#include "glm/glm.hpp"
#include "Car.h"

struct Camera {
	Car* car;

	Camera();
	Camera(Car* car);

	glm::mat4 mvp();

	virtual ~Camera();
};

#endif /* GAME_CAMERA_H_ */
