#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "readdata.h"

// #include <cudnn.h>
// #include <cuda_runtime.h>
// #include <device_launch_parameters.h>
// #include <cuda.h>
using namespace std;
int main()
{
	//braing the data and labels for training and test
	uint8_t *trainLabels, *trainImages;
	size_t trainRows, trainCols, trainSize;
	uint8_t *testLabels, *testImages;
	size_t testRows, testCols, testSize;

	if (readData("/home/roni/lenetPrac/train-images-idx3-ubyte", "/home/roni/lenetPrac/train-labels-idx1-ubyte",
			trainImages, trainLabels, trainSize, trainRows, trainCols)) {
		cerr<<"error"<<endl;
		return -1;
	}
	cout<<"Number of images in training are : "<<trainSize<<endl;
	cout<<"Number of Rows in training are : "<<trainRows<<endl;
	cout<<"Number of Cols in training are : "<<trainCols<<endl;
	if (readData("/home/roni/lenetPrac/t10k-images-idx3-ubyte", "/home/roni/lenetPrac/t10k-labels-idx1-ubyte",
			testImages, testLabels, testSize,testRows, testCols)) {
		cerr<<"error"<<endl;
		return -1;
	}
	cout<<"Number of images in testing are"<<testSize<<endl;
	cout<<"Number of Rows in testing are : "<<testRows<<endl;
	cout<<"Number of Cols in testing are : "<<testCols<<endl;
	return 0;
}