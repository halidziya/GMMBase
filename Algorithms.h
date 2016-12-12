#include "FastMat.h"
#include "GMMBase.h"

// Our matrices are square in buffer , to be implemented later, this is not limitation in main program since it is only used in initilization
class KmeansTask : public Task
{
public:
	Matrix& data;
	Matrix& means;
	Vector& labels;
	Vector counts;
	Matrix sums;
	KmeansTask(Matrix& data, Matrix& means,Vector& labels,int k);
	void run(int id);
	int k;
};

Vector kmeans(Matrix& ds,int k);



extern  int MAXCOMP;
Vector stickBreaker(double ustar, double betastar = 1.0, double alpha = 1);