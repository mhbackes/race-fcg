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

	static double limit(double angle);

	friend Angle operator+(const Angle& lhs, const Angle& rhs){
		double angle = limit(lhs.angle + rhs.angle);
		return Angle(angle);
	}
	friend Angle operator-(const Angle& lhs, const Angle& rhs){
		double angle = limit(lhs.angle - rhs.angle);
		return Angle(angle);
	}

	virtual ~Angle();
};

#endif /* GEOMETRY_ANGLE_H_ */
