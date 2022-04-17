#include <stdio.h>
#include "X11GL/X11GL.h"

int main(int argc, char** argv) {
  
  X11GL x11gl;
  //x11gl.test("", 0, 0.0);
  //x11gl.initX11();
  //x11gl.initGL();
  x11gl.xmain(420,42,1280,768, false);
  //x11gl.render();
  printf("Done!\n");
}
