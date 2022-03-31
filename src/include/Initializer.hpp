//! class Initializer
//! Determine the initial state of a species of particles

#ifndef _INITIALIZER_HPP_
#define _INITIALIZER_HPP_
#include <random>
#include <string>
#include "Vector3.hpp"

class Particle;
class Tokamak;
class Initializer {
protected:
	int num = 0;   /// # particles
	double vc, vd; /// characteristic/drift velocity
	
public:
	virtual Vector3<double> randomVelocity() = 0;
	virtual ~Initializer() {};
	friend class Particle;
	friend class Tokamak;
};

class Maxwellian : public Initializer {
public:
	Vector3<double> randomVelocity() override;
};

class SlowingDown : public Initializer {
public:
	Vector3<double> randomVelocity() override;
};

class Uniform : public Initializer {
public:
	Vector3<double> randomVelocity() override;
};

class Passing : public Initializer {
public:
	Vector3<double> randomVelocity() override;
};

class Trapped : public Initializer {
public:
	Vector3<double> randomVelocity() override;
};





#endif /* _INITIALIZER_HPP_ */
