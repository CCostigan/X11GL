#include "X11GL.h"
#include "gears.h"

// Much of this code lifted from this Apple example
// https://opensource.apple.com/source/X11apps/X11apps-13/glxgears.c.auto.html
// https://github.com/davidanthonygardner/glxgears/blob/master/glxgears.c


static GLfloat vrx = 0.0, vry = 0.0, vrz = 0.0, zoom = -40.0;
static GLfloat alpha = 0.0;
static int gear1, gear2, gear3;
static Display *disp;
static Window xwin;
static GLXContext xctx;
int attrib[] = {GLX_RGBA,
                GLX_RED_SIZE, 1,
                GLX_GREEN_SIZE, 1,
                GLX_BLUE_SIZE, 1,
                GLX_DOUBLEBUFFER,
                GLX_DEPTH_SIZE, 1,
                None};
int scrnum;
std::string caption = "OpenGL X11 Test";



X11GL::X11GL()
{
    printf("(X11) Constructor called!\n");
    char *dispvar = getenv("DISPLAY");
    disp = XOpenDisplay(dispvar);
}

X11GL::~X11GL()
{
    printf("(X11) Destructor called!\n");
    // Shut down
    glDeleteLists(gear1, 1);
    glDeleteLists(gear2, 1);
    glDeleteLists(gear3, 1);
    glXMakeCurrent(disp, None, NULL);    
    glXDestroyContext(disp, xctx);
    XDestroyWindow(disp, xwin);
    XCloseDisplay(disp);    
}

void X11GL::test(std::string s, int i, float d)
{
    printf("(X11) test called: %s %d %f\n", s.c_str(), i, d);
}

void X11GL::xmain(int x, int y, int w, int h, bool showinfo)
{
    printf("(X11) XMain called:\n");

    getwindow(x, y, w, h, caption);
    XMapWindow(disp, xwin);
    glXMakeCurrent(disp, None, NULL);
    glXMakeCurrent(disp, xwin, xctx);
    reshapewindow(w, h);

    if (showinfo) info();
    init();

    mainloop(disp, xwin, xctx);
}

int X11GL::getwindow(int x, int y, int w, int h, std::string &caption) {
    XSetWindowAttributes attr;
    unsigned long mask;
    Window root;
    Window win;
    GLXContext ctx;
    XVisualInfo *visinfo;

    scrnum = DefaultScreen(disp);
    root = RootWindow(disp, scrnum);

    visinfo = glXChooseVisual(disp, scrnum, attrib);
    if (!visinfo)
    {
        printf("Error: couldn't get an RGB, Double-buffered visual\n");
        exit(1);
    }

    /* window attributes */
    attr.background_pixel = 0;
    attr.border_pixel = 0;
    attr.colormap = XCreateColormap(disp, root, visinfo->visual, AllocNone);
    attr.event_mask = ExposureMask //| StructureNotifyMask | ConfigureNotify //ResizeRedirectMask //FocusChangeMask
                    | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask
                    | PointerMotionMask | PropertyChangeMask
                ;
    mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

    win = XCreateWindow(disp, root, x, y, w, h,
                        0, visinfo->depth, InputOutput,
                        visinfo->visual, mask, &attr);

    /* set hints and properties */
    {
        XSizeHints sizehints;
        sizehints.x = x;
        sizehints.y = y;
        sizehints.width = w;
        sizehints.height = h;
        sizehints.flags = USSize | USPosition;
        XSetNormalHints(disp, win, &sizehints);
        XSetStandardProperties(disp, win, caption.c_str(), caption.c_str(),
                               None, (char **)NULL, 0, &sizehints);
    }

    ctx = glXCreateContext(disp, visinfo, NULL, True);
    if (!ctx)
    {
        printf("Error: glXCreateContext failed\n");
        exit(1);
    }

    XFree(visinfo);

    xwin = win;
    xctx = ctx;
    printf("GLX11 getwindow done:\n");
    return 0;
}

void newContext(Display *disp, Window xwin, int x, int y, int w, int h) {    
    XVisualInfo *visinfo;
    visinfo = glXChooseVisual(disp, scrnum, attrib);
        XSizeHints sizehints;
        sizehints.x = x;
        sizehints.y = y;
        sizehints.width = w;
        sizehints.height = h;
        sizehints.flags = USSize | USPosition;
        XSetNormalHints(disp, xwin, &sizehints);
        XSetStandardProperties(disp, xwin, caption.c_str(), caption.c_str(),
                               None, (char **)NULL, 0, &sizehints);    
    xctx = glXCreateContext(disp, visinfo, NULL, True);
    XFree(visinfo);
    XStoreName(disp, xwin, "VERY SIMPLE APPLICATION");
}

