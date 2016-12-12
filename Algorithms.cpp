#include "Algorithms.h"


Vector kmeans(Matrix& data,int k)
{
	//k = d;// thread::hardware_concurrency(); // Our matrices are square in buffer , to be implemented later, this is not limitation in main program 
	Matrix means(k,d); // This need to be modified , But buffer size is fixed so I am exploting that
	Vector counts(d);
	ThreadPool tpool(thread::hardware_concurrency());
	vector<KmeansTask> ktasks;

	for (auto i = 0; i < k; i++) {
		Vector v = data(i*(n / k));
		means(i) = v;
	}

	Vector labels(n);
	for (auto iter = 0; iter < 20; iter++){

		for (auto i = 0; i < tpool.numthreads; i++) {
			ktasks.push_back(KmeansTask(data, means, labels,k));
		}
		for (auto i = 0; i < tpool.numthreads; i++) {
			tpool.submit(ktasks[i]);
		}
		tpool.waitAll();

		means.zero();
		counts.zero();
		
		for (auto i = 0; i < tpool.numthreads; i++) {
			means = means + ktasks[i].sums;
			counts = counts + ktasks[i].counts;
		}

		for (auto i = 0; i < k; i++) {
			means(i) = means(i) / counts(i);
		}
	}

	return labels;
}


KmeansTask::KmeansTask(Matrix& data, Matrix& centers, Vector& labels,int k) : data(data), means(centers), labels(labels), k(k)
{
}

void KmeansTask::run(int id)
{
	threadid = id;
	int l;
	double mindist, dist;
	int d = data.m;
	counts = Vector(k);
	sums = Matrix(k,d);
	sums.zero();
	counts.zero();
	auto range = trange(n, nthd, threadid-1); // Threadids start from 1 
	for (auto i = range[0]; i < range[1]; i++)
	{
		mindist = INFINITY;
		for (auto j = 0; j < k; j++)
		{
			dist = (data(i) - means(j)).norm();
			if (dist < mindist) {
				mindist = dist;
				l = j;
			}
		}
		labels[i] = l;
		counts[l]++;
		sums(l) =  sums(l) +  data(i);
	}
}




int MAXCOMP = 20;
//extern double alpha = 1;

Normal priormean;
IWishart priorcov;

Vector stickBreaker(double ustar, double betastar, double alpha)
{
	Dirichlet  ds(v({ 1, alpha })); // Beta
	Vector lengths(MAXCOMP);
	for (int i = 0; i < MAXCOMP; i++)
		lengths[i] = ds.rnd()[0];
	Vector beta = zeros(MAXCOMP + 1);
	int i = 0;
	double totallength = betastar;
	double betasum = 0;
	for (i = 0; i<MAXCOMP; i++)
	{
		if (betastar < ustar)
			break;
		beta[i] = betastar*lengths[i];
		betasum += beta[i];
		betastar = betastar*(1 - lengths[i]);
	}
	beta.resize(i + 1);
	beta[i] = totallength - betasum;
	return beta;
}