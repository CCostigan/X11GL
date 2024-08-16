#include <stdio.h>
#include "x11lib/X11.h"


// https://code.visualstudio.com/docs/cpp/config-linux
// https://www.youtube.com/watch?v=45MIykWJ-C4
// https://www.youtube.com/watch?v=45MIykWJ-C4
//other

// https://www.youtube.com/watch?v=LnzuMJLZRdU 6502 
// https://www.youtube.com/watch?v=oXlwWbU8l2o OpenCV
// https://www.youtube.com/watch?v=AVXYq8aL47Q  Command line 
// https://www.youtube.com/watch?v=6avJHaC3C2U - Unsettling

X11GL x11gl;

int main(int argc, char** argv) {
  
  x11gl.init(420,42,800,600, false);

  x11gl.xmain();

  //x11gl.render();
  printf("Done!\n");
}
