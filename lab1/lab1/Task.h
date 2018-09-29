#pragma once
#include <functional>
#include <cmath>

#include "Point.h"

template<class RT, class ...Args>
struct Task
{
public:

	static double eps;

	Task() = delete;
	constexpr explicit Task(std::function<RT(Args...)> function)
		:_func(function) {}

	constexpr RT f(Args... args) const noexcept {
		return _func(std::forward<Args>(args)...);
	}

	constexpr RT f(const std::tuple<Args...> &tpl) const noexcept {
		return _f_helper(tpl, std::make_index_sequence<sizeof...(Args)>{});
		//return _f_helper(t, std::index_sequence_for<Args...>);
	}

	constexpr RT f(const Point<sizeof...(Args)> &point) const noexcept {
		return _f_helper(point, std::make_index_sequence<sizeof...(Args)>{});;
	}

	constexpr RT f(const std::array<RT, sizeof...(Args)> &arr) const noexcept {
		return _f_helper(arr, std::make_index_sequence<sizeof...(Args)>{});
	}

	constexpr RT df_x(const Point<sizeof...(Args)> &point, size_t idx = 0, double h = 1e-5) const noexcept {
		Point<sizeof...(Args)> point_h;
		point_h[idx] = h;

		return (f(point + point_h) - f(point - point_h)) / (2 * h);
	}

private:
	std::function<RT(Args...)> _func;

	template<class CTC, std::size_t... Is>
	constexpr RT _f_helper(const CTC &compile_time_container, std::index_sequence<Is...>) const noexcept {
		return f(std::get<Is>(compile_time_container)...);
	}
};


template<class RT, class ...Args>
struct TaskHelper {
public:
	TaskHelper() = delete;
	constexpr explicit TaskHelper(std::function<RT(Args...)> function,
		double a,
		double b)
		:task(Task<RT, Args...>(function)), a(make_point(a)), b(make_point(b)) {}

	auto getTask() { return task; };
	auto get_a() { return a; };
	auto get_b() { return b; };

private:
	Task<RT, Args...> task;
	Point<sizeof...(Args)> a;
	Point<sizeof...(Args)> b;
};
