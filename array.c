/*
 * array.c
 *
 *  Created on: Feb 26, 2015
 *      Author: sinnaig
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"


//////////////////////////////////////////////////////////////////////
/// checking if gray array of new generation is the same /////////////
int gray_array_evolution(gray_array oldArray, gray_array newArray) {
	int i, j;

	for (i=0; i<IMAGE_HEIGHT; i++)
		for (j=0; j<IMAGE_WIDTH; j++)
			// if any pixel has changed, then array still evolving
			if (oldArray[i][j] != newArray[i][j]) {
				return TRUE;
			}
	return FALSE;
}


///////////////////////////////////////////////////////////////////////////////
/// checking if colored array of new generation is the same ///////////////////
int colored_array_evolution(colored_array oldArray, colored_array newArray) {
	int i, j;

	for (i=0; i<IMAGE_HEIGHT; i++)
		for (j=0; j<IMAGE_WIDTH; j++)
			// if any value of RGB has changed, then array still evolving
			if ( (oldArray[i][j].red != newArray[i][j].red) || (oldArray[i][j].green != newArray[i][j].green) || (oldArray[i][j].blue != newArray[i][j].blue) )
				return TRUE;
	return FALSE;
}




void destroy_gray_array(gray_array arr) {
	int i;
	for (i=0; i<IMAGE_HEIGHT; i++)
		free(arr[i]);
	free(arr);
}


void destroy_colored_array(colored_array arr) {
	int i;
	for (i=0; i<IMAGE_HEIGHT; i++)
		free(arr[i]);
	free(arr);

}


colored_array create_colored_array() {
	int i;

	colored_array newArray = malloc(sizeof(colored_pixel*)*IMAGE_HEIGHT);
	for (i=0; i<IMAGE_HEIGHT; i++)
		newArray[i] = malloc(sizeof(colored_pixel)*IMAGE_WIDTH);

	return newArray;
}

gray_array create_gray_array() {
	int i;

	gray_array newArray = malloc(sizeof(int*) * IMAGE_HEIGHT);
	for (i=0; i<IMAGE_HEIGHT; i++)
		newArray[i] = malloc(sizeof(gray_pixel) * IMAGE_WIDTH);

	return newArray;
}


void printArray(gray_array arr) {
	int i, j;
	for (i=0; i<IMAGE_HEIGHT; i++) {
		printf("\n");
		for (j=0; j<IMAGE_WIDTH; j++)
;//			printf(" %.2f ", arr[i][j]);
	}
}

void initArray(gray_array* arr) {

	int i, j;
	for (i=0; i<IMAGE_HEIGHT; i++)
		for (j=0; j<IMAGE_WIDTH; j++)
			(*arr)[i][j] = i*j+20.3;

}


void breakLine(){
	printf("\n");
}


