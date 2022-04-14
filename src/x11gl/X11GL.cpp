#include "X11GL.h"


X11GL::X11GL() {
    printf("(X11) Constructor called!\n");
}

X11GL::~X11GL() {
    printf("(X11) Destructor called!\n");
}

void X11GL::test(std::string s, int i, float d) {
    printf("(X11) test called: %s %d %f\n", s.c_str(), i, d);
}

void X11GL::init() {
    printf("(X11) Init called:\n");
    Display *disp;
    Visual *xvis;
    Window xwnd;
    GC gctx;
    XSetWindowAttributes xattrs;
    int scrn;
    int white;
    int black;
    int red, green, blue;

    char *dispvar = getenv("DISPLAY");
    disp = XOpenDisplay(dispvar); //XOpenDisplay((char*)0);
    scrn = DefaultScreen(disp);
    xvis = XDefaultVisual(disp, scrn);


    gctx = XDefaultGC(disp, scrn);
    white = WhitePixel(disp, scrn);
    black = BlackPixel(disp, scrn);    
    red = 0xFF0000; green = 0x00FF00; blue=0x0000FF;
    //GL Stuff start
    //printf("Visual depth: %d\n", xvis->depth);
    xattrs.border_pixel = 0x000000;
    xattrs.background_pixel = 0x000040;
    xattrs.override_redirect = True;
    xattrs.colormap = XCreateColormap(disp, RootWindow(disp, scrn), xvis, AllocNone);
    xattrs.event_mask = ExposureMask|KeyPressMask|ButtonPressMask;
    xwnd = XCreateWindow(disp, RootWindow(disp, scrn), 
        0, 0, 800, 600, 0, 24,
        InputOutput, xvis, 
        CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &xattrs);

	// Show the window
	XClearWindow(disp, xwnd);
	XMapRaised(disp, xwnd);



    //Display *dpy( XOpenDisplay( NULL ));
    int screen = XDefaultScreen( disp );
    const int fbCfgAttribslist[] = {
                GLX_RENDER_TYPE, GLX_RGBA_BIT,
                GLX_DRAWABLE_TYPE, GLX_PBUFFER_BIT,
                None
            };
    int nElements = 0;
    GLXFBConfig * glxfbCfg = glXChooseFBConfig( disp, screen, fbCfgAttribslist, &nElements );
    const int pfbCfg[] = {
                GLX_PBUFFER_WIDTH, 800,
                GLX_PBUFFER_HEIGHT, 600,
                GLX_PRESERVED_CONTENTS, True,
                GLX_LARGEST_PBUFFER, False,
                None
            };
    GLXPbuffer pBufferId = glXCreatePbuffer( disp, glxfbCfg[ 0 ], pfbCfg );
    XVisualInfo * visInfo = glXGetVisualFromFBConfig( disp, glxfbCfg[ 0 ] );
    GLXContext  glCtx = glXCreateContext( disp, visInfo, NULL, True );
    glXMakeContextCurrent( disp, pBufferId, pBufferId, glCtx );   
    printf("GLX11 init done:\n");

    bool done = false;
    char text[255];
    KeySym key;
    XEvent evnt;
    struct _point {
        int x;
        int y;
    } point1, point2;    
    while(!done) {
        XNextEvent(disp, &evnt);
        switch(evnt.type) {
            case Expose:
                if(evnt.xexpose.count == 0) {
                    XWindowAttributes attribs;
                    XGetWindowAttributes(disp, xwnd, &attribs);
                }
            break;            
            case KeyPress: 
                if (XLookupString(&evnt.xkey, text, 255, &key, 0)==1) {
                    if(evnt.xkey.keycode==9) done = true;
                    else printf("You pressed '%c'\n", text[0]);  // fflush(stdout);
                }
            break;
            case ButtonPress: 
                int x = evnt.xbutton.x; int y = evnt.xbutton.y;
                XSetForeground(disp, gctx, green);
                XDrawLine(disp, xwnd, gctx, x, y, point1.x, point1.y);
                point1.x = x; point1.y = y;
                sprintf(text, "Test %d %d", point1.x, point1.y);
                XSetForeground(disp, gctx, blue);
                XDrawString(disp,xwnd, gctx, point1.x, point1.y, text, strlen(text));
                printf("%s\n", text);
            break;
        }
        render();
    }
}

