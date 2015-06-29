/*
 * CheckPoint.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GAME_CHECKPOINT_H_
#define GAME_CHECKPOINT_H_

#include "../geometry/Circle.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include <vector>

struct Checkpoint: public Circle {
	static GLuint vertexID;
	static GLuint vertexBuffer;
	static GLuint uvBuffer;
	static GLuint vertexArray;
	static GLuint textureID;
	static std::vector<glm::vec3> vertices;
	static std::vector<glm::vec2> uvs;
	static std::vector<glm::vec3> normals;
	static int vertex_data_size;

	Checkpoint();
	Checkpoint(Point& center, float radius);
	static bool load_model(char* obj_path, char* bmp_path, GLuint programID);
	void draw(glm::mat4& mvp, GLuint modelID, GLuint matrixID);
	virtual ~Checkpoint();
};

#endif /* GAME_CHECKPOINT_H_ */
