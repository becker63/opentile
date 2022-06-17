#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <ctype.h>


void enum_windows(Display* display, Window window, int depth) {
  int num_string =3;
    char* strings [ ] = {"First string", "Second string", "Third string" };
    Atom atom [num_string ];
    int status = XInternAtoms (display, //The connection
                    strings, //The strings
                    num_string, // count of strings
                    0,  // only_if_exists
                    atom );
    if (status == 0 ){
        fprintf (stderr, "Error: XInternAtoms \n" );


    for (int i2 = 0; i2 < num_string; i2++ )
        printf("atom [%d ] is %lu\n", i2, atom[i2 ] );
    }

}



int main() {
  Display* display = XOpenDisplay(NULL);
  Window root = XDefaultRootWindow(display);
  enum_windows(display, root, 0);
}