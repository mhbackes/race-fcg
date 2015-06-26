//============================================================================
// Name        : car-race.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "geometry/Angle.h"
#include "geometry/Boundingbox.h"
#include "geometry/Point.h"
#include "geometry/Rectangle.h"
#include "geometry/Triangle.h"
using namespace std;

int main() {
	Point c(0, 0);
	Angle a(90);
	Rectangle r(c, a, 2, 1);
	r.get_vertex();
	return 0;
}
