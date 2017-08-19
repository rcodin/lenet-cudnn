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

int readData(char *imagesFilePath, char *labelsFilePath,
	uint8_t *data, uint8_t *labels, size_t &numImages, size_t &rows, size_t &cols)
{
	FILE* imagesFile;
	FILE* labelsFile;

	struct ImageMetaData imagesHeader;
	struct LabelMetaData labelsHeader;	

	imagesFile = fopen (imagesFilePath , "rb" );	
	if (imagesFile == NULL) {
		cerr<<"Unable to read image file"<<endl;
		return -1;
	}



	labelsFile = fopen (labelsFilePath, "rb" );
	if (labelsFile == NULL) {
		cerr<<"Unable to read Labels file"<<endl;
		return -1;
	}

	//getting the header
	if (fread(&imagesHeader, sizeof(ImageMetaData), 1, imagesFile) != 1)
	{
		cerr<<"Unable to get the Image Meta Data"<<endl;
		return -1;
	}
	imagesHeader.swap();
	data = (uint8_t*)malloc(sizeof(uint8_t) * imagesHeader.numImages * imagesHeader.numRows * imagesHeader.numCols);
	if (imagesHeader.magicNum != IMAGE_MAGIC_NUM)
	{
		cerr<<"Err in train image file"<<endl;
		return -1;
	}

	if (fread(&labelsHeader, sizeof(LabelMetaData), 1, labelsFile) != 1)
	{
		cerr<<"Unable to get the Image Meta Data"<<endl;
		return -1;
	}
	labelsHeader.swap();

	labels = (uint8_t*)malloc(sizeof(uint8_t) * labelsHeader.numLabels);
	if (labelsHeader.magicNum != LABEL_MAGIC_NUM)
	{
		cerr<<"Err in train image file"<<endl;
		return -1;
	}

	rows = imagesHeader.numRows;
	cols = imagesHeader.numCols;
	numImages = imagesHeader.numImages;
	// Read images and labels (if requested)
    if (data != nullptr)
    {
        if (fread(data, sizeof(uint8_t), imagesHeader.numImages * rows * cols, imagesFile)
        											!= imagesHeader.numImages * rows * cols)
        {
            printf("ERROR: Invalid dataset file (partial image dataset)\n");
            return 0;
        }
    }
    if (labels != nullptr)
    {
        if (fread(labels, sizeof(uint8_t), labelsHeader.numLabels , labelsFile)
        												!= labelsHeader.numLabels)
        {
            printf("ERROR: Invalid dataset file (partial label dataset)\n");
            return 0;
        }
    }
    
	fclose(imagesFile);
	fclose(labelsFile);
	return 0;	
}