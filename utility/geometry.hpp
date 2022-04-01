#pragma once

#include <complex>

#include "math_util.hpp"

namespace ishihalib {

struct Point {	//点
	double x_, y_;
	Point(double x, double y) : x_(x), y_(y) {}
	Point(std::complex<double> w) : x_(w.real()), y_(w.imag()) {}
	std::complex<double> get_complex() { return std::complex<double>(x_, y_); }
};

struct LineSeg {  //線分
	Point a_, b_;
	LineSeg(Point a, Point b) : a_(a), b_(b) {
	}
	static bool crossing(LineSeg line1, LineSeg line2) {
		std::complex<double> lineVec;
		std::complex<double> vec;

		double crossproduct[4] = {};  //外積

		lineVec = line1.a_.get_complex() - line1.b_.get_complex();
		vec = line2.a_.get_complex() - line1.a_.get_complex();
		crossproduct[0] = lineVec.real() * vec.imag() - lineVec.imag() * vec.real();  //線分と2点間の外積計算

		vec = line2.b_.get_complex() - line1.a_.get_complex();
		crossproduct[1] = lineVec.real() * vec.imag() - lineVec.imag() * vec.real();  //線分と2点間の外積計算

		lineVec = line2.a_.get_complex() - line2.b_.get_complex();
		vec = line1.a_.get_complex() - line2.a_.get_complex();
		crossproduct[2] = lineVec.real() * vec.imag() - lineVec.imag() * vec.real();  //線分と2点間の外積計算

		vec = line1.b_.get_complex() - line2.a_.get_complex();
		crossproduct[3] = lineVec.real() * vec.imag() - lineVec.imag() * vec.real();  //線分と2点間の外積計算

		return ((crossproduct[0] * crossproduct[1] < 0) && (crossproduct[2] * crossproduct[3] < 0));
	}
};
}  // namespace ishihalib