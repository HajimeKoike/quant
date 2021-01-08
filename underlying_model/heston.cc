#define EIGEN_USE_MKL_ALL

#include <bits/stdc++.h>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

void heston_em ( MatrixXd& xin, MatrixXd& xout, 
				 double dt, MatrixXd dw, 
				 double mu, double kappa, double theta, double xi, int m ) {
	VectorXd sin(m), vin(m), dws(m), dwv(m);
	sin = xin.col(0); vin = xin.col(1);
	dws = dw.col(0); dwv = dw.col(1);
	VectorXd sout(m), vout(m);
	for ( int j=0; j<m; ++j ) {
		sout(j) = sin(j) + (mu*sin(j)) * dt + sqrt(vin(j)) * sin(j) * dws(j);
		vout(j) = vin(j) + kappa * ( theta-vin(j) ) * dt + xi*sqrt(vin(j)) * dwv(j);
	}
	xout.col(0) = sout; xout.col(1) = vout;
}

int main() {
{
	int seed=42;
	double mu=0.02;
	double kappa=0.1;
	double alpha=0.01;
	double theta=0.01;
	double xi=0.01;
	double rho=0;

	assert ( 2*kappa*theta > xi*xi );

	int nt=100;
	int m=10000;
	double dt=1.e-2;

	cin >> m >> dt;

	double s0=1.0;
	double v0=0.01;
	MatrixXd xin(m,2),xout(m,2);

	mt19937 mt(seed);
	normal_distribution<double> n(0,1);

	xin.col(0)=s0 * VectorXd::Ones(m);
	xin.col(1)=v0 * VectorXd::Ones(m);
	cout << setprecision(10) << xin.col(1).transpose() << endl;
	for ( int i=1; i<int(nt/dt); ++i ) {
		MatrixXd dw(m,2);
		for ( int j=0; j<m; ++j ) 
			for ( int k=0; k<2; ++k ) dw(j,k) = n(mt);
		heston_em(xin,xout,dt,dw,mu,kappa,theta,xi,m);
		xin=xout;
		cout << setprecision(10) << xin.col(1).transpose() << endl;
	}
}
}
