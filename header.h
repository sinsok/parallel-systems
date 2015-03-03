
#ifndef HEADER_
#define HEADER_

#define MAX_PIXEL_VALUE 255
#define MIN_PIXEL_VALUE 0
#define IMAGE_HEIGHT 2520
#define IMAGE_WIDTH 1920
#define FILTER_HEIGHT 3
#define FILTER_WIDTH 3
#define NUM_OF_FILTERINGS 10
#define TRUE 1
#define FALSE 0

extern double filter[FILTER_HEIGHT][FILTER_WIDTH];
extern short evolution_has_stopped;

typedef int gray_pixel;
typedef int** gray_array;
typedef struct Colored_pixel colored_pixel;
typedef struct Colored_pixel** colored_array;

struct Colored_pixel {
	int red;
	int green;
	int blue;
};

void filter_gray_array(gray_array*);
gray_pixel filter_gray_pixel(gray_array, int, int);
void filter_colored_array(colored_array*);
colored_pixel filter_colored_pixel(colored_array, int, int);
void read_gray_image(gray_array*);
void read_colored_image(colored_array*);
void write_gray_image(gray_array);
void write_colored_image(colored_array);
gray_array create_gray_array();
colored_array create_colored_array();
void destroy_gray_array(gray_array);
void destroy_colored_array(colored_array);

int gray_array_evolution(gray_array, gray_array);
int colored_array_evolution(colored_array, colored_array);

void gray_plot();
void color_plot();





#endif /* HEADER_ */


