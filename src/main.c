#include <stdio.h>
#include <stdlib.h>
#include "../include/canvas.h"

int main(int argc, char *argv[])
{
  canvas cv_read, cv_bin, cv_skelt;

  pnread("imgs/a.png", &cv_read);
  cv2bin(&cv_bin, cv_read);
  //pnwrite("bin.png", cv_bin);
 
  cv2skelt(&cv_skelt, cv_bin);
  pnwrite("skelt.png", cv_skelt);
 
  release_canvas(&cv_skelt);
  release_canvas(&cv_read);
  release_canvas(&cv_bin);
	return 0;
}
