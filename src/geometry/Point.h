/*
 * Point.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GLM_POINT_H_
#define GLM_POINT_H_

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

	virtual ~Point();
};

#endif /* GLM_POINT_H_ */
