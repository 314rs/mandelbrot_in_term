#include <stdio.h>
#include <math.h>

#define W (80)
#define H (80)
#define N_MAX (11)
#define X_MAX (1)
#define X_MIN (-2)
#define Y_MAX (1.5)
#define Y_MIN (-1.5)


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
	char* bild = (int*) malloc(W * H * sizeof(int));
	
	
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
			bild[cmd_y * W + cmd_x] = pixels[iteration];
		}
	}
	
	
	//das Bild speichern:
	for (int x = 0; x < H; x++) {
		for (int y = 0; y < W; y++) {
			fprintf(bild[i]);
		}
		printf("");
	}
	
	//den Speicherplatz wieder freigeben:
	free(bild);
	
	return(0);
}