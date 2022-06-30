#include <X11/Xlib.h>

extern int findwindow(char *name);

extern int numwindows();

extern int display_get_current_desktop(Display *display, Window window);

extern int window_get_desktop(Display *display, Window window);

extern int enumwindows();

extern unsigned char *getname(int window);

extern void printewin();