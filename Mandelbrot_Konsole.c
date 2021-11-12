#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//zoom out as far as possible to appreceate the beauty of the mandelbrot fractal
#define W (1000)
#define H (333)
#define N_MAX (50)
#define ALL
#ifdef ALL
#define X_MAX (1)
#define X_MIN (-2)
#define Y_MAX (1.5)
#define Y_MIN (-1.5)
#else
#define X_MAX (-0.25)
#define X_MIN (-0.75)
#define Y_MAX (1)
#define Y_MIN (0.5)
#endif


void toMath(int cmd_x, int cmd_y, double* math_x, double* math_y) {
	*math_x = ((double)(cmd_x * (X_MAX - X_MIN)) / W) + X_MIN;
	*math_y = ((double)((H - cmd_y) * (Y_MAX - Y_MIN)) / H) + Y_MIN;
}

void toCMD(double math_x, double math_y, int* cmd_x, int* cmd_y) {
	*cmd_x = ((math_x - X_MIN) / (X_MAX - X_MIN)) * W;
	*cmd_y = -((((math_y - Y_MIN) / (Y_MAX - Y_MIN)) * H) - H);
	
	if (*cmd_y < 0) {
		*cmd_y = 0;
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
	//Variablen für die Umwandlung der Koordinatensysteme
	double math_x, math_y;
	int cmd_x, cmd_y;
	char*  pixels = ".,-~:;=!*#$@";
	
		
	//Speicherplatz für das Bild allokieren
		//int size = W * H;
	char* bild = (char*) malloc(W * H * sizeof(char));
	
	
	// weise jeder Rückgabe der mandelbrot-Funktion eine eigene Farbe zu.
	int iteration;
	int color;
	for (cmd_x = 0; cmd_x < W; cmd_x++) {
		for (cmd_y = 0; cmd_y < H; cmd_y++) {
			toMath(cmd_x, cmd_y, &math_x, &math_y);
			iteration = mandelbrot(0.0, 0.0, N_MAX, math_x, math_y);
			
			/*if (iteration >= N_MAX){
				color = COLOR_BLACK;
			} else {
				color = (((double)  (iteration)) / ((double) N_MAX)) * 0x00FFFFFF;
			}*/
			bild[cmd_y * W + cmd_x] = pixels[(int) iteration * 11 / N_MAX];
		}
	}
	
	
	//das Bild speichern:
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			printf("%c", bild[y*W+x]);
		}
		printf("\n");
	}
	
	//den Speicherplatz wieder freigeben:
	free(bild);
	
	return(0);
}