#include "wave.h" /* checks for this file in current directory */
#include <stdio.h>

int main(void) {
  graph g;
  g = give_example();
  g = compute_wave();
  write_plot(&g);
  free_graph(&g);

  return 0;
}
