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
 

int findClosest(int x, int y){
    int size = enumwindows();
    int distancelist[size];


    for(int i = 0; ewindows[i].on == 1; i++){
        int distance = sqrt(pow(x - ewindows[i].expectedx, 2) + pow(y - ewindows[i].expectedy, 2));
        distancelist[i] = distance;
        //printf("distance: %i, xy: %ix%i, exy: %ix%i, name: %s\n", distancelist[i], x,y,ewindows[i].expectedx,ewindows[i].expectedy,windows[i].name);
    }

    int i = smallest_element_index(distancelist, size);
    //printf("%i", i);
    

    //printf("\ndistance: %i, xy: %ix%i, exy: %ix%i. name: %s\n", distancelist[i], x,y,ewindows[i].expectedx,ewindows[i].expectedy,windows[i].name);


    //printf("\n\n\n");
    return i;
    
}