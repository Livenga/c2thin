#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../include/canvas.h"

/* 細線化処理 */
void
cv2skelt(canvas *dest,
         const canvas src) {
  const int img_size = src.width * src.height;
  const int idx[8][9] = {
    {0, 0, 2, 0, 1, 1, 2, 1, 2},
    {0, 0, 0, 2, 1, 2, 1, 1, 2},
    {2, 0, 0, 1, 1, 0, 2, 1, 2},
    {1, 2, 0, 1, 1, 0, 2, 2, 0},
    {2, 1, 2, 1, 1, 0, 2, 0, 0},
    {2, 1, 1, 2, 1, 2, 0, 0, 0},
    {2, 1, 2, 0, 1, 1, 0, 0, 2},
    {0, 2, 2, 0, 1, 1, 0, 2, 1}
  };
  int cnt_idx;
  const size_t idx_size = sizeof(idx) / sizeof(idx[0]);

  /* 変換先 */
  dest->width  = src.width;
  dest->height = src.height;
  dest->colors = 1;
  dest->data = (uchar *)calloc(
      img_size, sizeof(uchar));
  memmove((void *)dest->data,
      (const void *)src.data, img_size * sizeof(uchar));

  int idx_x, idx_y,
      cv_x, cv_y,
      x, y;
  int cv_pos;
  int cnt;
  int f_exit;

  do {
    f_exit = 0;

    for(cnt_idx = 0; cnt_idx < idx_size; cnt_idx++) {
      for(cv_y = 0; cv_y < src.height; cv_y++) {
        for(cv_x = 0; cv_x < src.width; cv_x++) {
          cv_pos = cv_y * src.width + cv_x;

          if(dest->data[cv_pos] == 0xFF) {
            cnt = 0;
            /* 近傍状態の調査 */
            for(idx_y = 0; idx_y < 3; idx_y++) {
              y = cv_y + idx_y - 1;

              for(idx_x = 0; idx_x < 3; idx_x++) {
                x = cv_x + idx_x - 1;

                if(x > -1 && y > -1 &&
                    x < src.width && y < src.height) {
                  if(idx[cnt_idx][idx_y * 3 + idx_x] == 2) cnt++;

                  else if(idx[cnt_idx][idx_y * 3 + idx_x]
                      == (dest->data[y * dest->width + x] / 0xFF))  cnt++;
                }
                else cnt++;

              } /* for(idx_x) */
            } /* for(idx_y) */
#if 0
            printf("%3dx%3d (%d) ==> %d\n",
                dest->width, dest->height, cnt_idx, cnt);
#endif
            if(cnt == 9) {
              dest->data[cv_pos] = 0x00;
              f_exit = 1;
            }
          } /* if(dest>data) */

        } /* for(cv_x) */
      } /* for(cv_y) */
    } /* for(cnt_idx) */
  } while(f_exit == 1);
}