void X11GL::init() {
    static GLfloat pos[4] = {5.0, 5.0, 10.0, 0.0};
    static GLfloat red[4] = {0.8, 0.1, 0.0, 1.0};
    static GLfloat grn[4] = {0.0, 0.8, 0.2, 1.0};
    static GLfloat blu[4] = {0.2, 0.2, 1.0, 1.0};

    glClearColor(0.0, 0.0, 0.2, 1.0);

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    // Load objects here...
    /* For now we copy the make the gears code */
        gear1 = glGenLists(1);
            glNewList(gear1, GL_COMPILE);
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
            gear(1.0, 4.0, 1.0, 20, 0.7);
        glEndList();
        gear2 = glGenLists(1);
            glNewList(gear2, GL_COMPILE);
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, grn);
            gear(0.5, 2.0, 2.0, 10, 0.7);
        glEndList();
        gear3 = glGenLists(1);
            glNewList(gear3, GL_COMPILE);
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blu);
            gear(1.3, 2.0, 0.5, 10, 0.7);
        glEndList();        
    glEnable(GL_NORMALIZE);
    printf("GLX11 init done:\n");
}

void X11GL::reshapewindow(int w, int h) {
    GLfloat ar = (GLfloat)h / (GLfloat)w;    
    // glXMakeCurrent(disp, None, NULL);
    // newContext(disp, xwin, 0, 0, w, h);    
    // glXMakeCurrent(disp, xwin, xctx);
    //getContext();
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -ar, ar, 4.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, zoom);    
    printf("GLX11 reshape done: %d %d\n", w, h);
}

