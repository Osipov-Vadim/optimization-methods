#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "Task.h"

#include "stats.h"



template<unsigned N>
struct _Fib : _Fib<N - 1> {
	static int const value = _Fib<N - 1>::value + _Fib<N - 2>::value;
	static int const prev = _Fib<N - 1>::value;
	using prev_ = _Fib<N - 1>;
};

template<>
struct _Fib<0> {
	static int const value = 0;
};

template<>
struct _Fib<1> {
	static int const value = 1;
	static int const prev = _Fib<0>::value;
	using prev_ = _Fib<0>;
};

//---------------------------------------------------
std::vector<unsigned> Fib;

int setFib(double lim) {
	Fib.clear();
	Fib.push_back(1);
	Fib.push_back(1);
	int count = 1;

	while (Fib[count] <= lim) {
		++count;
		Fib.push_back(Fib[count - 1] + Fib[count - 2]);
	}
	return count;
}

//---------------------------------------------------

template<class RT, class ...Args>
Point<sizeof...(Args)> Dichotomy(const Task<RT, Args...> &task,
	const Point<sizeof...(Args)> &a,
	const Point<sizeof...(Args)> &b)
{
	double eps = Task<RT, Args...>::eps;
	auto l = a;
	auto r = b;

	//stat
	Stats<sizeof...(Args)> stat(2);
	stat.a = l; stat.b = r;
	stat.showFirst();
	//stat

	while (r - l > eps) {
		auto m = (l + r) / 2;
		auto x1 = m - eps / 3;
		auto x2 = m + eps / 3;

		if (task.f(x1) < task.f(x2))
			r = m;
		else
			l = m;
		m = (l + r) / 2;

		//stat
		stat.call_f += 2; stat.iter++;
		stat.a = l; stat.b = r;
		stat.x_fx[0].first = x1; stat.x_fx[0].second = task.f(x1);
		stat.x_fx[1].first = x2; stat.x_fx[1].second = task.f(x2);
		stat.show();
		//stat
	}
	return (l + r) / 2;
}

//---------------------------------------------------

template<class RT, class ...Args>
Point<sizeof...(Args)> goldenSection(const Task<RT, Args...> &task,
	const Point<sizeof...(Args)> &a,
	const Point<sizeof...(Args)> &b)
{
	static double gr = (1 + sqrt(5)) / 2;
	double eps = Task<RT, Args...>::eps;
	auto l = a;
	auto r = b;

	auto x1 = r - (r - l) / gr;
	auto x2 = l + (r - l) / gr;

	auto y1 = task.f(x1);
	auto y2 = task.f(x2);

	//stat
	Stats<sizeof...(Args)> stat(2);
	stat.a = l; stat.b = r;
	stat.x_fx[0].first = x1; stat.x_fx[0].second = y1;
	stat.x_fx[1].first = x2; stat.x_fx[1].second = y2;
	stat.call_f += 2;
	stat.show();
	//stat

	while (r - l > eps) {
		if (y1 < y2) {
			r = x2;
			x2 = x1;
			x1 = r - (r - l) / gr;

			y2 = y1;
			y1 = task.f(x1);
		}
		else {
			l = x1;
			x1 = x2;
			x2 = l + (r - l) / gr;

			y1 = y2;
			y2 = task.f(x2);
		}
		//stat
		stat.call_f += 1; stat.iter++;
		stat.a = l; stat.b = r;
		stat.x_fx[0].first = x1; stat.x_fx[0].second = y1;
		stat.x_fx[1].first = x2; stat.x_fx[1].second = y2;
		stat.show();
		//stat
	}
	return (l + r) / 2;
}

//---------------------------------------------------

template<class RT, class ...Args>
Point<sizeof...(Args)> Fibonacci(const Task<RT, Args...> &task,
	const Point<sizeof...(Args)> &a,
	const Point<sizeof...(Args)> &b)
{
	double eps = Task<RT, Args...>::eps;
	auto l = a;
	auto r = b;
	size_t n = setFib((r - l).lenght() / eps);
	//n = 6 + 2;
	size_t k = 1;

	auto x1 = l + (r - l) * static_cast<double>(Fib[n - k - 1])	/ Fib[n - k + 1];
	auto x2 = l + (r - l) * static_cast<double>(Fib[n - k])		/ Fib[n - k + 1];

	auto y1 = task.f(x1);
	auto y2 = task.f(x2);

	//stat
	Stats<sizeof...(Args)> stat(2);
	stat.a = l; stat.b = r;
	stat.x_fx[0].first = x1; stat.x_fx[0].second = y1;
	stat.x_fx[1].first = x2; stat.x_fx[1].second = y2;
	stat.call_f += 2;
	stat.show();
	//stat

	while (true) {
		if (y1 < y2) {
			r = x2;
			x2 = x1;
			x1 = l + (r - l) * static_cast<double>(Fib[n - k - 2]) / Fib[n - k];

			y2 = y1;
			y1 = task.f(x1);
		}
		else {
			l = x1;
			x1 = x2;
			x2 = l + (r - l) * static_cast<double>(Fib[n - k - 1]) / Fib[n - k];

			y1 = y2;
			y2 = task.f(x2);
		}
		
		//stat
		stat.call_f += 1; stat.iter++;
		stat.a = l; stat.b = r;
		stat.x_fx[0].first = x1; stat.x_fx[0].second = y1;
		stat.x_fx[1].first = x2; stat.x_fx[1].second = y2;
		stat.show();
		//stat
		if (k == n - 2) {
			break;
		}
		else {
			++k;
		}
		
	}
	return (l + r) / 2;

	//while (n != 1) {
	//	--n;
	//	if (y1 < y2) {
	//		r = x2;
	//		x2 = x1;
	//		x1 = l + (r - x2);

	//		y2 = y1;
	//		y1 = task.f(x1);
	//	}
	//	else {
	//		l = x1;
	//		x1 = x2;
	//		x2 = r - (x1 - l);

	//		y1 = y2;
	//		y2 = task.f(x2);
	//	}
	//	//stat
	//	stat.call_f += 1; stat.iter++;
	//	stat.a = l; stat.b = r;
	//	stat.x_fx[0].first = x1; stat.x_fx[0].second = y1;
	//	stat.x_fx[1].first = x2; stat.x_fx[1].second = y2;
	//	stat.show();
	//	//stat
	//}
	//return (l + r) / 2;
}

//---------------------------------------------------