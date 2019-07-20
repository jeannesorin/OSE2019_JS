#include <iostream>
#include <cmath>

using namespace std;
 
int main ()
{
	float a, b, c;
	cout << "Enter a ";
	cin >> a;
	cout << "Enter b ";
	cin >> b;
	cout << "Enter c ";
	cin >> c;

	
	float delta = pow(b,2)-4*a*c ;
	float r1,r2;
	r1 = (-1*b - sqrt(delta))/(2*a); 
	r2 = (-1*b + sqrt(delta))/(2*a);

	cout << "Root 1 is " << r1 << endl;
	cout << "Root 2 is " << r2 << endl; 
	return 0;
}
