/*
 * Camera.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GAME_CAMERA_H_
#define GAME_CAMERA_H_

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Car.h"

struct Camera {
	Car* car;

	Camera();
	Camera(Car* car);

	glm::vec3 eye();
	glm::vec3 car_front();
	glm::vec3 car_center();
	glm::vec3 eagle_eye();
	glm::mat4 mvp();

	virtual ~Camera();
};

#endif /* GAME_CAMERA_H_ */
