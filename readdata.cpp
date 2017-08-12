#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstddef>

//we have to swap the order because the files are in big endian and x86-64 is little endian
#define IMAGE_MAGIC_NUM 2051
#define LABEL_MAGIC_NUM 2049

#define u32swap(x) __builtin_bswap32(x);

struct ImageMetaData {
	uint32_t magicNum;
	uint32_t numImages;
	uint32_t numRows;
	uint32_t numCols;
	//swaps all variable endianess
	void swap()
	{
		magicNum = u32swap(magicNum);
		numImages = u32swap(numImages);
		numRows = u32swap(numRows);
		numCols = u32swap(numCols);
	}
};

struct LabelMetaData {
	uint32_t magicNum;
	uint32_t numLabels;
	void swap()
	{
		magicNum = u32swap(magicNum);
		numLabels = u32swap(numLabels);
	}
};


using namespace std;
int main()
{
	FILE* trainImages;
	FILE* trainLabels;
	FILE* testImages;
	FILE* testLabels;

	struct ImageMetaData trainImageMData;
	struct ImageMetaData testImageMData;
	
	struct LabelMetaData trainLabelMData;
	struct LabelMetaData testLabelMData;
	// uint32_t magicTrainImages;

	//reading the files from disks
	trainImages = fopen ("/home/roni/lenetPrac/train-images-idx3-ubyte" , "rb" );	
	if (trainImages == NULL) {
		cerr<<"Unable to read train image file"<<endl;
		return -1;
	}

	trainLabels = fopen ("/home/roni/lenetPrac/train-labels-idx1-ubyte" , "rb" );
	if (trainLabels == NULL) {
		cerr<<"Unable to read train Labels file"<<endl;
		return -1;
	}
	
	testImages = fopen ("/home/roni/lenetPrac/t10k-images-idx3-ubyte" , "rb" );
	if (testImages == NULL) {
		cerr<<"Unable to open test image files"<<endl;
		return -1;
	}

	testLabels = fopen ("/home/roni/lenetPrac/t10k-labels-idx1-ubyte" , "rb" );
	if (testLabels == NULL) {
		cerr<<"Unable to open test Labels file"<<endl;
		return -1;
	}


	//getting the metadata
	if (fread(&trainImageMData, sizeof(ImageMetaData), 1, trainImages) != 1)
	{
		cerr<<"Unable to get the train Image Meta Data"<<endl;
		return -1;
	}
	trainImageMData.swap();
	if (trainImageMData.magicNum != IMAGE_MAGIC_NUM)
	{
		cerr<<"Err in train image file"<<endl;
		return -1;
	}

	if (fread(&trainLabelMData, sizeof(LabelMetaData), 1, trainLabels) != 1)
	{
		cerr<<"Unable to get the Meta Data"<<endl;
		return -1;
	}
	trainLabelMData.swap();
	if (trainLabelMData.magicNum != LABEL_MAGIC_NUM) {
		cerr<<"Err in train label file"<<endl;
		return -1;
	}
	if (fread(&testImageMData, sizeof(ImageMetaData), 1, testImages) != 1)
	{
		cerr<<"Unable to get the Meta Data"<<endl;
		return -1;
	}
	if (fread(&testLabelMData, sizeof(LabelMetaData), 1, testLabels) != 1)
	{
		cerr<<"Unable to get the Meta Data"<<endl;
		return -1;
	}

}