void X11GL::renderwindow(Display *disp, GLXDrawable xwnd) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

        glRotatef(vrx, 1.0, 0.0, 0.0);
        glRotatef(vry, 0.0, 1.0, 0.0);
        glRotatef(vrz, 0.0, 0.0, 1.0);

        glPushMatrix();
            glTranslatef(-3.0, -2.0, 0.0);
            glRotatef(alpha, 0.0, 0.0, 1.0);
            glCallList(gear1);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(3.1, -2.0, 0.0);
            glRotatef(-2.0 * alpha - 9.0, 0.0, 0.0, 1.0);
            glCallList(gear2);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-3.1, 4.2, 0.0);
            glRotatef(-2.0 * alpha - 25.0, 0.0, 0.0, 1.0);
            glCallList(gear3);
        glPopMatrix();

    glPopMatrix();
    glXSwapBuffers(disp, xwnd);

    //printf("Render... ");
}
void X11GL::info()
{
    printf("GL_RENDERER   = %s\n", (char *)glGetString(GL_RENDERER));
    printf("GL_VERSION    = %s\n", (char *)glGetString(GL_VERSION));
    printf("GL_VENDOR     = %s\n", (char *)glGetString(GL_VENDOR));
    printf("GL_EXTENSIONS = %s\n", (char *)glGetString(GL_EXTENSIONS));
}
void X11GL::mainloop(Display *disp, Window xwnd, GLXContext xctx)
{
    printf("GLX11 mainloop started.\n");
    bool done = false;
    char text[255];
    KeySym key;
    XEvent evnt;
    struct _point {
        int x, y;
    } dn, up, loc;
    XWindowAttributes attribs;
    while (!done) {
        alpha += 1.0;
        XNextEvent(disp, &evnt);
        switch (evnt.type) {
        case Expose:
            //printf("Expose %d\n", evnt.xexpose.count);             
            if (evnt.xexpose.count == 0 || true) XGetWindowAttributes(disp, xwnd, &attribs);                
            break;
        case KeyPress:
            switch (evnt.xkey.keycode) {
                case 80: vrx-=1.0; break;
                case 88: vrx+=1.0; break;
                case 83: vry+=1.0; break;
                case 85: vry-=1.0; break;
                case 79: vrz+=1.0; break;
                case 81: vrz-=1.0; break;
                case 87: zoom+=1.0; break;
                case 89: zoom-=1.0; break;
                default:
                    printf("You pressed %d '%c'\n", evnt.xkey.keycode, text[0]); // fflush(stdout);
                break;
            }
            if (XLookupString(&evnt.xkey, text, 255, &key, 0) == 1) {
                if (evnt.xkey.keycode == 9) done = true;
                //if (evnt.xkey.keycode == 38,38,40,25) vrx += 0.1;
            }
            break;
        case PropertyNotify:       
            //printf("PropertyNotify %d\n", evnt.xproperty.type); 
            break;
        case ConfigureNotify: //Called when moving the window around
            //printf("ConfigureNotify\n");             
            break;
        case ResizeRequest: 
            printf("ResizeRequest\n");   
            XGetWindowAttributes(disp, xwnd, &attribs);   
            getwindow(attribs.x, attribs.y, evnt.xresizerequest.width, evnt.xresizerequest.height, caption);
            reshapewindow(evnt.xresizerequest.width ,evnt.xresizerequest.height);
            break;
        case ClientMessage:
            printf("ClientMessage case hit!\n");
            break;
        case ButtonPress:
            //printf("ButtonPress %d, %d, %d\n", evnt.xbutton.button, evnt.xbutton.x, evnt.xbutton.y); 
            dn.x = evnt.xbutton.x;
            dn.y = evnt.xbutton.y;
            //sprintf(text, "Test %d %d", dn.x, dn.y);
            break;
        case  ButtonRelease:        
            //printf("ButtonRelease %d, %d, %d\n", evnt.xbutton.button, evnt.xbutton.x, evnt.xbutton.y); 
            // XSetForeground(disp, gctx, green);
            // XDrawLine(disp, xwnd, gctx, x, y, up.x, up.y);
            up.x = evnt.xbutton.x;
            up.y = evnt.xbutton.y;
            // XSetForeground(disp, gctx, blue);
            // XDrawString(disp,xwnd, gctx, up.x, up.y, text, strlen(text));
            //printf("%s\n", text);
            break;
        case  MotionNotify:   
            loc.x = evnt.xmotion.x;
            loc.y = evnt.xmotion.y;
            if(evnt.xmotion.state != 0 && false) 
                printf("Motionotify %d %d %d %d\n", evnt.xmotion.state, evnt.xmotion.type, evnt.xmotion.x, evnt.xmotion.y); 
            if (evnt.xmotion.state==256) {                
                vry+=(loc.x-dn.x)/1.0;
                vrx+=(loc.y-dn.y)/1.0;
                dn.x=loc.x;
                dn.y=loc.y;
            }
            break;

        //case  KeyPress:             printf("KeyPress"); break;
        //case  KeyRelease:           printf("KeyRelease"); break;
        //case  ButtonPress:          printf("ButtonPress"); break;
        //case  ButtonRelease:        printf("ButtonRelease\n"); break;
        //case  MotionNotify:         printf("Motionotify\n"); break;
        case  EnterNotify:          printf("EnterNotify\n"); break;
        case  LeaveNotify:          printf("LeaveNotify\n"); break;
        case  FocusIn:              printf("FocusIn\n"); break;
        case  FocusOut:             printf("FocusOut\n"); break;
        case  KeymapNotify:         printf("KeyMapNotify\n"); break;
        //case  Expose:               printf("Expose\n"); break;
        case  GraphicsExpose:       printf("GraphicsExpose\n"); break;
        case  NoExpose:             printf("NoExpose\n"); break;
        case  VisibilityNotify:     printf("VisibilityNotify\n"); break;
        case  CreateNotify:         printf("CreateNotify\n"); break;
        case  DestroyNotify:        printf("DestroyNotify\n"); break;
        case  UnmapNotify:          printf("UnmapNotify\n"); break;
        case  MapNotify:            printf("MapNotify\n"); break;
        case  MapRequest:           printf("MapRequest\n"); break;
        case  ReparentNotify:       printf("ReparentNotify\n"); break;
        //case  ConfigureNotify:      printf("ConfigureNotify\n"); break;
        case  ConfigureRequest:     printf("ConfigureRequest\n"); break;
        case  GravityNotify:        printf("GravityNotify\n"); break;
        //case  ResizeRequest:        printf("ResizeRequest\n"); break;
        case  CirculateNotify:      printf("CirculateNotify\n"); break;
        case  CirculateRequest:     printf("CirculateRequest\n"); break;
        //case  PropertyNotify:       printf("PropertyNotify\n"); break;
        case  SelectionClear:       printf("SelectionClear\n"); break;
        case  SelectionRequest:     printf("SelectionRequest\n"); break;
        case  SelectionNotify:      printf("SelectionNotify\n"); break;
        case  ColormapNotify:       printf("ColormapNotify\n"); break;
        //case  ClientMessage:        printf("ClientMessage\n"); break;
        case  MappingNotify:        printf("MappingNotify\n"); break;
        case  GenericEvent:         printf("GenericEvent\n"); break;
        case  LASTEvent:            printf("LASTEvent\n"); break;	/* must be bigger than any event # */        
        default: printf("Default case!\n");
        break;
        }
        renderwindow(disp, xwnd);
    }
    printf("GLX11 mainloop done:\n");
}
// void X11GL::initX11() {y
//     printf("(X11) InitX11 called:\n");
//     Display *disp;
//     Window xwnd;
//     Visual *xvis;
//     GC gctx;
//     XSetWindowAttributes xattrs;
//     int scrn;
//     int white;
//     int black;
//     int red, green, blue;
//     struct _point {
//         int x;
//         int y;
//     } point1, point2;
//     uint WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;

