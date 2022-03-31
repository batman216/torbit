#ifndef _TOKAMAK_HPP_
#define _TOKAMAK_HPP_

//! class Tokamak
//! A tokamak contains the information of magnetic field
//! and the pointer list of loaded particles

#include <vector>
#include <array>
#include <fstream>
#include <sstream>
#include <cmath>
#include <random>
#include <algorithm>
#include <unordered_map>
#include "Vector3.hpp"
#include "Particle.hpp"

class Initializer;
class Particle;
class Tokamak {
	Tokamak(); /// singleton tokamak

	std::ofstream os_tfl;		
public:
	static const int NR = 256, NZ = 256, NT = 10;
	double dR, dZ, LR, LZ;
	double RMAX, RMIN, ZMAX, ZMIN;
	double RAXIS, ZAXIS, RXP, ZXP;


	static Tokamak* __tokamak; 
	static Tokamak* __get();
	
	typedef Vector3<double> b_vector;
	std::array<std::array<
			b_vector,NR>,NZ> b_field;
	b_vector interpB(double,double) const;
	
	std::unordered_map<std::string,
			Particle*> particle_list;
	void loadParticle(std::string);
	void pushParticle(double dt) const;
	void traceFieldLine();

	friend std::ifstream& 
		operator>>(std::istream&, Tokamak&);	
};

/// read from input
std::ifstream& 
	operator>>(std::ifstream&, Tokamak&);


#endif /* _TOKAMAK_HPP_ */
