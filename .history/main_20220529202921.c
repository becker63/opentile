#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

//useful macro to find type of a var
#define type_name(expr) \
    (_Generic((expr), \
              char: "char", unsigned char: "unsigned char", signed char: "signed char", \
              short: "short", unsigned short: "unsigned short", \
              int: "int", unsigned int: "unsigned int", \
              long: "long", unsigned long: "unsigned long", \
              long long: "long long", unsigned long long: "unsigned long long", \
              float: "float", \
              double: "double", \
              long double: "long double", \
              void*: "void*", \
              default: "?")) 

struct windowarray {
    char name;
    int screenx;
    int screeny;
    int sizex;
    int sizey;
};

struct windowarray windows[100];


Window * twindows = NULL;
unsigned long nitems_return = 0;

int display_get_current_desktop(Display* display, Window window) {
  Atom actual_type_return;
	int actual_format_return = 0;
	unsigned long nitems_return = 0;
	unsigned long bytes_after_return = 0;
	long * desktop = 0;
	long ret;

	if (XGetWindowProperty(display, window, XInternAtom(display, "_NET_CURRENT_DESKTOP", False), 0, 1,
		False, XA_CARDINAL, &actual_type_return, &actual_format_return,
		&nitems_return, &bytes_after_return, (unsigned char**)&desktop) != Success) {
			return 0;
	}
	if (actual_type_return != XA_CARDINAL || nitems_return == 0) {
		return 0;
	}

	ret = desktop[0];
	XFree(desktop);

	return ret;


}

int window_get_desktop(Display * display, Window window) {
	Atom actual_type_return;
	int actual_format_return = 0;
	unsigned long nitems_return = 0;
	unsigned long bytes_after_return = 0;
	long * desktop = 0;
	long ret = 0;

	if (XGetWindowProperty(display, window, XInternAtom(display, "_NET_WM_DESKTOP", False), 0, 1, False, XA_CARDINAL, &actual_type_return, &actual_format_return, &nitems_return, &bytes_after_return, (unsigned char**)(void*)&desktop) != Success) return 0;

	ret = desktop[0];
	XFree(desktop);

	return ret;

}

int display_get_windows(Display* display, Window window, int desktop) {
	Atom actual_type_return;
	int actual_format_return = 0;
	unsigned long bytes_after_return = 0;
	unsigned long count;

	if (XGetWindowProperty(display, window, XInternAtom(display, "_NET_CLIENT_LIST", False), 0, 0x7fffffff, False, XA_WINDOW, &actual_type_return, &actual_format_return, &nitems_return, &bytes_after_return, (unsigned char **)&twindows) != Success) {
		fprintf( stderr, "eh?" );
        exit(1);
	}

    int x = 0;
    for (count = 0; count < nitems_return; count++) {
		long w_desktop = window_get_desktop(display, twindows[count]);
		if (w_desktop == desktop) {
            XTextProperty text;
            XGetWMName(display, twindows[count], &text);

            int x, y;
            
            XWindowAttributes attr;
            Window child;
            XGetWindowAttributes(display, twindows[count], &attr);

            XTranslateCoordinates( display, twindows[count], window, 0, 0, &x, &y, &child );

            printf("%s     %d x %d,    %d x %d \n", text.value, attr.width, attr.height, x - attr.x,y - attr.y);

            windows[count].name = text.value;
            windows[count].screenx = x - attr.x;
            windows[count].screeny = y - attr.y;
            windows[count].sizex = attr.width;
            windows[count].sizey = attr.height;
			x = x + 1;
		}
    }
    


	return x;
}




int main() {
  Display* display = XOpenDisplay(NULL);
  Window root = XDefaultRootWindow(display);
  int desktop = display_get_current_desktop(display, root);
  int currentwindows = display_get_windows(display, root, desktop);

  
  int a;
  for(a = 0; a < n; a++)
     {
        printf(windows[a].)
     }


}