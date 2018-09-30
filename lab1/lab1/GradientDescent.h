#pragma once
#include "OneDimensionalSearch.h"

template<class RT, class ...Args>
std::pair<	Point<sizeof...(Args)>,
	Point<sizeof...(Args)>>
	findSegmentWithMin(const Task<RT, Args...> &task,
		const Point<sizeof...(Args)> &point,
		const Point<sizeof...(Args)> &min_dir,
		bool &is_bad)
{
	//int step = 0;
	auto dir = min_dir;
	auto cur_point = point;
	auto last_point = cur_point;
	auto pred_last = last_point;

	dir *= 1e-3; //?
	do {
		pred_last = last_point;
		last_point = cur_point;
		cur_point += dir;
		dir *= 2;
		//if (step > 10) {bad = true; break;}
		//++step;
	} while (task.f(last_point) > task.f(cur_point));
	return std::make_pair(pred_last, cur_point);
}


template<class RT, class ...Args>
Point<sizeof...(Args)> GradientDescent(const Task<RT, Args...> &task,
	const Point<sizeof...(Args)> &_x)
{
	double eps = Task<RT, Args...>::eps;
	double eps_x = 1e-3;
	double eps_f = 1e-3;
	size_t size = sizeof...(Args);

	Point<sizeof...(Args)> x = _x;
	Point<sizeof...(Args)> dx;

	while (true) {
		for (size_t i = 0; i < size; ++i) {
			dx[i] = -task.df_x(x, i);
		}
		double fx = task.f(x);

		if (dx.lenght() <= 0.0001) return x;
		bool bad = false;
		auto points = findSegmentWithMin(task, x, dx / dx.lenght(), bad);
		if (bad == true) {
			std::cout << "Not segment\n";
		}

		auto min = goldenSection(task, points.first, points.second);
		std::cout << "x:  " << min[0] << ' ' << min[1] << '\n';

		if (abs(x[0] - min[0]) < eps_x && abs(x[1] - min[1]) < eps_x) {
			//std::cout << "x:  " << x[0] << ' ' << min[0] << "  y:  " << x[1] << ' ' << min[1] << '\n';
			return min;
		}
		if (abs(task.f(min) - fx) < eps_f) {
			//std::cout << "fx: " << task.f(min) << ' ' << fx << '\n';
			return min;
		}

		x = min;
	}
}


template<class RT, class ...Args>
void RunOnTheArea(	const Task<RT, Args...> &task, 
					const Point<sizeof...(Args)> &p1, 
					const Point<sizeof...(Args)> &p2, double eps) {
	for (double i = p1[0]; i < p2[0]; i += eps) {
		for (double j = p1[0]; j < p2[0]; j += eps) {
			auto p = make_point(i, j);
			std::cout << "--------------------------\n";
			cout_point(p);
			GradientDescent(task, p);
			std::cout << "--------------------------\n";
		}
	}
}

template<class RT, class ...Args>
void func_ab(	const Task<RT, Args...> &task,
				const Point<sizeof...(Args)> &p1,
				const Point<sizeof...(Args)> &p2, double count) {
	Point dir = (p2 - p1) / count;
	auto maxmin = task.f(p1);
	for (auto i = p1[0], k = p1[1]; i <= p2[0] + 1e-4; i += dir[0], k += dir[1]) {
		auto min = task.f(make_point(i, k));
		if (min < maxmin) maxmin = min;
		std::cout << min << ' ' << i << ' ' << k << '\n';
	}
	std::cout << "MaxMin = " << maxmin << '\n';
}

template<class RT, class ...Args>
void func_sab(	const Task<RT, Args...> &task,
				const Point<sizeof...(Args)> &p1,
				const Point<sizeof...(Args)> &p2, double eps) {
	//double eps = 0.1;
	std::cout << std::fixed << std::setprecision(3);
	int tch = 9;
	auto maxmin = task.f(p1);
	std::cout << std::setw(tch) << ' ';
	for (auto j = p1[1]; j < p2[1] + 1e-4; j += eps) {
		std::cout << std::setw(tch) << j;
	}
	std::cout << '\n';

	for (auto i = p1[0]; i < p2[0] + 1e-4; i += eps) {
		std::cout << std::setw(tch) << i;
		for (auto j = p1[1]; j < p2[1] + 1e-4; j += eps) {
			auto min = task.f(make_point(i, j));
			if (min < maxmin) maxmin = min;
			std::cout << std::setw(tch) << min;//' ' << i << ' ' << j;
		}
		std::cout << '\n';
	}
	std::cout << "MaxMin = " << maxmin << '\n';
}

template<class RT, class ...Args>
void func_eps_point(const Task<RT, Args...> &task,
					const Point<sizeof...(Args)> &p1, 
					double eps) {
	std::cout << std::fixed << std::setprecision(3);
	int tch = 9;
	auto maxmin = task.f(p1);

	std::cout << std::setw(tch) << ' ';
	for (auto j = p1[1] - eps; j < p1[1] + eps + 1e-4; j += eps / 5) {
		std::cout << std::setw(tch) << j;
	}

	std::cout << '\n';

	for (auto i = p1[0] - eps; i < p1[0] + eps + 1e-4; i += eps / 5) {
		std::cout << std::setw(tch) << i;
		for (auto j = p1[1] - eps; j < p1[1] + eps + 1e-4; j += eps / 5) {
			auto min = task.f(make_point(i, j));
			if (min < maxmin) maxmin = min;
			std::cout << std::setw(tch) << min;//' ' << i << ' ' << j;
		}
		std::cout << '\n';
	}
	std::cout << "MaxMin = " << maxmin << '\n';
}

template<class RT, class ...Args>
void check_min(const Task<RT, Args...> &task, Point<sizeof...(Args)> p1, double eps) {
	std::cout << std::fixed << std::setprecision(3);
	int tch = 9;
	auto maxmin = task.f(p1);

	std::cout << std::setw(tch) << ' ';
	for (auto j = p1[1] - eps; j < p1[1] + eps + 1e-4; j += eps / 1) {
		std::cout << std::setw(tch) << j;
	}

	std::cout << '\n';

	for (auto i = p1[0] - eps; i < p1[0] + eps + 1e-4; i += eps / 1) {
		std::cout << std::setw(tch) << i;
		for (auto j = p1[1] - eps; j < p1[1] + eps + 1e-4; j += eps / 1) {
			auto min = task.f(make_point(i, j));
			if (min < maxmin) maxmin = min;
			std::cout << std::setw(tch) << min;//' ' << i << ' ' << j;
		}
		std::cout << '\n';
	}
	std::cout << "MaxMin = " << maxmin << '\n';
}