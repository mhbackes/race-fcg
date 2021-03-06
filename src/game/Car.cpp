/*
 * Car.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Car.h"
#include "Race.h"
#include "../common/texture.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

const float Car::MAX_SPEED = 1;
const float Car::MIN_SPEED = -0.2;
const float Car::MAX_SPEED_OUTSIDE_TRACK = 0.2;
const float Car::MIN_SPEED_OUTSIDE_TRACK = -0.1;
const float Car::MAX_BOOST_LOAD = 1.0;
const float Car::BOOST_ACCELERATION = 0.01;
int Car::collision_cout = 0;

Car::Car() {
	this->race = nullptr;
	this->position = Rectangle();
	this->speed = 0;
	this->gas_acceleration = 0.5;
	this->idle_acceleration = -0.5;
	this->brake_acceleration = -1;
	this->turn_angle = 10;
	this->turn_l = false;
	this->turn_r = false;
	this->boost_active = false;
	this->boost_load = MAX_BOOST_LOAD;
	lap = 0;
	checkpoint = 0;
}

void Car::gas() {
	if (speed >= 0) {
		if (boost_active == false)
			speed += gas_acceleration;

		else {
			speed += (gas_acceleration + BOOST_ACCELERATION);
			boost_active = false;
		}
	} else
		speed -= brake_acceleration;
	limit_speed(MIN_SPEED, MAX_SPEED);
}

void Car::idle() {
	if (speed > 0) {
		speed += idle_acceleration;
		limit_speed(0, MAX_SPEED);
	} else {
		speed -= idle_acceleration;
		limit_speed(MIN_SPEED, 0);
	}
}

void Car::brake() {
	if (speed > 0)
		speed += brake_acceleration;
	else
		speed -= gas_acceleration;
	limit_speed(MIN_SPEED, MAX_SPEED);
}

void Car::limit_speed(float min, float max) {
	if (speed > max)
		speed = max;
	if (speed < min)
		speed = min;
}

Car::Car(Race *r, Rectangle& pos, float ga, float ia, float ba, Angle ta) {
	race = r;
	position = pos;
	gas_acceleration = ga;
	idle_acceleration = ia;
	brake_acceleration = ba;
	turn_angle = ta;
	speed = 0;
	lap = 0;
	checkpoint = 0;
	this->turn_l = false;
	this->turn_r = false;
	this->boost_active = false;
	this->boost_load = MAX_BOOST_LOAD;
}

void Car::turn_left() {
	if (speed != 0)
		turn_l = true;
}

void Car::turn_right() {
	if (speed != 0)
		turn_r = true;
}

void Car::boost() {
	if(boost_load > 0){
		boost_active = true;
		boost_load -= 0.01;
	}
	else
		boost_active = false;
}

void Car::update() {
	if (!is_on_track())
		limit_speed(MIN_SPEED_OUTSIDE_TRACK, MAX_SPEED_OUTSIDE_TRACK);
	float dx = -speed * position.angle.cos();
	float dy = -speed * position.angle.sin();
	Rectangle new_pos = position;
	new_pos.move(dx, dy);
	turn(new_pos);
	if (collides(new_pos))
		return;
	position = new_pos;
	update_checkpoint();
	if(boost_load < MAX_BOOST_LOAD)
		boost_load += 0.001;
}

void Car::update_checkpoint() {
	if (intersects(race->checkpoints[checkpoint])) {
		checkpoint += 15;
	}
	if (checkpoint >= race->checkpoints.size()) {
		checkpoint = 0;
		lap++;
	}
}

bool Car::intersects(Rectangle& r) {
	return position.intersects(r);
}

bool Car::intersects(Car& c) {
	return intersects(c.position);
}

bool Car::is_on_track() {
	Track& t = race->track;
	vector<Point> v = position.vertex();
	return t.contains(*this);
}

bool Car::intersects(Circle& r) {
	return position.intersects(r);
}

bool Car::load_model(char* obj_path, char* bmp_path, GLuint programID) {

	// car texture
	glActiveTexture(GL_TEXTURE0);
	textureID = loadBMP_custom(bmp_path);
	// car vertex
	glGenBuffers(1, &vertexBuffer);
	glGenVertexArrays(1, &vertexArray);

	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	bool res = loadOBJ(obj_path, vertices, uvs, normals);

	// Make a cube out of triangles (two triangles per side)
	vertex_data_size = 3 * vertices.size() + 2 * uvs.size()
			+ 3 * normals.size();
	GLfloat vertex_data[vertex_data_size];

	float max_x = 0;
	float max_y = 0;

	for (unsigned i = 0; i < vertices.size(); i++) {
		vertex_data[i * 8] = vertices[i][0];
		vertex_data[(i * 8) + 1] = vertices[i][1];
		vertex_data[(i * 8) + 2] = vertices[i][2];

		max_x = std::max(max_x, fabs(vertices[i].x));
		max_y = std::max(max_y, fabs(vertices[i].z));

		vertex_data[(i * 8) + 3] = uvs[i][0];
		vertex_data[(i * 8) + 4] = uvs[i][1];

		vertex_data[(i * 8) + 5] = normals[i][0];
		vertex_data[(i * 8) + 6] = normals[i][1];
		vertex_data[(i * 8) + 7] = normals[i][2];
	}
	position.height = max_x * 2;
	position.base = max_y * 2;

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data,
	GL_STATIC_DRAW);

	// connect the xyz to the "vert" attribute of the vertex shader
	glEnableVertexAttribArray(glGetAttribLocation(programID, "vert"));
	glVertexAttribPointer(glGetAttribLocation(programID, "vert"), 3, GL_FLOAT,
	GL_FALSE, 8 * sizeof(GLfloat), (const GLvoid*) (0 * sizeof(GLfloat)));

	// connect the uv coords to the "vertTexCoord" attribute of the vertex shader
	glEnableVertexAttribArray(glGetAttribLocation(programID, "vertTexCoord"));
	glVertexAttribPointer(glGetAttribLocation(programID, "vertTexCoord"), 2,
	GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat),
			(const GLvoid*) (3 * sizeof(GLfloat)));

	// connect the normal to the "vertNormal" attribute of the vertex shader
	glEnableVertexAttribArray(glGetAttribLocation(programID, "vertNormal"));
	glVertexAttribPointer(glGetAttribLocation(programID, "vertNormal"), 3,
	GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat),
			(const GLvoid*) (5 * sizeof(GLfloat)));

	// unbind the VAO
	glBindVertexArray(0);

	return res;
}

void Car::draw(glm::mat4& mvp, GLuint modelID, GLuint mvpID, GLuint programID) {
	Point& car_center = position.center;
	glm::mat4 onemat = glm::mat4(1.0f);
	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 car_pos = glm::vec3(car_center.x, 0, car_center.y);
	glm::mat4 rotation = glm::rotate(onemat,
			-(position.angle + Angle(180)).get_degree(), up);
	glm::mat4 size = glm::mat4(1);
	glm::mat4 translation = glm::translate(onemat, car_pos);
	glm::mat4 model = translation * size * rotation;
	glm::mat4 MVP = mvp * model;

	glUseProgram(programID);

	//iluminacao

	glUniform1f(glGetUniformLocation(programID, "material_shininess"), 10000);

	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &MVP[0][0]);
	//bind the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//bind VAO and draw
	glBindVertexArray(vertexArray);
	glDrawArrays(GL_TRIANGLES, 0, vertex_data_size);

	glBindVertexArray(vertexBuffer);
	glBindTexture(GL_TEXTURE_2D, textureID);

//	draw_position(mvp, modelID, mvpID);
}

void Car::turn(Rectangle& pos) {
	if (turn_l) {
		pos.rotate_counter_clockwise(turn_angle);
		turn_l = false;
	}
	if (turn_r) {
		pos.rotate_clockwise(turn_angle);
		turn_r = false;
	}
}

Car::~Car() {
	// TODO Auto-generated destructor stub
}

void Car::draw_position(glm::mat4& mvp, GLuint modelID, GLuint mvpID) {
	glm::mat4 model(1.0);
	glm::mat4 MVP = mvp * model;

	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &MVP[0][0]);

	vector<Point> v = position.vertex();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_QUAD_STRIP);
	glNormal3f(0, 1, 0);
	glVertex3f(v[0].x, 0.2, v[0].y);
	glVertex3f(v[1].x, 0.2, v[1].y);
	glVertex3f(v[2].x, 0.2, v[2].y);
	glVertex3f(v[3].x, 0.2, v[3].y);

	//glVertex3f(v[0].x, 0.1, v[0].y);
	glEnd();
	glFlush();
}

bool Car::collides(Rectangle& pos) {
	for (AICar& car : race->ai_cars) {
		if (this != &car && car.intersects(pos)) {
			collision_speed(car);
			return true;
		}
	}
	return false;
}

void Car::collision_speed(Car& car) {
	collision_cout++;
	Angle diff_angle = position.angle - car.position.angle;
	float diff = diff_angle.get_degree();
	if (diff < 60 || diff > 300) { //parallel semi-inelastic collision
		float new_speed = (speed + car.speed) / 2;
		speed = new_speed * 0.95;
		car.speed = new_speed * 1.05;
	} else if (diff > 120 && diff < 240) { //frontal inelastic collision
		float new_speed = (speed - car.speed) / 2;
		if (new_speed >= 0) {
			speed = new_speed;
			car.speed = -new_speed;
		} else {
			speed = -new_speed;
			car.speed = new_speed;
		}
	} else { //lateral collision
		speed = 0;
	}
}
