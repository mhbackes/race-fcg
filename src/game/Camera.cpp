/*
 * Camera.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Camera.h"
#include "../geometry/Rectangle.h"
#include "../geometry/Angle.h"
#include "../geometry/Point.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera() {
	// TODO Auto-generated constructor stub
	car = NULL;
}

Camera::Camera(Car* car) {
	this->car = car;
	this->vision = NORMAL;
}

glm::mat4 Camera::mvp() {
	glm::vec3 eye, center;
	switch (vision) {
	case NORMAL:
		eye = eye_back();
		center = car_front();
		break;
	case REAR:
		eye = eye_front();
		center = car_back();
		break;
	case EAGLE:
		eye = eye_eagle();
		center = car_center();
	}

	glm::mat4 model = glm::mat4(1.0);
	glm::mat4 view = glm::lookAt(eye, center, glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(60.0f, 16.0f / 9.0f, 0.1f, 100.0f);
	return projection * view * model;
}

glm::vec3 Camera::eye_back() {
	glm::vec3 eye;
	Angle car_to_eye_angle = car->position.angle;
	Point car_center = car->position.center;
	eye.x = car_to_eye_angle.cos() * 6 + car_center.x;
	eye.y = 3;
	eye.z = car_to_eye_angle.sin() * 6 + car_center.y;
	return eye;
}

glm::vec3 Camera::car_front() {
	glm::vec3 car_front;
	Angle car_to_eye_angle = car->position.angle - Angle(180);
	Point car_center = car->position.center;
	car_front.x = car_to_eye_angle.cos() * 7 + car_center.x;
	car_front.y = 0;
	car_front.z = car_to_eye_angle.sin() * 7 + car_center.y;
	return car_front;
}

glm::vec3 Camera::car_center() {
	glm::vec3 car_center;
	Point car_center_pos = car->position.center;
	car_center.x = car_center_pos.x + 0.1;
	car_center.y = 0;
	car_center.z = car_center_pos.y;
	return car_center;
}

glm::vec3 Camera::eye_eagle() {
	glm::vec3 eagle_eye;
	Point car_center_pos = car->position.center;
	eagle_eye.x = car_center_pos.x;
	eagle_eye.y = 60;
	eagle_eye.z = car_center_pos.y;
	return eagle_eye;
}

glm::vec3 Camera::eye_front() {
	glm::vec3 eye;
	Angle car_to_eye_angle = car->position.angle - Angle(180);
	Point car_center = car->position.center;
	eye.x = car_to_eye_angle.cos() * 6 + car_center.x;
	eye.y = 3;
	eye.z = car_to_eye_angle.sin() * 6 + car_center.y;
	return eye;
}

glm::vec3 Camera::car_back() {
	glm::vec3 car_front;
	Angle car_to_eye_angle = car->position.angle;
	Point car_center = car->position.center;
	car_front.x = car_to_eye_angle.cos() * 7 + car_center.x;
	car_front.y = 0;
	car_front.z = car_to_eye_angle.sin() * 7 + car_center.y;
	return car_front;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::toggle_eagle() {
	switch (vision) {
	case NORMAL:
		vision = EAGLE;
		break;
	default:
		vision = NORMAL;
	}
}

void Camera::toggle_rear() {
	switch (vision) {
	case NORMAL:
		vision = REAR;
		break;
	default:
		vision = NORMAL;
	}
}

glm::vec3 Camera::position() {
	switch (vision) {
	case NORMAL:
		eye_back();
		break;
	case REAR:
		eye_front();
		break;
	case EAGLE:
		eye_eagle();
	}
}
