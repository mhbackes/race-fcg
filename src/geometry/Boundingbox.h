/*
 * Boundingbox.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GEOMETRY_BOUNDINGBOX_H_
#define GEOMETRY_BOUNDINGBOX_H_

#include "Point.h"

class Bounding_box {
	// p0 ponto mais a esquerda e abaixo
	// p1 ponto mais a direita e acima
	Point p0, p1;
public:
	Bounding_box(float xmin, float ymin, float xmax, float ymax);
	Bounding_box(Point center, float height, float base);
	bool intersects(Bounding_box& b);
	Point get_bot_left();
	Point get_top_left();
	Point get_bot_right();
	Point get_top_right();


	virtual ~Bounding_box();
};

#endif /* GEOMETRY_BOUNDINGBOX_H_ */
