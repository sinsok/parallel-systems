#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "header.h"


short evolution_has_stopped = FALSE;


/*
double filter[FILTER_HEIGHT][FILTER_WIDTH] = {
		  -1, -1,  0,
		    -1,  0,  1,
		     0,  1,  1
};
*/

double filter[FILTER_HEIGHT][FILTER_WIDTH] = {
		{0.0625,	0.125,	0.0625},
		{0.125, 	0.25, 	0.125},
		{0.0625, 	0.125,	0.0625}
	};


//////////////////////////////////////////////////////////////////////
//////// Gray filtering //////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

void filter_gray_array(gray_array* arr) {
	int i, j;
	gray_array newArray = create_gray_array();

	for (i=0; i<IMAGE_HEIGHT; i++)
		for (j=0; j<IMAGE_WIDTH; j++)
			newArray[i][j] = filter_gray_pixel(*arr, i, j);

	if (gray_array_evolution(*arr, newArray) == FALSE)
		evolution_has_stopped = TRUE;

	gray_array tempArray = *arr;
	*arr = newArray;
	destroy_gray_array(tempArray);

	return;
}


gray_pixel filter_gray_pixel(gray_array arr, int x, int y) {
	gray_pixel newPixel = 0;

	// by using double variable for new element calculations
	// we lose less decimal digits
	// (output image will be much darker if not use this double)
	double tempPixel = 0.0;

	//--- up-left ---//
	tempPixel += arr[(IMAGE_HEIGHT + x-1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y-1)%IMAGE_WIDTH] * filter[0][0];
	//--- up-center ---//
	tempPixel += arr[(IMAGE_HEIGHT+x-1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y)%IMAGE_WIDTH] *filter[0][1];
	//--- up-right ---//
	tempPixel += arr[(IMAGE_HEIGHT+x-1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y+1)%IMAGE_WIDTH] *filter[0][2];
	//--- left ---//
	tempPixel += arr[(IMAGE_HEIGHT+x)%IMAGE_HEIGHT][(IMAGE_WIDTH+y-1)%IMAGE_WIDTH] *filter[1][0];
	//--- right ---//
	tempPixel += arr[(IMAGE_HEIGHT+x)%IMAGE_HEIGHT][(IMAGE_WIDTH+y+1)%IMAGE_WIDTH] *filter[1][2];
	//--- down-left ---//
	tempPixel += arr[(IMAGE_HEIGHT+x+1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y-1)%IMAGE_WIDTH] *filter[2][0];
	//--- down ---//
	tempPixel += arr[(IMAGE_HEIGHT+x+1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y)%IMAGE_WIDTH] *filter[2][1];
	//--- down-right ---//
	tempPixel += arr[(IMAGE_HEIGHT+x+1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y+1)%IMAGE_WIDTH] *filter[2][2];
	//--- center ---//
	tempPixel += arr[ x ][ y ] * filter[1][1];

	newPixel = (int)tempPixel;

	if (newPixel > MAX_PIXEL_VALUE)
		return MAX_PIXEL_VALUE;
	else if (newPixel< MIN_PIXEL_VALUE)
		return MIN_PIXEL_VALUE;

	return newPixel;
}




////////////////////////////////////////////////////////////////////
//////// Colored filtering /////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void filter_colored_array(colored_array* arr) {
	int i, j;
	colored_pixel pixel;
	colored_array newArray = create_colored_array();

	for (i=0; i<IMAGE_HEIGHT; i++) {
		for (j=0; j<IMAGE_WIDTH; j++) {
			pixel = filter_colored_pixel(*arr, i, j);
			newArray[i][j].red = pixel.red;
			newArray[i][j].green = pixel.green;
			newArray[i][j].blue = pixel.blue;
		}
	}
	if (colored_array_evolution(*arr, newArray) == FALSE)
		evolution_has_stopped = TRUE;

	colored_array tempArray = *arr;
	*arr = newArray;
	destroy_colored_array(tempArray);

	return;
}


