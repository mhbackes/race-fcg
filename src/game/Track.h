/*
 * Track.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GAME_TRACK_H_
#define GAME_TRACK_H_

#include <vector>
#include "../geometry/Triangle.h"
#include "Car.h"
#include "GL/glew.h"
#include "GL/freeglut.h"

using std::vector;

struct Track {
	vector<Triangle> track_parts;

	GLuint vertexID;
	GLuint vertexBuffer;
	GLuint vertexArray;
	GLuint uvBuffer;
	GLuint textureID;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	int vertex_data_size;

	Track();
	Track(vector<Triangle>& tp);
	bool contains(Car& car);

	bool load_model(char* obj_path, char* bmp_path, GLuint programID);
	void draw(glm::mat4& mvp, GLuint modelID, GLuint matrixID, GLuint programID);

	virtual ~Track();
};

#endif /* GAME_TRACK_H_ */
