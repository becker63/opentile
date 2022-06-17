#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>




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
	unsigned long nitems_return = 0;
	unsigned long bytes_after_return = 0;
	unsigned long count;
	Window * windows = NULL;

	if (XGetWindowProperty(display, window, XInternAtom(display, "_NET_CLIENT_LIST", False), 0, 0x7fffffff, False, XA_WINDOW, &actual_type_return, &actual_format_return, &nitems_return, &bytes_after_return, (unsigned char **)&windows) != Success) {
		fprintf( stderr, "eh?" );
        exit(1);
	}

    int x = 0;
    for (count = 0; count < nitems_return; count++) {
		long w_desktop = window_get_desktop(display, windows[count]);
		if (w_desktop == desktop) {
            typeof(windows[count]
			x = x + 1;
		}
    }
    
	XFree(windows);

	return x;
}




int main() {
  Display* display = XOpenDisplay(NULL);
  Window root = XDefaultRootWindow(display);
  int currentwindows = display_get_windows(display, root, display_get_current_desktop(display, root));

  printf("%i", currentwindows);
}