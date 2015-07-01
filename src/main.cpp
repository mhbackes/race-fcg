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
#include <unistd.h>

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
#include "game/Light.h"

#include "common/shader.hpp"
#include "common/text2D.hpp"

#include <iostream>
#include <fstream>

GLuint programID;
GLuint mvpID;
GLuint modelID;

bool keystates[260];
const int UP_ARROW = 256;
const int DOWN_ARROW = 257;
const int LEFT_ARROW = 258;
const int RIGHT_ARROW = 259;

Light gLight;
Race race;

void free_resources();

inline float clamp(float x, float a, float b) {
    return x < a ? a : (x > b ? b : x);
}

int init_resources() {
	glClearColor(0.52f, 0.80f, 0.98f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	initText2D("resources/textures/Arial.dds");


	//light
	Light::position = glm::vec3(0.0f, 20.0f, 0.0f);
	Light::diffuse_component = glm::vec3(1.0f, 1.0f, 1.0f);
	Light::specular_component = glm::vec3(1.0f, 1.0f, 1.0f);
	Light::ambient_component = glm::vec3(.1f, .1f, .1f);

	//program
	programID = LoadShaders("resources/shader/vertex.shader",
			"resources/shader/fragment.shader");
	glUseProgram(programID);
	mvpID = glGetUniformLocation(programID, "MVP");
	modelID = glGetUniformLocation(programID, "model");

	glActiveTexture(GL_TEXTURE0);
	/*race.skybox.load_model("resources/textures/f.bmp",
			"resources/textures/b.bmp",
			"resources/textures/l.bmp",
			"resources/textures/r.bmp",
			"resources/textures/t.bmp",
			"resources/textures/bt.bmp", programID); */
	//player car
	Rectangle car_pos(Point(30, -24.5), Angle(180), 6.52, 2.6);
	race.player_car = Car(&race, car_pos, 0.001, -0.001, -0.009, 1.2);
	race.player_car.load_model("resources/objects/tank.obj",
			"resources/textures/cammo.bmp", programID);

	//ia car

	Rectangle dummy_car_pos(Point(100, -24.5), Angle(180), 6.52, 2.6);
	AICar dummy_car = AICar(&race, dummy_car_pos, 0.001, -0.001, -0.004, 2);
	dummy_car.load_model("resources/objects/camaro.obj",
			"resources/textures/camaro-green.bmp", programID);

	race.ai_cars.push_back(dummy_car);
	dummy_car.position.center = Point(85, -24.5);
	dummy_car.load_model("resources/objects/camaro.obj",
			"resources/textures/camaro-blue.bmp", programID);
	race.ai_cars.push_back(dummy_car);
	dummy_car.position.center = Point(70, -24.5);
	dummy_car.load_model("resources/objects/camaro.obj",
			"resources/textures/camaro-red.bmp", programID);
	race.ai_cars.push_back(dummy_car);
	dummy_car.position.center = Point(55, -24.5);
	dummy_car.load_model("resources/objects/camaro.obj",
			"resources/textures/camaro-orange.bmp", programID);
	race.ai_cars.push_back(dummy_car);
	dummy_car.position.center = Point(40, -24.5);
	dummy_car.load_model("resources/objects/camaro.obj",
			"resources/textures/camaro-yellow.bmp", programID);
	race.ai_cars.push_back(dummy_car);

	//camera
	race.camera = Camera(&race.player_car); // camera on player
//	race.camera = Camera(&race.ai_cars[0]); // camera on bot

	//track
	race.track.load_model("resources/objects/dijon.obj",
			"resources/textures/road.bmp", programID);

	//terrain
	race.terrain.load_model("resources/objects/terrain.obj",
			"resources/textures/grass.bmp", programID);

	//checkpoints parsing
	Checkpoint::load_model("resources/objects/flag.obj",
			"resources/textures/green.bmp", programID);
	race.parse_checkpoints("resources/etc/checkpoints4.txt");

	//race
	race.reset_time();
	race.max_lap = 3;
	race.paused = false;

	return programID;

}

void game_restart() {
	int i = race.ai_cars.size();
	for (AICar& car : race.ai_cars) {
		car.lap = 0;
		car.checkpoint = 0;
		car.position = Rectangle(Point((100 - (i - 1) * 15), -24.5),
				Angle(180), 6.52, 2.6);
		car.speed = 0;
		i--;
	}
	race.player_car.position = Rectangle(Point(30, -24.5),
			Angle(180), 6.52,2.6);
	race.player_car.lap = 0;
	race.player_car.checkpoint = 0;
	race.player_car.speed = 0;
	race.player_car.boost_load = Car::MAX_BOOST_LOAD;
	race.paused = false;
}

void key_down(unsigned char key, int x, int y) {
	keystates[key] = true;

	if (keystates['p'])
		race.paused = !race.paused;

	if (key == 'v') {
		race.camera.toggle_eagle();
	} else if (key == 'V') {
		race.camera.toggle_rear();
	}

	if (key == 'c') {
		Point np = race.player_car.position.center;
		std::ofstream cp;
		cp.open("resources/etc/checkpoints.txt", std::ios_base::app);
		cp << np.x << " " << np.y << " " << 5 << std::endl;
		cp.close();
	}
}

void key_up(unsigned char key, int x, int y) {

	keystates[key] = false;

}

void spec_key_down(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		keystates[UP_ARROW] = true;
		break;
	case GLUT_KEY_DOWN:
		keystates[DOWN_ARROW] = true;
		break;
	case GLUT_KEY_LEFT:
		keystates[LEFT_ARROW] = true;
		break;
	case GLUT_KEY_RIGHT:
		keystates[RIGHT_ARROW] = true;
	}
}

