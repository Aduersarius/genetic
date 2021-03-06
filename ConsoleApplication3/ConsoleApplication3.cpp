#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
using namespace std;

struct chromo {
	double x;
	double y;
	double fitness;
};

double func(double x, double y) {  // функция приспособленности
	return (cos(x)*cos(y));
	return (-(1 - x)*(1 - x) - pow(2.718281, x));
}

double mutation(double x, double g) {
	
	x = x + (double)(-5 + rand() % 10) / 1000;
	if(x > -g && x < g)
		return x;
	else if (x <= -g) return -g;
	else return g;
}

void crossover(chromo *o) {
	o[3].x = o[0].x;
	o[3].y = o[2].y;
	o[2].y = o[0].y;
	swap(o[1].y, o[0].y);
}

void print(chromo o[4]) {
	cout << "x1 = " << o[0].x << " y1 = " << o[0].y << " F1 = " << o[0].fitness << endl;
	cout << "x2 = " << o[1].x << " y2 = " << o[1].y << " F2 = " << o[1].fitness << endl;
	cout << "x3 = " << o[2].x << " y3 = " << o[2].y << " F3 = " << o[2].fitness << endl;
	cout << "x4 = " << o[3].x << " y4 = " << o[3].y << " F4 = " << o[3].fitness << endl << endl;
}

double genetic(double x1, double y1, int k) {
	chromo popul[4];
	srand(time(0));
	for (int i = 0; i < 4; i++) {
		popul[i].x = (double)(-(x1 * 1000) + rand() % (int)(x1 * 2000)) / 1000;
		popul[i].y = (double)(-(y1 * 1000) + rand() % (int)(y1 * 2000)) / 1000;
		popul[i].fitness = func(popul[i].x, popul[i].y);
	}
	for (int i = 0; i < k; i++) {
		sort(begin(popul), end(popul), [](chromo a, chromo b) {return a.fitness > b.fitness; });
		print(popul);
		crossover(popul);
		for (int j = 0; j < 4; j++) {
			popul[j].fitness = func(popul[j].x, popul[j].y);
			popul[j].x = mutation(popul[j].x, x1);
			popul[j].y = mutation(popul[j].y, y1);
		}
	}
	sort(begin(popul), end(popul), [](chromo a, chromo b) {return a.fitness > b.fitness; });
	return popul[0].fitness;
}

int main()
{
	double res = genetic(2.2, 2.2, 10000);
    return 0;
}

