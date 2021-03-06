/*
 * Terrain.cpp
 *
 *  Created on: Jun 28, 2015
 *      Author: mhbackes
 */

#include "Terrain.h"
#include "../common/objloader.h"
#include "../common/texture.hpp"
#include <glm/glm.hpp>
#include <iostream>

Terrain::Terrain() {
	// TODO Auto-generated constructor stub

}

void Terrain::draw(glm::mat4& mvp, GLuint modelID, GLuint mvpID, GLuint programID) {
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 MVP = mvp * model;

	// INTENSIDADE da iluminacao ESPECULAR
	glUniform1f(glGetUniformLocation(programID, "material_shininess"), 1000);

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

bool Terrain::load_model(char* obj_path, char* bmp_path, GLuint programID) {
	textureID = loadBMP_custom(bmp_path);

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

Terrain::~Terrain() {
	// TODO Auto-generated destructor stub
}

