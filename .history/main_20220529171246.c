#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

void enum_windows(Display* display, Window window, int depth) {
  int i;

  XTextProperty text;
  XGetWMName(display, window, &text);
  char* name;
  XFetchName(display, window, &name);

  if (text.value != null)
  printf("%s\n", text.value);

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