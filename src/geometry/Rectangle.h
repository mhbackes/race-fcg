/*
 * Rectangle.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GEOMETRY_RECTANGLE_H_
#define GEOMETRY_RECTANGLE_H_

#include "Point.h"
#include "Angle.h"
#include "Boundingbox.h"
#include "Circle.h"
#include <vector>

using std::vector;

struct Rectangle {
	Point center;
	Angle angle;
	float height;
	float base;

public:
	Rectangle();
	Rectangle(Point center, Angle angle, float height, float base);
	void rotate_clockwise(Angle angle);
	void rotate_counter_clockwise(Angle angle);
	void move(float dx, float dy);
	Bounding_box get_bounding_box();
	bool intersects(Bounding_box& b);
	bool intersects(Rectangle& r);
	bool intersects(Circle& c); // não é 100% precisa, mas é suficiente
	bool contains(Point& p);
	vector<Point> vertex();
	virtual ~Rectangle();
};

#endif /* GEOMETRY_RECTANGLE_H_ */
