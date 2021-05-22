#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random(int arr[], int n){
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        arr[i] = rand();
}

void copy_arr(int a[], int b[], int n){
    for (int i = 0; i<n;i++)
        a[i] = b[i];
}

void insertion_sort(int arr[], int n){
    int i, j;
    int next;
    for (i=1; i < n; i++){
        next = arr[i];
        for (j=i-1;j>=0 && next< arr[j];j--)
            arr[j+1] = arr[j];
        arr[j+1] = next;
    }
}

double selection_sort(int arr[], int n){
    int i, j, min;
    int tmp;
    for (i= 0; i< n-1; i++){
        min = i;
        for (j = i+1; j <=n-1 ; j++)
            if ( arr[j] < arr[min])
                min = j;
        tmp = arr[i];
        arr[i]= arr[min];
        arr[min] = tmp;
    }
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i){
    int largest = i;
    int l = 2*i+1;
    int r = 2*i+2;
    //if leftchild is greater than parent
    if(l<n && arr[l]>arr[largest])
        largest = l;
    //if rightchild is greater than parent
    if(r<n && arr[r]>arr[largest])
        largest = r;

    if(largest != i){
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapsort(int arr[], int n){
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i); //creates a max heap
    for (int i = n -1; i>= 0; i--){
        swap(&arr[0], &arr[i]); //swaps first and last node
        heapify(arr, i, 0); //creates max heap on reduced array
    }
}

int partition(int list[], int left, int right){
    int pivot = list[right];
    int i = left - 1;
    for (int j = left; j < right; j++)
        if (list[j] < pivot){
            i++;
            swap(&list[i], &list[j]);
        }
    swap(&list[i+1], &list[right]);
    return i+1;
}

void quicksort(int list[], int left, int right){
    if (left>=right)
        return;

    int p = partition(list, left, right);
    quicksort(list, left, p-1);
    quicksort(list, p+1, right);
}

void merge(int arr[], int left, int mid, int right) { 
    int i, j, k; 
    int n1 = mid -left + 1; 
    int n2 =  right - mid; 
/* create temporary subarrays and copy data to them*/
    int Left_Arr[n1], Right_Arr[n2]; 
    for (i= 0; i< n1; i++) 
        Left_Arr[i] = arr[left + i]; 
    for (j = 0; j < n2; j++) 
        Right_Arr[j] = arr[mid + 1+ j]; 
/* Merge data from temporary sub array into original array arr[left..right]*/
    i= 0; 
    j = 0; 
    k = left; 
    while (i< n1 && j < n2) { 
        if (Left_Arr[i] <= Right_Arr[j]) { 
            arr[k] = Left_Arr[i]; i++; } 
        else{ 
            arr[k] = Right_Arr[j]; 
            j++; 
        } 
        k++; 
    } 
/* Copy the remaining member of Left_Arr[], if there are any */
    while (i< n1) { 
        arr[k] = Left_Arr[i]; 
        i++; 
        k++; 
    } 
/* Copy the remaining member of Right_Arr[], if there are any */
    while (j < n2) { 
        arr[k] = Right_Arr[j]; 
        j++; 
        k++; 
    } 
}

void mergeSort(int arr[], int left, int right) { 
    if (left < right) {
        int mid = left + (right -left)/2; 
        mergeSort(arr, left, mid); 
        mergeSort(arr, mid + 1, right); 
        merge(arr, left, mid, right); 
    } 
}

int main(){
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int arr[n], insert[n], select[n], heap[n], quick[n], merge[n];
    printf("\n");
    random(arr, n);
    clock_t start, end;
    double cpu_time_used;

    copy_arr(insert, arr, n);
    start = clock();
    insertion_sort(insert, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("The running time when using insertion sort is %lf s\n", cpu_time_used);

    copy_arr(select, arr, n);
    start = clock();
    selection_sort(select, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("The running time when using selection sort is %lf s\n", cpu_time_used);

    copy_arr(heap, arr, n);
    start = clock();
    heapsort(heap, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("The running time when using heap sort is %lf s\n", cpu_time_used);

    copy_arr(quick, arr, n);
    start = clock();
    quicksort(quick, 0, n-1);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("The running time when using quick sort is %lf s\n", cpu_time_used);
    
    copy_arr(merge, arr, n);
    start = clock();
    mergeSort(merge, 0, n-1);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("The running time when using merge sort is %lf s\n", cpu_time_used);
    return 0;
}
