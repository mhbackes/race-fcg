//============================================================================
// Name        : car-race.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#define GLEW_STATIC

#include <stdio.h>
#include <stdlib.h>

#include "GL/glew.h"
#include "GL/freeglut.h"

// Include GLM
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "game/Race.h"
#include "game/Car.h"
#include "game/Camera.h"
#include "game/Track.h"

#include "common/shader.hpp"

#include <iostream>

GLuint programID;
GLuint mvpID;
GLuint modelID;

bool keystates[256];

struct Light {
	glm::vec3 position;
	glm::vec3 intensities; //a.k.a. the color of the light
};

Light gLight;
Race race;

int init_resources() {
	glClearColor(0.4f, 0.4f, 0.4f, 0.4f);
	glEnable(GL_DEPTH_TEST);

	//light
	gLight.position = glm::vec3(0.0f, 10.0f, -10.0f);
	gLight.intensities = glm::vec3(1.0f, 1.0f, 1.0f);

	//program
	programID = LoadShaders("resources/shader/vertex.shader", "resources/shader/fragment.shader");
	/*programID = LoadShaders("/home/prlanzarin/github/race-fcg/resources/shader/vertex.shader",
			"/home/prlanzarin/github/race-fcg/resources/shader/fragment.shader"); */
	glUseProgram(programID);
	mvpID = glGetUniformLocation(programID, "MVP");
	modelID = glGetUniformLocation(programID, "model");

	glActiveTexture(GL_TEXTURE0);

	//player car
	Rectangle car_pos(Point(0, 0), Angle(0), 4.0, 1.5);
	race.player_car = Car(&race, car_pos, 0.1, -0.001, -0.01, 1);


	//camera
	race.camera = Camera(&race.player_car);

	//track
	/*race.track.load_model("/home/prlanzarin/github/race-fcg/resources/objects/gpdoquadrado.obj",
			"/home/prlanzarin/github/race-fcg/resources/textures/green.bmp", programID);
	race.player_car.load_model("/home/prlanzarin/github/race-fcg/resources/objects/camaro.obj",
			"/home/prlanzarin/github/race-fcg/resources/textures/camaro.bmp", programID);*/
	race.track.load_model("resources/objects/gpdoquadrado.obj",
				"resources/textures/green.bmp", programID);
	race.player_car.load_model("/home/prlanzarin/github/race-fcg/resources/objects/camaro.obj",
				"resources/textures/camaro.bmp", programID);

	//race
	race.reset_time();

	return programID;

}

void keyboardDown(unsigned char key, int x, int y) {

	keystates[key] = true;

}

void keyboardUp(unsigned char key, int x, int y) {

	keystates[key] = false;

}

float roty = 180;
void idle() {
	clock_t curr_time = clock();
	if((curr_time - race.curr_time) < Race::clocks_per_frame) // sets fps to 60
		return;

	if (keystates['s'])
		race.player_car.brake();
	else if (keystates['w'])
		race.player_car.gas();
	else
		race.player_car.idle();

	if (keystates['a'])
		race.player_car.turn_left();
	if (keystates['d'])
		race.player_car.turn_right();

	race.update();
	//printf("Light position: (%f, %f, %f)\n", gLight.position[0], gLight.position[1], gLight.position[2] );

}

void onDisplay() {

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programID);

	glm::mat4 mvp = race.camera.mvp();

	/**passa os parametros para a glsl***************************************************************************/

	glUniform1ui(glGetAttribLocation(programID, "tex"), 0);

	//iluminacao
	glUniform3fv(glGetUniformLocation(programID, "light_position"), 1,
			glm::value_ptr(gLight.position));
	glUniform3fv(glGetUniformLocation(programID, "light_intensities"), 1,
			glm::value_ptr(gLight.intensities));

	/**************************************************************************************************************/

	race.player_car.draw(mvp, modelID, mvpID);
	race.track.draw(mvp, modelID, mvpID);

	glutSwapBuffers();
	glutPostRedisplay();

}

//libera recursos
void free_resources() {

	glDeleteBuffers(1, &race.player_car.vertexBuffer);
	glDeleteVertexArrays(1, &race.player_car.vertexID);
	glDeleteBuffers(1, &race.track.vertexBuffer);
	glDeleteVertexArrays(1, &race.track.vertexID);
	glDeleteProgram(programID);

}

int main(int argc, char* argv[]) {

	//inicia janela
	glutInit(&argc, argv);
	glutInitDisplayMode(
	GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("FPS Game");

	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return 1;
	}

	if (init_resources() != 0) {

		glutDisplayFunc(onDisplay);
		glutIdleFunc(idle);
		glutIgnoreKeyRepeat(1);
		glutKeyboardFunc(keyboardDown);
		glutKeyboardUpFunc(keyboardUp);

		glutMainLoop();
	}

	free_resources();
	return 0;
}

