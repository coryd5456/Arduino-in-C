#include <stdio.h>
#include "GaborTransform.h"


int main(int argc, char const *argv[])
{
	
	init_ComplexExp();
	init_Data();
	init_GaborWindow();
	DFT();
	GaborTransform();

	printf("This is the chosen Gabor Window\n");
	printf("[ ");
	for (int i = 0; i < N; ++i)
	{
		printf("%lf  ", G[i] );
	}
	printf(" ]\n");


	printf("This is the Data Set\n");
	printf("[ ");
	for (int i = 0; i < N; ++i)
	{
		printf("%lf  ", X[i] );
	}
	printf(" ]\n");

	printf("This is the Discrete Fourier Transform of the Data\n");
	printf("[ ");
	for (int i = 0; i < N; ++i)
	{
		printf("%lf  ", Mfft[i] );
	}
	printf(" ]\n");

	printf("This is the Magnitude of the Gabor Transform of the Data \n");
	//note: the X axis is time, and the Y axis is frequency
	for (int l = 0; l < N; ++l)
	{
	printf("[ ");
		for (int m = 0; m < N; ++m)
		{
			printf("%lf  ", MagSf[m][l] );
		}
	printf(" ]\n");
	}
	

	return 0;
}

