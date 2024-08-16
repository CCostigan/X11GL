#include "UtilX11.h"

// Some good starting points
// https://opensource.apple.com/source/X11apps/X11apps-13/glxgears.c.auto.html
// https://github.com/davidanthonygardner/glxgears/blob/master/glxgears.c


static float vrx = 0.0, vry = 0.0, vrz = 0.0, zoom = -40.0;
static float alpha = 0.0;
static int gear1, gear2, gear3;
static Display *disp;
static Window xwin;
// static GLXContext xctx;
// int attrib[] = {GLX_RGBA,
//                 GLX_RED_SIZE, 8,
//                 GLX_GREEN_SIZE, 8,
//                 GLX_BLUE_SIZE, 8,
//                 GLX_DOUBLEBUFFER,
//                 GLX_DEPTH_SIZE, 1,
//                 None};
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
    XDestroyWindow(disp, xwin);
    XCloseDisplay(disp);    
}

void X11GL::init(int x, int y, int w, int h, bool showinfo) {
    printf("(X11) init called:\n");
    getwindow(x, y, w, h, caption);
    XMapWindow(disp, xwin);
    reshapewindow(w, h);

    if (showinfo) info();    
}

void X11GL::xmain()
{
    printf("(X11) xmain called:\n");
    mainloop(disp, xwin);
}

int X11GL::getwindow(int x, int y, int w, int h, std::string &caption) {
    printf("(X11) getwindow start:\n");

    XSetWindowAttributes attr;
    unsigned long mask;
    Window root;
    Window win;
    // GLXContext ctx;
    XVisualInfo *visinfo;

    scrnum = DefaultScreen(disp);
    root = RootWindow(disp, scrnum);

    /* window attributes */
    attr.background_pixel = 0;
    attr.border_pixel = 0;
    // attr.colormap = XCreateColormap(disp, root, visinfo->visual, AllocNone);
    attr.event_mask = ExposureMask 
                    | StructureNotifyMask 
                    //| ConfigureNotify
                    //| ResizeRedirectMask
                    //| FocusChangeMask
                    | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask
                    | PointerMotionMask | PropertyChangeMask
                ;
    mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

    // win = XCreateSimpleWindow(disp, root, x,y,w,h, 0, 0, 0);

    win = XCreateWindow(disp, root, x, y, w, h,
                        0, 24, InputOutput,
                        0, mask, &attr);

    xwin = win;
    // xctx = ctx;
    printf("(X11) getwindow done:\n");
    return 0;
}

void X11GL::reshapewindow(int w, int h) {
    printf("(X11) reshapewindow called:\n");    
}

void X11GL::renderwindow(Display *) {
    // printf("(X11) renderwindow called:\n");    
}

