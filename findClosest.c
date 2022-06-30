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

void printTransform(struct Transform transform[]){
    int size = enumwindows();
    for(int i = 0; i != size; i++){
                
        printf("\ndistance: %i\neid: %i\nid: %i\n\n", transform[i].distance, transform[i].eid, transform[i].id);

    }
}

void checkDupes(struct Transform transform[], int size){

   for (int i = 0; i < size; i++) {
        transform[transform[i].eid % size].eid
            = transform[transform[i].eid % size].eid + size;
    }
    printf("The repeating elements are : \n");
    for (int i = 0; i < size; i++) {
        if (transform[i].eid >= size * 2) {
            printf("%d  \n", i );
        }
    }
}

void transformgen(struct Transform transform[]){
    int size = enumwindows();

    for(int i = 0; i != size; i++){

        int distancelist[size];
        transform[i].id = windows[i].id;
        for(int i2 = 0; i2 != size; i2++){

            int distance = sqrt(pow(windows[i].posx - ewindows[i2].expectedx, 2) + pow(windows[i].posy - ewindows[i2].expectedy, 2));

            distancelist[i2] = distance;
        }

        int smallest = smallest_element_index(distancelist, size);
        transform[i].distance = distancelist[smallest];
        transform[i].eid = smallest;

    }
}

void transformClean(struct Transform transform[]){
    
}

int findClosest(int x, int y, int id){
    int size = enumwindows();
    struct Transform transform[size * size];
    transformgen(transform);
    printTransform(transform);
    checkDupes(transform, size);
    puts("\n\n\n\n\n");
}