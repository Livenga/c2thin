#include <stdlib.h>
#include <png.h>

#include "../../include/canvas.h"

int pnwrite_rgb(const char *path,
    canvas cv) {
  int i, j;
  int pos;
  FILE *png_fp;
  png_structp png_ptr;
  png_infop info_ptr;
  uchar **png_data;

  if((png_fp = fopen(path, "wb")) == NULL) {
    perror(path);
    return EOF;
  }

  png_ptr = png_create_write_struct(
      PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  info_ptr = png_create_info_struct(png_ptr);
  png_init_io(png_ptr, png_fp);

  png_set_IHDR(png_ptr, info_ptr,
      cv.width, cv.height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
      PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_data = (uchar **)calloc(cv.height, sizeof(uchar *));
  for(i = 0; i < cv.height; i++) {
    png_data[i] = (uchar *)calloc(cv.width * 3, sizeof(uchar));

    for(j = 0; j < cv.width; j++) {
      pos = i * cv.width + j;

      if(cv.data[pos * 4 + 3] == 0x00) {
        png_data[i][j * 3 + 0] = 0xFF;
        png_data[i][j * 3 + 1] = 0xFF;
        png_data[i][j * 3 + 2] = 0xFF;
      }
      else {
        png_data[i][j * 3 + 0] =
          cv.data[pos * 4 + 0] - cv.data[pos * 4 + 3];
        png_data[i][j * 3 + 1] =
          cv.data[pos * 4 + 1] - cv.data[pos * 4 + 3];
        png_data[i][j * 3 + 2] =
          cv.data[pos * 4 + 2] - cv.data[pos * 4 + 3];
      }
    }
  }
  png_write_info(png_ptr, info_ptr);
  png_write_image(png_ptr, (png_bytepp)png_data);
  png_write_end(png_ptr, info_ptr);

  png_destroy_info_struct(png_ptr, &info_ptr);
  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(png_fp);

  for(i = 0; i < cv.height; i++) {
    for(j = 0; j < cv.width; j++) {
      png_data[i][j * 3 + 0] = '\0';
      png_data[i][j * 3 + 1] = '\0';
      png_data[i][j * 3 + 2] = '\0';
    }
    free(png_data[i]);
    png_data[i] = NULL;
  }
  free(png_data);
  png_data = NULL;

  return 0;
}
