#ifndef CANVAS_H
#define CANVAS_H

typedef unsigned char uchar;

typedef struct _canvas {
  int rev;
  size_t width, height, colors;
  uchar *data;
} canvas;

/* src/canvas/cv_png.c */
extern int
pnread(const char *path,
       canvas *cv);
extern int
pnwrite(const char *path,
        canvas cv);

/* src/canvas/cv_conv.c */
extern void
cv2skelt(canvas *dest,
         const canvas src);
extern void
cv2bin(canvas *dest,
       const canvas src);
extern uchar **
cv2dim(canvas cv);

/* src/canvas/cv_util.c */
extern void
release_canvas(canvas *cv);
extern void
release_dim(int width,
            int height,
            int colors,
            uchar **dim);

/* src/canvas/cv_save.c */
extern int
pnwrite_rgb(const char *path,
            canvas cv);
#endif