colored_pixel filter_colored_pixel(colored_array arr, int x, int y) {
	colored_pixel newPixel;
	newPixel.red = 0;
	newPixel.green = 0;
	newPixel.blue = 0;

	// by using double variable for new element calculations
	// we lose less decimal digits
	// (output image will be much darker if not use this double)
	double tempRed=0;
	double tempGreen=0;
	double tempBlue=0;


	//--- up-left ---//
	tempRed += arr[(IMAGE_HEIGHT + x-1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y-1)%IMAGE_WIDTH].red * filter[0][0];
	tempGreen += arr[(IMAGE_HEIGHT + x-1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y-1)%IMAGE_WIDTH].green * filter[0][0];
	tempBlue += arr[(IMAGE_HEIGHT + x-1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y-1)%IMAGE_WIDTH].blue * filter[0][0];
	//--- up-center ---//
	tempRed += arr[(IMAGE_HEIGHT+x-1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y)%IMAGE_WIDTH].red *filter[0][1];
	tempGreen += arr[(IMAGE_HEIGHT+x-1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y)%IMAGE_WIDTH].green *filter[0][1];
	tempBlue += arr[(IMAGE_HEIGHT+x-1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y)%IMAGE_WIDTH].blue *filter[0][1];
	//--- up-right ---//
	tempRed += arr[(IMAGE_HEIGHT+x-1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y+1)%IMAGE_WIDTH].red *filter[0][2];
	tempGreen += arr[(IMAGE_HEIGHT+x-1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y+1)%IMAGE_WIDTH].green *filter[0][2];
	tempBlue += arr[(IMAGE_HEIGHT+x-1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y+1)%IMAGE_WIDTH].blue *filter[0][2];
	//--- left ---//
	tempRed += arr[(IMAGE_HEIGHT+x)%IMAGE_HEIGHT][(IMAGE_WIDTH+y-1)%IMAGE_WIDTH].red *filter[1][0];
	tempGreen += arr[(IMAGE_HEIGHT+x)%IMAGE_HEIGHT][(IMAGE_WIDTH+y-1)%IMAGE_WIDTH].green *filter[1][0];
	tempBlue += arr[(IMAGE_HEIGHT+x)%IMAGE_HEIGHT][(IMAGE_WIDTH+y-1)%IMAGE_WIDTH].blue *filter[1][0];
	//--- right ---//
	tempRed += arr[(IMAGE_HEIGHT+x)%IMAGE_HEIGHT][(IMAGE_WIDTH+y+1)%IMAGE_WIDTH].red *filter[1][2];
	tempGreen += arr[(IMAGE_HEIGHT+x)%IMAGE_HEIGHT][(IMAGE_WIDTH+y+1)%IMAGE_WIDTH].green *filter[1][2];
	tempBlue += arr[(IMAGE_HEIGHT+x)%IMAGE_HEIGHT][(IMAGE_WIDTH+y+1)%IMAGE_WIDTH].blue *filter[1][2];
	//--- down-left ---//
	tempRed += arr[(IMAGE_HEIGHT+x+1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y-1)%IMAGE_WIDTH].red *filter[2][0];
	tempGreen += arr[(IMAGE_HEIGHT+x+1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y-1)%IMAGE_WIDTH].green *filter[2][0];
	tempBlue += arr[(IMAGE_HEIGHT+x+1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y-1)%IMAGE_WIDTH].blue *filter[2][0];
	//--- down ---//
	tempRed += arr[(IMAGE_HEIGHT+x+1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y)%IMAGE_WIDTH].red *filter[2][1];
	tempGreen += arr[(IMAGE_HEIGHT+x+1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y)%IMAGE_WIDTH].green *filter[2][1];
	tempBlue += arr[(IMAGE_HEIGHT+x+1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y)%IMAGE_WIDTH].blue *filter[2][1];
	//--- down-right ---//
	tempRed += arr[(IMAGE_HEIGHT+x+1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y+1)%IMAGE_WIDTH].red *filter[2][2];
	tempGreen += arr[(IMAGE_HEIGHT+x+1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y+1)%IMAGE_WIDTH].green *filter[2][2];
	tempBlue += arr[(IMAGE_HEIGHT+x+1)%IMAGE_HEIGHT][(IMAGE_WIDTH+y+1)%IMAGE_WIDTH].blue *filter[2][2];
	//--- center ---//
	tempRed += arr[ x ][ y ].red * filter[1][1];
	tempGreen += arr[ x ][ y ].green * filter[1][1];
	tempBlue += arr[ x ][ y ].blue * filter[1][1];


	newPixel.red = (int)tempRed;
	newPixel.green = (int)tempGreen;
	newPixel.blue = (int)tempBlue;

	if (newPixel.red > MAX_PIXEL_VALUE) newPixel.red = MAX_PIXEL_VALUE;
	else if (newPixel.red < MIN_PIXEL_VALUE) newPixel.red = MIN_PIXEL_VALUE;

	if (newPixel.green > MAX_PIXEL_VALUE) newPixel.green = MAX_PIXEL_VALUE;
	else if (newPixel.green < MIN_PIXEL_VALUE) newPixel.green = MIN_PIXEL_VALUE;

	if (newPixel.blue > MAX_PIXEL_VALUE) newPixel.blue = MAX_PIXEL_VALUE;
	else if (newPixel.blue < MIN_PIXEL_VALUE) newPixel.blue = MIN_PIXEL_VALUE;

	return newPixel;
}




