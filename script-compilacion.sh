#!/bin/env bash

cat > programa.c << EOF

#include <stdio.h>

double powern(double d, unsigned n) {
  double x = 1.0;
  unsigned j;
 
 for (j = 1; j <= n; j++) {
    x *= d;
  }

  return x;
}

int main() {
  double sum = 0.0;
  unsigned i;
  
 for (i = 1; i <= 1000000000; i++) {
    sum += powern (i, i % 5);
  }
  
  printf ("sum = %g\n", sum);
  
  return 0;
}

EOF

echo "Compilando y ejecutando sin optimizacion"

gcc -Wall -O0 programa.c -lm -o programa
ls -l programa
time ./programa
rm -f programa
echo ""

echo "Compilando y Optimizando nivel 1"

gcc -Wall -O1 programa.c -lm -o programa
ls -l programa
time ./programa
rm -f programa
echo ""
