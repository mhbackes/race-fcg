/*
 * Point.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GLM_POINT_H_
#define GLM_POINT_H_

#include <string>
using std::string;

class Point {
public:
	float x, y;

	Point();
	Point(float x, float y);
	void move(float dx, float dy);
	float distance(Point& p);

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
