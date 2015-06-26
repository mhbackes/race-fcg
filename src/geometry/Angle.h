/*
 * Angle.h
 *
 *  Created on: Jun 26, 2015
 *      Author: mhbackes
 */

#ifndef GEOMETRY_ANGLE_H_
#define GEOMETRY_ANGLE_H_

class Angle {
	float angle;
public:
	Angle();
	Angle(float angle);
	Angle(const Angle& angle);
	void clockwise(Angle angle);
	void counter_clockwise(Angle angle);
	void clockwise(float angle);
	void counter_clockwise(float angle);
	float get_degree();
	float get_rad();
	double sin();
	double cos();

	friend Angle operator+(const Angle& lhs, const Angle& rhs){
		return Angle(lhs.angle + rhs.angle);
	}
	friend Angle operator-(const Angle& lhs, const Angle& rhs){
		return Angle(lhs.angle - rhs.angle);
	}

	virtual ~Angle();
};

#endif /* GEOMETRY_ANGLE_H_ */
