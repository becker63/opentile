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
    void fancyMoveResizeWindow(int id, Display *display, int newX, int newY, int newSizex, int newSizey){
        for(int i = 0; i != 100; i++){;  
            int tvaluex = windows[id].screenx - newX;
            int valuex = generate(i, tvaluex);

            int tvaluey = windows[id].screeny - newY;
            int valuey = generate(i, tvaluey);

            int tsizex = windows[id].posx - newSizex;
            int sizex = generate(i, tsizex);

            int tsizey = windows[id].posy - newSizey;
            int sizey = generate(i, tsizey);

            printf("i: %i,  val = %i\n\nx: %i\ny: %i\nsx: %i\nsy: %i\n\nrx: %i\nry: %i\nrsx: %i\nrsy: %i",i, generate(i, newX), windows[id].screenx, windows[id].screeny, windows[id].posx, windows[id].posy,valuex, valuey,sizex, sizey);
            XMoveResizeWindow(display, windows[id].id, valuex, valuey, sizex, sizey);
            XFlush(display);
            msleep(100);
        }
        XMoveResizeWindow(display, windows[id].id, newX, newY, newSizex, newSizey);
        XFlush(display);

    }

    int sine(Display *display)
    {  
        //Display *display = XOpenDisplay(NULL);
        int final;
        char name[] = "becker@becker: ~";
        int cur = findwindow(name); 


        int expdist = 300;
        int dist = expdist + (expdist / 100);
        
        XMoveResizeWindow(display, windows[cur].id, 0, 0, 10, 10);
        XFlush(display);
        fancyMoveResizeWindow(cur, display, expdist, 0, expdist, expdist);
        XMoveResizeWindow(display, windows[cur].id, 0, 0, 10, 10);
        
        //printf("%i  %i  %i\n",expdist - final, expdist, final);

        return 0;
        
    }