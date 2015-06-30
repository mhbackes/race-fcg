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

enum Vision {NORMAL, REAR, EAGLE};

struct Camera {
	Car* car;
	Vision vision;

	Camera();
	Camera(Car* car);

	void toggle_eagle();
	void toggle_rear();

	glm::vec3 eye_back();
	glm::vec3 eye_front();
	glm::vec3 car_front();
	glm::vec3 car_back();
	glm::vec3 car_center();
	glm::vec3 eye_eagle();
	glm::mat4 mvp();
	glm::vec3 position();

	virtual ~Camera();
};

#endif /* GAME_CAMERA_H_ */
