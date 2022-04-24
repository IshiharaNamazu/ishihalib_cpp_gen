#pragma once

namespace ishihalib {
struct Circle {
	Circle(double circumference, double value_ = 0) : circumference_(circumference), value_(value_) {
	}

	Circle(const Circle& c) : circumference_(c.circumference_), value_(c.value_) {
	}

	void set(double value) {
		value_ = value;
		normalize();
	}

	double circumference_;
	double value_;

  private:
	void normalize() {
		while (value_ <= -circumference_ / 2.) {
			value_ += circumference_;
		}
		while (value_ > circumference_ / 2.) {
			value_ -= circumference_;
		}
	}

  public:
	Circle operator+() const {
		return (*this);
	}
	Circle operator-() const {
		Circle ret(value_);
		return ret;
	}
	Circle& operator+=(const double& rhs) {
		set(value_ + rhs);
		return *this;
	}
	Circle& operator-=(const double& rhs) {
		set(value_ - rhs);
		return *this;
	}
	Circle& operator*=(const double& rhs) {
		set(value_ * rhs);
		return *this;
	}
	Circle& operator/=(const double& rhs) {
		set(value_ / rhs);
		return *this;
	}
	Circle& operator+=(const Circle& rhs) {
		set(value_ + rhs.value_);
		return *this;
	}
	Circle& operator-=(const Circle& rhs) {
		set(value_ - rhs.value_);
		return *this;
	}
	Circle& operator*=(const Circle& rhs) {
		set(value_ * rhs.value_);
		return *this;
	}
	Circle& operator/=(const Circle& rhs) {
		set(value_ / rhs.value_);
		return *this;
	}
	Circle& operator=(const Circle& rhs) {
		set(rhs.value_);
		return *this;
	}
	Circle& operator=(const double& rhs) {
		set(rhs);
		return *this;
	}
	operator double() const {
		return value_;
	}
};
}  // namespace ishihalib