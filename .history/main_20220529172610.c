#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <ctype.h>

int isUpper(char c) {
  // check if the argument is the uppercase bound
  if (c >= 'A' && c <= 'Z') return 1;
  else 						return 0;
}

void enum_windows(Display* display, Window window, int depth) {
  int i;

  XTextProperty text;
  XGetWMName(display, window, &text);

  XWindowAttributes attr;

  if (text.value != NULL && text.value){
  XGetWindowAttributes(display, window, &attr);
  printf("%s %d x %d\n", text.value, attr.width, attr.height);
  }
  Window root, parent;
  Window* children;
  int n;
  XQueryTree(display, window, &root, &parent, &children, &n);
  if (children != NULL) {
    for (i = 0; i < n; i++) {
      enum_windows(display, children[i], depth + 1);
    }
    XFree(children);
  }
}



int main() {
  Display* display = XOpenDisplay(NULL);
  Window root = XDefaultRootWindow(display);
  enum_windows(display, root, 0);
}