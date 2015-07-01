/*
 * Skybox.cpp
 */

#include "Skybox.h"
#include "../common/objloader.h"
#include "../common/texture.hpp"
#include <glm/glm.hpp>

#include <stdio.h>

#include <iostream>
using std::cout;
using std::endl;

Skybox::Skybox() {
}

void Skybox::draw(glm::mat4& mvp, GLuint modelID, GLuint mvpID,
		GLuint programID) {
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 MVP = mvp * model;
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &MVP[0][0]);

	// Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	// Just in case we set all vertices to white.
	glColor4f(1, 1, 1, 1);

	// Render the front quad
	glBindTexture(GL_TEXTURE_2D, textureID[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 1);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	// Render the left quad
	glBindTexture(GL_TEXTURE_2D, textureID[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 0);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 1);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 1);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glEnd();

	// Render the back quad
	glBindTexture(GL_TEXTURE_2D, textureID[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 0);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glEnd();

	// Render the right quad
	glBindTexture(GL_TEXTURE_2D, textureID[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1, 0);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glEnd();

	// Render the top quad
	glBindTexture(GL_TEXTURE_2D, textureID[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 0);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1, 1);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glEnd();

	// Render the bottom quad
	glBindTexture(GL_TEXTURE_2D, textureID[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0, 1);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 1);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1, 0);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();

	// Restore enable bits and matrix
	glPopAttrib();
	glPopMatrix();

	glDepthMask(1);
}

bool Skybox::load_model(char* obj_path, char* t_front, char* t_back, char* t_left,
		char* t_right, char* t_top, char* t_bottom, GLuint programID) {
	textureID[0] = loadBMP_custom(t_front);
	textureID[1] = loadBMP_custom(t_back);
	textureID[2] = loadBMP_custom(t_left);
	textureID[3] = loadBMP_custom(t_right);
	textureID[4] = loadBMP_custom(t_top);
	textureID[5] = loadBMP_custom(t_bottom);

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

Skybox::~Skybox() {
}
