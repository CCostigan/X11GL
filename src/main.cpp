#include <stdio.h>
#include "x11gl/X11GL.h"



int main(int argc, char** argv) {
  
  X11GL x11gl(420,42,800,600, false);
  

  x11gl.xmain();
  //x11gl.render();
  printf("Done!\n");
}
