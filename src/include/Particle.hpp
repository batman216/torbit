//! class Particle
//! Particle contains a list of Markers

#ifndef _PARTICLE_HPP_
#define _PARTICLE_HPP_
#include <list>
#include <string>
#include <fstream>
#include "Pusher.hpp"
#include "Initializer.hpp"
#include "FactoryTemplate.hpp"
#include "Marker.hpp"

#define MP 1836.15
#define ME 1.00000
#define QE 1.00000

class Pusher;
class Initializer;
class Particle {
	
protected:
	const double mass, charge;
	std::list<Marker> marker;
public:
	Pusher *pusher;
	Initializer *initer;
	Particle(double,double);
	virtual ~Particle() {};				

	double m() { return mass; }
	double q() { return charge; }
	auto size() { return marker.size(); }
	auto begin() { return marker.begin(); }
	auto end() { return marker.end(); }
	auto begin() const { return marker.begin(); }
	auto end() const { return marker.end(); }

	friend class Tokamak;
	friend std::ostream& operator<<(
			std::ostream& os, const Particle& p);
};

std::ostream& operator<<(
			std::ostream& os, const Particle& p);


class Electron : public Particle {
public:
	static constexpr double mass = ME, charge = -QE*1.0;
	Electron() : Particle(mass,charge) {}
};

class Deuterium : public Particle {
public:
	static constexpr double mass = MP*2.0, charge = QE*1.0;

	Deuterium()	: Particle(mass,charge) {}
};

class Tritium : public Particle {
public:
	static constexpr double mass = MP*3.0, charge = QE*1.0;

	Tritium() : Particle(mass,charge) {}
};

class Helium : public Particle {
public:
	static constexpr double mass = MP*4.0, charge = QE*2.0;

	Helium() : Particle(mass,charge) {}
};



#endif /* _PARTICLE_HPP_ */
