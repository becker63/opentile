#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <ctype.h>


void enum_windows(Display* display, Window window, int depth) {
  int i;
  char **names;
  int count;
  Atom *atoms_return;
  XInternAtoms(display, names, count, 1, atoms_return);

  for(i = 0; names[i] != '\0'; i++)
{
   printf("%c", names[i]);
}

}



int main() {
  Display* display = XOpenDisplay(NULL);
  Window root = XDefaultRootWindow(display);
  enum_windows(display, root, 0);
}