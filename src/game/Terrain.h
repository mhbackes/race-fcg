/*
 * Terrain.h
 *
 *  Created on: Jun 28, 2015
 *      Author: mhbackes
 */

#ifndef GAME_TERRAIN_H_
#define GAME_TERRAIN_H_

#include <vector>
#include "../geometry/Triangle.h"
#include "Car.h"
#include "GL/glew.h"
#include "GL/freeglut.h"

struct Terrain {
	GLuint vertexID;
	GLuint vertexBuffer;
	GLuint vertexArray;
	GLuint uvBuffer;
	GLuint textureID;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	int vertex_data_size;

	Terrain();

	void draw(glm::mat4& mvp, GLuint modelID, GLuint mvpID, GLuint programID);
	bool load_model(char* obj_path, char* bmp_path, GLuint programID);
	virtual ~Terrain();
};

#endif /* GAME_TERRAIN_H_ */
