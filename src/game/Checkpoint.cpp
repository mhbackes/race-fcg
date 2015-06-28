/*
 * CheckPoint.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Checkpoint.h"
#include <cmath>

Checkpoint::Checkpoint() :
		Circle() {
	// TODO Auto-generated constructor stub

}

Checkpoint::Checkpoint(Point& center, float radius) :
		Circle(center, radius) {
}

Checkpoint::~Checkpoint() {
	// TODO Auto-generated destructor stub
}

void Checkpoint::draw(glm::mat4& mvp, GLuint modelID, GLuint mvpID) {
	glm::mat4 model(1.0);
	glm::mat4 MVP = mvp * model;

	glUniformMatrix4fv(modelID, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &MVP[0][0]);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.0, 1.0, 0);
	glNormal3f(0, 1, 0);
	glVertex3f(center.x, 0, center.y);
	for (int i = 0; i <= 300; i++) {
		float angle = 2 * M_PI * i / 300;
		float x = radius * cos(angle) + center.x;
		float y = radius * sin(angle) + center.y;
		glVertex3f(x, 0, y);
	}
	glEnd();

	glEnd();
}
