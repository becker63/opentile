#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define n 4
// useful macro to find type of a var
#define type_name(expr)                       \
  (_Generic((expr),                           \
            char                              \
            : "char", unsigned char           \
            : "unsigned char", signed char    \
            : "signed char",                  \
              short                           \
            : "short", unsigned short         \
            : "unsigned short",               \
              int                             \
            : "int", unsigned int             \
            : "unsigned int",                 \
              long                            \
            : "long", unsigned long           \
            : "unsigned long",                \
              long long                       \
            : "long long", unsigned long long \
            : "unsigned long long",           \
              float                           \
            : "float",                        \
              double                          \
            : "double",                       \
              long double                     \
            : "long double",                  \
              void *                          \
            : "void*",                        \
              default                         \
            : "?"))

struct windowarray
{
  char name[50];
  long id;
  int screenx;
  int screeny;
  int sizex;
  int sizey;
};

struct windowarray windows[n];

Window *twindows = NULL;
unsigned long nitems_return = 0;

int display_get_current_desktop(Display *display, Window window)
{
  Atom actual_type_return;
  int actual_format_return = 0;
  unsigned long nitems_return = 0;
  unsigned long bytes_after_return = 0;
  long *desktop = 0;
  long ret;

  if (XGetWindowProperty(display, window, XInternAtom(display, "_NET_CURRENT_DESKTOP", False), 0, 1,
                         False, XA_CARDINAL, &actual_type_return, &actual_format_return,
                         &nitems_return, &bytes_after_return, (unsigned char **)&desktop) != Success)
  {
    return 0;
  }
  if (actual_type_return != XA_CARDINAL || nitems_return == 0)
  {
    return 0;
  }

  ret = desktop[0];
  XFree(desktop);

  return ret;
}

int window_get_desktop(Display *display, Window window)
{
  Atom actual_type_return;
  int actual_format_return = 0;
  unsigned long nitems_return = 0;
  unsigned long bytes_after_return = 0;
  long *desktop = 0;
  long ret = 0;

  if (XGetWindowProperty(display, window, XInternAtom(display, "_NET_WM_DESKTOP", False), 0, 1, False, XA_CARDINAL, &actual_type_return, &actual_format_return, &nitems_return, &bytes_after_return, (unsigned char **)(void *)&desktop) != Success)
    return 0;

  ret = desktop[0];
  XFree(desktop);

  return ret;
}

int display_get_windows(Display *display, Window window, int desktop)
{
  Atom actual_type_return;
  int actual_format_return = 0;
  unsigned long bytes_after_return = 0;
  unsigned long count;

  if (XGetWindowProperty(display, window, XInternAtom(display, "_NET_CLIENT_LIST", False), 0, 0x7fffffff, False, XA_WINDOW, &actual_type_return, &actual_format_return, &nitems_return, &bytes_after_return, (unsigned char **)&twindows) != Success)
  {
    fprintf(stderr, "eh?");
    exit(1);
  }

  int x1 = 0;
  for (count = 0; count < nitems_return; count++)
  {
    long w_desktop = window_get_desktop(display, twindows[count]);
    if (w_desktop == desktop)
    {
      XTextProperty text;
      XGetWMName(display, twindows[count], &text);

      int x, y;

      XWindowAttributes attr;
      Window child;
      XGetWindowAttributes(display, twindows[count], &attr);

      XTranslateCoordinates(display, twindows[count], window, 0, 0, &x, &y, &child);

      //printf("%s: %lu    %d x %d,  %d x %d   %i\n\n", text.value, twindows[count], attr.width, attr.height, x - attr.x, y - attr.y, x1);

      strcpy(windows[x1].name, text.value);
      windows[x1].id = twindows[count];
      windows[x1].screenx = x - attr.x;
      windows[x1].screeny = y - attr.y;
      windows[x1].sizex = attr.width;
      windows[x1].sizey = attr.height;
      x1 = x1 + 1;
    }
  }
}

void printstructs()
{
  int a;
  printf("num    x       y      sx     sy             name                id\n\n");
  for (a = 0; a < n; a++)
  {
    if (windows[a].id != 0)
    {
      char formatedname[20] = "";
      // neat trick: https://tinyurl.com/stratindex prints string at index
      strncpy(formatedname, &windows[a].name[0], 17);
      strcat(formatedname, "...");
      printf(" %i:    %i  *  %i     %i  *  %i    %s    %lu\n", a, windows[a].screenx, windows[a].screeny, windows[a].sizex, windows[a].sizey, formatedname, windows[a].id);
    }
  }
}

int findwindow(char *name){
  int a;
  for (a = 0; a < n; a++)
  {
    if (windows[a].id != 0)
    {
      if(strchr(name, *windows[a].name) != NULL)
      {
        return a;
      }
    }
    }
}

int main()
{
  Display *display = XOpenDisplay(NULL);
  Window root = XDefaultRootWindow(display);
  int desktop = display_get_current_desktop(display, root);
  int currentwindows = display_get_windows(display, root, desktop);

  puts("\n");

  printstructs();

  int j = findwindow("main.c");

  printf("%i\n\n", j);

  Screen *screen = ScreenOfDisplay(display, 0);

  int sizey = screen->height - 50;

  int sizex = (screen->width / 2) - 50;

  //printf("%i\n", screen->height);

  printf("%i\n", sizex);

  printf("%d\n", sizey);


   //XMoveWindow(display, windows[j].id, screen->width + 25, screen->height +  25);

   XResizeWindow(display, windows[j].id, sizex, sizey);
   
   XFlush(display);




  printf("%ix%i", windows[j].screenx, windows[j].screeny);




}








