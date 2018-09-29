#pragma once
#include <iostream>
#include <algorithm>
#include <initializer_list>
#include <array>
#include <utility>


template<size_t N>
class Point final {
public:
	constexpr Point();
	constexpr Point(std::initializer_list<double> init);
	constexpr Point(const Point& point);
	constexpr Point &operator = (const Point<N>& point);
	constexpr Point &operator = (const Point<N>& point)			const = delete;

	constexpr Point(Point&& point);
	constexpr Point& operator=(Point<N>&& point);
	constexpr Point& operator=(Point<N>&& point)				const = delete;

	~Point();

	constexpr size_t size()										const;
	constexpr double lenght()									const;

	constexpr inline double& operator[](size_t idx);
	constexpr inline const double operator[](size_t idx)		const;

	constexpr Point operator+(const Point<N> &point)			const;
	constexpr Point operator-(const Point<N> &point)			const;
	constexpr Point& operator+=(const Point<N> &point);
	constexpr Point& operator-=(const Point<N> &point);

	constexpr Point& operator+=(double number);
	constexpr Point& operator-=(double number);
	constexpr Point& operator*=(double number);
	constexpr Point& operator/=(double number);

	constexpr bool operator==(const Point<N> &point);

private:
	std::array<double, N> _point;

	template<size_t I, size_t N>
	friend constexpr double& std::get(Point<N> &point);

	template<size_t I, size_t N>
	friend constexpr double std::get(const Point<N> &point);

	template<size_t N>
	friend constexpr std::array<double, N>& getArray(Point<N> &point);
};


//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------

template<size_t N>
constexpr inline Point<N>::Point()
{
	_point.fill(0.0);
}

template<size_t N>
constexpr inline Point<N>::Point(std::initializer_list<double> init)
{
	size_t idx = 0;
	for (auto it = init.begin(); it != init.end(); ++it) {
		if (idx >= N) break;
		_point[idx] = *it;
		++idx;
	}
}

template<size_t N>
constexpr inline Point<N>::Point(const Point<N> & point)
	:_point(point._point)
{

}

template<size_t N>
constexpr inline Point<N> & Point<N>::operator=(const Point<N> & point)
{
	this->_point = point._point;
	return *this;
}

template<size_t N>
constexpr inline Point<N>::Point(Point && point)
	:_point(point._point)
{

}

template<size_t N>
constexpr inline Point<N> & Point<N>::operator=(Point<N> && point)
{
	this->_point = std::move(point._point);
	return *this;
}

template<size_t N>
inline Point<N>::~Point()
{

}

//-----------------------------------------------------

template<size_t N>
constexpr inline size_t Point<N>::size() const
{
	return N;
}

template<size_t N>
inline constexpr double Point<N>::lenght() const
{
	double len = 0;
	for (size_t i = 0; i < this->size(); ++i) {
		len += pow(this->operator[](i), 2);
	}
	return sqrt(len);
}

template<size_t N>
constexpr inline double & Point<N>::operator[](size_t idx)
{
	return _point.at(idx);
}

template<size_t N>
constexpr inline const double Point<N>::operator[](size_t idx) const
{
	return _point.at(idx);
}

//-----------------------------------------------------

template<size_t N>
constexpr inline Point<N> Point<N>::operator+(const Point<N> & point) const
{
	Point<N> _p(*this);
	for (int i = 0; i < this->size(); ++i) {
		_p[i] += point[i];
	}
	return _p;
}

template<size_t N>
constexpr inline Point<N> Point<N>::operator-(const Point<N> & point) const
{
	Point<N> _p(*this);
	for (int i = 0; i < this->size(); ++i) {
		_p[i] -= point[i];
	}
	return _p;
}

template<size_t N>
constexpr inline Point<N> & Point<N>::operator+=(const Point<N> & point)
{
	for (size_t i = 0; i < this->size(); ++i) {
		this->operator[](i) += point[i];
	}
	return *this;
}

template<size_t N>
constexpr inline Point<N> & Point<N>::operator-=(const Point<N> & point)
{
	for (size_t i = 0; i < this->size(); ++i) {
		this->operator[](i) -= point[i];
	}
	return *this;
}

