/*
 * Car.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GAME_CAR_H_
#define GAME_CAR_H_

#include "../geometry/Rectangle.h"
#include "../geometry/Angle.h"
#include "glm/glm.hpp"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>

#include "../common/objloader.h"

struct Race;

struct Car {
	Race* race;
	Rectangle position;
	float speed;
	float gas_acceleration;
	float idle_acceleration;
	float brake_acceleration;
	Angle turn_angle;

	int checkpoint;
	int lap;

	GLuint vertexID;
	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint vertexArray;
	GLuint textureID;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	int vertex_data_size;

	bool turn_l, turn_r;

	void limit_speed(float min, float max);

	static const float MAX_SPEED;
	static const float MIN_SPEED;
	static const float MAX_SPEED_OUTSIDE_TRACK;
	static const float MIN_SPEED_OUTSIDE_TRACK;

	Car();
	Car(Race* race, Rectangle& pos, float ga, float ia, float ba, Angle ta);
	void gas();
	void idle();
	void brake();
	void turn_left();
	void turn_right();

	virtual void update();
	virtual void update_checkpoint();
	void turn(Rectangle& pos);

	bool is_on_track();

	bool intersects(Rectangle& r);
	bool intersects(Circle& r);
	bool intersects(Car& c);
	virtual bool collides(Rectangle& new_pos);

	bool load_model(char* obj_path, char* bmp_path, GLuint programID);
	void draw(glm::mat4& mvp, GLuint modelID, GLuint matrixID, GLuint programID);

	void draw_position(glm::mat4& mvp, GLuint modelID, GLuint matrixID);

	virtual ~Car();
};

#endif /* GAME_CAR_H_ */
