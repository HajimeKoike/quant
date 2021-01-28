#define ANAL 0
#define EM 1

#include <bits/stdc++.h>

using namespace std;

void gbm( double& x0, double& xout, 
		  int i, double w, 
		  double mu, double sigma ) {
	xout = x0 * exp( (mu-sigma*sigma/2.)*i + sigma*w );
}

void gbm_em( vector<double>& xin, vector<double>& xout, 
			 double dt, vector<double> dw, 
			 double mu, double sigma, int m ) {
	for ( int j=0; j<m; ++j ) 
		xout[j] = xin[j] + mu*xin[j] * dt + sigma*xin[j]*sqrt(dt) * dw[j];
}

int main() {
#if ANAL
{
	int seed = 42;
	double mu = 0.02;
	double sigma = 0.01;

	int nt = 100;

	double x0 = 1.0;
	double xout;

	mt19937 mt(seed);
	normal_distribution<double> n(0,1);

	for ( int i=1; i<=nt; ++i ) {
		double w = sqrt(i) * n(mt);
		gbm(x0,xout,i,w,mu,sigma);
	}
	cout << setprecision(10) << xout << endl;
}
#endif
#if EM
{
	int seed = 42;
	double mu = 0.02;
	double sigma = 0.01;

	int nt = 100;
	int m = 10000;
	double dt = 1.e-2;

	cin >> m >> dt;

	double x0 = 1.0;
	vector<double> x0_vec(m,x0)
	vector<double> xin(m),xout(m);

	mt19937 mt(seed);
	normal_distribution<double> n(0,1);

	xin=x0_vec;
	for ( int i=1; i<=int(nt/dt); ++i ) {
		vector<double> dw(m);
		for ( int j=0; j<m; ++j ) dw[j] = n(mt);
		gbm_em(xin,xout,dt,dw,mu,sigma,m);
		xin=xout;
	}
	for ( int j=0; j<m; ++j ) cout << setprecision(10) << xin[j] << endl;
}
#endif
}
