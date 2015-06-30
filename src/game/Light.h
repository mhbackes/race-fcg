/*
 *
 *
 *  Created on: Jun 30, 2015
 *      Author: mhbackes
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "glm/glm.hpp"

struct Light {
	static glm::vec3 position;
	static glm::vec3 diffuse_component;
	static glm::vec3 specular_component;
	static glm::vec3 ambient_component;
};

#endif /* LIGHT_H_ */
