#include <stdio.h>

typedef struct Address
{
    char name[30];
    char phone[15];
    char email[30];
}Address;

void selection_sort(Address list[], int n){
    int i, j, min;
    Address tmp;
    for (i= 0; i< n-1; i++){
        min = i;
        for (j = i+1; j <=n-1 ; j++)
            if ( list[j].name[0] < list[min].name[0])
                min = j;
        tmp = list[i];
        list[i]= list[min];
        list[min] = tmp;
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
    selection_sort(list, n);
    print_result(list, n);
    store (list, n);
    return 0;
}
