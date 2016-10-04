#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"



int main() {


	color_plot();
	//gray_plot();

	return 0;
}






/// Code for colored image ///
//////////////////////////////

void color_plot() {
	int counter = 0;

	colored_array arr;
	read_colored_image(&arr);
	printf("\nFiltering image, please wait...");
	while ((evolution_has_stopped == FALSE) && (counter++ < NUM_OF_FILTERINGS)) {
		filter_colored_array(&arr);
		printf("\nImage filtered %d times", counter);
	}
	write_colored_image(arr);
	destroy_colored_array(arr);

	return;
}


/// Code for gray image //////
//////////////////////////////
void gray_plot() {

	int counter = 0;
		gray_array arr;
		read_gray_image(&arr);
		printf("\nFiltering image, please wait...");
		while ((evolution_has_stopped == FALSE) && (counter++ < NUM_OF_FILTERINGS)) {
			filter_gray_array(&arr);
			printf("\nImage filtered %d times", counter);
		}
		write_gray_image(arr);
		destroy_gray_array(arr);

	return;
}
