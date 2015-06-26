/*
 * Camera.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Camera.h"

Camera::Camera() {
	// TODO Auto-generated constructor stub
	car = NULL;
}

Camera::Camera(Car* car) {
	this->car = car;
}

glm::mat4 Camera::mvp() {
	// TODO implement function mvp
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	return projection * view * model;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

