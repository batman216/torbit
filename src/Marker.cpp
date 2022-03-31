#include "include/Marker.hpp"	

Marker make_marker(Vector3<double> x, 
				   Vector3<double> v) {
	return Marker(x, v);
}


std::ostream& operator<<(
		std::ostream& os, const Marker& m) {
	os << m.x[1] << '\t' << m.x[2] 
			<< '\t' << m.x[3] << '\t'
	   << m.v[1] << '\t' << m.v[2] 
	   		<< '\t' << m.v[3] << '\t';
	return os;
}
