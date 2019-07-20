#include <iostream>
#include <cmath>
#include <random>
#include <stdio.h>

using namespace std;

int circle(double x, double y)
{
	
	int g_result = (x*x + y*y <= 1)*1;
	return g_result;
}

int main()
{
	using namespace std;


	const int nroll=1000; //Number of draws
	
	//cout << "What is n?" << endl;
	//cin >> nroll;
	//tr1::random_device rd;
	//tr1::mt19937 gen(rd());
	//tr1::uniform_real_distribution<double> dis(-1.0, 1.0);

	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(-1.0, 1.0);



	double x = 0;
	double y = 0;
	double sum = 0;
	for (int i=0; i<nroll; ++i) {
        	x = distribution(generator);
        	y = distribution(generator);
        	int g = circle (x,y);
       		cout << "x is " << x << "y is " << y << "g is "<< g << endl;
       		sum = sum + g;
        	cout << "sum " << sum << endl;
       	}	
       	cout << "Pi is approximately: " <<  sum/nroll*4 << endl;
	return sum/nroll*4;
}

