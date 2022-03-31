//! Interface of pusher
 
#ifndef _PUSHER_HPP_
#define _PUSHER_HPP_
#include <iostream>
#include "Particle.hpp"
#include "Tokamak.hpp"

class Tokamak;
class Particle;
class Pusher {

public:
	virtual void push(Particle*,const Tokamak*) = 0;
	virtual ~Pusher() {}

};

class BorisPusher : public Pusher {
public:
	void push(Particle*, const Tokamak*) override;

};

class LittlejohnPusher : public Pusher {
public:
	void push(Particle*, const Tokamak*) override;

};


#endif /* _PUSHER_HPP_ */
