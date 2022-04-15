
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
    #include <GL/glu.h>
#endif

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>


class X11GL {

    public:
        X11GL();
        virtual ~X11GL();
        void test(std::string, int, float);
        int getwindow(Display* , Window& , GLXContext& , int , int , int , int , std::string&);
        void init();        
        void xmain(bool);        
        // void initX11();
        // void initGL(Display *);
        void reshape(int, int);
        void render(Display *, GLXDrawable, float, float, float, float);
        void mainloop(Display *, Window, GLXContext);
        void info(void);
};


#endif //_X11GL_HPP

