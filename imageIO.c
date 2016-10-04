#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"



///////// Gray image I/O ////////////////////////////////////
/////////////////////////////////////////////////////////////

void read_gray_image(gray_array* arr) {
	int i, j;
	FILE* fpIn;

	*arr = create_gray_array();

	fpIn = fopen("waterfall_grey_1920_2520.raw", "rb");
	if (fpIn == NULL) {
		perror("Error while opening the file.\n");
		return;
	}
	for (i=0; i<IMAGE_HEIGHT; i++)
		for (j=0; j<IMAGE_WIDTH; j++)
			fread(&((*arr)[i][j]), sizeof(char), 1, fpIn);

	fclose(fpIn);
	printf("\nSuccessfully read %d x %d *.raw file", IMAGE_HEIGHT, IMAGE_WIDTH);

	return;
}



void write_gray_image(gray_array arr) {
	int i, j;
	FILE* fpOut;

	fpOut = fopen("grey_output.raw", "w+b");
	if (fpOut == NULL) {
		perror("Error while opening the file.\n");
		return;
	}
	for (i=0; i<IMAGE_HEIGHT; i++)
		for (j=0; j<IMAGE_WIDTH; j++)
			fwrite(&(arr[i][j]), sizeof(char), 1, fpOut);

	fclose(fpOut);
	printf("\nSuccessfully written filtered image to *output.raw file\n");

	return;
}




///////// Colored image I/O //////////////////////////////////
/////////////////////////////////////////////////////////////

void read_colored_image(colored_array* arr) {
	int i, j;
	FILE* fpIn;

	*arr = create_colored_array();

	fpIn = fopen("waterfall_1920_2520.raw", "rb");
	if (fpIn == NULL) {
		perror("Error while opening the file.\n");
		exit(0);
	}

	for (i=0; i<IMAGE_HEIGHT; i++)
		for (j=0; j<IMAGE_WIDTH; j++) {
			fread(&((*arr)[i][j].red), sizeof(char), 1, fpIn);
			fread(&((*arr)[i][j].green), sizeof(char), 1, fpIn);
			fread(&((*arr)[i][j].blue), sizeof(char), 1, fpIn);
		}

	fclose(fpIn);

	printf("\nSuccessfully read %dx%d *.raw file", IMAGE_HEIGHT, IMAGE_WIDTH);

	return;
}


void write_colored_image(colored_array arr) {
	int i, j;
	FILE* fpOut;

	fpOut = fopen("colored_output.raw", "w+b");
	if (fpOut == NULL) {
		perror("Error while opening the file.\n");
		return;
	}
	for (i=0; i<IMAGE_HEIGHT; i++)
		for (j=0; j<IMAGE_WIDTH; j++) {
			fwrite(&(arr[i][j].red), sizeof(char), 1, fpOut);
			fwrite(&(arr[i][j].green), sizeof(char), 1, fpOut);
			fwrite(&(arr[i][j].blue), sizeof(char), 1, fpOut);
		}
	fclose(fpOut);
	printf("\nSuccessfully written filtered image to *output.raw file\n");

	return;
}



