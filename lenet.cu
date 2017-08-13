#include <iostream>

#include <cudnn.h>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <cuda.h>

int main()
{
	char* string;
	cudaMalloc(&string, 1000*size(char));
}