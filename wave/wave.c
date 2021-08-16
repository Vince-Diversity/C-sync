#include "wave.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Implement functions here */

graph give_example(void) {
  graph sine;
  double ** pu = (double **) malloc(sizeof(double *));
  double * py = (double *) malloc(M * sizeof(double));

  int i;
  double xi;
  double dN = (double) 1/(M-1);
  for (i = 0; i < M; i++) {
    xi = (double) (i+1) * dN;
    sine.x[i] = xi;
    py[i] = sin(2*M_PI*xi); // same as *(py + i)
  }
//  pu = &py; // error when freeing because it assignes pu instead
  pu[0] = py;
  sine.pu = pu;
  sine.N = 1;
  return sine;
}

graph compute_wave(void) {
  graph g;
  double * x = g.x;
  make_mesh(x);
  /* Reason for allocation here is to have an unknown array size */
  // if this barely starts with any memory freeing errors will begin at 4th element
  // Had N been unknown, need to increase allocated memory while running
  double** pu = (double**) malloc(N * sizeof(double*));

  pu[0] = make_u0(x);
  int n = 0;
  double dx = (double) 1/(M-1);
  double dt = (double) 1/(N-1);
  while (done_condition(pu[n]) && n < (N-1)) {
    pu[n+1] = step_u(pu[n], dx/dt);
    n++;
  }
  
  g.N = n+1;
  g.pu = pu;
  return g;
}

void write_plot(graph * g_in) {
  graph g = *g_in;

  int disp = 10;
  int Mdisp = M/disp;
  int Ndisp = N/disp;

  int i, n;
  FILE *fp = NULL;
  fp = fopen("wave.txt", "w");

  for (i = 0; i < Mdisp; i++) {
    fprintf(fp, "%lf\t", g.x[i*disp]);
    for (n = 0; n < Ndisp; n++) {
      double * u = g.pu[n];
      fprintf(fp, "%lf\t", u[i*disp]);
    }
    fprintf(fp, "\n");
  }
}

void free_graph(graph * g_in) {
  graph g = *g_in;
  int n; 
  for (n = 0; n < g.N; n++) {
    free(g.pu[n]);
  }
  free(g.pu);
}


/* Inner functions */

int done_condition(double * u) {
  return 1;
}

void make_mesh(double* x) {
  int i;
  double dM = (double) 1/(M-1);
  for (i = 0; i < M; i++) {
    x[i] = i * dM;
  }
}

double* make_u0(double* x) {
  // reason for allocation is make it accesible outside function scope
  // without using a static array that occupies the "u0" name
  double* u0 = (double*) malloc(M * sizeof(double));
  int i;
  u0[0] = 0;
  u0[M-1] = 0;
  for (i = 1; i < (M-1); i++) {
    u0[i] = exp( -pow(16 * (x[i] - 0.25), 2) );
  }
  return u0;
}

double* step_u(double* u_in, double dxdt) {
  double* u = (double*) malloc(M * sizeof(double));
  int i;
  // Dirichlet
  u[0] = 0;
  u[M-1] = 0;
 /* Neumann
 u[0] = u_in[2];
 u[M-1] = u_in[M-3];
 */
  for (i = 1; i < (M-1); i++) {
    u[i] = u_in[i] + dxdt*(u_in[i-1] - u_in[i]);
  }
  return u;
}