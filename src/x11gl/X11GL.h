
#ifndef _X11GL_HPP
#define _X11GL_HPP


    //#include <X11/XF86keysym.h>
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/Xos.h>
    #include <X11/Xatom.h>// Tried to use for toggle fullscreen

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>


class X11GL {

    public:
        float vrx = 0.0, vry = 0.0, vrz = 0.0, zoom = -40.0;
        float alpha = 0.0;

        X11GL();
        virtual ~X11GL();
        void test(std::string, int, float);
        int getwindow(int , int , int , int , std::string&);
        void init();        
        void xmain(int, int, int, int, bool);        
        // void initX11();
        // void initGL(Display *);
        void reshapewindow(int, int);
        void renderwindow(Display *);
        void mainloop(Display *, Window);
        void info(void);
};

#endif //_X11GL_HPP