//-----------------------------------------------------

template<size_t N>
constexpr inline Point<N> & Point<N>::operator+=(double number)
{
	for (size_t i = 0; i < this->size(); ++i) {
		this->operator[](i) += number;
	}
	return *this;
}

template<size_t N>
constexpr inline Point<N> & Point<N>::operator-=(double number)
{
	for (size_t i = 0; i < size(); ++i) {
		this->operator[](i) -= number;
	}
	return *this;
}

template<size_t N>
constexpr inline Point<N> & Point<N>::operator*=(double number)
{
	for (size_t i = 0; i < this->size(); ++i) {
		this->operator[](i) *= number;
	}
	return *this;
}

template<size_t N>
constexpr inline Point<N> & Point<N>::operator/=(double number)
{
	for (size_t i = 0; i < this->size(); ++i) {
		this->operator[](i) /= number;
	}
	return *this;
}

template<size_t N>
constexpr inline bool Point<N>::operator==(const Point<N>& point)
{
	return this->_point == point._point;
}

//-----------------------------------------------------

template<class H, class ...Args>
inline constexpr Point<sizeof...(Args) + 1> make_point(H h, Args...args) {
	Point<sizeof...(Args) + 1> p;
	_make_point_helper(p, 0, h, args...);
	return p;
}

template<class Point, class H, class ...Args>
inline constexpr void _make_point_helper(Point &p, size_t i, H h, Args...args) {
	p[i] = h;
	_make_point_helper(p, i + 1, args...);
}

template<class Point, class H>
inline constexpr void _make_point_helper(Point &p, size_t i, H h)
{
	p[i] = h;
}

namespace std {
	template<size_t I, size_t N>
	inline constexpr double& get(Point<N>& point)
	{
		static_assert(I >= 0 && I < N, "Out of range");
		return std::get<I>(point._point);
	}

	template<size_t I, size_t N>
	inline constexpr double get(const Point<N>& point)
	{
		static_assert(I >= 0 && I < N, "Out of range");
		return std::get<I>(point._point);
	}
}

template<size_t N>
inline constexpr std::array<double, N>& getArray(Point<N>& point)
{
	return point._point;
}

//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------

template<size_t N>
inline Point<N> operator+(const Point<N>& p, double number)
{
	Point<N> _p(p);
	for (size_t i = 0; i < _p.size(); ++i) {
		_p[i] += number;
	}
	return _p;
}

template<size_t N>
inline Point<N> operator-(const Point<N>& p, double number)
{
	Point<N> _p(p);
	for (size_t i = 0; i < _p.size(); ++i) {
		_p[i] -= number;
	}
	return _p;
}

template<size_t N>
inline Point<N> operator*(const Point<N>& p, double number)
{
	Point<N> _p(p);
	for (size_t i = 0; i < _p.size(); ++i) {
		_p[i] *= number;
	}
	return _p;
}

template<size_t N>
inline Point<N> operator/(const Point<N>& p, double number)
{
	Point<N> _p(p);
	for (size_t i = 0; i < _p.size(); ++i) {
		_p[i] /= number;
	}
	return _p;
}

//-----------------------------------------------------

template<size_t N>
bool operator<(const Point<N>& p, double number)
{
	double res = 0;
	for (int i = 0; i < p.size(); ++i) {
		res += p[i] * p[i];
	}
	return res < number * number;
}

template<size_t N>
bool operator>(const Point<N>& p, double number)
{
	double res = 0;
	for (int i = 0; i < p.size(); ++i) {
		res += p[i] * p[i];
	}
	return res > number * number;
}

template<size_t N>
bool operator<=(const Point<N>& p, double number)
{
	double res = 0;
	for (int i = 0; i < p.size(); ++i) {
		res += p[i] * p[i];
	}
	return res <= number * number;
}

template<size_t N>
bool operator>=(const Point<N>& p, double number)
{
	double res = 0;
	for (int i = 0; i < p.size(); ++i) {
		res += p[i] * p[i];
	}
	return res >= number * number;
}

//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------
//-----------------------------------------------------