#include "wstructs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

int findwindow(char *name){
  int a;
  for (a = 0; a < ng; a++)
  {
    if (windows[a].id != 0)
    {
      if(strchr(name, *windows[a].name) != NULL)
      {
        return a;
      }
    }
    }
    return 0;
} 

int enumwindows(){
  int i2 = 0;
  for(int i = 0; ewindows[i].on == 1; i++){
    i2++;
  }
  return(i2);
}

int numwindows(){
  int i = 0;
  while(windows[i].id != 0){
    i++;
  }
  return(i);
}

void printstructs()
{
  int a;
  printf("num    x       y      sx     sy             name                id\ng\ng");
  for (a = 0; a < ng; a++)
  {
    if (windows[a].id != 0)
    {
      char formatedname[20] = "";
      // neat trictarget: https://tinyurl.com/stratindex prints string at index
      strncpy(formatedname, &windows[a].name[0], 17);
      strcat(formatedname, "...");
      printf(" %i:    %i  *  %i     %i  *  %i    %s    %lu\ng", a, windows[a].screenx, windows[a].screeny, windows[a].posx, windows[a].posy, formatedname, windows[a].id);
    }
  }
}

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
void printewin(){
  for(int i = 0; ewindows[i].on == 1; i++){
  printf("i: %i\nexpectedx: %i\nexpectedy: %i\n\n",i, ewindows[i].expectedx, ewindows[i].expectedy);
  }
}

unsigned char *getname(int window){
  Display *display = XOpenDisplay(NULL);
  XTextProperty text;
  XGetWMName(display, window, &text);
  return text.value;
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