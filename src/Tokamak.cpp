#include "include/Tokamak.hpp"

using namespace std;

Tokamak* Tokamak::__tokamak = nullptr;
Tokamak::Tokamak() { 
	cout<< "!\tThe tokamak is ready." << endl; 
}

Tokamak* Tokamak::__get() { 
	if (__tokamak == nullptr)
		__tokamak = new Tokamak;
	return __tokamak;
}


ifstream& operator>>(ifstream& is, Tokamak& tok) {
	string sbuf = "#";
	do { 
		getline(is,sbuf);
	} while (sbuf[0] == '#');

	auto assign = [&] (double& val) {
		getline(is,sbuf,'|'); 
		stringstream buf(sbuf);
		buf >> val; 
	};
	assign(tok.RMAX); 	assign(tok.RMIN);
	assign(tok.ZMAX);	assign(tok.ZMIN);
	assign(tok.RAXIS);	assign(tok.ZAXIS);
	assign(tok.RXP);	assign(tok.ZXP);
	
	tok.LR = tok.RMAX - tok.RMIN; tok.LZ = tok.ZMAX - tok.ZMIN;
	tok.dR = tok.LR / (tok.NR-1); tok.dZ = tok.LZ / (tok.NZ-1);
	
	while (sbuf[0] != 'B') { getline(is,sbuf); }
	
	for (auto idx : {1,2,3})
		for (auto& elem : tok.b_field) 
			for (auto& selem : elem)
				is >> selem[idx];
	return is;
}



Tokamak::b_vector Tokamak::interpB(double pR, double pZ) const {

	Tokamak::b_vector b_interp;
	pR -= RMIN; pZ -= ZMIN;

	int iR = floor(pR/dR), iZ = floor(pZ/dZ);
	if (iR<0||iR+2>NR||iZ<0||iZ+2>NZ)
		return Vector3<double>(0,0,0);
	
	double inverseA = 1.0/dZ/dR;

	double w1 = (pR - iR*dR)    * (pZ - iZ*dZ)      * inverseA; 
	double w2 = (dR - pR+iR*dR) * (pZ - iZ*dZ)      * inverseA; 
	double w3 = (dR - pR+iR*dR) * (dZ - pZ + iZ*dZ) * inverseA; 
	double w4 = (pR - iR*dR)    * (dZ - pZ + iZ*dZ) * inverseA; 

		
	b_interp = b_field[ iZ ][ iR ] * w3 + b_field[iZ][iR+1] * w4 
			 + b_field[iZ+1][iR+1] * w1 + b_field[iZ+1][iR] * w2; 

	return b_interp;

}

void Tokamak::loadParticle(string file_name) {
	ifstream ifs(file_name);
	string str, name, species, dist, algorithm;
   	string num_str, vc_str, vd_str;	

	auto assign = [&] (string& name) {
		getline(ifs,str);
		name = str.substr(str.find('=')+1,str.size());
		name.erase(remove_if(name.begin(),
							 name.end(), 
							 [](auto& x){return x==' '||x=='\t'; }),
				   name.end());
	};
	
	while (getline(ifs,str)) {
		if (str[0] == '!')	{
			assign(name);
			assign(species);
			assign(dist);
			assign(algorithm);
				
			particle_list[name] = 
				Proxy<Particle>::Instance().get(species);
			particle_list[name]->pusher =
				Proxy<Pusher>::Instance().get(algorithm);
			particle_list[name]->initer =
				Proxy<Initializer>::Instance().get(dist);

			assign(num_str);
			stringstream nss(num_str); 
			nss >> particle_list[name]->initer->num;
			assign(vd_str);
			stringstream vdss(vd_str); 
			vdss >> particle_list[name]->initer->vd;
			assign(vc_str);
			stringstream vcss(vc_str); 
			vcss >> particle_list[name]->initer->vc;

			std::replace(name.begin(), name.end(), '_', ' ');
			name[0] -= 32;
			cout << "!\t" << name
			  	<< "is registered with a " <<  
				algorithm << " pusher." << endl;
		}
	}

	cout << "!\tLoading particles..." << endl;
	for_each(particle_list.begin(), 
				particle_list.end(), [&](auto& cont) {
		random_device rd;
		mt19937 gen(rd());
		uniform_real_distribution<> 
			disR(RMIN,RMAX), disZ(ZMIN,ZMAX), disT(0,2.0*M_PI);

		while (cont.second->marker.size() 
					< cont.second->initer->num) {
			Vector3<double> x(disR(gen),disZ(gen),disT(gen));
			cont.second->marker.push_back(make_marker(x,
				cont.second->initer->randomVelocity()));	
		}
					
	});

}

void Tokamak::pushParticle(double dl) const {
	for_each(particle_list.begin(), 
				particle_list.end(), [&](auto& cont) {
		cont.second->pusher->push(cont.second,this);
	});
}

void Tokamak::traceFieldLine() {
	int NPSI = 80;
	double dpsi = (RMAX-RAXIS)/(NPSI-1);
	double dl = 0.01;
	os_tfl.open("field_line");

	for (int i=1; i<=NPSI/1.6; ++i) {
		Vector3<double> b_init(RAXIS+i*dpsi,
						ZAXIS,0.0);
		Vector3<double> b = b_init;
		
		Vector3<double> B = interpB(b[1],b[2]);
		double q = B[3]/sqrt(pow(B[2],2)+pow(B[1],2));
		while (fabs(b[3])<q*2.0*M_PI) {
			os_tfl << b;
			if (b[1]<RMAX&&b[1]>RMIN&&b[2]<ZMAX&&b[2]>ZMIN) {
				double coeff, step;	
				Vector3<double> bold, bbuf;
				for (int RK4 : {1,2,3,4}) {
					switch(RK4) {
					case 1:
						bold = b;
						bbuf = bold;
						coeff = 1.0 / 6.0;
				 		step = dl /2;
						break;
					case 2:
						coeff = 1.0 / 3.0;
						step = dl /2;
						break;
					case 3:
						coeff = 1.0 / 3.0;
						step = dl;
						break;
					case 4:
						coeff = 1.0 / 6.0;
						step = dl;
						break;
					}
					B = interpB(b[1],b[2]);
					Vector3<double> rhs = B/abs(B);
					rhs[3] = rhs[3] / b[1];
					b = bold + step*rhs;	
					bbuf += coeff*dl*rhs;	
				}
				b = bbuf;
			}
		}
		os_tfl << endl;
	}
	os_tfl.close();

}
