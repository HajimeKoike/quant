#define ANAL 1
#define MC 0

#include <bits/stdc++.h>

using namespace std;

void call( double s, double& c, double r, double sigma, int nt, int i, double k ) {
	double d1 = (log(s/k)+(r+sigma*sigma/2)*i)/(sigma*sqrt(i));
	c = exp(-r*(nt-i)) * 0.5*( erf( d2/sqrt(2) )+1 );
}

int main() {
#if ANAL
{
	double r=0.01;
	double sigma=0.01;
	double k=3.00;

	int nt=100+1;

	double s;
	int i=0;
	while ( cin>>s ) {
		double c;
		call( s, c, r, sigma, nt, i, k );
		cout << setprecision(10) << c << endl;
		++i;
	}
}
#endif
#if MC
{
	double r=0.01;
	double sigma=0.01;
	double k=3.00;

	double s;
	int i=0;
	while ( getline(cin,line) ) {
		stringstream ss(line);
		double c=0;
		for ( int j=0; j<m; ++j ) {
			getline(ss,s);
			c+= (s>k) ? exp(-r*i)*1.0 : 0;
		}
		c/=m;
		cout << setprecision(10) << c << endl;
		++i;
