/*
 * Circle.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GEOMETRY_CIRCLE_H_
#define GEOMETRY_CIRCLE_H_

#include "Point.h"
#include "Boundingbox.h"

struct Circle {
	Point center;
	float radius;

	Circle();
	Circle(Point c, float r);
	Point get_center();
	float get_radius();
	bool contains(Point& p);
	bool intersects(Bounding_box& b);
	virtual ~Circle();
};

#endif /* GEOMETRY_CIRCLE_H_ */