//     char *dispvar = getenv("DISPLAY");
//     disp = XOpenDisplay(dispvar); //XOpenDisplay((char*)0);
//     scrn = DefaultScreen(disp);
//     xvis = XDefaultVisual(disp, scrn);

//     gctx = XDefaultGC(disp, scrn);
//     white = WhitePixel(disp, scrn);
//     black = BlackPixel(disp, scrn);
//     red = 0xFF0000; green = 0x00FF00; blue=0x0000FF;
//     //GL Stuff start
//     //printf("Visual depth: %d\n", xvis->depth);
//     xattrs.border_pixel = 0x000000;
//     xattrs.background_pixel = 0x000040;
//     xattrs.override_redirect = True;
//     xattrs.colormap = XCreateColormap(disp, RootWindow(disp, scrn), xvis, AllocNone);
//     xattrs.event_mask = ExposureMask|KeyPressMask|ButtonPressMask;
//     xwnd = XCreateWindow(disp, RootWindow(disp, scrn),
//         0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 24,
//         InputOutput, xvis,
//         CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &xattrs);

// 	// Show the window
// 	XClearWindow(disp, xwnd);
// 	XMapRaised(disp, xwnd);
//     //initGL(disp);///
//     bool done = false;
//     char text[255];
//     KeySym key;
//     XEvent evnt;
//     while(!done) {
//         XNextEvent(disp, &evnt);
//         switch(evnt.type) {
//             case Expose:
//                 if(evnt.xexpose.count == 0) {
//                     XWindowAttributes attribs;
//                     XGetWindowAttributes(disp, xwnd, &attribs);
//                 }
//             break;
//             case KeyPress:
//                 if (XLookupString(&evnt.xkey, text, 255, &key, 0)==1) {
//                     if(evnt.xkey.keycode==9) done = true;
//                     else printf("You pressed '%c'\n", text[0]);  // fflush(stdout);
//                 }
//             break;
//             case ButtonPress:
//                 int x = evnt.xbutton.x; int y = evnt.xbutton.y;
//                 XSetForeground(disp, gctx, green);
//                 XDrawLine(disp, xwnd, gctx, x, y, point1.x, point1.y);
//                 point1.x = x; point1.y = y;
//                 sprintf(text, "Test %d %d", point1.x, point1.y);
//                 XSetForeground(disp, gctx, blue);
//                 XDrawString(disp,xwnd, gctx, point1.x, point1.y, text, strlen(text));
//                 printf("%s\n", text);
//             break;
//         }
//         //render();
//     }
// }

// void X11GL::initGL(Display *dpy) {
//     printf("(X11) InitGL called:\n");
//     // Solution from https://stackoverflow.com/questions/12856820/setup-opengl-on-x11
//     // Display *dpy( XOpenDisplay( NULL ));
//     int screen = XDefaultScreen( dpy );
//     const int fbCfgAttribslist[] = {
//                 GLX_RENDER_TYPE, GLX_RGBA_BIT,
//                 GLX_DRAWABLE_TYPE, GLX_PBUFFER_BIT,
//                 None
//             };
//     int nElements = 0;
//     GLXFBConfig * glxfbCfg = glXChooseFBConfig( dpy, screen, fbCfgAttribslist, &nElements );
//     const int pfbCfg[] = {
//                 GLX_PBUFFER_WIDTH, 800,
//                 GLX_PBUFFER_HEIGHT, 600,
//                 GLX_PRESERVED_CONTENTS, True,
//                 GLX_LARGEST_PBUFFER, False,
//                 None
//             };
//     GLXPbuffer pBufferId = glXCreatePbuffer( dpy, glxfbCfg[ 0 ], pfbCfg );
//     XVisualInfo * visInfo = glXGetVisualFromFBConfig( dpy, glxfbCfg[ 0 ] );
//     GLXContext  glCtx = glXCreateContext( dpy, visInfo, NULL, True );
//     glXMakeContextCurrent( dpy, pBufferId, pBufferId, glCtx );
//     printf("GL init done:\n");
// }
