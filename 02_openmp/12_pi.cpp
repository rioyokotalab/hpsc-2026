#include <cstdio>

int main() {
  int n = 10;
  double dx = 1. / n;
  double pi_int[n], tmp[n];
  double *pi = pi_int + n - 1;
  for (int i=0; i<n; i++)
  {
    double x = (i + 0.5) * dx;
    pi_int[i] = 4.0 / (1.0 + x * x) * dx;
  }
#pragma omp parallel
  {
    for (int j=1; j<n; j<<=1)
    {
#pragma omp for
      for(int i=0; i<n; i++)
	tmp[i] = pi_int[i];

#pragma omp for
      for(int i=j; i<n; i++)
	pi_int[i] += tmp[i-j];
    }
  }
  printf("%17.15f\n",*pi);
}
