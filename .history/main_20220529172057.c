#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

void enum_windows(Display* display, Window window, int depth) {
  int i;

  XTextProperty text;
  XGetWMName(display, window, &text);

  XWindowAttributes attr;

  if (text.value != NULL){
  printf("%s\n", text.value, window);
  XGetWindowAttributes(display, text.value, &attr);
  printf("[0x%x] %d x %d\n", , attr.width, attr.height);
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