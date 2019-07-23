#include <math.h>
int N = 16;
#define PI 3.14159265
#define exp 2.7182818
float C[16][16];
float S[16][16];
float X[16];
float G[16];

float MagSf[16][16];
float Mfft[16];
float d = 0;




/*FFT(x) {
  n=length(x);
  if (n==1) return x;
  m = n/2;
  X = (x_{2j})_{j=0}^{m-1};
  Y = (x_{2j+1})_{j=0}^{m-1};
  X = FFT(X);
  Y = FFT(Y);
  U = (X_{k mod m})_{k=0}^{n-1};
  V = (g^{-k}Y_{k mod m})_{k=0}^{n-1};
  return U+V;
}*/

void init_ComplexExp(){	
// sets up e^{-j2PI ln/N}
// where n is the time index
// and where l is the frequency index
	for (int n = 0; n < N; ++n)
	{
		for (int l = 0; l < N; ++l)
		{
			
			C[n][l] = cos(2*PI*n*l/N);
			S[n][l] = -1*sin(2*PI*n*l/N);
		}
	}
}


void init_GaborWindow(){
//choice of Gabor window
//where n is the time index
	for (int n = 0; n < N-1; ++n)
	{
		G[n] = pow(exp,-1*pow(n-N/2,2));
	}
}

void init_Data(){
//data where n is the time index
	for (int n = 0; n < N; ++n)
	{
		X[n] = 5.0 + 2.0*sin(2*PI*n/N) + 3.0*cos(4*PI*n/N) +10 * pow(exp,-1*pow((n-N/2)*2,2)) ;//+ 9.0*cos(16*PI*PI*n/N);
		//X[n] = 5.0 + sinh(2.0*n/N);
		//X[n] = 5.0 + 3.0*cos(4*PI*n/N + 12.0*cos(4*PI*n/N));
	}
}

void DFT(){
	for (int j = 0; j < N; ++j)
	{	float Sum[] = {0.0,0.0};
	
		for (int i = 0; i < N; ++i)
			{
				Sum[0] = X[i]*C[i][j] + Sum[0];
				Sum[1] = X[i]*S[i][j] + Sum[1];
	 	 
			}
				//Rfft[j] = Sum[0];
				//Ifft[j] = Sum[1];
			Mfft[j] = 2*sqrt(pow(Sum[0],2) + pow(Sum[1],2))/N;
		}
	Mfft[0] = Mfft[0]/2;
}

//pow(exp,-1*pow((n-m),2))
void GaborTransform(){
// n is the time index
// l is the frequency index
// m is the center of the time window

	for (int m = 0; m < N; ++m)
	{

		for (int l = 0; l < N; ++l)
			{	double Sum[] = {0.0,0.0};

			for (int n = 0; n < N; ++n)
				{
				// integrating the real part
				Sum[0] = X[n]*pow(exp,-1*pow((n-m),2))*C[n][l] + Sum[0];
				// integrating the imaginary part
				Sum[1] = X[n]*pow(exp,-1*pow((n-m),2))*S[n][l] + Sum[1];
 	 
				}
			// The divide by N here is the dt of the integral
			MagSf[m][l] = 2*sqrt(pow(Sum[0],2) + pow(Sum[1],2))/N;

			}
			MagSf[m][0] = MagSf[m][0]/2; 
	}
}

