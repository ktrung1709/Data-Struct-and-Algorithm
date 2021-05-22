#include <stdio.h>

typedef struct Address
{
    char name[30];
    char phone[15];
    char email[30];
}Address;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(Address list[], int n, int i){
    int largest = i;
    int l = 2*i+1;
    int r = 2*i+2;
    //if leftchild is greater than parent
    if(l<n && list[l].name[0]>list[largest].name[0])
        largest = l;
    //if rightchild is greater than parent
    if(r<n && list[r].name[0]>list[largest].name[0])
        largest = r;

    if(largest != i){
        swap(&list[i], &list[largest]);
        heapify(list, n, largest);
    }
}

void heapsort(Address list[], int n){
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(list, n, i); //creates a max heap
    for (int i = n -1; i>= 0; i--){
        swap(&list[0], &list[i]); //swaps first and last node
        heapify(list, i, 0); //creates max heap on reduced array
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
    heapsort(list, n);
    print_result(list, n);
    store (list, n);
    return 0;
}
