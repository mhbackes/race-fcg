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

Camera::Camera() {
	// TODO Auto-generated constructor stub
	car = NULL;
}

Camera::Camera(Car* car) {
	this->car = car;
}

glm::mat4 Camera::mvp() {
	glm::mat4 model = glm::mat4(1.0);
	glm::mat4 view = glm::lookAt(eye(), car_front(), glm::vec3(0, 1, 0));
	glm::mat4 projection = glm::perspective(60.0f, 16.0f / 9.0f, 0.1f, 100.0f);
	return projection * view * model;
}

glm::vec3 Camera::eye() {
	glm::vec3 eye;
	Rectangle& car_pos = car->get_position();
	Angle car_to_eye_angle = car_pos.get_angle() - Angle(180);
	Point car_center = car_pos.get_center();
	eye.x = car_to_eye_angle.cos() * 10 + car_center.x;
	eye.y = car_to_eye_angle.sin() * 10 + car_center.y;
	return eye;
}

glm::vec3 Camera::car_front() {
	glm::vec3 car_front;
	Rectangle& car_pos = car->get_position();
	Angle car_to_eye_angle = car_pos.get_angle();
	Point car_center = car_pos.get_center();
	car_front.x = car_to_eye_angle.cos() * 5 + car_center.x;
	car_front.y = car_to_eye_angle.sin() * 5 + car_center.y;
	return car_front;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

