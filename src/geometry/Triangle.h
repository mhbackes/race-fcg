/*
 * Triangle.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GEOMETRY_TRIANGLE_H_
#define GEOMETRY_TRIANGLE_H_

#include "Point.h"

class Triangle {
public:
	static float area(Point& p0, Point& p1, Point& p2);

	Point p0, p1, p2;
	Triangle();
	Triangle(Point& p0, Point& p1, Point& p2);
	bool contains(Point& p);
	virtual ~Triangle();
};

#endif /* GEOMETRY_TRIANGLE_H_ */
