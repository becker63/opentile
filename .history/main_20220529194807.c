int getprop (Display *disp, char *name, Window win) {
        Atom prop = XInternAtom(disp,name,False), type;
        int form, r = 0;
        unsigned long len, remain;
        unsigned char *list;
        char *tname;
 
        errno = 0;
        if (XGetWindowProperty(disp,win,prop,0,1024,False,AnyPropertyType,
                &type,&form,&len,&remain,&list) != Success) {
                perror("GetWinProp");
                return 0;
        }
        if (type == None) printf("%s is not available.\n",name);
        else {
                tname = atomtype(type);
                printf ("%s (type %s, %lu %d-bit items) remaining: %lu\n",name,tname,len,form,remain);
                XFree(tname);
                r = 1;
        }
        XFree(list);
        return r;
}
 
char *atomtype (Atom x) {
    char *type = malloc(32);
    switch (x) {
        case XA_PRIMARY:
            strcpy(type,"XA_PRIMARY");
            break;
        case XA_SECONDARY:
            strcpy(type,"XA_SECONDARY");
            break;
        case XA_ARC:
            strcpy(type,"XA_ARC");
            break;
        case XA_ATOM:
            strcpy(type,"XA_ATOM");
            break;
        case XA_CARDINAL:
            strcpy(type,"XA_CARDINAL");
            break;
        case XA_INTEGER:
            strcpy(type,"XA_INTEGER");
            break;
        case XA_STRING:
            strcpy(type,"XA_STRING");
            break;
        case XA_WINDOW:
            strcpy(type,"XA_WINDOW");
            break;
        case XA_WM_HINTS:
            strcpy(type,"XA_WM_HINTS");
            break;
        default:
            sprintf(type,"unlisted (%lu), see Xatom.h",x);
            break;
        }
        return type;
}