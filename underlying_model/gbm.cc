#define EIGEN_USE_MKL_ALL
#define ANAL 0
#define MC 1

#include <bits/stdc++.h>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

void gbm( double& x0, double& xout, 
		  int i, double w, 
		  double mu, double sigma ) {
	xout = x0 * exp( (mu-sigma*sigma/2.) * i + sigma * w );
}

void gbm_em( VectorXd& xin, VectorXd& xout, 
			 double dt, VectorXd dw, 
			 double mu, double sigma, int m ) {
	assert ( xin.rows()==m && xout.rows()==m && dw.rows()==m );
	xout = xin + mu*dt*xin + (sigma*sqrt(dt)*xin.array()*dw.array()).matrix();
}

int main() {
#if ANAL
{
	int seed=42;
	double mu=0.02;
	double sigma=0.01;

	int nt=100;

	double x0=1.0;
	double xout;

	mt19937 mt(seed);
	normal_distribution<double> n(0,1);

	cout << setprecision(10) << x0 << endl;
	for ( int i=1; i<nt; ++i ) {
		double w = sqrt(i) * n(mt);
		gbm(x0,xout,w,mu,sigma,i);
		cout << setprecision(10) << xout << endl;
	}
}
#endif
#if MC
{
	int seed=42;
	double mu=0.02;
	double sigma=0.01;

	int nt=100;
	int m=10000;
	double dt=1.e-2;

	cin >> m >> dt;

	double x0=1.0;
	VectorXd x0_vec = x0 * VectorXd::Ones(m);
	VectorXd xin(m),xout(m);

	mt19937 mt(seed);
	normal_distribution<double> n(0,1);

	xin=x0_vec;
	cout << setprecision(10) << xin.transpose() << endl;
	for ( int i=1; i<int(nt/dt); ++i ) {
		VectorXd dw(m);
		for ( int j=0; j<m; ++j ) dw(j) = n(mt);
		gbm_em(xin,xout,dt,dw,mu,sigma,m);
		xin=xout;
		cout << setprecision(10) << xin.transpose() << endl;
	}
}
#endif
}
