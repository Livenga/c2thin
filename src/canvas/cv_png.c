#include <stdlib.h>
#include <png.h>

#include "../../include/canvas.h"

int
pnread(const char *path,
       canvas *cv) {
  int i, j, k, pos;
  FILE *png_fp;
  png_structp png_ptr;
  png_infop info_ptr;

  png_uint_32 width, height;
  png_byte color_type, colors;
  uchar **png_data;

  if((png_fp = fopen(path, "rb")) == NULL) {
    perror(path);
    return EOF;
  }

  png_ptr = png_create_read_struct(
      PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  info_ptr = png_create_info_struct(png_ptr);

  png_init_io(png_ptr, png_fp);
  png_read_info(png_ptr, info_ptr);

  width      = png_get_image_width(png_ptr, info_ptr);
  height     = png_get_image_height(png_ptr, info_ptr);
  color_type = png_get_color_type(png_ptr, info_ptr);
  switch(color_type) {
    case PNG_COLOR_TYPE_GRAY: colors = 1; break;
    case PNG_COLOR_TYPE_GA:   colors = 2; break;
    case PNG_COLOR_TYPE_RGB:  colors = 3; break;
    case PNG_COLOR_TYPE_RGBA: colors = 4; break;
    default: colors = 3; break;
  }

  png_data = (uchar **)calloc(height, sizeof(uchar *));
  for(i = 0; i < height; i++)
    png_data[i] = (uchar *)calloc(width * colors, sizeof(uchar));

  png_read_image(png_ptr, png_data);
  png_read_end(png_ptr, info_ptr);
  png_destroy_info_struct(png_ptr, &info_ptr);
  png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

  fclose(png_fp);

  cv->width  = width;
  cv->height = height;
  cv->colors = colors;

  cv->data = (uchar *)calloc(
      width * height * colors, sizeof(uchar));
  for(i = 0; i < height; i++) {
    for(j = 0; j < width; j++) {
      pos = i * width + j;

      for(k = 0; k < colors; k++) {
        cv->data[pos * colors + k]  = png_data[i][j * colors + k];
        png_data[i][j * colors + k] = '\0';
      }
    }

    free(png_data[i]);
    png_data[i] = NULL;
  }
  free(png_data);
  png_data = NULL;

  return 0;
}

int
pnwrite(const char *path,
        canvas cv) {
  int color_type;
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

  switch(cv.colors) {
    case 1: color_type = PNG_COLOR_TYPE_GRAY; break;
    case 2: color_type = PNG_COLOR_TYPE_GA;   break;
    case 3: color_type = PNG_COLOR_TYPE_RGB;  break;
    case 4: color_type = PNG_COLOR_TYPE_RGBA; break;
  }

  png_set_IHDR(png_ptr, info_ptr,
      cv.width, cv.height, 8, color_type, PNG_INTERLACE_NONE,
      PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_data = cv2dim(cv);
  png_write_info(png_ptr, info_ptr);
  png_write_image(png_ptr, (png_bytepp)png_data);
  png_write_end(png_ptr, info_ptr);
  png_destroy_info_struct(png_ptr, &info_ptr);
  png_destroy_write_struct(&png_ptr, &info_ptr);

  release_dim(cv.width, cv.height, cv.colors, png_data);
  fclose(png_fp);
  return 0;
}
