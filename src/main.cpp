#include "x11lib/UtilX11.h"
#include "vk/VulkanUtil.hpp"

#include <stdio.h>

// https://code.visualstudio.com/docs/cpp/config-linux
// https://www.youtube.com/watch?v=45MIykWJ-C4
// https://www.youtube.com/watch?v=45MIykWJ-C4
//other

// https://www.youtube.com/watch?v=LnzuMJLZRdU 6502 
// https://www.youtube.com/watch?v=oXlwWbU8l2o OpenCV
// https://www.youtube.com/watch?v=AVXYq8aL47Q  Command line 
// https://www.youtube.com/watch?v=6avJHaC3C2U - Unsettling


void run() {
  X11GL x11gl;
  x11gl.init(420,42,800,600, false);
  x11gl.xmain();
}

int main(int argc, char** argv) {
  printf("(Main) Starting up\n");
  run();
  printf("(Main) Shutting down!\n");
}
