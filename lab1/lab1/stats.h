#pragma once
#include <vector> 
#include <ostream>
#include <fstream>
#include <iostream>
#include <iomanip> 
#include "Point.h"

template<size_t N>
struct Stats {
public:
	size_t iter;
	size_t call_f;

	std::vector<std::pair<Point<N>, double>> x_fx;

	Point<N> a;
	Point<N> b;

	Stats(size_t i = 1)
		:iter(0), call_f(0), 
		a(Point<N>()), b(Point<N>()), 
		last_len(-1), isFirst(true), os(std::cout)
	{
		x_fx.resize(i);
		fout.open("output.txt", std::ios::app);
		fout << std::setprecision(7);
		fout.setf(std::ios::fixed, std::ios::floatfield);
	}

	void show() {
#if statsOn
		if (isFirst) {
			showTitle();
			isFirst = false;
		}
		os << std::setw(t_s) << iter;
		os << std::setw(t_s) << call_f;
		//

		for (size_t j = 0; j < x_fx.size(); ++j) {
			for (size_t i = 0; i < x_fx[j].first.size(); ++i) {
				os << std::setw(t) << x_fx[j].first[i];
			}
			//
			os << std::setw(t) << x_fx[j].second;
		}

		//
		if (last_len == - 1)
			os << std::setw(t) << "-";
		else 
			os << std::setw(t) << last_len / (b - a).lenght();
		last_len = (b - a).lenght();
		//
		for (size_t i = 0; i < a.size(); ++i) {
			os << std::setw(t) << static_cast<double>(a[i]);
		}
		//
		for (size_t i = 0; i < b.size(); ++i) {
			os << std::setw(t) << static_cast<double>(b[i]);
		}
		os << std::setw(t_s) << std::endl;
#endif
	}

	void showFirst() {
#if statsOn

		if (isFirst) {
			showTitle();
			isFirst = false;
		}
		os << std::setw(t_s) << iter;
		os << std::setw(t_s) << call_f;

		for (size_t j = 0; j < x_fx.size(); ++j) {
			for (size_t i = 0; i < x_fx[j].first.size(); ++i) {
				os << std::setw(t) << "-";
			}
			//
			os << std::setw(t) << "-";
		}

		os << std::setw(t) << '-';
		last_len = (b - a).lenght();
		//
		for (size_t i = 0; i < a.size(); ++i) {
			os << std::setw(t) << static_cast<double>(a[i]);
		}
		//
		for (size_t i = 0; i < b.size(); ++i) {
			os << std::setw(t) << static_cast<double>(b[i]);
		}
		os << std::setw(t_s) << std::endl;
#endif
	}

private:
	std::ofstream fout;
	std::ostream &os;

	void showTitle() {
#if statsOn
		os << std::setw(t_s) << "iter";
		os << std::setw(t_s) << "call";
		for (size_t i = 0; i < x_fx.size(); ++i) {
			for (size_t j = 0; j < x_fx[i].first.size(); ++j)
				os << std::setw(t) << ("x" + std::to_string(i) + std::to_string(j));
			os << std::setw(t) << ("fx" + std::to_string(i));
		}
		os << std::setw(t) << "ll/l";
		os << std::setw(t) << "a";
		os << std::setw(t) << "b";
		os << std::endl;
#endif
	}

	double last_len;
	bool isFirst;
	size_t t_s	= 5;
	size_t t	= 15;
};