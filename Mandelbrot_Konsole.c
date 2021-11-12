#include "libBMP.h"
#include <stdio.h>
#include <math.h>

#define N_MAX (100)

#define W (10000)
#define H (10000)
#define X_MAX (1)
#define X_MIN (-2)
#define Y_MAX (1.5)
#define Y_MIN (-1.5)


void toMath(int bmp_x, int bmp_y, double* math_x, double* math_y) {
	*math_x = ((double)(bmp_x * (X_MAX - X_MIN)) / W) + X_MIN;
	*math_y = ((double)((H - bmp_y) * (Y_MAX - Y_MIN)) / H) + Y_MIN;
}

void toBMP(double math_x, double math_y, int* bmp_x, int* bmp_y) {
	*bmp_x = ((math_x - X_MIN) / (X_MAX - X_MIN)) * W;
	*bmp_y = -((((math_y - Y_MIN) / (Y_MAX - Y_MIN)) * H) - H);
	
	if (*bmp_y < 0) {
		*bmp_y = 0;
	}
}// aus Blatt 6

unsigned int mandelbrot(double x, double y, int max_iteration, double x0, double y0) {
	if ((sqrt((x * x) + (y * y)) >= 2) || max_iteration <= 0) {
		return(0); //Wenn eine Abbruchbedingung erreicht ist, melde 0 an die übergeordnete Rekursion
	} else {
		return(mandelbrot(((x * x) - (y * y)) + x0, (2 * x * y) + y0, (max_iteration - 1), x0, y0) + 1); // Rekursion. 
	}
}



int main(void) {
	printf("mandelbrot(0.1, 0.1, N_MAX) = %d\n", mandelbrot(0.0, 0.0, N_MAX, 0.1, 0.1));
	printf("mandelbrot(1.0, 1.0, N_MAX) = %d", mandelbrot(0.0, 0.0, N_MAX, 1.0, 1.0));
	printf("mandelbrot(-2.0, 1.0, N_MAX) = %d", mandelbrot(0.0, 0.0, N_MAX, -2.0, 1.0));
	
	//Variablen für die Umwandlung der Koordinatensysteme
	double math_x, math_y;
	int bmp_x, bmp_y;
	
		
	//Speicherplatz für das Bild allokieren
		//int size = W * H;
	uint32_t* bild = (uint32_t*) malloc(W * H * sizeof(uint32_t));
	
	
	// weise jeder Rückgabe der mandelbrot-Funktion eine eigene Farbe zu.
	int iteration;
	int color;
	for (bmp_x = 0; bmp_x < W; bmp_x++) {
		for (bmp_y = 0; bmp_y < H; bmp_y++) {
			toMath(bmp_x, bmp_y, &math_x, &math_y);
			iteration = mandelbrot(0.0, 0.0, N_MAX, math_x, math_y);
			
			if (iteration >= N_MAX){
				color = COLOR_BLACK;
			} else {
				color = (((double)  (iteration)) / ((double) N_MAX)) * 0x00FFFFFF;
			}
			bild[bmp_y * W + bmp_x] = (int) color;
		}
	}
	
	
	//das Bild speichern:
	bmp_create("Mandelbrot.bmp", bild, W, H);
	
	//den Speicherplatz wieder freigeben:
	free(bild);
	
	return(0);
}