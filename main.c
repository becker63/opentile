#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define n 10

struct windowarray
{
  char name[50];
  long id;
  int screenx;
  int screeny;
  int posx;
  int posy;
};

struct expected
{
  int expectedsizex;
  int expectedsizey;
  int expectedx;
  int expectedy;
  int on;
};

struct expected ewindows[n];

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
      windows[x1].posx = attr.width;
      windows[x1].posy = attr.height;
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
      // neat trictarget: https://tinyurl.com/stratindex prints string at index
      strncpy(formatedname, &windows[a].name[0], 17);
      strcat(formatedname, "...");
      printf(" %i:    %i  *  %i     %i  *  %i    %s    %lu\n", a, windows[a].screenx, windows[a].screeny, windows[a].posx, windows[a].posy, formatedname, windows[a].id);
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

int numwindows(){
  int i = 0;
  while(windows[i].id != 0){
    i++;
  }
  return(i);
}

int enumwindows(){
  int i = 0;
  int i2 = 0;
  while(i != n){
    if (ewindows[i].on == 1){
      i2++;
    }

    i++;
  }
  return(2);
}

int view1(Display *display,int gap){
    int i;
    Screen *screen = ScreenOfDisplay(display, 0);

    int screeny = screen->height;
    int screenx = screen->width;

    int res = windows[0].screenx;

    int nwindows = numwindows();

     ewindows[0].expectedsizex = screenx / 2;
     ewindows[0].expectedsizey = screeny;
     ewindows[0].expectedy = 0;
     ewindows[0].expectedx = 0;
     ewindows[0].on = 1;

    for ( i = 1; i != nwindows; i++) {
      int o = screeny / (nwindows - 1);


      int expectedsx = screenx / 2;
      int expectedsy = o;




      int expectedy =((o * i) - screeny) * -1;
      int expectedx = screenx / 2;

      ewindows[i].expectedsizex = expectedsx;
      ewindows[i].expectedsizey = expectedsy;
      ewindows[i].expectedy = expectedy;
      ewindows[i].expectedx = expectedx;
      ewindows[i].on = 1;


      //int distance = sqrt(pow(curx - expectedx, 2) + pow(cury - expectedy, 2));

      //printf("x: %i\ny: %i\nexpected x: %i\nexpected y: %i\ndistance: %i\n\n",curx, cury, expectedx,expectedy, distance);

      
    }
}
   
int windowinit(Display *display, Window root, int gap){
    view1(display, gap);
    int i = 0;
    while(windows[i].id != 0){
      
      int i2 = 0;
      while(i2 != n){
        if (ewindows[i2].on == 1){
          int curx = windows[i].screenx;
          int cury = windows[i].screeny;
          int expectedx = ewindows[i2].expectedx;
          int expectedy = ewindows[i2].expectedy;
  
          int distance = sqrt(pow(curx - expectedx, 2) + pow(cury - expectedy, 2));
  
          printf("x: %i\ny: %i\nexpected x: %i\nexpected y: %i\ndistance: %i\nname: %s\n\n",curx, cury, expectedx,expectedy, distance, windows[i].name);
      
        }
        i2++;

      }

      //printf("x: %i\ny: %i\nexpected x: %i\nexpected y: %i\ndistance: %i\nname: %s\n\n",curx, cury, expectedx,expectedy, distance, windows[i].name);
    i++;
  }
}
  
 






int main()
{
  Display *display = XOpenDisplay(NULL);
  Window root = XDefaultRootWindow(display);
  int desktop = display_get_current_desktop(display, root);
  int currentwindows = display_get_windows(display, root, desktop);

  //puts("\n");

  int gap = 40;


  windowinit(display, root, gap);

  Screen *screen = ScreenOfDisplay(display, 0);
  int posy = screen->height;
  int posx = screen->width;

















   
   //printf("\n\n\n\n\n0 pos: %ix%i\n1 pos: %ix%i\n\n0 size: %ix%i\n1 size: %ix%i\n", windows[0].screenx, windows[0].screeny,windows[1].screenx, windows[1].screeny,windows[0].posx, windows[0].posy,windows[1].posx, windows[1].posy);
   return 0;

}








