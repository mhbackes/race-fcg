/*
 * Triangle.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Triangle.h"
#include <cmath>

Triangle::Triangle() {
	// TODO Auto-generated constructor stub

}

Triangle::Triangle(Point& p0, Point& p1, Point& p2) {
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;
}

bool Triangle::contains(Point& p) {
	float _area = area(p0, p1, p2);
	float s = 1 / (2 * _area)
			* (p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x
					+ (p0.x - p2.x) * p.y);
	float t = 1 / (2 * _area)
			* (p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x
					+ (p1.x - p0.x) * p.y);
	return s >= 0 && t >= 0 && (1 - s - t) >= 0;
}

float Triangle::area(Point& p0, Point& p1, Point& p2) {
	return fabs((-p1.y * p2.x + p0.y * (-p1.x + p2.x) + p0.x * (p1.y - p2.y)
					+ p1.x * p2.y) / 2);
}

Triangle::~Triangle() {
	// TODO Auto-generated destructor stub
}

