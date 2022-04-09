#include "X11GL.h"


X11GL::X11GL() {
    printf("(X11) Constructor called!\n");
}

X11GL::~X11GL() {
    printf("(X11) Destructor called!\n");
}

void X11GL::init(std::string s, int i, float d) {
    printf("(X11) Init called: %s %d %f\n", s.c_str(), i, d);
}

int X11GL::render() {
    printf("(X11) Render called!\n");
}