void X11GL::mainloop(Display *disp, Window xwnd)
{
    printf("(X11) mainloop started.\n");
    bool done = false;
    char text[255];
    KeySym key;
    XEvent evnt;
    struct _point {
        int x, y;
    } dn, up, loc;
    XWindowAttributes attribs;
    Atom atoms[2] = { XInternAtom(disp, "_NET_WM_STATE_FULLSCREEN", False), None };
    while (!done) {
        alpha += 1.0;
        while (XPending(disp) > 0) {
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
                    case 42: // 'F'                        
                        XChangeProperty(disp, xwnd, XInternAtom(disp, "_NET_WM_STATE", False),
                            XA_ATOM, 32, PropModeReplace, (unsigned char *)atoms, 1);                    
                    break;
                    default:
                        printf("You pressed %d '%c'\n", evnt.xkey.keycode, text[0]); // fflush(stdout);
                    break;
                }
                if (XLookupString(&evnt.xkey, text, 255, &key, 0) == 1) {
                    if (evnt.xkey.keycode == 9) done = true;
                    //if (evnt.xkey.keycode == 38,38,40,25) vrx += 0.1;
                }
                break;
            case PropertyNotify: // Called when max/min/restore
                //printf("PropertyNotify %d\n", evnt.xproperty.type); 
                break;
            case ConfigureNotify: //Called when moving the window around
                //printf("ConfigureNotify %d %d\n", evnt.xconfigure.type, evnt.xconfigure.event);
                reshapewindow(evnt.xconfigure.width ,evnt.xconfigure.height);
                break;
            case ResizeRequest: 
                printf("-ResizeRequest.  Don't use this one\n");   
                break;
            case ClientMessage:
                printf("-ClientMessage case hit!\n");
                break;
            case ButtonPress:
                //printf("ButtonPress %d, %d, %d\n", evnt.xbutton.button, evnt.xbutton.x, evnt.xbutton.y); 
                dn.x = evnt.xbutton.x;
                dn.y = evnt.xbutton.y;
                if(evnt.xbutton.button == 4) zoom -= 10.0;
                if(evnt.xbutton.button == 5) zoom += 10.0;
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
                    printf("-Motionotify %d %d %d %d\n", evnt.xmotion.state, evnt.xmotion.type, evnt.xmotion.x, evnt.xmotion.y); 
                if (evnt.xmotion.state & 256) { // And with 0x0100 (left button down)
                    vry+=(loc.x-dn.x)/1.0;
                    vrx+=(loc.y-dn.y)/1.0;
                    dn.x=loc.x;
                    dn.y=loc.y;
                }
                if (evnt.xmotion.state & 512) { // And with 0x0200 (middle button down)
                    //printf("Middle button Motionotify %d %d %d %d\n", evnt.xmotion.state, evnt.xmotion.type, evnt.xmotion.x, evnt.xmotion.y); 
                }
                if (evnt.xmotion.state & 1024) { // And with 0x0400 (right button down)
                    //printf("Right button Motionotify %d %d %d %d\n", evnt.xmotion.state, evnt.xmotion.type, evnt.xmotion.x, evnt.xmotion.y); 
                }
                break;

            //case  KeyPress:             printf("-KeyPress"); break;
            //case  KeyRelease:           printf("-KeyRelease"); break;
            //case  ButtonPress:          printf("-ButtonPress"); break;
            //case  ButtonRelease:        printf("-ButtonRelease\n"); break;
            //case  MotionNotify:         printf("-Motionotify\n"); break;
            case  EnterNotify:          printf("-EnterNotify\n"); break;
            case  LeaveNotify:          printf("-LeaveNotify\n"); break;
            case  FocusIn:              printf("-FocusIn\n"); break;
            case  FocusOut:             printf("-FocusOut\n"); break;
            case  KeymapNotify:         printf("-KeyMapNotify\n"); break;
            //case  Expose:               printf("-Expose\n"); break;
            case  GraphicsExpose:       printf("-GraphicsExpose\n"); break;
            case  NoExpose:             printf("-NoExpose\n"); break;
            case  VisibilityNotify:     printf("-VisibilityNotify\n"); break;
            case  CreateNotify:         printf("-CreateNotify\n"); break;
            case  DestroyNotify:        printf("-DestroyNotify\n"); break;
            case  UnmapNotify:          printf("-UnmapNotify\n"); break;
            case  MapNotify:            printf("-MapNotify\n"); break;
            case  MapRequest:           printf("-MapRequest\n"); break;
            case  ReparentNotify:       printf("-ReparentNotify\n"); break;
            //case  ConfigureNotify:      printf("-ConfigureNotify\n"); break;
            case  ConfigureRequest:     printf("-ConfigureRequest\n"); break;
            case  GravityNotify:        printf("-GravityNotify\n"); break;
            //case  ResizeRequest:        printf("-ResizeRequest\n"); break;
            case  CirculateNotify:      printf("-CirculateNotify\n"); break;
            case  CirculateRequest:     printf("-CirculateRequest\n"); break;
            //case  PropertyNotify:       printf("-PropertyNotify\n"); break;
            case  SelectionClear:       printf("-SelectionClear\n"); break;
            case  SelectionRequest:     printf("-SelectionRequest\n"); break;
            case  SelectionNotify:      printf("-SelectionNotify\n"); break;
            case  ColormapNotify:       printf("-ColormapNotify\n"); break;
            //case  ClientMessage:        printf("-ClientMessage\n"); break;
            case  MappingNotify:        printf("-MappingNotify\n"); break;
            case  GenericEvent:         printf("-GenericEvent\n"); break;
            case  LASTEvent:            printf("-LASTEvent\n"); break;	/* must be bigger than any event # */        
            default: //printf("Default case!\n");
            break;
            }

        }
        renderwindow(disp);
    }
    printf("(X11) mainloop done:\n");
}

void X11GL::info(void){
    
}
