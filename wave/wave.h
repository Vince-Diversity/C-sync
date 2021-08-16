enum { M = 5001, N = 10001 };

typedef struct {
  // M needs special treatment
  // # define M 100 works too, const does not
  double x[M];  // space
  double ** pu; // u(x,t)-matrix
  int N;  // number of time steps
} graph;

/* Initialize functions here */
graph give_example(void);
graph compute_wave(void);
void write_plot(graph * g);
void free_graph(graph * g);
/* Inner functions */
int done_condition(double * u);
void make_mesh(double *);
double * make_u0(double *);
double * step_u(double *, double);