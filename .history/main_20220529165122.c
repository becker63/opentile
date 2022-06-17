#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>

int
main(int argc, char **argv)
{
    XtAppContext app;
    Display *display;
    int status = 0;

    app = XtCreateApplicationContext();
    display = XtOpenDisplay(app, 0, argv[0], "xgeometry", 0, 0, &argc, argv);

    if (display)
    {
        while (--argc)
        {
            char const *idstring = *++argv;
            char *endptr = 0;
            unsigned long id;

            if (idstring[0] != '0')
                id = strtoul(idstring, &endptr, 10);
            else if (idstring[1] == 'x' || idstring[1] == 'X')
                id = strtoul(idstring + 2, &endptr, 16);
            else
                id = strtoul(idstring + 1, &endptr, 8);
            if (*endptr)
            {
                fprintf(stderr, "Invalid window id: %s\n", idstring);
                status = 1;
            }
            else
            {
                Window win = (Window) id;

                while (1)
                {
                    Window parent;
                    Window  root;
                    Window *children;
                    int nchildren;
                    

                    if (!XQueryTree(display, win, &root, &parent, &children, &nchildren))
                    {
                        fprintf(stderr, "Error finding top level window for %08lx", id);
                        status = 1;
                        break;
                    }
                    XFree(children);
                    if (parent == root)
                    {
                        int x, y;
                        unsigned w, h;
                        unsigned border;
                        unsigned depth;

                        if (XGetGeometry(display, win, &root, &x, &y, &w, &h, &border, &depth))
                        {
                            printf("0x%08lx %d %d %u %u %u\n", id, x, y, w, h, border);
                        }
                        else
                        {
                            fprintf(stderr, "Could not get location of window 0x%08lx\n", id);
                            status = 1;
                        }
                        break;
                    }
                    win = parent;
                }
            }

        }
        XtCloseDisplay(display);
    }
    else
    {
        fprintf(stderr, "Cannot open display\n");
        status = 1;
    }

    XtDestroyApplicationContext(app);

    return status;
}