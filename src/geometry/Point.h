/*
 * Point.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GLM_POINT_H_
#define GLM_POINT_H_

#include "Angle.h"
#include <string>
using std::string;

struct Point {

	float x, y;

	Point();
	Point(float x, float y);
	void move(float dx, float dy);
	float distance(Point& p);
	float distance_x(Point& p);
	float distance_y(Point& p);

	Angle angle(Point& a, Point& b);

	friend Point operator+(const Point& p, const Point& q) {
		return Point(p.x + q.x, p.y + q.y);
	}
	friend Point operator-(const Point& p, const Point& q) {
		return Point(p.x - q.x, p.y - q.y);
	}
	string to_string();


	virtual ~Point();
};

#endif /* GLM_POINT_H_ */
