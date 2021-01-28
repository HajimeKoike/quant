#define ANAL 0
#define MC 1

#include <bits/stdc++.h>

using namespace std;

/* price of EUROPEAN CALL OPTION
 * 
 * INPUT:
 * 		s .. price of underlying at maturity nt
 * 		r .. risk-free rate
 * 	sigma .. standard deviation of underlying
 * 	   nt .. maturity
 * 	    i .. time to evaluate
 * 		k .. strike price
 * 		
 * OUTPUT:
 * 		c .. option price
 *
 */
void call( double s, double& c, double r, double sigma, int nt, int i, double k ) {
	double d1 = (log(s/k)+(r+sigma*sigma/2)*i)/(sigma*sqrt(i));
	double d2 = (log(s/k)+(r-sigma*sigma/2)*i)/(sigma*sqrt(i));
	c = s * 0.5*( erf( d1/sqrt(2) )+1 ) - exp(-r*(nt-i)) * 0.5*( erf( d2/sqrt(2) )+1 );
}

int main() {
#if ANAL
{
	double r = 0.01;
	double sigma = 0.01;
	double k = 3.00;

	int nt = 100+1;

	double s;
	cin >> s;
	call( s, c, r, sigma, nt, 0, k );
	cout << c << endl;
}
#endif
#if MC
{
	double r = 0.01;
	double sigma = 0.01;
	double k = 3.00;

	int nt = 100+1;

	double c=0;
	int m=0;
	double s;
	while ( cin >> s )
		++m;
		c+=exp(-r*nt)*max(s-k,0.0);
	}
	c/=m;
	cout << setprecision(10) << c << endl;
}
#endif
}
