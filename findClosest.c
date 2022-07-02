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
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
// Function to perform Selection Sort
void selectionSort(int arr[], int n)
{   
    int i2 = 0;
    for (int i = 0; i != n; i++) {
        int temp = arr[i];
//        printArray(arr, n);
//        printf("cur: %i | ", arr[i]);
        arr[i] = arr[smallest_element_index(arr, n)];
        arr[smallest_element_index(arr, n)] = temp;
//        printf("new: %i\n", arr[i]);
//        printArray(arr, n);
//        puts("\n");

    }
}

void printTransform(struct Transform transform[], int it){
    int size = enumwindows();
    if(it == -1){
    for(int i = 0; i != size; i++){
                
        printf("\ndistance: %i\neid: %i\nid: %i\nname: %s\n\n", transform[i].distance, transform[i].eid, transform[i].id, getname(transform[i].id));

    }
    }
    else{
        printf("\ndistance: %i\neid: %i\nid: %i\nname: %s\n\n", transform[it].distance, transform[it].eid, transform[it].id, getname(transform[it].id));
    }
}
void transformClean(struct Transform transform[], int size, int i, int j){
    if (transform[i].distance < transform[j].distance){ 
    transform[j].eid++;
    transform[j].distance = transform[i].distancelist[size - 1];
    }
    else{
       transform[i].eid++;
       transform[i].distance = transform[i].distancelist[size - 1]; 
    }

}


void checkDupes(struct Transform transform[], int size){

    for (int i = 0; i < size - 1; i++) {
    for (int j = i + 1; j < size; j++) {
        if (transform[i].eid == transform[j].eid) {
            printf("\ndupe");
            printTransform(transform, i);
            transformClean(transform, size, i, j);
            printf("\ntransform");
            printTransform(transform, i);
            puts("\n\n");
        }
    }
}
}
size_t FindIndex( const int a[], size_t size, int value )
{
    size_t index = 0;

    while ( index < size && a[index] != value ) ++index;

    return ( index == size ? -1 : index );
}
void transformgen(struct Transform transform[]){
    int size = enumwindows();

    for(int i = 0; i != size; i++){

        transform[i].distancelist = (int*)malloc(sizeof(int) * size);
        //printf("size: %i\n", size);
        transform[i].id = windows[i].id;
        for(int i2 = 0; i2 != size; i2++){

            int distance = sqrt(pow(windows[i].screenx - ewindows[i2].expectedx, 2) + pow(windows[i].screeny - ewindows[i2].expectedy, 2));

            transform[i].distancelist[i2] = distance;

        }
        puts("\n");
        //printArray(transform[i].distancelist, size);
        //selectionSort(transform[i].distancelist, size);
        //printArray(transform[i].distancelist, size);
        int smallest = smallest_element_index(transform[i].distancelist, size);
        transform[i].distance = transform[i].distancelist[smallest];
        transform[i].eid = smallest;
        //printf("x: %i, y: %i, ex: %i, ey: %i, dist: %i, name: %s\n", windows[i].screenx, windows[i].screeny, ewindows[smallest].expectedx, ewindows[smallest].expectedy, transform[i].distancelist[smallest], windows[i].name);

    }
}


int genClosest(){
    int size = enumwindows();
    struct Transform transform[size * size];
    transformgen(transform);
    checkDupes(transform, size);

    for(int i = 0; i != size; i++){
        printTransform(transform, i);
        windows[i].screenx = ewindows[transform[i].eid].expectedx;
        windows[i].screeny = ewindows[transform[i].eid].expectedy;
        windows[i].posx = ewindows[transform[i].eid].expectedsizex;
        windows[i].posy = ewindows[transform[i].eid].expectedsizey;
        printf("\nx: %i, y: %i\n",windows[i].screenx, windows[i].screeny);
    }
    puts("\n\n\n\n\n");

}