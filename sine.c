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

    int sine()
    {  
        Display *display = XOpenDisplay(NULL);
        int final;
        char name[] = "becker@becker: ~";
        int cur = findwindow(name); 

        for(int i2 = 0; i2 != 100; i2++){

        int expdist = 100 * i2;
        int dist = expdist + 2;
        

        for(int i = 0; i != 100; i++){
            int value = generate(i, dist);
            //printf("i: %i,  val = %i\nx: %i\n",i, value, windows[cur].screenx + value);
            final = windows[cur].screenx + value;
            XMoveWindow(display, windows[cur].id, windows[cur].screenx + value, windows[cur].screeny);
            XFlush(display);
            // msleep(10);
        }
        printf("%i  %i  %i\n",expdist - final, expdist, final);
        }
        return 0;
        
    }