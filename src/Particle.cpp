#include "include/Particle.hpp"

Particle::Particle(double m,double q)
	: mass(m), charge(q) {

}

std::ostream& operator<<(
	std::ostream& os, const Particle& p) {	

	std::copy(p.begin(), p.end(), 
			  std::ostream_iterator<Marker>(os,"\n"));
	return os;
}

