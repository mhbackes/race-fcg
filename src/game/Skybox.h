/*
 * Skybox.h
 *
 *  Created on: Jun 30, 2015
 *      Author: prlanzarin
 */

#ifndef GAME_SKYBOX_H_
#define GAME_SKYBOX_H_

#include "../geometry/Rectangle.h"
#include "../geometry/Angle.h"
#include "glm/glm.hpp"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>

#include "../common/objloader.h"

struct Skybox {

	GLuint vertexID;
	GLuint vertexBuffer;
	GLuint vertexArray;
	GLuint uvBuffer;
	GLuint textureID[6];
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	int vertex_data_size;

	Skybox();
	~Skybox();

	bool load_model(char* obj_path, char* t_front, char* t_back, char* t_left, char* t_right,
			char* t_top, char* t_bottom, GLuint programID);
	void draw(glm::mat4& mvp, GLuint modelID, GLuint mvpID, GLuint programID);

	void free();
};

#endif /* GAME_SKYBOX_H_ */
