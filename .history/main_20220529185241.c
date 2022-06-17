#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <ctype.h>


void enum_windows(Display* display, Window window) {
  int i;
  char **names;
  int count;
  Bool only_if_exists = True;
  Atom *atoms_return;
  int status = XInternAtoms(display, names, count, only_if_exists, atoms_return);


}



int main() {
  Display* display = XOpenDisplay(NULL);
  Window root = XDefaultRootWindow(display);
  enum_windows(display, root, 0);
}