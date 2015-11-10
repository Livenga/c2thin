#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/canvas.h"

/* 二値化変換 */
void
cv2bin(canvas *dest,
       const canvas src) {
  const int img_size = src.width * src.height;
  int i, j, pos;
  double bright;

  dest->rev    = 1; /* 二値化反転 */
  dest->width  = src.width;
  dest->height = src.height;
  dest->colors = 1;
  dest->data   = (uchar *)calloc(img_size, sizeof(uchar));

  for(i = 0; i < src.height; i++) {
    for(j = 0; j < src.width; j++) {
      pos = i * src.width + j;
      bright = 0.3 * (double)src.data[pos * src.colors + 0] +
        0.6 * (double)src.data[pos * src.colors + 1] +
        0.1 * (double)src.data[pos * src.colors + 2];

      if(bright > 127.0)
        dest->data[pos] = 0x00;
      else
        dest->data[pos] = 0xFF;
    }
  }
}

/* 二次元配列変換 */
uchar **
cv2dim(canvas cv) {
  int i, j, k;
  int pos;
  uchar **dim;

  dim = (uchar **)calloc(
      cv.height, sizeof(uchar *));
  for(i = 0; i < cv.height; i++) {
    dim[i] = (uchar *)calloc(
        cv.width * cv.colors, sizeof(uchar));
    for(j = 0; j < cv.width; j++) {
      pos = i * cv.width + j;

      for(k = 0; k < cv.colors; k++) {
        if(!cv.rev)
          dim[i][j * cv.colors + k] = 0xFF - 
            cv.data[pos * cv.colors + k];
        else
          dim[i][j * cv.colors + k] =
            cv.data[pos * cv.colors + k];
      }
    }
  }

  return dim;
}