void spec_key_up(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		keystates[UP_ARROW] = false;
		break;
	case GLUT_KEY_DOWN:
		keystates[DOWN_ARROW] = false;
		break;
	case GLUT_KEY_LEFT:
		keystates[LEFT_ARROW] = false;
		break;
	case GLUT_KEY_RIGHT:
		keystates[RIGHT_ARROW] = false;
	}
}

float roty = 180;
void idle() {
	clock_t curr_time = clock();
	if (keystates['r'])
		game_restart();

	if (keystates[27]) {
		printText2D("TCHAU!", 300, 280, 40);
		glutSwapBuffers();
		glutPostRedisplay();
		sleep(2);
		glutLeaveMainLoop();
		return;
	}

	if ((curr_time - race.curr_time) < Race::clocks_per_frame) // sets fps to 60
		return;

	if (race.paused)
		return;

	if (race.finished()) {
		race.paused = true;
		return;
	}

	if (keystates['s'] || keystates[DOWN_ARROW])
		race.player_car.brake();
	else if (keystates['w'] || keystates[UP_ARROW])
		race.player_car.gas();
	else
		race.player_car.idle();

	if (keystates['a'] || keystates[LEFT_ARROW])
		race.player_car.turn_left();
	if (keystates['d'] || keystates[RIGHT_ARROW])
		race.player_car.turn_right();
	if (keystates[' '])
		race.player_car.boost();

	race.update();

}

void print_hud_info() {

	if(race.finished()) {
		if (race.player_car.lap == race.max_lap)
			printText2D("YOU WIN!", 350, 280, 40);
		else
			printText2D("YOU LOSE :(", 200, 280, 40);
		return;
	}
	else
		if(race.paused) {
			printText2D("PAUSED", 280, 280, 40);
			return;
		}

	char curr_speed[5];
	snprintf(curr_speed, 6, "%f", fabs(race.camera.car->speed * 200));
	printText2D(curr_speed, 50, 50, 50);
	printText2D("Mph", 280, 25, 20);
	printText2D("SPEED", 50, 100, 20);

	char boost_n[3];
	snprintf(boost_n, 4, "%d", (int)clamp((race.player_car.boost_load*100), 0, 100));
	printText2D(boost_n, 600, 50, 50);
	printText2D("BOOST", 600, 100, 20);

	char m_lap[2], act_lap[2];
	snprintf(act_lap, 3, "%d", (race.max_lap));
	snprintf(m_lap, 3, "%d", (race.player_car.lap));
	printText2D("LAP", 340, 550, 30);
	printText2D(act_lap, 420, 515, 40);
	printText2D("of", 384, 525, 20);
	printText2D(m_lap, 350, 515, 40);

}

void onDisplay() {

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(programID);

	glm::mat4 mvp = race.camera.mvp();

	/**passa os parametros para a glsl***************************************************************************/

	glUniform1ui(glGetAttribLocation(programID, "tex"), 0);
	glm::vec3 camera_pos = race.camera.eye_back();
	glUniform3fv(glGetUniformLocation(programID, "camera_position"), 1,
			glm::value_ptr(camera_pos));
	//iluminacao
	glUniform3fv(glGetUniformLocation(programID, "light_position"), 1,
			glm::value_ptr(Light::position));
	glUniform3fv(glGetUniformLocation(programID, "light_diffuse"), 1,
			glm::value_ptr(Light::diffuse_component));
	glUniform3fv(glGetUniformLocation(programID, "light_specular"), 1,
			glm::value_ptr(Light::specular_component));
	glUniform3fv(glGetUniformLocation(programID, "light_ambient"), 1,
			glm::value_ptr(Light::ambient_component));
	/**************************************************************************************************************/
	//race.skybox.draw(mvp, modelID, mvpID, programID);
	race.player_car.draw(mvp, modelID, mvpID, programID);
	race.checkpoints[race.player_car.checkpoint].draw(mvp, modelID, mvpID,
			programID);

	for (AICar& car : race.ai_cars)
		car.draw(mvp, modelID, mvpID, programID);

	race.track.draw(mvp, modelID, mvpID, programID);
	race.terrain.draw(mvp, modelID, mvpID, programID);

	print_hud_info();

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
	glutCreateWindow("Race Game");

	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
		return 1;
	}

	if (init_resources() != 0) {

		glutDisplayFunc(onDisplay);
		glutIdleFunc(idle);
		glutIgnoreKeyRepeat(1);
		glutKeyboardFunc(key_down);
		glutKeyboardUpFunc(key_up);
		glutSpecialFunc(spec_key_down);
		glutSpecialUpFunc(spec_key_up);

		glutMainLoop();
	}

	free_resources();
	return 0;
}

