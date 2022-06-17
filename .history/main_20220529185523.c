#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <ctype.h>


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

GArray * display_get_windows(struct display * display, long desktop) {
	Atom actual_type_return;
	int actual_format_return = 0;
	unsigned long nitems_return = 0;
	unsigned long bytes_after_return = 0;
	unsigned long count;
	Window * windows = NULL;

	GArray * array;

	if (XGetWindowProperty(display->display, display->root, XInternAtom(display->display, "_NET_CLIENT_LIST", False), 0, 0x7fffffff, False, XA_WINDOW, &actual_type_return, &actual_format_return, &nitems_return, &bytes_after_return, (unsigned char **)&windows) != Success) {
		return NULL;
	}

	array = g_array_new(FALSE, FALSE, sizeof(Window));
	for (count = 0; count < nitems_return; count++) {
		long w_desktop = window_get_desktop(display, windows[count]);
		if (w_desktop == desktop || w_desktop == ULONG_MAX) {
			g_array_append_val(array, windows[count]);
		}
	}

	XFree(windows);

	return array;
}




int main() {
  Display* display = XOpenDisplay(NULL);
  Window root = XDefaultRootWindow(display);
  printf("%i", display_get_current_desktop(display, root));
}