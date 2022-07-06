#include <X11/X.h>
#include <math.h>
#include <stdio.h>
#include "helpers.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include "wstructs.h"
#include "helpers.h"

    #define degToRad(angleInDegrees) ((angleInDegrees)*M_PI / 180.0)

    int generate(int i, int dist){
        int height = 300;
        //int value = ((height + sin(degToRad(i / 2 + 1)) * height)/2) * 0.5;
        //int value = 3276*sin(1.8*i*rads)+32767;
        float rads = M_PI/180;
        int value = dist*sin(1*i*rads);
        return value;

    }
    
    void fancyMoveResizeWindow(int id, Display *display, int newX, int newY/**, int newSizex, int newSizey**/){
        int expdistx = newX - windows[id].screenx;
        int distx = expdistx + expdistx/100;
        int valuex;



        for(int i = 0; i != 100; i++){
            valuex = windows[id].screenx + generate(i, distx);

            XMoveWindow(display, windows[id].id, valuex, windows[id].screeny);
            XFlush(display);
            msleep(10);
        }

        windows[id].screenx = valuex;
        int expdisty = newY - windows[id].screeny;
        int disty = expdisty + expdisty/100;
        int valuey;


        for(int i = 0; i != 100; i++){
            valuey = windows[id].screeny + generate(i, disty);

            XMoveWindow(display, windows[id].id, windows[id].screenx, valuey);
            XFlush(display);
            msleep(10);
        }
        

        windows[id].screeny = valuey;
        
        
    }

    int sine()
    {  
        Display *display = XOpenDisplay(NULL);
        int final;
        char name[] = "becker@becker: ~/Desktop";
        int cur = findwindow(name); 
        cur++;

        fancyMoveResizeWindow(cur, display, 1280, 540);
        printf("x: %i\ny: %i\n", windows[cur].screenx, windows[cur].screeny);

        int expx = 1200;
        
        return 0;

    } 