void X11GL::initX11() {
    printf("(X11) InitX11 called:\n");
    Display *disp;
    Window xwnd;
    Visual *xvis;
    GC gctx;
    XSetWindowAttributes xattrs;
    int scrn;
    int white;
    int black;
    int red, green, blue;
    struct _point {
        int x;
        int y;
    } point1, point2;
    uint WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

    char *dispvar = getenv("DISPLAY");
    disp = XOpenDisplay(dispvar); //XOpenDisplay((char*)0);
    scrn = DefaultScreen(disp);
    xvis = XDefaultVisual(disp, scrn);
	

    gctx = XDefaultGC(disp, scrn);
    white = WhitePixel(disp, scrn);
    black = BlackPixel(disp, scrn);    
    red = 0xFF0000; green = 0x00FF00; blue=0x0000FF;
    //GL Stuff start
    //printf("Visual depth: %d\n", xvis->depth);
    xattrs.border_pixel = 0x000000;
    xattrs.background_pixel = 0x000040;
    xattrs.override_redirect = True;
    xattrs.colormap = XCreateColormap(disp, RootWindow(disp, scrn), xvis, AllocNone);
    xattrs.event_mask = ExposureMask|KeyPressMask|ButtonPressMask;
    xwnd = XCreateWindow(disp, RootWindow(disp, scrn), 
        0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 24, 
        InputOutput, xvis, 
        CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &xattrs);

	// Show the window
	XClearWindow(disp, xwnd);
	XMapRaised(disp, xwnd);
    //initGL(disp);///
    bool done = false;
    char text[255];
    KeySym key;
    XEvent evnt;
    while(!done) {
        XNextEvent(disp, &evnt);
        switch(evnt.type) {
            case Expose:
                if(evnt.xexpose.count == 0) {
                    XWindowAttributes attribs;
                    XGetWindowAttributes(disp, xwnd, &attribs);
                }
            break;            
            case KeyPress: 
                if (XLookupString(&evnt.xkey, text, 255, &key, 0)==1) {
                    if(evnt.xkey.keycode==9) done = true;
                    else printf("You pressed '%c'\n", text[0]);  // fflush(stdout);
                }
            break;
            case ButtonPress: 
                int x = evnt.xbutton.x; int y = evnt.xbutton.y;
                XSetForeground(disp, gctx, green);
                XDrawLine(disp, xwnd, gctx, x, y, point1.x, point1.y);
                point1.x = x; point1.y = y;
                sprintf(text, "Test %d %d", point1.x, point1.y);
                XSetForeground(disp, gctx, blue);
                XDrawString(disp,xwnd, gctx, point1.x, point1.y, text, strlen(text));
                printf("%s\n", text);
            break;
        }
        render();
    }
}

void X11GL::initGL(Display *dpy) {
    printf("(X11) InitGL called:\n");
    // Solution from https://stackoverflow.com/questions/12856820/setup-opengl-on-x11 
    // Display *dpy( XOpenDisplay( NULL ));
    int screen = XDefaultScreen( dpy );
    const int fbCfgAttribslist[] = {
                GLX_RENDER_TYPE, GLX_RGBA_BIT,
                GLX_DRAWABLE_TYPE, GLX_PBUFFER_BIT,
                None
            };
    int nElements = 0;
    GLXFBConfig * glxfbCfg = glXChooseFBConfig( dpy, screen, fbCfgAttribslist, &nElements );
    const int pfbCfg[] = {
                GLX_PBUFFER_WIDTH, 800,
                GLX_PBUFFER_HEIGHT, 600,
                GLX_PRESERVED_CONTENTS, True,
                GLX_LARGEST_PBUFFER, False,
                None
            };
    GLXPbuffer pBufferId = glXCreatePbuffer( dpy, glxfbCfg[ 0 ], pfbCfg );
    XVisualInfo * visInfo = glXGetVisualFromFBConfig( dpy, glxfbCfg[ 0 ] );
    GLXContext  glCtx = glXCreateContext( dpy, visInfo, NULL, True );
    glXMakeContextCurrent( dpy, pBufferId, pBufferId, glCtx );   
    printf("GL init done:\n");
}

int X11GL::render() {
    //printf("(X11) Render called!\n");
    return 0;
}

