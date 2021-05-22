#include <stdio.h>

typedef struct Address
{
    char name[30];
    char phone[15];
    char email[30];
}Address;

void merge(Address arr[], int left, int mid, int right) { 
    int i, j, k; 
    int n1 = mid -left + 1; 
    int n2 =  right - mid; 
/* create temporary subarrays and copy data to them*/
    Address Left_Arr[n1], Right_Arr[n2]; 
    for (i= 0; i< n1; i++) 
        Left_Arr[i] = arr[left + i]; 
    for (j = 0; j < n2; j++) 
        Right_Arr[j] = arr[mid + 1+ j]; 
/* Merge data from temporary sub array into original array arr[left..right]*/
    i= 0; 
    j = 0; 
    k = left; 
    while (i< n1 && j < n2) { 
        if (Left_Arr[i].name[0] <= Right_Arr[j].name[0]) { 
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

void mergeSort(Address arr[], int left, int right) { 
    if (left < right) {
        int mid = left + (right -left)/2; 
        mergeSort(arr, left, mid); 
        mergeSort(arr, mid + 1, right); 
        merge(arr, left, mid, right); 
    } 
}

int count(){
    int n;
    FILE *f = fopen("AddressBook.txt","r");
    fscanf(f, "%d", &n);
    fclose(f);
    return n;
}

void load(Address list[], int count){
    int n;
    FILE *f = fopen("AddressBook.txt","r");
    fscanf(f, "%d", &n);
    for (int i = 0; i < count; i++){
        fscanf(f, "%s", list[i].name);
        fscanf(f, "%s", list[i].phone);
        fscanf(f, "%s", list[i].email);
    }
    fclose(f);
}

void print_result(Address list[], int count){
    for (int i = 0; i < count; i++)
    {
        printf("%s ", list[i].name);
        printf("%s ", list[i].phone);
        printf("%s ", list[i].email);
        printf("\n");
    }

}

void store(Address list[], int count){
    FILE *f = fopen("AddressBook.txt","w");
    fprintf(f, "%d\n", count);
    for (int i = 0; i < count; i++)
    {
        fprintf(f, "%s ", list[i].name);
        fprintf(f, "%s ", list[i].phone);
        fprintf(f, "%s ", list[i].email);
        fprintf(f, "\n");
    }
    fclose(f);
}

int main(){
    int n = count();
    Address list[100];
    load (list, n);
    mergeSort(list, 0, n-1);
    print_result(list, n);
    store (list, n);
    return 0;
}
