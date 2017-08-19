#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstddef>

int readData(char *imagesFilePath, char *labelsFilePath,
	uint8_t *data, uint8_t *labels, size_t &numImages, size_t &rows, size_t &cols);