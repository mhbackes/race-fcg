/*
 * Rectangle.cpp
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#include "Rectangle.h"
#include "Triangle.h"
#include <cfloat>

Rectangle::Rectangle() {
	center = Point();
	angle = Angle();
	height = 1;
	base = 1;
}

Rectangle::Rectangle(Point center, Angle angle, float height, float base) {
	this->center = center;
	this->angle = angle;
	this->height = height;
	this->base = base;
}

void Rectangle::rotate_clockwise(Angle angle) {
	this->angle.counter_clockwise(angle);
}

void Rectangle::rotate_counter_clockwise(Angle angle) {
	this->angle.clockwise(angle);
}

void Rectangle::move(float dx, float dy) {
	center.move(dx, dy);
}

Bounding_box Rectangle::get_bounding_box() {
	Angle yaxis(90);
	Angle diff = yaxis - angle;
	float ortho_height = angle.cos() * base + angle.sin() * height;
	float ortho_base = angle.sin() * base + angle.cos() * height;
	return Bounding_box(center, ortho_height, ortho_base);
}

bool Rectangle::intersects(Bounding_box& b) {
	return get_bounding_box().intersects(b);
}

bool Rectangle::intersects(Rectangle& r) {
//	Bounding_box r_bbox = r.get_bounding_box();
//	return intersects(r_bbox);
	vector<Point> u = vertex();
	for (Point &p : u) {
		if (r.contains(p)) {
			return true;
		}
	}
	vector<Point> v = r.vertex();
	for (Point &p : v) {
		if (contains(p)) {
			return true;
		}
	}
	return false;
}

bool Rectangle::intersects(Circle& c) {
	vector<Point> v = vertex();
	for (Point& vertex : v) {
		if (c.contains(vertex))
			return true;
	}
	return false;
}

bool Rectangle::contains(Point& p) {
	vector<Point> v = vertex();
	Point &a = v[0], &b = v[1], &c = v[2], &d = v[3];
	float a0 = Triangle::area(p, a, b);
	float a1 = Triangle::area(p, b, c);
	float a2 = Triangle::area(p, c, d);
	float a3 = Triangle::area(p, d, a);
	float area_sum = a0 + a1 + a2 + a3;
	float area_rec = base * height;
	return area_sum <= area_rec + FLT_EPSILON;
}

Rectangle::~Rectangle() {
	// TODO Auto-generated destructor stub
}

vector<Point> Rectangle::vertex() {
	vector<Point> v(4);
	float half_base = base / 2;
	float half_height = height / 2;
	v[0] = Point(half_height, half_base);
	v[1] = Point(-half_height, half_base);
	v[2] = Point(half_height, -half_base);
	v[3] = Point(-half_height, -half_base);
	float cos_angle = angle.cos();
	float sin_angle = angle.sin();
	for (Point& p : v) {
		float x = p.x * cos_angle - p.y * sin_angle;
		float y = p.x * sin_angle + p.y * cos_angle;
		p = Point(x, y) + center;
	}
	return v;
}
