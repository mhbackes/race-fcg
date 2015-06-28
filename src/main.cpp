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
#include <fstream>

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
	gLight.position = glm::vec3(0.0f, 30.0f, -10.0f);
	gLight.intensities = glm::vec3(1.0f, 1.0f, 1.0f);

	//program
	programID = LoadShaders("resources/shader/vertex.shader",
			"resources/shader/fragment.shader");
	glUseProgram(programID);
	mvpID = glGetUniformLocation(programID, "MVP");
	modelID = glGetUniformLocation(programID, "model");

	glActiveTexture(GL_TEXTURE0);

	//player car
	Rectangle car_pos(Point(-30, -20), Angle(90), 6.52, 2.6);
	race.player_car = Car(&race, car_pos, 0.0001, -0.00001, -0.001, 1);
	race.player_car.load_model("resources/objects/camaro.obj",
			"resources/textures/camaro.bmp", programID);

	//ia car

	Rectangle dummy_car_pos(Point(0, -60), Angle(-90), 6.52, 2.6);
	AICar dummy_car = AICar(&race, dummy_car_pos, 0.1, -0.001, -0.01, 1);
	race.ai_cars.push_back(dummy_car);
	race.ai_cars[0].load_model("resources/objects/camaro.obj",
			"resources/textures/camaro.bmp", programID);

	//camera
	//race.camera = Camera(&race.player_car); // camera on player
	race.camera = Camera(&race.ai_cars[0]); // camera on bot

	//track
	race.track.load_model("resources/objects/dijon.obj",
			"resources/textures/road.bmp", programID);

	// checkpoints
	if(race.parse_checkpoints("resources/etc/checkpoints.txt")
			== false) {
		Point check_center0(135, -20);
		Checkpoint c0(check_center0, 10);
		Point check_center1(-75, -20);
		Checkpoint c1(check_center1, 10);

		race.checkpoints.push_back(c0);
		race.checkpoints.push_back(c1);
	}


	//race
	race.reset_time();

	return programID;

}

void keyboardDown(unsigned char key, int x, int y) {

	keystates[key] = true;

	if (key == 'v') {
		race.camera.toggle_eagle();
	} else if (key == 'V') {
		race.camera.toggle_rear();
	}

	if (key == 'c') {
		Point np = race.player_car.position.get_center();
		std::ofstream cp;
		cp.open("resources/etc/checkpoints.txt",
				std::ios_base::app);
		cp << np.x << " " << np.y << " " << 10 << std::endl;
		cp.close();
	}
}
void keyboardUp(unsigned char key, int x, int y) {

	keystates[key] = false;

}

float roty = 180;
void idle() {
	clock_t curr_time = clock();
	if ((curr_time - race.curr_time) < Race::clocks_per_frame) // sets fps to 60
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
	for (AICar& car : race.ai_cars) {
		car.draw(mvp, modelID, mvpID);
		race.checkpoints[car.checkpoint].draw(mvp, modelID, mvpID);
	}
	race.track.draw(mvp, modelID, mvpID);

	std::cout << "Position: "
			<< race.ai_cars[0].position.get_center().to_string() << " Check: "
			<< race.ai_cars[0].checkpoint << " Lap: " << race.ai_cars[0].lap
			<< std::endl;

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

