#include <stdio.h>

typedef struct Address
{
    char name[30];
    char phone[15];
    char email[30];
}Address;

void swap(Address *a, Address *b){
    Address temp = *a;
    *a = *b;
    *b = temp;
}

int partition(Address list[], int left, int right){
    char pivot = list[right].name[0];
    int i = left - 1;
    for (int j = left; j < right; j++)
        if (list[j].name[0] < pivot){
            i++;
            swap(&list[i], &list[j]);
        }
    swap(&list[i+1], &list[right]);
    return i+1;
}

void quicksort(Address list[], int left, int right){
    if (left>=right)
        return;

    int p = partition(list, left, right);
    quicksort(list, left, p-1);
    quicksort(list, p+1, right);
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
    quicksort(list, 0, n-1);
    print_result(list, n);
    store (list, n);
    return 0;
}
