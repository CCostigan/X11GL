
#ifndef _X11GL_HPP
#define _X11GL_HPP


#ifndef __APPLE__
    //#include <X11/XF86keysym.h>
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/Xos.h>

    #define GL_GLEXT_PROTOTYPES
    #include <GL/glx.h>
    //#include <GL/glxew.h>
    #include <GL/glxext.h>
    //#include <GL/glxint.h>
#endif

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>


class X11GL {

    public:
        X11GL();
        virtual ~X11GL();
        void init(std::string, int, float);
        int render();
};


#endif //_X11GL_HPP

