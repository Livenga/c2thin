#include <stdlib.h>
#include "../../include/canvas.h"

void release_canvas(canvas *cv) {
  int i, j, k;
  int pos;

  for(i = 0; i < cv->height; i++) {
    for(j = 0; j < cv->width; j++) {
      pos = i * cv->width + j;

      for(k = 0; k < cv->colors; k++)
        cv->data[pos * cv->colors + k] = '\0';
    }
  }
  free(cv->data);
  cv->data = NULL;
}

void release_dim(int width,
                 int height,
                 int colors,
                 uchar **dim) {
  int i, j, k;

  for(i = 0; i < height; i++) {
    for(j = 0; j < width; j++) {
      for(k = 0; k < colors; k++)
        dim[i][j * colors + k] = '\0';
    }
    free(dim[i]);
    dim[i] = NULL;
  }
  free(dim);
  dim = NULL;
}
