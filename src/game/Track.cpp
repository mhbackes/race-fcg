/*
 * Track.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Track.h"
#include "../common/objloader.h"
#include "../common/texture.hpp"
#include <glm/glm.hpp>
#include <iostream>

Track::Track() {
}

Track::Track(vector<Triangle>& tps) {
	track_parts = tps;
}

bool Track::contains(Car& car) {
	vector<Point> car_vertex = car.position.vertex();
	for (Point& v : car_vertex) {
		bool contains = false;
		for (Triangle& t : track_parts) {
			if (t.contains(v)){
				contains = true;
				break;
			}
		}
		if(!contains)
			return false;
	}
	return true;
}

void Track::draw(glm::mat4& mvp, GLuint modelID, GLuint mvpID) {
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 MVP = mvp * model;

	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &MVP[0][0]);
	//bind the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//bind VAO and draw
	glBindVertexArray(vertexArray);
	glDrawArrays(GL_TRIANGLES, 0, vertex_data_size);

	glBindVertexArray(vertexArray);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

Track::~Track() {
	// TODO Auto-generated destructor stub
}

bool Track::load_model(char* obj_path, char* bmp_path, GLuint programID) {
	textureID = loadBMP_custom(bmp_path);
//	// track vertex
	glGenBuffers(1, &vertexBuffer);
	glGenVertexArrays(1, &vertexArray);

	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	bool res = loadOBJ(obj_path, vertices, uvs, normals);

	// Make a cube out of triangles (two triangles per side)
	vertex_data_size = 3 * vertices.size() + 2 * uvs.size()
			+ 3 * normals.size();
	GLfloat vertex_data[vertex_data_size];

	for (int i = 0; i < vertices.size(); i++) {

		vertex_data[i * 8] = vertices[i][0];
		vertex_data[(i * 8) + 1] = vertices[i][1];
		vertex_data[(i * 8) + 2] = vertices[i][2];

		vertex_data[(i * 8) + 3] = uvs[i][0];
		vertex_data[(i * 8) + 4] = uvs[i][1];

		vertex_data[(i * 8) + 5] = normals[i][0];
		vertex_data[(i * 8) + 6] = normals[i][1];
		vertex_data[(i * 8) + 7] = normals[i][2];

	}

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data,
	GL_STATIC_DRAW);

	for (int i = 0; i < vertices.size(); i = i + 3) {
		Point p0(vertices[i].x, vertices[i].z);
		Point p1(vertices[i + 1].x, vertices[i + 1].z);
		Point p2(vertices[i + 2].x, vertices[i + 2].z);
//		std::cout << p0.to_string() << " " << p1.to_string() << " " << p2.to_string() << std::endl;
		track_parts.push_back(Triangle(p0, p1, p2));
	}

	// connect the xyz to the "vert" attribute of the vertex shader
	glEnableVertexAttribArray(glGetAttribLocation(programID, "vert"));
	glVertexAttribPointer(glGetAttribLocation(programID, "vert"), 3, GL_FLOAT,
			GL_FALSE, 8 * sizeof(GLfloat),
			(const GLvoid*) (0 * sizeof(GLfloat)));

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
