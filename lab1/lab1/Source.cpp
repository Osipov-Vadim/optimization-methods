//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
//#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES 

#include <iostream>
#include <iomanip> 
#include <fstream>

#define statsOn true
#include "OneDimensionalSearch.h"
#include "GradientDescent.h"


template<class T>
auto cout_point(T &p) {
	for (int i = 0; i < p.size(); ++i) {
		std::cout << p[i] << ' ';
	}
	std::cout << '\n';
}

//---------------------------------------------------

template<class RT, class ...Args>
double Task<RT, Args...>::eps = 1e-3;

int main() {
	//--------------------------------
	setlocale(LC_ALL, "Russian");
	system("color F2");
	std::ios_base::sync_with_stdio(false);
	std::ifstream fin("input.txt");
	std::ofstream fout("output.txt");
	std::cout << std::setprecision(5);
	std::cout.setf(std::ios::fixed, std::ios::floatfield);
	//--------------------------------
	

#if 1
	{
		TaskHelper<double, double> t1([](double x) {return sin(x); }, -M_PI / 2, M_PI / 2);
		TaskHelper<double, double> t2([](double x) {return cos(x); }, 0, M_PI);
		TaskHelper<double, double> t3([](double x) {return pow(x - 2, 2); }, -2, 20);
		TaskHelper<double, double> t4([](double x) {return pow(x - 15, 2) + 5; }, 2, 200);
		TaskHelper<double, double> t5([](double x) {return pow(x + 5, 4); }, -10, 15);
		TaskHelper<double, double> t6([](double x) {return exp(x); }, 0, 100);
		TaskHelper<double, double> t7([](double x) {return x * x + 2 * x - 4; }, -10, 20);
		TaskHelper<double, double> t8([](double x) {return x * x*x - x; }, 0, 1);
		TaskHelper<double, double> h1([](double x) {return 4.2 * x * x + 23/x; }, 0, 8);

		auto &curTask = t4;
		//

		std::cout << "Dichotomy" << '\n';;
		auto p1 = Dichotomy(curTask.getTask(), curTask.get_a(), curTask.get_b());
		std::cout << "---------------------------------------------------\n";
		std::cout << p1[0] << '\n';
		std::cout << "---------------------------------------------------\n";

		std::cout << "Golden Section" << '\n';
		auto p2 = goldenSection(curTask.getTask(), curTask.get_a(), curTask.get_b());
		std::cout << "---------------------------------------------------\n";
		std::cout << p2[0] << '\n';
		std::cout << "---------------------------------------------------\n";

		std::cout << "Fibonacci" << '\n';
		auto p3 = Fibonacci(curTask.getTask(), curTask.get_a(), curTask.get_b());
		std::cout << "---------------------------------------------------\n";
		std::cout << p3[0] << '\n';
		std::cout << "---------------------------------------------------\n";
	}
#endif


#if 0
	{
		Task<double, double, double> t1(
			[](double x1, double x2) {
			return 100 * pow(x2 - pow(x1, 2), 2) + pow(1 - x1, 2);
		});
		Task<double, double, double> t2(
			[](double x1, double x2) {
			return x1 * x1 + x2 * x2;
		});
		Task<double, double, double> t3(
			[](double x1, double x2) {
			return 3 * x1*x1 + x1 * x2 + x2 * x2 * 2 - x1 - 4 * x2;
		});

		Task<double, double, double> tt(
			[](double x1, double x2) {
			return 8 * x1*x1 + 4 * x1*x2 + 5 * x2*x2;
		});



		auto curTask = t1;


		//auto dir = make_point(0.01, 0.0);
		//func_sab(t1, make_point(2, 14.5), make_point(3, 15.5), 0.1);
		//func_eps_point(t1, make_point(2.46, 14.97), 0.01);
		//check_min(t1, make_point(2.4646, 14.9729), 0.01);


		/*bool bad = false;
		auto point = findSegmentWithMin(tt, p1, dir, bad);
		if (bad == true) std::cout << " lool \n";*/
		//std::cout << point.first[0] << ' ' << point.first[1] << ' ' << point.second[0] << ' ' << point.second[1] << '\n';



		
		std::cout << "Gradient" << '\n';
		auto p1 = make_point(-5, -5);
		auto p2 = make_point(5, 5);
		RunOnTheArea(curTask, p1, p2, 5);
		std::cout << "--------------------------\n";




		auto min = GradientDescent(t1, p1);
		cout_point(min);
	}
#endif



	system("pause");
	return 0;
}