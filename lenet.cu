#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "readdata.h"

#include <cudnn.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <cuda.h>
using namespace std;

struct ConvolutionLayer {
	int in_channels, out_channels, kernel_size;
	int in_hight, out_hight, in_width, out_width;
	//here stride is 1
	ConvolutionLayer(int in_channels_, int out_channels_, int kernel_size_,
				int kernel_size_, int in_hight_, int in_width_) {
		in_channels = in_channels_;
		out_channels = out_channels_;
		kernel_size = kernel_size_;
		in_hight = in_hight_;
		in_width = in_width_;
		out_hight = in_hight_ - kernel_size_ + 1;
		out_width = in_width_ - kernel_size_ + 1;
	}
};
struct PoolingLayer {
	int size, stride;
	PoolingLayer(int size_,int stride_) {
		size = size_;
		stride = stride_;
	}
};
struct FullyConnectedLayer {
	int inputs, outputs;
	FullyConnectedLayer(int inputs_, int outputs_) {
		inputs = inputs_;
		outputs = outputs_;
	}
}
struct TrainingContext {
	int batch_size;

}
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
	// cout<<"Number of images in training are : "<<trainSize<<endl;
	// cout<<"Number of Rows in training are : "<<trainRows<<endl;
	// cout<<"Number of Cols in training are : "<<trainCols<<endl;
	if (readData("/home/roni/lenetPrac/t10k-images-idx3-ubyte", "/home/roni/lenetPrac/t10k-labels-idx1-ubyte",
			testImages, testLabels, testSize,testRows, testCols)) {
		cerr<<"error"<<endl;
		return -1;
	}
	// cout<<"Number of images in testing are"<<testSize<<endl;
	// cout<<"Number of Rows in testing are : "<<testRows<<endl;
	// cout<<"Number of Cols in testing are : "<<testCols<<endl;
	ConvolutionLayer conv1(1, 20, 5, trainRows, trainCols);
	PoolingLayer pool1(2,2);
	ConvolutionLayer conv2(conv1.out_channels, 50, 5, conv1.out_hight/pool1.stride, conv2.out_width/pool1.stride);
	PoolingLayer pool2(2,2);


	return 0;
}