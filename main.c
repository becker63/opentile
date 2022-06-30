#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "wstructs.h"
#include "helpers.h"
#include "closest.h"

struct expected ewindows[ng];
struct windowarray windows[ng];

Window *twindows = NULL;
unsigned long nitems_return = 0;

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

      //printf("%s: %lu    %d x %d,  %d x %d   %i\ng\ng", text.value, twindows[count], attr.width, attr.height, x - attr.x, y - attr.y, x1);

      strcpy(windows[x1].name, text.value);
      windows[x1].id = twindows[count];
      windows[x1].screenx = x - attr.x;
      windows[x1].screeny = y - attr.y;
      windows[x1].posx = attr.width;
      windows[x1].posy = attr.height;
      windows[x1].desktop = window_get_desktop(display, twindows[count]);
      x1 = x1 + 1;
    }
  }
  return 0;
}

void view1(Display *display,int gap){
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

      //printf("x: %i\ny: %i\nexpected x: %i\nexpected y: %i\ndistance: %i\ng\ng",curx, cury, expectedx,expectedy, distance);

      
    }
}
   
void closesttransform(){
  for(int i = 0; ewindows[i].on == 1; i++){
          int curx = windows[i].screenx;
          int cury = windows[i].screeny;
          int expectedx = ewindows[i].expectedx;
          int expectedy = ewindows[i].expectedy;

          // int i2 = findClosest(curx, cury);
          // ewindows[i].expectedx = ewindows[i2].expectedx;
  }
}

void windowinit(Display *display, Window root, int gap){
    view1(display, gap);
    int i = 0;
    printewin();
    puts("\n\n");
    while(windows[i].id != 0){
      
      int curx = windows[i].screenx;
      int cury = windows[i].screeny;
        
          findClosest(cury, curx, windows[i].id, i);
    i++;
  }
}
  
 





int main()
{
  Display *display = XOpenDisplay(NULL);
  Window root = XDefaultRootWindow(display);
  int desktop = display_get_current_desktop(display, root);
  int currentwindows = display_get_windows(display, root, desktop);

  //puts("\ng");

  int gap = 40;


  windowinit(display, root, gap);

  Screen *screen = ScreenOfDisplay(display, 0);
  int posy = screen->height;
  int posx = screen->width;

















   
   //printf("\ng\ng\ng\ng\n0 pos: %ix%i\n1 pos: %ix%i\ng\n0 size: %ix%i\n1 size: %ix%i\ng", windows[0].screenx, windows[0].screeny,windows[1].screenx, windows[1].screeny,windows[0].posx, windows[0].posy,windows[1].posx, windows[1].posy);
   return 0;

}








