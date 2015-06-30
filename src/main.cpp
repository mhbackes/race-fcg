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
	float ambient_coefficient;
};

GLfloat shininess = 50.0f;

Light gLight;
Race race;

int init_resources() {
	glClearColor(0.52f, 0.80f, 0.98f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	//light
	gLight.position = glm::vec3(0.0f, 20.0f, 0.0f);
	gLight.intensities = glm::vec3(1.0f, 1.0f, 1.0f);
	gLight.ambient_coefficient = 0.005f;

	//program
	programID = LoadShaders("resources/shader/vertex.shader",
			"resources/shader/fragment.shader");
	glUseProgram(programID);
	mvpID = glGetUniformLocation(programID, "MVP");
	modelID = glGetUniformLocation(programID, "model");

	glActiveTexture(GL_TEXTURE0);

	//player car
	Rectangle car_pos(Point(-50, -20), Angle(180), 6.52, 2.6);
	race.player_car = Car(&race, car_pos, 0.00095, -0.001, -0.009, 1.2);
	race.player_car.load_model("resources/objects/camaro.obj",
			"resources/textures/green.bmp", programID);

	//ia car

	Rectangle dummy_car_pos(Point(-30, -20), Angle(180), 6.52, 2.6);
	AICar dummy_car = AICar(&race, dummy_car_pos, 0.001, -0.001, -0.004, 2);
	dummy_car.load_model("resources/objects/camaro.obj",
			"resources/textures/green.bmp", programID);
	race.ai_cars.push_back(dummy_car);
	dummy_car.position.center = Point(-40, -25);
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
			"resources/textures/flag.bmp", programID);
	race.parse_checkpoints("resources/etc/checkpoints4.txt");

	//race
	race.reset_time();
	race.max_lap = 3;
	race.paused = false;

	return programID;

}

void keyboardDown(unsigned char key, int x, int y) {

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
void keyboardUp(unsigned char key, int x, int y) {

	keystates[key] = false;

}

float roty = 180;
void idle() {
	clock_t curr_time = clock();
	if ((curr_time - race.curr_time) < Race::clocks_per_frame) // sets fps to 60
		return;

	if (race.paused)
		return;

	std::cout << "Lap: " << race.player_car.lap << " Check: " << race.player_car.checkpoint << std::endl;
	if (race.finished()) {
		race.paused = true;
		if (race.player_car.lap == race.max_lap)
			std::cout << "You win!" << std::endl;
		else
			std::cout << "You lose!" << std::endl;
		return;
	}

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
    //envio do coeficiente ambiente
    glUniform1f(glGetUniformLocation(programID, "light_ambient_coefficient"),
                gLight.ambient_coefficient);
    //envio da cor especular: escolhi por enviar a cor BRANCA
    glUniform3fv(glGetUniformLocation(programID, "COR_ESPECULAR_MAT"),
                  1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
    // INTENSIDADE da iluminacao ESPECULAR
    glUniform1f(glGetUniformLocation(programID, "material_shininess"),
                shininess);

	/**************************************************************************************************************/

	race.player_car.draw(mvp, modelID, mvpID);
	race.checkpoints[race.player_car.checkpoint].draw(mvp, modelID, mvpID);
//	std::cout << "Position: " << race.player_car.position.center.to_string()
//			<< " Check: " << race.player_car.checkpoint << " Lap: "
//			<< race.player_car.lap << " Speed: " << race.player_car.speed
//			<< std::endl;
	for (AICar& car : race.ai_cars) {
		car.draw(mvp, modelID, mvpID);
//		race.checkpoints[car.checkpoint].draw(mvp, modelID, mvpID);
//		std::cout << "Position: "
//				<< car.position.center.to_string()
//				<< " Check: " << car.checkpoint << " Lap: "
//				<< car.lap << " Speed: " << car.speed
//				<< std::endl;
	}
	race.track.draw(mvp, modelID, mvpID);
	race.terrain.draw(mvp, modelID, mvpID);

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

