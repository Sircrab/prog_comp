#include <bits/stdc++.h>
using namespace std;
 
double integral(double a, double b, int k, double (*f)(double)){
  double dx, x, t;
  int i;
  dx = (b-a)/(2.0*k);
  t = 0;
  for( i=0; i<k; i++ ) {
    t += (i==0 ? 1.0 : 2.0) * (*f)(a+2.0*i*dx);
    t += 4.0 * (*f)(a+(2.0*i+1.0)*dx);
  }
  t += (*f)(b);
  return t * (b-a)/6.0/k;
}
 
double x2(double x) {
    return x * x;
}
 
int main(int argc, char** argv) {
    for (int i = 1; i <= 10; i++) {
        printf("k = %d, val = %f\n", i, integral(0, 10, i, x2));
    }
    return 0;
}