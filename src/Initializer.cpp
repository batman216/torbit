#include "include/Initializer.hpp"

using namespace std;

Vector3<double> Maxwellian::randomVelocity() {
	random_device rd{};
	mt19937 gen{rd()};
	normal_distribution<> d{vd,vc*ISQRT3};

	return Vector3<double>(d(gen),d(gen),d(gen));
}

Vector3<double> SlowingDown::randomVelocity() {
	random_device rd{};
	mt19937 gen{rd()};
	normal_distribution<> d{vd,vc*ISQRT3};

	return Vector3<double>(d(gen),d(gen),d(gen));

}

Vector3<double> Uniform::randomVelocity() {
	random_device rd{};
	mt19937 gen{rd()};
	normal_distribution<> d{vd,vc*ISQRT3};

	return Vector3<double>(d(gen),d(gen),d(gen));

}

Vector3<double> Trapped::randomVelocity() {
	random_device rd{};
	mt19937 gen{rd()};
	normal_distribution<> d{vd,vc*ISQRT3};

	return Vector3<double>(d(gen),d(gen),d(gen));

}

Vector3<double> Passing::randomVelocity() {
	random_device rd{};
	mt19937 gen{rd()};
	normal_distribution<> d{vd,vc*ISQRT3};

	return Vector3<double>(d(gen),d(gen),d(gen));

}





