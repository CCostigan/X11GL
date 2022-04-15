#include "X11GL.h"

// Much of this code lifted from this Apple example
// https://opensource.apple.com/source/X11apps/X11apps-13/glxgears.c.auto.html

X11GL::X11GL() {
    printf("(X11) Constructor called!\n");
}

X11GL::~X11GL() {
    printf("(X11) Destructor called!\n");
}

void X11GL::test(std::string s, int i, float d) {
    printf("(X11) test called: %s %d %f\n", s.c_str(), i, d);
}

static GLint gear1;
void gear(GLfloat inner_radius, GLfloat outer_radius, 
    GLfloat width, GLint teeth, GLfloat tooth_depth)
{
   GLint i;
   GLfloat r0, r1, r2;
   GLfloat angle, da;
   GLfloat u, v, len;

   r0 = inner_radius;
   r1 = outer_radius - tooth_depth / 2.0;
   r2 = outer_radius + tooth_depth / 2.0;

   da = 2.0 * M_PI / teeth / 4.0;

   glShadeModel(GL_FLAT);

   glNormal3f(0.0, 0.0, 1.0);

   /* draw front face */
   glBegin(GL_QUAD_STRIP);
   for (i = 0; i <= teeth; i++) {
      angle = i * 2.0 * M_PI / teeth;
      glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
      glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
      if (i < teeth) {
	 glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
	 glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da),
		    width * 0.5);
      }
   }
   glEnd();

   /* draw front sides of teeth */
   glBegin(GL_QUADS);
   da = 2.0 * M_PI / teeth / 4.0;
   for (i = 0; i < teeth; i++) {
      angle = i * 2.0 * M_PI / teeth;

      glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
      glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
      glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da),
		 width * 0.5);
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da),
		 width * 0.5);
   }
   glEnd();

   glNormal3f(0.0, 0.0, -1.0);

   /* draw back face */
   glBegin(GL_QUAD_STRIP);
   for (i = 0; i <= teeth; i++) {
      angle = i * 2.0 * M_PI / teeth;
      glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
      glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
      if (i < teeth) {
	 glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da),
		    -width * 0.5);
	 glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
      }
   }
   glEnd();

   /* draw back sides of teeth */
   glBegin(GL_QUADS);
   da = 2.0 * M_PI / teeth / 4.0;
   for (i = 0; i < teeth; i++) {
      angle = i * 2.0 * M_PI / teeth;

      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da),
		 -width * 0.5);
      glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da),
		 -width * 0.5);
      glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
      glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
   }
   glEnd();

   /* draw outward faces of teeth */
   glBegin(GL_QUAD_STRIP);
   for (i = 0; i < teeth; i++) {
      angle = i * 2.0 * M_PI / teeth;

      glVertex3f(r1 * cos(angle), r1 * sin(angle), width * 0.5);
      glVertex3f(r1 * cos(angle), r1 * sin(angle), -width * 0.5);
      u = r2 * cos(angle + da) - r1 * cos(angle);
      v = r2 * sin(angle + da) - r1 * sin(angle);
      len = sqrt(u * u + v * v);
      u /= len;
      v /= len;
      glNormal3f(v, -u, 0.0);
      glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), width * 0.5);
      glVertex3f(r2 * cos(angle + da), r2 * sin(angle + da), -width * 0.5);
      glNormal3f(cos(angle), sin(angle), 0.0);
      glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da),
		 width * 0.5);
      glVertex3f(r2 * cos(angle + 2 * da), r2 * sin(angle + 2 * da),
		 -width * 0.5);
      u = r1 * cos(angle + 3 * da) - r2 * cos(angle + 2 * da);
      v = r1 * sin(angle + 3 * da) - r2 * sin(angle + 2 * da);
      glNormal3f(v, -u, 0.0);
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da),
		 width * 0.5);
      glVertex3f(r1 * cos(angle + 3 * da), r1 * sin(angle + 3 * da),
		 -width * 0.5);
      glNormal3f(cos(angle), sin(angle), 0.0);
   }

   glVertex3f(r1 * cos(0), r1 * sin(0), width * 0.5);
   glVertex3f(r1 * cos(0), r1 * sin(0), -width * 0.5);

   glEnd();

   glShadeModel(GL_SMOOTH);

   /* draw inside radius cylinder */
   glBegin(GL_QUAD_STRIP);
   for (i = 0; i <= teeth; i++) {
      angle = i * 2.0 * M_PI / teeth;
      glNormal3f(-cos(angle), -sin(angle), 0.0);
      glVertex3f(r0 * cos(angle), r0 * sin(angle), -width * 0.5);
      glVertex3f(r0 * cos(angle), r0 * sin(angle), width * 0.5);
   }
   glEnd();
}


void X11GL::xmain(bool showinfo) {
    printf("(X11) XMain called:\n");
    Display *disp;
    Window xwnd;
    GLXContext xctx;
    //GC gctx;
    Visual *xvis;
    XSetWindowAttributes xattrs;
    int scrn;
    int white;
    int black;
    int red, green, blue;
    std::string caption = "TEST";

    char *dispvar = getenv("DISPLAY");
    disp = XOpenDisplay(dispvar); 
    getwindow(disp, xwnd, xctx, 0,0,800,600, caption);
    XMapWindow(disp, xwnd);
    glXMakeCurrent(disp, xwnd, xctx);
    reshapewindow(20, 20, 1024, 768) ;
    
    if (showinfo) info();
    init();
    
    mainloop(disp, xwnd, xctx);

    //Shut down
    glXDestroyContext(disp, xctx);
    XDestroyWindow(disp, xwnd);
    XCloseDisplay(disp);  
}

