#include <X11/Xlib.h>
#include <X11/Xatom.h>

#include <stdio.h>
#include <stdlib.h>

 
int
        main
            (int argc , char* argv[ ] ){


    Display* display;
    char* connection_string = NULL;
    display = XOpenDisplay (connection_string  );
    if (display == NULL ){
        fprintf (stderr, "Error: XOpenDisplay (%s )\n", connection_string == NULL ? "NULL" :  connection_string );
        exit (EXIT_FAILURE );}

    char* atom_name;
    atom_name = XGetAtomName (display, XA_PRIMARY );

    printf ("Name of atom XA_PRIMARY %lu is : %s\n", XA_PRIMARY, atom_name );
    XFree (atom_name );


    int num_atoms = 3;
    char* atom_names [num_atoms ];
    Atom atoms [ ] = {_NET_CURRENT_DESKTOP, XA_COLORMAP, XA_WM_SIZE_HINTS };
    int status = XGetAtomNames (display, 
                                atoms, 
                                num_atoms, 
                                atom_names ); 

    if (status == 0 ){
        fprintf (stderr, "Error: XGetAtomNames \n" );
        exit (EXIT_FAILURE );}

    printf ("Name of atom XA_STRING %lu is : %s\n", XA_STRING, atom_names [0 ] );
    printf ("Name of atom XA_COLORMAP %lu is : %s\n", XA_COLORMAP, atom_names [1 ] );
    printf ("Name of atom XA_WM_SIZE_HINTS %lu is : %s\n", XA_WM_SIZE_HINTS, atom_names [2 ] );

    exit (EXIT_SUCCESS );}