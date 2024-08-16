
#ifndef _X11GL_HPP
#define _X11GL_HPP


#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>// Tried to use for toggle fullscreen


#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>

#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_xlib.h>
#include <vulkan/vulkan_xcb.h>

class X11GL {

    public:
        XSetWindowAttributes attr;
        unsigned long mask;
        Window root;
        Window win;
        // GLXContext ctx;
        XVisualInfo *visinfo;

        float vrx, vry, vrz, zoom;
        float alpha;
        int xloc, yloc, width, height, deppth = 24;
        Display *disp;
        Window xwin;
        int scrnum;
        std::string caption = "OpenGL X11 Test";

        // X11GL();
        X11GL(int x, int y, int w, int h, bool showinfo);
        virtual ~X11GL();
        void test(std::string, int, float);
        int getwindow(int , int , int , int , std::string&);
        void init();        
        void xmain();        
        // void initX11();
        // void initGL(Display *);
        void reshapewindow(int, int);
        void renderwindow(Display *);
        void mainloop(Display *, Window);
        void info(void);
};

#endif //_X11GL_HPP

