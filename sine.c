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
        for(int i = 0; i != 100; i++){
            int values[4] = {0,0,0,0};  
            values[0] =  values[0] + generate(i, newX);
            values[1] = values[1] + generate(i, newY);
            values[2] = values[2] + generate(i, newSizex);
            values[3] = values[3] + generate(i, newSizey);
            for(int i2 = 0; i2 != 4; i2++){
                printf("%i: %i\n", i2, values[i2]);
            }
            printf("i: %i,  val = %i\n\nx: %i\ny: %i\nsx: %i\nsy: %i\n\nrx: %i\nry: %i\nrsx: %i\nrsy: %i",i, generate(i, newX), windows[id].screenx, windows[id].screeny, windows[id].posx, windows[id].posy,values[0], values[1],values[2], values[3]);
            XMoveResizeWindow(display, windows[id].id, values[0], values[1], values[2], values[3]);
            XFlush(display);
            msleep(10);
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