#include "DataSet.h"
#include <iostream>
#include <fstream>

using namespace std;
int hypersample = 1;
DataSet::DataSet(int argc,char** argv)
{
	Matrix conf;
	if ((argc > 1) &&  fexists(argv[1])) {
		data.readBin(argv[1]); // Datafile
	}
	else {
		cout << "File not found : " << argv[1] << endl;
		exit(1);
	}
	n = data.r;
	d = data.m;
	init_buffer(nthd, d);

	if ((argc > 3) && fexists(argv[3]))
	{
		conf.readBin(argv[3]);
		m = conf(0)[1];
		kappa = conf(0)[2];
		kappa1 = conf(0)[3];
		alpha = conf(0)[4];
		gam = conf(0)[5];
	}
	else
	{
		m = d + 2;
		kappa = 0.05;
		kappa1 = 0.5;
		alpha = 0.1;
		gam = 1;
	}


	if ((argc > 2) && fexists(argv[2]))
	{
		prior.readBin(argv[2]);
		hypersample = 1; // 0 actual value would be changed in further versions
		Psi = prior;
		Psi.r = d; // Last row is shadowed
		Psi.n = d*d;
		mu0 = prior(d).copy();
	}
	else
	{
		Psi = (eye(d)*(m - d - 1));
		mu0 = data.mean();
	}
	

	
	cout << n << " " << d << " " << kappa << " " << kappa1 << " " << alpha << " " << gam << endl;

	//if ((argc > 2) & fexists(argv[2]))
		//group.readBin(groupfile);
}


DataSet::~DataSet(void)
{
}


