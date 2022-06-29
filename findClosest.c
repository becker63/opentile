#include "wstructs.h"
#include "helpers.h"
#include <stdio.h>
#include <math.h>

int smallest_element_index(int work_array[], int max_j)
{
        int index = 0;
        int i;
        for( i = 1; i < max_j; i++)
        {
                if(work_array[i] < work_array[index])
                        index = i;
        }

        return index;
}
 

int findClosest(int x, int y, int id){
    int size = enumwindows();
    int distancelist[size];


    for(int i = 0; ewindows[i].on == 1; i++){
        int distance = sqrt(pow(x - ewindows[i].expectedx, 2) + pow(y - ewindows[i].expectedy, 2));
        distancelist[i] = distance;
        //printf("\nid: %i\ndistance: %i\n xy: %ix%i\n exy: %ix%i\n name: %s\n\n",i, distancelist[i], x,y,ewindows[i].expectedx,ewindows[i].expectedy,getname(id));
    }

    int i = smallest_element_index(distancelist, size);
    //printf("%i", i);
    

    //printf("\nselected: %i\ndistance: %i\n xy: %ix%i\n exy: %ix%i\n name: %s\n\n",i, distancelist[i], x,y,ewindows[i].expectedx,ewindows[i].expectedy,getname(id));

    ewindows[i].corrWinDistance = distancelist[i];
    ewindows[i].correspondingWin = id;

    printf("expectedx: %i\nexpectedy: %i\ncorrWin: %s\ndistWin: %i",ewindows[i].expectedx, ewindows[i].expectedy, getname(ewindows[i].correspondingWin), ewindows[i].corrWinDistance);


    printf("\n\n\n");
    return i;
    
}