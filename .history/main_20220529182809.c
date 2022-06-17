#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <ctype.h>


void enum_windows(Display* display, Window window, int depth) {
  int i;

  unsigned long prop = 0xFFFFFFFF; // note long! even if long is 64 bit

  XChangeProperty(display, window, XInternAtom(display, "_NET_WM_DESKTOP", 1),
                XA_ATOM, // note CARDINAL not ATOM
                32,
                PropModeReplace,
                (unsigned char*)&prop,
                1); // note 1

   XMapWindow(display, window);
}



int main() {
  Display* display = XOpenDisplay(NULL);
  Window root = XDefaultRootWindow(display);
  enum_windows(display, root, 0);
}