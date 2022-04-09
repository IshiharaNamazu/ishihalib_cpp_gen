#pragma once

#include <complex>

#include "math_util.hpp"

namespace ishihalib {

struct Point {	//点
	double x_, y_;
	Point(double x, double y) : x_(x), y_(y) {}
	Point(std::complex<double> w) : x_(w.real()), y_(w.imag()) {}
	std::complex<double> get_complex() { return std::complex<double>(x_, y_); }
	static double distance(Point a, Point b) {	// 2点間距離
		return abs(a.get_complex() - b.get_complex());
	}
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
	double length() {
		return Point::distance(a_, b_);
	}

	static double distance(LineSeg ls, Point p) {
		if (ls.a_.get_complex() == ls.b_.get_complex()) {
			return Point::distance(ls.a_, p);
		}
		std::complex<double> AB, AP;
		AB = ls.b_.get_complex() - ls.a_.get_complex();	 // AB
		AP = p.get_complex() - ls.a_.get_complex();		 // AP
		double absAB = abs(AB);
		double t = (AB.real() * AP.real() + AB.imag() * AB.imag()) / (absAB * absAB);  //距離を最小とする内分点

		if (0 < t && t < 1) {
			return abs(AB.real() * AP.imag() - AB.imag() * AP.real()) / absAB;
		} else {
			return std::min(Point::distance(ls.a_, p), Point::distance(ls.b_, p));
		}
	}

	static double distance(LineSeg a, LineSeg b) {
		if (LineSeg::crossing(a, b)) return 0;
		return std::min(LineSeg::distance(a, b.a_), LineSeg::distance(a, b.b_));
	}
};
}  // namespace ishihalib