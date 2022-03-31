//! class Marker
//! contains the coordinates and velocity of a Marker

#ifndef _MARKER_HPP_
#define _MARKER_HPP_
#include <iterator>
#include "Vector3.hpp"


struct Marker {

	int number = 0;
	Vector3<double>  x, v;

	Marker() {}
	Marker(Vector3<double> x,Vector3<double> v) 
		: x(x), v(v) {};
	
};

Marker make_marker(Vector3<double> x, 
				   Vector3<double> v);

std::ostream& operator<<(std::ostream& os, const Marker& m);

#endif /* _MARKER_HPP_ */
