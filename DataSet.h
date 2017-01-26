#pragma once
#include "Matrix.h"
#include "Global.h"
#include "Stut.h"

extern int hypersample;
class DataSet
{
public:
	DataSet(int argc,char** argv); // Group info is for topic models like Aspire
	Matrix data;
	Matrix prior;
	Vector group;
	~DataSet(void);
};

