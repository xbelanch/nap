#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

double get_time(void)
{
  struct timeval timev;
  gettimeofday(&timev, NULL);
  return (double)timev.tv_sec + (((double)timev.tv_usec) / 1000000);
}

// gcc main.c -lX11 -ggdb -o main
int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv[0];

    Display *display;
    Window window;
    int screen;
    XEvent event;
    const char *msg = "Hello, X11!";

    XSizeHints hint;
    hint.x = 10;
    hint.y = 10;
    hint.width = 640;
    hint.height = 480;
    hint.flags = PPosition|PSize;

    display = XOpenDisplay((char*)0); // WHAT?
    if (display == NULL) {
      fprintf(stderr, "Cannot open display\n");
      exit(1);
    }
    screen = DefaultScreen(display);


    XColor color;
    Colormap colormap;
    char pink[] = "#FF00FF"; // Pink!
    colormap = DefaultColormap(display, 0);
    XParseColor(display, colormap, pink, &color);
    XAllocColor(display, colormap, &color);

    window =  XCreateSimpleWindow(display,
                                  RootWindow(display, screen),
                                  hint.x, hint.y,
                                  hint.width, hint.height,
                                  5,
                                  WhitePixel(display, screen),
                                  color.pixel);

    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);
    XFlush(display);

    /* graphics context */
    GC gc = XCreateGC(display, window, 0, 0);
    XSetBackground(display, gc, BlackPixel(display, screen));
    XSetForeground(display, gc, WhitePixel(display, screen));

    // XMapRaised(display, window);

    /* event loop */
    while(1){
        XNextEvent(display, &event);
        if (event.type == Expose) {
            XFillRectangle(display, window, gc, 128, 128, 32, 32);
            XDrawString(display, window, gc, 10, 50, msg, strlen(msg));
        }

        if (event.type == KeyPress)
            break;
    }

    /* finalization */
    XFreeGC(display,gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
    return (0);
}
