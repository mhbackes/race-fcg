/*
 * Triangle.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Triangle.h"
#include <cmath>
#include <cfloat>

Triangle::Triangle() {
	// TODO Auto-generated constructor stub

}

Triangle::Triangle(Point& p0, Point& p1, Point& p2) {
	this->p0 = p0;
	this->p1 = p1;
	this->p2 = p2;
}

bool Triangle::contains(Point& p) {
	float area_tri = area(p0, p1, p2);
	float a0 = area(p, p0, p1);
	float a1 = area(p, p1, p2);
	float a2 = area(p, p2, p0);
	float area_sum = a0 + a1 + a2;
	return area_sum <= area_tri + 8192 * FLT_EPSILON;
}

float Triangle::area(Point& p0, Point& p1, Point& p2) {
	return fabs((-p1.y * p2.x + p0.y * (-p1.x + p2.x) + p0.x * (p1.y - p2.y)
					+ p1.x * p2.y) / 2);
}

Triangle::~Triangle() {
	// TODO Auto-generated destructor stub
}