int X11GL::getwindow(Display* disp, Window& xwin, GLXContext& xctx
    , int x, int y, int w, int h, std::string& caption) {
   int attrib[] = { GLX_RGBA,
		    GLX_RED_SIZE, 1,
		    GLX_GREEN_SIZE, 1,
		    GLX_BLUE_SIZE, 1,
		    GLX_DOUBLEBUFFER,
		    GLX_DEPTH_SIZE, 1,
		    None };
   int scrnum;
   XSetWindowAttributes attr;
   unsigned long mask;
   Window root;
   Window win;
   GLXContext ctx;
   XVisualInfo *visinfo;

   scrnum = DefaultScreen( disp );
   root = RootWindow( disp, scrnum );

   visinfo = glXChooseVisual( disp, scrnum, attrib );
   if (!visinfo) {
      printf("Error: couldn't get an RGB, Double-buffered visual\n");
      exit(1);
   }

   /* window attributes */
   attr.background_pixel = 0;
   attr.border_pixel = 0;
   attr.colormap = XCreateColormap( disp, root, visinfo->visual, AllocNone);
   attr.event_mask = StructureNotifyMask | ExposureMask | KeyPressMask | ButtonPressMask;
   mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

   win = XCreateWindow( disp, root, 0, 0, w, h,
		        0, visinfo->depth, InputOutput,
		        visinfo->visual, mask, &attr );

   /* set hints and properties */
   {
      XSizeHints sizehints;
      sizehints.x = x;
      sizehints.y = y;
      sizehints.width  = w;
      sizehints.height = h;
      sizehints.flags = USSize | USPosition;
      XSetNormalHints(disp, win, &sizehints);
      XSetStandardProperties(disp, win, caption.c_str(), caption.c_str(),
        None, (char **)NULL, 0, &sizehints);
   }

   ctx = glXCreateContext( disp, visinfo, NULL, True );
   if (!ctx) {
      printf("Error: glXCreateContext failed\n");
      exit(1);
   }

   XFree(visinfo);

   xwin = win;
   xctx = ctx;
   printf("GLX11 getwindow done:\n");
   return 0;
}
void X11GL::init() {
    static GLfloat pos[4] = { 5.0, 5.0, 10.0, 0.0 };
    static GLfloat red[4] = { 0.8, 0.1, 0.0, 1.0 };
    static GLfloat grn[4] = { 0.0, 0.8, 0.2, 1.0 };
    static GLfloat blu[4] = { 0.2, 0.2, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    //Load objects here...
        /* For now we copy the make the gears code */
        gear1 = glGenLists(1);
        glNewList(gear1, GL_COMPILE);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
        gear(1.0, 4.0, 1.0, 20, 0.7);
        glEndList();

    glEnable(GL_NORMALIZE);
    printf("GLX11 init done:\n");
}
void X11GL::reshapewindow(int x, int y, int w, int h) {
    GLfloat ar = (GLfloat) h / (GLfloat) w;
    glViewport((GLint) x,(GLint) y, (GLint) w, (GLint) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -ar, ar, 5.0, 60.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -40.0);
    printf("GLX11 reshape done:\n");
}
void X11GL::renderwindow(Display *disp, GLXDrawable draw
    , float vrx, float vry, float vrz, float alpha) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();

        glRotatef(vrx, 1.0, 0.0, 0.0);
        glRotatef(vry, 0.0, 1.0, 0.0);
        glRotatef(vrz, 0.0, 0.0, 1.0);

        glPushMatrix();
            glTranslatef(-3.0, -2.0, 0.0);
            glRotatef(alpha, 0.0, 0.0, 1.0);
            /// FINALLY DRAW SOMETHING!
            glCallList(gear1);
            /// Some work needed here :D
        glPopMatrix();

    glPopMatrix();    
    printf("GLX11 render done:\n");
}
void X11GL::info() {
    printf("GL_RENDERER   = %s\n", (char *) glGetString(GL_RENDERER));
    printf("GL_VERSION    = %s\n", (char *) glGetString(GL_VERSION));
    printf("GL_VENDOR     = %s\n", (char *) glGetString(GL_VENDOR));
    printf("GL_EXTENSIONS = %s\n", (char *) glGetString(GL_EXTENSIONS));
}
void X11GL::mainloop(Display *disp, Window xwnd, GLXContext xctx) {
    printf("GLX11 mainloop started.\n");
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
                //XSetForeground(disp, gctx, green);
                //XDrawLine(disp, xwnd, gctx, x, y, point1.x, point1.y);
                point1.x = x; point1.y = y;
                sprintf(text, "Test %d %d", point1.x, point1.y);
                //XSetForeground(disp, gctx, blue);
                //XDrawString(disp,xwnd, gctx, point1.x, point1.y, text, strlen(text));
                printf("%s\n", text);
            break;
        }
        renderwindow(disp, xwnd, 10.0, 20.0, 30.0, 45.0);
    }
    printf("GLX11 mainloop done:\n");
}
// void X11GL::initX11() {
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


