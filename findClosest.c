#include "wstructs.h"
#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
 

int transformgen(int x, int y, int id, int i, struct Transform transform[]){
    int size = enumwindows();
    struct Temp  {
        int *distance;
        int *ex;
        int *ey;
        int *x;
        int *y;
        int *id;
    };

    struct Temp tdata;

    tdata.distance = (int*)malloc(sizeof(int) * size);
    /** lol so dumb, I only need one of these (distance), Ill clean up later **/
    tdata.ex = (int*)malloc(sizeof(int) * size);
    tdata.ey = (int*)malloc(sizeof(int) * size);
    tdata.x = (int*)malloc(sizeof(int) * size);
    tdata.y = (int*)malloc(sizeof(int) * size);
    tdata.id = (int*)malloc(sizeof(int) * size);

    for(int i = 0; ewindows[i].on == 1; i++){
        int distance = sqrt(pow(x - ewindows[i].expectedx, 2) + pow(y - ewindows[i].expectedy, 2));
        tdata.distance[i] = distance;
        tdata.ex[i] = ewindows[i].expectedx;
        tdata.ey[i] = ewindows[i].expectedy;
        tdata.x[i] = windows[i].posx;
        tdata.y[i] = windows[i].posy;
        tdata.id[i] = windows[i].id;
    }

    int closest = smallest_element_index(tdata.distance, size); /** Smallest eWindow index **/

    transform[i].distance = tdata.distance[closest];
    transform[i].expectedx = tdata.ex[closest];
    transform[i].expectedy = tdata.ey[closest];
    transform[i].x = tdata.x[closest];
    transform[i].y = tdata.y[closest];
    transform[i].id = tdata.id[closest];
    

    free(tdata.distance);
    free(tdata.ex);
    free(tdata.ey);
    free(tdata.x);
    free(tdata.y);
    printf("\n\n\n\n");
    return closest;
    
}

void transformClean(struct Transform transform[]){
    
}

int findClosest(int x, int y, int id){
    puts("start");
    int size = enumwindows();
    struct Transform transform[size];
    for(int i = 0; ewindows[i].on == 1; i++){
        transformgen(windows[i].screenx, windows[i].screeny, windows[i].id, i, transform);
        
        printf("tdistance: %i\n tex: %i\n tey: %i\ntx: %i\nty: %i\ntid: %i", transform[i].distance, transform[i].expectedx,  transform[i].expectedy, transform[i].x, transform[i].y, transform[i].id);
    }
    puts("\n\nend\n\n\n\n");
}