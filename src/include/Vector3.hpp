//! class Vector3
//! 3-dimensional vector

#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_
#include <array>
#include <iostream>
#include <cmath>
#include <ratio>

#define SQRT2  1.414213562373095 
#define SQRT3  1.732050807568877 
#define ISQRT2 0.707106781186548 
#define ISQRT3 0.577350269189626 

template <typename T>
class Vector3 {

	std::array<T,3> val; 
	typedef Vector3<T> self;
public:
	Vector3(T t1=0, T t2=0, T t3=0) {
		val[0] = t1;
		val[1] = t2;
		val[2] = t3;
	}
	double& operator[](int idx) {
		return val[idx-1];
	}
	double operator[](int idx) const {
		return val[idx-1];
	}
	
	self& operator+() {
		return *this;
	}
	self& operator-() {
		for (int i : {0,1,2})
			val[i] = -val[i];
		return *this;
	}
	self& operator+=(const self& other) {
		for (int i : {0,1,2})
			val[i] += other.val[i];
		return *this;
	}
	self& operator-=(const self& other) {
		for (int i : {0,1,2})
			val[i] -= other.val[i];
		return *this;
	}
	self& operator*=(const T& t) {
		for (int i : {0,1,2})
			val[i] *= t;
		return *this;
	}
};

template <typename U> U
dotProduct(const Vector3<U> x, const Vector3<U> y) {
	U res;
	for (int i : {1,2,3})
		res += x[i]*y[i];
	return res;

};


template <typename U> U
abs(const Vector3<U> x) {
	U res;
	for (int i : {1,2,3})
		res += std::sqrt(x[i]*x[i]);
	return res;

};


template <typename U> Vector3<U>
crossProduct(const Vector3<U> x, const Vector3<U> y) {
	Vector3<U> res;
	res[1] = x[2]*y[3] - x[3]*y[2];
	res[2] = x[3]*y[1] - x[3]*y[1];
	res[3] = x[1]*y[2] - x[2]*y[1];
	return res;
};

template <typename U> Vector3<U>
operator+(const Vector3<U> x, U y) {
	Vector3<U> res;
	for (int i : {1,2,3})
		res[i] = x[i] + y;
	return res;
}

template <typename U> Vector3<U>
operator+(U x, const Vector3<U> y) {
	Vector3<U> res;
	for (int i : {1,2,3})
		res[i] = x + y[i];
	return res;
}

template <typename U> Vector3<U>
operator+(const Vector3<U> x, const Vector3<U> y) {
	Vector3<U> res;
	for (int i : {1,2,3})
		res[i] = x[i] + y[i];
	return res;
}

template <typename U> Vector3<U>
operator-(const Vector3<U> x, U y) {
	Vector3<U> res;
	for (int i : {1,2,3})
		res[i] = x[i] - y;
	return res;
}

template <typename U> Vector3<U>
operator-(U x, const Vector3<U> y) {
	Vector3<U> res;
	for (int i : {1,2,3})
		res[i] = x - y[i];
	return res;
}

template <typename U> Vector3<U>
operator-(const Vector3<U> x, const Vector3<U> y) {
	Vector3<U> res;
	for (int i : {1,2,3})
		res[i] = x[i] - y[i];
	return res;
}

template <typename U> Vector3<U>
operator*(U x, const Vector3<U> y) {
	Vector3<U> res;
	for (int i : {1,2,3})
		res[i] = x*y[i];
	return res;
}

template <typename U> Vector3<U>
operator*(const Vector3<U> x, U y) {
	Vector3<U> res;
	for (int i : {1,2,3})
		res[i] = x[i]*y;
	return res;
}

template <typename U> Vector3<U>
operator/(const Vector3<U> x, U y) {
	Vector3<U> res;
	for (int i : {1,2,3})
		res[i] = x[i] / y;
	return res;
}



template <typename U> std::ostream& 
operator<<(std::ostream& os, const Vector3<U>& vec) {
	return os << vec[1] << '\t' << vec[2] << '\t' << vec[3] << '\t';
}

#endif /* _VECTOR3_HPP_ */
