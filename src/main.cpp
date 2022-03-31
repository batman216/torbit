#include "include/torbit.hpp"

int main(int argc, char* argv[]) {
#ifdef __cplusplus
	std::cout << "cpp version: " << __cplusplus << std::endl;
#endif
#ifdef __GNUC__
	std::cout << "gnu version: " << __GNUC__ << std::endl;
#endif
#ifdef MPI_INT
	std::cout << "parallel mode." << std::endl;
	MPI_Init(&argc,&argv);
#endif

	/**
	 * The creator of ConcreteFactory call the singleton product Proxy
	 * (Proxy<t_Product>) to register the corresponding concrete product
	 * i.e., to bind the concrete product together with a name ("fourier").
	 */	
	ConcreteFactory<Pusher, BorisPusher> boris("boris");
	ConcreteFactory<Pusher, LittlejohnPusher> littlejohn("littlejohn");
		
	ConcreteFactory<Initializer, Maxwellian> maxwellian("maxwellian"); 
	ConcreteFactory<Initializer, SlowingDown> slowingdown("slowingdown");
	ConcreteFactory<Initializer, Uniform> uniform("uniform");
	ConcreteFactory<Initializer, Passing> passing("passing");
	ConcreteFactory<Initializer, Trapped> trapped("trapped");

	ConcreteFactory<Particle, Electron> electron("electron"); 
	ConcreteFactory<Particle, Tritium> tritium("tritium");
	ConcreteFactory<Particle, Deuterium> deuterium("deuterium");
	ConcreteFactory<Particle, Helium> helium("helium");
	
    /**
	 * The Proxy requests the factory to produce a concrete product 
 	 * according to the regedit (the name-ConcreteFactory pair),
 	 * which is analog to the polymorphic new of a normal factory 
 	 * method, e.g., product = factory->produce(), instead, we have	
	 * product = Proxy<Pusher>::Instance().get("boris");
	 */
	
	Tokamak* tokamak = Tokamak::__get();
	std::ifstream ifs("input_file/east_tokamak"); 
	ifs >> *tokamak; ifs.close();
	tokamak->traceFieldLine();
	tokamak->loadParticle("input_file/particle.in");

	std::ofstream pofs("test");
	pofs << *(tokamak->particle_list["alpha_particle_"]);	

	//tokamak->pushParticle(0.01);

}
