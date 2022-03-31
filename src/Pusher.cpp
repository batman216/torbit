#include "include/Pusher.hpp"

using namespace std;

void BorisPusher::push(Particle* p, const Tokamak* tok) {
	double dt = 0.0001;
	double m = p->m(), q = p->q();
	for (auto it = p->begin(); it != p->end(); ++it) {

    	Vector3<double> rhsX, rhsV;
    	Vector3<double> B_p = tok->interpB(it->x[1],it->x[2]);

    	//! calculate electric force, here is the centrifugal force
   		rhsV[1] =  (it->v[3] * it->v[3]) / it->x[1];
    	rhsV[3] = -(it->v[1] * it->v[3]) / it->x[1];
    	it->v   = it->v + dt * 0.5 * rhsV;

    	//! rotate the velocity according to magnetic field
    	Vector3<double> tt	= (q * dt / (2.0 * m)) * B_p;
    	Vector3<double> vp	= it->v + crossProduct(it->v, tt);
    	double 		 ttemp	= dotProduct(tt, tt);
    	Vector3<double>  s	= (2.0 / (1.0 + ttemp)) * tt;
    	
		it->v  = it->v + crossProduct(vp, s);

    	//! calculate electric force for the second half time step
    	rhsV[1] = it->v[3] * it->v[3] / it->x[1];
    	rhsV[3] = -it->v[1] * it->v[3] / it->x[1];
    	it->v   = it->v + dt * 0.5 * rhsV;

    	//! push particle
    	rhsX    = it->v;
    	rhsX[3] = rhsX[3] / it->x[1];
    	it->x   = it->x + dt * rhsX;

	}

}
void LittlejohnPusher::push(Particle* p, const Tokamak* tokama) {

}
