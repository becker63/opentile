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
        printArray(arr, n);
        printf("cur: %i | ", arr[i]);
        arr[i] = arr[smallest_element_index(arr, n)];
        arr[smallest_element_index(arr, n)] = temp;
        printf("new: %i\n", arr[i]);
        printArray(arr, n);
        puts("\n");

    }
}

int main(){
    int arr[] = { 0, 23, 14, 12, 9 };
    int n = sizeof(arr) / sizeof(arr[0]);
    selectionSort(arr, n);
}